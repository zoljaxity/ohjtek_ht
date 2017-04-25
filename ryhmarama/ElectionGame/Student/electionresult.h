#ifndef ELECTIONRESULT_H
#define ELECTIONRESULT_H

#include "location.h"
#include "player.h"
#include "game.h"
#include "locationdata.h"

using std::shared_ptr;
using Interface::Game;

class ElectionResult
{
public:
    ElectionResult() = default;
    void calculateWinner(shared_ptr<Game> *game);
    QVector<Options::electionResultRow> getStatRows() const;
    bool isTie() const;
    QString getWinner() const;
    unsigned getTopElectionWinAmount() const;

private:
    shared_ptr<Game> game_;
    QVector<Options::electionResultRow> statRows_;
    bool isTie_;
    QString electionWinner_;
    unsigned topElectionWinAmount_;
};

#endif // ELECTIONRESULT_H
