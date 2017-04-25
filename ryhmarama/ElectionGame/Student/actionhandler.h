#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QVector>
#include "game.h"
#include "location.h"
#include "player.h"
#include "agent.h"
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
    bool canSendAgentToLocation();
    bool canAgentInLocationAct();
    void sendAgent();
    void changeCurrentLocation(QString locationName);
    void doRelations();
    void doCollect();
    void doNegotiate();
    void doWithdraw();

private:

    void playerSetup();
    void initializeLocations();
    void createCards();
    void refreshUI();

    shared_ptr<Game> game_;
    MainWindow *ui_;
    QVector<shared_ptr<Location>> locationList_;
    QVector<shared_ptr<Agent>> agentList_;
    QVector<shared_ptr<Player>> players_;
    std::map<QString, shared_ptr<Location>> locations_;
    std::map<QString, shared_ptr<Agent>> agents_;
    shared_ptr<Location> currentLocation_;

    // Usage: playerAgentLocations_[locationName][playerName] returns agent pointer
    std::map<QString, std::map<QString, shared_ptr<Agent>>> playerAgentLocations_;

    // Usage: playerAgentLocations_[locationName][playerName] returns relations multiplier
    std::map<QString, std::map<QString, float>> locationPlayerRelationsMultiplier_;
};

#endif // ACTIONHANDLER_H
