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
    void changeCurrentLocation(QString locationName);
    std::map<QString, bool> getAvailableActions();
    void sendAgent();
    void doRelations();
    void doCollect();
    void doNegotiate();
    void doWithdraw();
    void endTurn();

private:

    // Game setup
    void playerSetup();
    void initializeLocations();
    void createCards();

    // UI related
    void refreshUI();
    bool canSendAgentToLocation();
    bool canAgentInLocationAct();

    shared_ptr<Game> game_;
    MainWindow *ui_;
    unsigned short maxRounds_;
    unsigned short currentRound_;
    QVector<shared_ptr<Location>> locationList_;
    QVector<shared_ptr<Agent>> agentList_;
    QVector<shared_ptr<Player>> players_;
    std::map<QString, shared_ptr<Location>> locations_;
    std::map<QString, shared_ptr<Agent>> agents_;
    shared_ptr<Location> currentLocation_;
    shared_ptr<Agent> currentAgent_;

    // Usage: playerAgentLocations_[locationName][playerName] returns agent pointer
    std::map<QString, std::map<QString, shared_ptr<Agent>>> playerAgentLocations_;

    // Usage: playerAgentLocations_[locationName][playerName] returns relations multiplier
    std::map<QString, std::map<QString, float>> locationPlayerRelationsMultiplier_;
};

#endif // ACTIONHANDLER_H
