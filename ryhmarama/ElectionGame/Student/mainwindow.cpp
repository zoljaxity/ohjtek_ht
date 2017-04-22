#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include <QSpacerItem>
#include <QSignalMapper>
#include <QDialogButtonBox>

#include "actionhandler.h"
#include "locationdata.h"

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionHandler(ActionHandler *actionHandler) {
    this->actionHandler = actionHandler;
}

void MainWindow::onLocationClicked(QString locationName)
{
    QPushButton *setAgent = new QPushButton("Set agent");
    QPushButton *relations = new QPushButton("Public relations");
    QPushButton *collect = new QPushButton("Collect resources");
    QPushButton *negotiate = new QPushButton("Negotiate");
    QPushButton *withdraw = new QPushButton("Withdraw agent");
    withdraw->setDisabled(true);
    QPushButton *cancel   = new QPushButton("Cancel");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(setAgent, QDialogButtonBox::ActionRole);
    buttonBox->addButton(relations, QDialogButtonBox::ActionRole);
    buttonBox->addButton(collect, QDialogButtonBox::ActionRole);
    buttonBox->addButton(negotiate, QDialogButtonBox::ActionRole);
    buttonBox->addButton(withdraw, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancel, QDialogButtonBox::NoRole);

    buttonBox->setFixedSize(200, 200);
    buttonBox->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );
    buttonBox->setWindowTitle(locationName);
    QIcon icon(":/Resources/areaicon.png");
    buttonBox->setWindowIcon(icon);
    buttonBox->show();

    //this->close();
    //qDebug() << "painettu kiltaa: " << locationName;
    //this->actionHandler->say();
}
