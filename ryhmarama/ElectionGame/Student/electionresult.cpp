#include "electionresult.h"
#include <QDebug>
#include "location.h"
#include "player.h"
#include "cardinterface.h"

using Interface::Player;
using Interface::Location;
using Interface::CardInterface;

void ElectionResult::calculateWinner(shared_ptr<Interface::Game> *game)
{
    isTie_ = true;
    std::map<QString, unsigned> electionWins;
    electionWinner_ = "";
    topElectionWinAmount_ = 0;

    std::map<QString, std::map<QString, unsigned>> influenceCards;
    foreach (shared_ptr<Player> player, (*game)->players()) {
        electionWins[player->name()] = 0;

        // Initialize influence card amount to zero
        foreach (std::shared_ptr<Location> location, (*game)->locations()) {
            influenceCards[location->name()][player->name()] = 0;
        }

        // Then count them
        foreach (shared_ptr<CardInterface> card, player->cards()) {
            if (card->typeName() == "Influence") {
                influenceCards[card->location().lock()->name()][player->name()]++;
            }
        }
    }

    foreach (std::shared_ptr<Location> location, (*game)->locations()) {
        qDebug() << location->name();
        shared_ptr<Player> winner;
        unsigned short winningPoints = 0;
        Options::electionResultRow resultRow;
        resultRow.locationName = location->name();
        foreach (shared_ptr<Player> player, (*game)->players()) {
            unsigned short influence = location->influence(player);
            unsigned short influenceCardAmount = influenceCards[location->name()][player->name()];
            unsigned short influenceTotal = influence * influenceCardAmount;
            Options::influenceStats stats;
            stats.influencePoints = influence;
            stats.influenceCards = influenceCardAmount;
            stats.influenceTotal = influence * influenceCardAmount;
            resultRow.stats[player->name()] = stats;
            if (influenceTotal > winningPoints) {
                winner = player;
                winningPoints = influenceTotal;
            } else if (influenceTotal == winningPoints) {
                winner = nullptr;
            }
        }
        if (winner) {
            resultRow.electionWinner = winner->name();
            electionWins[winner->name()]++;
            if (electionWins[winner->name()] > topElectionWinAmount_) {
                topElectionWinAmount_ = electionWins[winner->name()];
                electionWinner_ = winner->name();
                isTie_ = false;
            } else if (electionWins[winner->name()] == topElectionWinAmount_) {
                electionWinner_ = "";
                isTie_ = true;
            }
        }
        statRows_.push_back(resultRow);
    }

}

QVector<Options::electionResultRow> ElectionResult::getStatRows() const
{
    return statRows_;
}

bool ElectionResult::isTie() const
{
    return isTie_;
}

QString ElectionResult::getWinner() const
{
    return electionWinner_;
}

unsigned ElectionResult::getTopElectionWinAmount() const
{
    return topElectionWinAmount_;
}
