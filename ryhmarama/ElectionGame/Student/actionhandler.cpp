#include "actionhandler.h"
#include "player.h"
#include "locationdata.h"
#include "agent.h"
#include "cardinterface.h"
#include "deckinterface.h"
#include "random.h"
#include "influence.h"
#include "agentfactory.h"
#include "electionresult.h"
#include <QDebug>

using Interface::Influence;
using Interface::AgentFactory;

ActionHandler::ActionHandler() {
    maxRounds_ = Options::playerCount * Options::gameRounds;
    currentRound_ = 1;
}

void ActionHandler::setUI(MainWindow *ui) {
    ui_ = ui;
}

void ActionHandler::gameSetup() {

    // create a game object
    game_ = make_shared<Game>();
    playerSetup();
    initializeLocations();
    createCards();

    refreshUI();

    game_->setActive(true);
}

void ActionHandler::endTurn() {
    game_->nextPlayer();
    currentRound_++;

    // Run out of turns, game over
    if (currentRound_ > maxRounds_) {
        ElectionResult *result = new ElectionResult();
        result->calculateWinner(&game_);
        ui_->endGame(result);
        return;
    }

    // New turn - agents can do stuff
    for(auto const &agent : agents_) {
        shared_ptr<Interface::Player> cardOwner = agent.second->owner().lock();
        if (cardOwner == game_->currentPlayer()) {
            agent.second->setCanAct(true);
        }
    }

    refreshUI();
}

bool ActionHandler::canSendAgentToLocation() {
    shared_ptr<Player> player = game_->currentPlayer();
    if (currentLocation_->canSendAgent(player)) {
        foreach (shared_ptr<CardInterface> card, player->cards()) {
            if (card->typeName() == Options::agentTypeName) {
                return true;
            }
        }
    }
    return false;
}

bool ActionHandler::canAgentInLocationAct()
{
    shared_ptr<Player> player = game_->currentPlayer();
    std::shared_ptr<Agent> agent = playerAgentLocations_[currentLocation_->name()][player->name()];
    if (agent) {
        return agent->canAct();
    }
    return false;
}

void ActionHandler::sendAgent()
{
    shared_ptr<Player> player = game_->currentPlayer();
    foreach (shared_ptr<CardInterface> card, player->cards()) {
        if (card->typeName() == Options::agentTypeName) {
            std::shared_ptr<Agent> agent = agents_[card->name()];
            if (agent) {
                currentLocation_->sendAgent(agent);
                currentAgent_ = agent;
                player->playCard(agent);
                playerAgentLocations_[currentLocation_->name()][player->name()] = agent;

                refreshUI();
                return;
            }
        }
    }
}

void ActionHandler::changeCurrentLocation(QString locationName)
{
    currentLocation_ = locations_[locationName];
    QString playerName = game_->currentPlayer()->name();
    currentAgent_ = playerAgentLocations_[locationName][playerName];
}

void ActionHandler::doRelations()
{
    shared_ptr<Player> player = game_->currentPlayer();

    if (currentAgent_) {
        locationPlayerRelationsMultiplier_[currentLocation_->name()][player->name()] += 0.4;
        currentAgent_->setCanAct(false);
    }
    refreshUI();
}

void ActionHandler::doCollect()
{
    if (currentAgent_ && currentLocation_->deck()->canDraw()) {
        std::shared_ptr<CardInterface> card = currentLocation_->deck()->draw();
        game_->currentPlayer()->addCard(card);
        currentAgent_->setCanAct(false);
        refreshUI();
    }
}

void ActionHandler::doNegotiate()
{
    if (currentAgent_) {
        shared_ptr<Player> player = game_->currentPlayer();
        float multiplier = locationPlayerRelationsMultiplier_
                [currentLocation_->name()][player->name()];
        unsigned short newInfluence = currentLocation_->influence(player) + multiplier;
        currentLocation_->setInfluence(player, newInfluence);
        currentAgent_->setCanAct(false);
        refreshUI();
    }
}

void ActionHandler::doWithdraw()
{
    if (currentAgent_) {
        shared_ptr<Player> player = game_->currentPlayer();
        player->addCard(currentAgent_);
        currentLocation_->removeAgent(currentAgent_);
        auto agentIterator = playerAgentLocations_[currentLocation_->name()].find(player->name());
        playerAgentLocations_[currentLocation_->name()].erase(agentIterator);
        currentAgent_->setCanAct(false);
        refreshUI();
    }
}

std::map<QString, bool> ActionHandler::getAvailableActions()
{
    bool canSendAgent = canSendAgentToLocation();
    bool agentCanAct = canAgentInLocationAct();
    bool canDrawCards = currentLocation_->deck()->canDraw();
    return {
        {"setAgent",  canSendAgent},
        {"relations", agentCanAct},
        {"collect",   agentCanAct && canDrawCards},
        {"negotiate", agentCanAct},
        {"withdraw",  agentCanAct}
    };
}

void ActionHandler::createCards() {
    enum cardType { action, influence };
    unsigned locationCount = locationList_.length();

    // Initial agents to the hand cards - one per player
    for (int i = 0; i < players_.length(); i++) {
        shared_ptr<Agent> agent = AgentFactory::AGENTFACTORY.createAgent();
        agents_[agent->name()] = agent;
        players_.at(i)->addCard(agent);
    }

    // Ten cards per location
    for (unsigned i = 0; i < locationCount; i++) {

        shared_ptr<Location> location = locationList_.at(i);
        for (unsigned a = 0; a < 10; a++) {
            shared_ptr<Interface::CardInterface> card;

            // Shuffle all the cards in the game now so that
            // we can have varying amounts of agents/influence cards
            // in each deck
            if (Interface::Random::RANDOM.uint(1) == 0) {
                shared_ptr<Agent> agent = AgentFactory::AGENTFACTORY.createAgent();
                card = agent;
                agents_[agent->name()] = agent;
            } else {
                card = make_shared<Influence>("Influence", location, 1);
            }
            location->deck()->addCard(card);
        }
        location->deck()->shuffle();
    }
}

void ActionHandler::refreshUI()
{
    ui_->setPlayerView(
        game_->currentPlayer(),
        locationList_,
        locationPlayerRelationsMultiplier_,
        game_->players()
    );
}

void ActionHandler::initializeLocations() {
    foreach(Options::locationDataUnit locationInfo, Options::locations) {
        shared_ptr<Location> location = make_shared<Location>(1, locationInfo.name);
        location->initialize();
        game_->addLocation(location);
        locations_[locationInfo.name] = location;
        locationList_.push_back(location);

        foreach (shared_ptr<Player> player, players_) {
            playerAgentLocations_[locationInfo.name][player->name()] = nullptr;
            locationPlayerRelationsMultiplier_[locationInfo.name][player->name()] = 1;
        }
    }
}

// set up players
void ActionHandler::playerSetup() {
    for (int i = 0; i < Options::playerCount; i++) {
        players_.push_back(game_->addPlayer("Player " + QString::number(i+1)));
    }
}
