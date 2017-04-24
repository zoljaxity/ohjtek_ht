#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QIcon>
#include <QLabel>
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
            QLabel *test = new QLabel("20 / 150 / yes");
            test->setAlignment(Qt::AlignCenter);
            test->setStyleSheet("QLabel { font-size: 10px; font-weight: bold; background-color: rgba(0,0,0,0.7); border-radius: 5px; color: " + playerColour + "; }");
            ui->gridLayout->addWidget(test,location.buttonRow + 11 + 8*i, location.buttonCol, 7, 30);

            QLabel *playerName = new QLabel("Player " + QString::number(i));
            playerName->setStyleSheet("QLabel { font-size: 15px; font-weight: bold; background-color: rgba(0,0,0,0.0); border-radius: 5px; color: " + playerColour + "; }");
            ui->gridLayout->addWidget(playerName, 11 + 8*i, 2, 7, 70);
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
    // Create action dialog buttons
    dialogButtons_["setAgent"]  = new QPushButton("Set agent");
    dialogButtons_["relations"] = new QPushButton("Public relations");
    dialogButtons_["collect"]   = new QPushButton("Collect resources");
    dialogButtons_["negotiate"] = new QPushButton("Negotiate");
    dialogButtons_["withdraw"]  = new QPushButton("Withdraw agent");
    dialogButtons_["cancel"]    = new QPushButton("Cancel");

    // Create signal mapper & map values to buttons
    actionSignalMapper_ = new QSignalMapper(this);
    actionSignalMapper_->setMapping(dialogButtons_["setAgent"],  "setAgent");
    actionSignalMapper_->setMapping(dialogButtons_["relations"], "relations");
    actionSignalMapper_->setMapping(dialogButtons_["collect"],   "collect");
    actionSignalMapper_->setMapping(dialogButtons_["negotiate"], "negotiate");
    actionSignalMapper_->setMapping(dialogButtons_["withdraw"],  "withdraw");

    // Connect buttons to signal mapper
    connect(dialogButtons_["setAgent"],  SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    connect(dialogButtons_["relations"], SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    connect(dialogButtons_["collect"],   SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    connect(dialogButtons_["negotiate"], SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    connect(dialogButtons_["withdraw"],  SIGNAL(clicked()), actionSignalMapper_, SLOT(map()));
    connect(dialogButtons_["cancel"],    SIGNAL(clicked()), this,                SLOT(closeDialog()));

    // Connect signal mapper to function
    connect(actionSignalMapper_, SIGNAL(mapped(QString)), this, SLOT(onCommitAction(QString)));

    // Create dialog box, add buttons to it, some settings
    buttonBox_ = new QDialogButtonBox(Qt::Vertical);
    buttonBox_->addButton(dialogButtons_["setAgent"],  QDialogButtonBox::ActionRole);
    buttonBox_->addButton(dialogButtons_["relations"], QDialogButtonBox::ActionRole);
    buttonBox_->addButton(dialogButtons_["collect"],   QDialogButtonBox::ActionRole);
    buttonBox_->addButton(dialogButtons_["negotiate"], QDialogButtonBox::ActionRole);
    buttonBox_->addButton(dialogButtons_["withdraw"],  QDialogButtonBox::ActionRole);
    buttonBox_->addButton(dialogButtons_["cancel"],    QDialogButtonBox::NoRole);
    buttonBox_->setWindowIcon(QIcon(":/Resources/areaicon.png"));
    buttonBox_->setFixedSize(200, 200);
    buttonBox_->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );
}

void MainWindow::setActionHandler(ActionHandler *actionHandler)
{
    actionHandler_ = actionHandler;
}

void MainWindow::setPlayerView(std::shared_ptr<Interface::Player> player) {
    int agentAmount = 0;
    foreach (shared_ptr<CardInterface> card, player->cards()) {
        if (card->typeName() == Options::agentTypeName) {
            agentAmount++;
        }
    }
    ui->agentsAmount->setText("Agents: " + QString::number(agentAmount));
    ui->currentPlayerLabel->setText("Vuorossa: " + player->name());
}

void MainWindow::onLocationClicked(QString locationName)
{
    currentLocation_ = locationName;
    if (actionHandler_->canSendAgentToLocation(locationName)) {
        dialogButtons_["setAgent"]->setDisabled(false);
        dialogButtons_["relations"]->setDisabled(true);
        dialogButtons_["collect"]->setDisabled(true);
        dialogButtons_["negotiate"]->setDisabled(true);
        dialogButtons_["withdraw"]->setDisabled(true);
    } else {
        dialogButtons_["setAgent"]->setDisabled(true);
    }
    buttonBox_->setWindowTitle(locationName);
    buttonBox_->show();
}

void MainWindow::onCommitAction(QString action)
{
    qDebug() << "suoritetaan toiminto" << action << "kohteessa" << currentLocation_;
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
