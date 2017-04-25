#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agentinterface.h"
#include <QDir>
#include <QIcon>
#include <QDebug>
#include <QGridLayout>
#include <QSpacerItem>
#include <QSignalMapper>

#include "actionhandler.h"
#include "agent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap villagePixMap(":/Resources/village.jpg");
    QLabel *village = new QLabel();
    village->setPixmap(villagePixMap);
    ui->gridLayout->addWidget(village, 0, 0, 200, 200);

    QSignalMapper* signalMapper = new QSignalMapper(this);
    foreach(Options::locationDataUnit location, Options::locations) {
        QPushButton *button = new QPushButton(location.name);
        ui->gridLayout->addWidget(button, location.buttonRow, location.buttonCol, 10, 30);
        connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(button, location.name);

        for (int i = 0; i < Options::playerCount; i++) {
            QString playerColour;
            switch (i) {
            case 1:
                playerColour = "#99ff33";
                break;
            case 2:
                playerColour = "yellow";
                break;
            case 3:
                playerColour = "cyan";
                break;
            default:
                playerColour = "white";
                break;
            }
            QLabel *stats = new QLabel("0 / 0");
            stats->setAlignment(Qt::AlignCenter);
            stats->setStyleSheet("QLabel { font-size: 10px; font-weight: bold; background-color: rgba(0,0,0,0.7); border-radius: 5px; color: " + playerColour + "; }");
            ui->gridLayout->addWidget(stats,location.buttonRow + 11 + 8*i, location.buttonCol, 7, 30);

            QLabel *playerName = new QLabel("Player " + QString::number(i+1));
            playerName->setStyleSheet("QLabel { font-size: 15px; font-weight: bold; background-color: rgba(0,0,0,0.0); border-radius: 5px; color: " + playerColour + "; }");
            ui->gridLayout->addWidget(playerName, 11 + 8*i, 2, 7, 70);

            // TODO: fix this and get player names from some actual place
            locationPlayerStats_[location.name][playerName->text()] = stats;
        }
    }
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onLocationClicked(QString)));

    QLabel *meanings = new QLabel("Meanings: Influence / multiplier / Has agent");
    meanings->setAlignment(Qt::AlignCenter);
    meanings->setStyleSheet("QLabel { font-size: 10px; font-weight: bold; background-color: rgba(0,0,0,0.7); border-radius: 5px; color: white; }");
    ui->gridLayout->addWidget(meanings, 0, 0, 10, 70);

    // Set location influence card labels
    int locationLabelsSet = 0;
    foreach(Options::locationDataUnit location, Options::locations) {
        QLabel *locationLabel = new QLabel(location.name + ": 0");
        locationInfluenceLabels_[location.name] = locationLabel;
        locationLabel->setStyleSheet("margin-left: 20px;");
        ui->cardGrid->addWidget(
            locationLabel, // Player's influence cards from location
            1 + locationLabelsSet % 3, // Rows of three
            2 + locationLabelsSet / 3  // Columns of three
        );
        ++locationLabelsSet;
    }

    initializeActionDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeActionDialog()
{
    // Create button signal mapper and dialog window
    actionSignalMapper_ = new QSignalMapper(this);
    buttonBox_ = new QDialogButtonBox(Qt::Vertical);

    // Create action buttons, connect them to signal mapper & add buttons to window
    foreach (QString buttonName, Options::agentButtons) {
        dialogButtons_[buttonName] = new QPushButton(Options::buttonLabels.at(buttonName));
        buttonBox_->addButton(dialogButtons_[buttonName], QDialogButtonBox::ActionRole);
        actionSignalMapper_->setMapping(dialogButtons_[buttonName], buttonName);
        connect(dialogButtons_[buttonName], SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    }

    // Connect signal mapper to action handler
    connect(actionSignalMapper_, SIGNAL(mapped(QString)), this, SLOT(onCommitAction(QString)));

    // Create cancel button and connect it to dialog closer
    dialogButtons_["cancel"] = new QPushButton("Cancel");
    connect(dialogButtons_["cancel"], SIGNAL(clicked()), this, SLOT(closeDialog()));
    buttonBox_->addButton(dialogButtons_["cancel"], QDialogButtonBox::NoRole);

    // Dialog window settings
    buttonBox_->setWindowIcon(QIcon(":/Resources/areaicon.png"));
    buttonBox_->setFixedSize(200, 200);
    buttonBox_->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );
}

void MainWindow::refreshButtonOptions()
{
    for(auto const &action : actionHandler_->getAvailableActions()) {
        dialogButtons_[action.first]->setDisabled(!action.second);
    }
}

void MainWindow::setActionHandler(ActionHandler *actionHandler)
{
    actionHandler_ = actionHandler;
}

void MainWindow::setPlayerView(std::shared_ptr<Interface::Player> player,
    QVector<shared_ptr<Interface::Location>> locationList,
    std::map<QString, std::map<QString, float>> locationPlayerRelationsMultiplier,
    std::vector<std::shared_ptr<Interface::Player>> players
)
{

    // Update influence labels

    std::map<QString, unsigned short> locationInfluences;
    foreach (const auto &label, locationInfluenceLabels_) {
        label.second->setText(label.first + ": 0");
        locationInfluences[label.first] = 0;
    }

    // Update agent amount
    int agentAmount = 0;
    foreach (shared_ptr<CardInterface> card, player->cards()) {
        if (card->typeName() == Options::agentTypeName) {
            agentAmount++;
        } else {
            std::shared_ptr<Location> location = card->location().lock();
            if (location) {
                locationInfluences.at(location->name())++;
                locationInfluenceLabels_.at(location->name())->setText(
                    location->name() + ": " + QString::number(locationInfluences[location->name()])
                );
            }
        }
    }
    ui->agentsAmount->setText("Agents: " + QString::number(agentAmount));

    // Update current turn label
    ui->currentPlayerLabel->setText("In turn: " + player->name());

    // Update game canvas player statistics
    foreach (shared_ptr<Location> location, locationList) {
        foreach (const auto &player, players) {
            QLabel* label = this->locationPlayerStats_[location->name()][player->name()];
            float relationsMultiplier =
                locationPlayerRelationsMultiplier[location->name()][player->name()];
            label->setText(
                QString::number(location->influence(player))
                + " / " + QString::number(relationsMultiplier)
            );
        }

        foreach (shared_ptr<Interface::AgentInterface> agent, location->agents()) {
            QLabel* label = this->locationPlayerStats_[location->name()][agent->owner().lock()->name()];
            label->setText(label->text() + " agent");
        }
    }
}


void MainWindow::onLocationClicked(QString locationName)
{
    currentLocation_ = locationName;
    actionHandler_->changeCurrentLocation(currentLocation_);
    refreshButtonOptions();
    buttonBox_->setWindowTitle(locationName);
    buttonBox_->show();
}

void MainWindow::onCommitAction(QString action)
{
    // Would've used action enum here but signal mapper doesn't
    // support custom types - Also switch case doesn't work on strings
    if (action == "setAgent") {
        actionHandler_->sendAgent();
    } else if (action == "relations") {
        actionHandler_->doRelations();
    } else if (action == "collect") {
        actionHandler_->doCollect();
    } else if (action == "negotiate") {
        actionHandler_->doNegotiate();
    } else if (action == "withdraw") {
        //actionHandler_->doWithdraw();
    }
    refreshButtonOptions();
}

void MainWindow::closeDialog() {
    buttonBox_->close();
}

void MainWindow::on_endTurnButton_clicked()
{
    actionHandler_->endTurn();
}

void MainWindow::on_exitGameButton_clicked()
{
    this->close();
}
