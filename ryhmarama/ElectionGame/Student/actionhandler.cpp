#include "actionhandler.h"
#include "player.h"
#include "location.h"
#include "agent.h"
#include <QDebug>

using Interface::Location;
using Interface::Player;
using Interface::Game;
using std::make_shared;

ActionHandler::ActionHandler() {}

void ActionHandler::setUI(MainWindow *ui) {
    ui_ = ui;
}

void ActionHandler::setGameEngine(shared_ptr<Game> *game) {
    game_ = game;
}

void ActionHandler::say() {

    std::shared_ptr<Agent> agent = make_shared<Agent>();
    std::shared_ptr<Player> player = (*game_)->players().at(0);
    std::shared_ptr<Location> location = (*game_)->locations().at(0);

    agent->setOwner(player);
    qDebug() << location->canSendAgent(player) << agent->isCommon();
    location->sendAgent(agent);
    qDebug() << location->canSendAgent(player) << agent->isCommon();
}
