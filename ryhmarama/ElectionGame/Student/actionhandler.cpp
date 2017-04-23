#include "actionhandler.h"
#include "player.h"
#include "locationdata.h"
#include "agent.h"
#include "cardinterface.h"
#include "deckinterface.h"
#include "random.h"
#include "influence.h"
#include <QDebug>

using Interface::Influence;

ActionHandler::ActionHandler() {}

void ActionHandler::setUI(MainWindow *ui) {
    ui_ = ui;
}

void ActionHandler::say() {

}

void ActionHandler::gameSetup() {

    // create a game object
    game_ = make_shared<Game>();
    playerSetup();
    initializeLocations();
    createCards();
    ui_->refreshCards( game_->currentPlayer()->cards());
    game_->setActive(true);
}

void ActionHandler::createCards() {
    enum cardType { action, influence };
    unsigned locationCount = locations_.length();

    // Ten cards per location
    for (int i = 0; i < locationCount * 10; i++) {

        shared_ptr<Location> location = locations_.at(i / 10);
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
        players_.at(i)->addCard(
            make_shared<Agent>()
        );
    }
}

void ActionHandler::initializeLocations() {
    foreach(Options::locationDataUnit locationInfo, Options::locations) {
        shared_ptr<Location> location = make_shared<Location>(1, locationInfo.name);
        location->initialize();
        game_->addLocation(location);
        locations_.push_back(location);
    }
}

// set up players
void ActionHandler::playerSetup() {
    players_.push_back(game_->addPlayer("Player 1"));
    players_.push_back(game_->addPlayer("Player 2"));
}
