#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QVector>
#include "game.h"
#include "location.h"
#include "player.h"
#include "mainwindow.h"

using Interface::Location;
using Interface::Player;
using Interface::Game;
using std::make_shared;
using std::shared_ptr;

class MainWindow;

class ActionHandler
{
public:
    ActionHandler();
    void setUI(MainWindow *ui);
    void gameSetup();

    // Called from UI:
    void endTurn();
    void canSendAgentToLocation(QString locationName);

private:

    void playerSetup();
    void initializeLocations();
    void createCards();

    shared_ptr<Game> game_;
    MainWindow *ui_;
    QVector<shared_ptr<Location>> locationList_;
    std::map<QString, shared_ptr<Location>> locations_;
    QVector<shared_ptr<Player>> players_;
};

#endif // ACTIONHANDLER_H
