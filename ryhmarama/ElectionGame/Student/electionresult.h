#ifndef ELECTIONRESULT_H
#define ELECTIONRESULT_H

#include "location.h"
#include "player.h"
#include "game.h"
#include "locationdata.h"

/**
* @file
* @brief Määrittelee pelin loppumisen yhteydessä pisteiden laskua kuvaavan luokan
*/

using std::shared_ptr;
using Interface::Game;

/**
 * @brief ElectionResult on luokka, joka laskee pelin pisteet ja voittajan
 *
 * Pelin päätyttyä voi laskea pelaajien pisteet kutsumalla tämän luokan instanssia.
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
class ElectionResult
{
public:

    /**
     * @brief ElectionResult rakentaja
     */
    ElectionResult() = default;

    /**
     * @brief calculateWinner laskee pelin lopputuloksen
     * @pre Peli on päättynyt, mutta pisteet laskematta
     * @param *game osoitin peliobjektiin
     * @post Pelin pelaajien pisteet on laskettu
     */
    void calculateWinner(shared_ptr<Game> *game);

    /**
     * @brief getStatRows antaa pelaajien pisteet helposti käsiteltävässä rivimuodossa
     * @pre Peli on päättynyt ja pisteet laskettu
     * @post Poikkeustakuu: nothrow
     */
    QVector<Options::electionResultRow> getStatRows() const;
    /**
     * @brief isTie kertoo päättyikö peli tasan
     * @pre Peli on päättynyt ja pisteet laskettu
     * @post Poikkeustakuu: nothrow
     */
    bool isTie() const;
    /**
     * @brief getWinner antaa voittajan nimen
     * @pre Peli on päättynyt ja pisteet laskettu
     * @post Poikkeustakuu: nothrow
     */
    QString getWinner() const;
    /**
     * @brief getTopElectionWinAmount kertoo montako ääntä voittaja sai
     * @pre Peli on päättynyt ja pisteet laskettu
     * @post Poikkeustakuu: nothrow
     */
    unsigned getTopElectionWinAmount() const;

private:
    shared_ptr<Game> game_;
    QVector<Options::electionResultRow> statRows_;
    bool isTie_;
    QString electionWinner_;
    unsigned topElectionWinAmount_;
};

#endif // ELECTIONRESULT_H
