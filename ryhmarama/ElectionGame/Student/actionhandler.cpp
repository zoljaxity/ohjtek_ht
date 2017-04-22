#include "actionhandler.h"
#include "player.h"
#include <QDebug>

using Interface::Location;
using Interface::Player;
using Interface::Game;

ActionHandler::ActionHandler()
{
    qDebug("testin kestin");
}

void ActionHandler::setUI(MainWindow *ui) {
    ui_ = ui;
}

void ActionHandler::setGameEngine(shared_ptr<Game> *game) {
    game_ = game;
}

void ActionHandler::say() {
    (*game_)->nextPlayer();
    qDebug() << (*game_)->currentPlayer()->name();
}
