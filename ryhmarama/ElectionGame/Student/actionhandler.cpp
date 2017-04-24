#include "actionhandler.h"
#include "player.h"
#include "locationdata.h"
#include "agent.h"
#include "cardinterface.h"
#include "deckinterface.h"
#include "random.h"
#include "influence.h"
#include "agentfactory.h"
#include <QDebug>

using Interface::Influence;
using Interface::AgentFactory;

ActionHandler::ActionHandler() {}

void ActionHandler::setUI(MainWindow *ui) {
    ui_ = ui;
}

void ActionHandler::gameSetup() {

    // create a game object
    game_ = make_shared<Game>();
    playerSetup();
    initializeLocations();
    createCards();

    // Refresh UI
    ui_->setPlayerView(game_->currentPlayer());

    game_->setActive(true);
}

void ActionHandler::endTurn() {
    game_->nextPlayer();
    ui_->setPlayerView(game_->currentPlayer());
}

void ActionHandler::canSendAgentToLocation(QString locationName) {
    shared_ptr<Location> location = locations_[locationName];
    shared_ptr<Player> player = game_->currentPlayer();
    std::shared_ptr<Interface::AgentInterface> card_;


    qDebug() << "voi lähettää:" << location->canSendAgent(player);

    foreach(std::shared_ptr<Interface::CardInterface> card, player->cards()) {
        //card_ = dynamic_cast<std::shared_ptr<Interface::AgentInterface>>(card);
        qDebug() << card->typeName();
    }

    location->sendAgent(card_);

    qDebug() << "------";
    foreach(std::shared_ptr<Interface::CardInterface> card, player->cards()) {
        qDebug() << card->typeName();
    }

    qDebug() << "voi lähettää:" << location->canSendAgent(player);
}

void ActionHandler::createCards() {
    enum cardType { action, influence };
    unsigned locationCount = locationList_.length();

    // Ten cards per location
    for (int i = 0; i < locationCount * 10; i++) {

        shared_ptr<Location> location = locationList_.at(i / 10);
        shared_ptr<Interface::CardInterface> card;

        // Shuffle all the cards in the game now so that
        // we can have varying amounts of agents/influence cards
        // in each deck
        if (Interface::Random::RANDOM.uint(1) == 0) {
            card = make_shared<Agent>();
        } else {
            card = make_shared<Influence>("Influence", location, 1);
        }

        location->deck()->addCard(card);
    }

    for (int i = 0; i < players_.length(); i++) {
        players_.at(i)->addCard(AgentFactory::AGENTFACTORY.createAgent());
    }
}

void ActionHandler::initializeLocations() {
    foreach(Options::locationDataUnit locationInfo, Options::locations) {
        shared_ptr<Location> location = make_shared<Location>(1, locationInfo.name);
        location->initialize();
        game_->addLocation(location);
        locations_[locationInfo.name] = location;
    }
}

// set up players
void ActionHandler::playerSetup() {
    players_.push_back(game_->addPlayer("Player 1"));
    players_.push_back(game_->addPlayer("Player 2"));
}
