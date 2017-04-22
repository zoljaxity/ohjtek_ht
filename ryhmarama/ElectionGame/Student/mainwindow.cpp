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
#include "locationdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug("koikkelis");
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
    }
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onLocationClicked(QString))) ;
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug("tuhoutuu");
}

void MainWindow::setActionHandler(ActionHandler *actionHandler) {
    this->actionHandler = actionHandler;
    qDebug("actionhandler set!");
}

void MainWindow::onLocationClicked(QString locationName)
{
    //this->close();
    qDebug() << "painettu kiltaa: " << locationName;
    this->actionHandler->say();
}
