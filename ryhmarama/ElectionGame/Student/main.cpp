//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
//                                                                        //
// TIE-02400 Ohjelmoinnin tekniikat, kevät 2017, harjoitustyö             //
// Ryhmärämä - Lauri Solja & Elena Lassila                                //
// Op.nrot: 229739 & 228889                                               //
// lauri.solja@student.tut.fifi                                           //
// elena.lassila@student.tut.fi                                           //
//                                                                        //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
//                                                                        //
//                        ---Valtaistuinpeli---                           //
//                                                                        //
// Peliä pelataan kaupunkia esittävällä laudalla, jonne pelaajat (kaksi   //
// tai useampia) asettavat kortteja ja pelimerkkejään. Laudalla on useita //
// eri alueita (vähintään neljä), esim. kauppiaiden kilta, kaupunginvar-  //
// tiosto jne. Kutakin aluetta edustaa tietty hallintoneuvoston jäsen.    //
// Kullakin alueella on oma pelipaikkansa, joka issältää ainakin seuraa-  //
// vanlaisia kortteja:                                                    //
//      -Vaikutusvaltakortit: Pelin lopussa pelaajien käteensä keräämät   //
//       vaikutusvaltakortit vaikuttavat ratkaisevat äänetyksen lopputu-  //
//       lokseen.                                                         //
//      -Agenttikortit: Agenttikortteja voi pelata pelilaudalla, jossa ne //
//       voivat suorittaa pelaajan tavoitteita edistäviä operaatioita.    //
//                                                                        //
// Pelaaja voi pelata kädessään olevan agenttikortin mille tahansa peli-  //
// laudan alueelle. Tällöin kortti asetetaan laudalle, ja sen päälle ase- //
// tetaan pelaajan pelimerkki osoittamaan kortin omistaja. Alueella oleva //
// agentti voi suorittaa siellä ainakin seuraavia operaatioita:           //
//      -Suhteiden vaaliminen: Pelaaja lisää agentin päälle uusia peli-   //
//       merkkejä ilmaisemaan vahvempia suhteita alueen toimijoihin. Pa-  //
//       remmat suhteet tehostavat muiden operaatioiden suorittamista.    //
//      -Resurssien kerääminen: Pelaaja nostaa alueen pakasta kortteja    //
//       käteensä.                                                        //
//      -Neuvottelut: Pelaaja asettaa uusia pelimerkkejä alueelle kuvas-  //
//      -tamaan kasvanutta vaikutusvaltaansa siihen liittyvään neuvoston  //
//       jäseneen.                                                        //
//      -Vetäytyminen: Pelaaja nostaa agenttikortin takaisin käteensä.    //
//                                                                        //
// Pelin aikana kukin pelaaja voi vuorollaan pelata laudalle kädestään    //
// agentteja ja/tai suorittaa laudalla olevilla agenteillaan operaatioi-  //
// ta. Pelin lopussa tulee äänestys, jossa kunkin neuoston jäsenen ääni   //
// perustuu pelilaudalla heidän alueelleen asetettuihin pelimerkkeihin ja //
// pelaajien kädessä oleviin vaikutusvaltakortteihin. Äänestyksen voit-   //
// tanut pelaaja voittaa pelin.                                           //
//                                                                        //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

#include "deckinterface.h"
#include "game.h"
#include "influence.h"
#include "location.h"
#include "mainwindow.h"
#include "player.h"
#include "locationdata.h"

#include <QApplication>
#include <QDebug>

using Interface::Game;
using Interface::Influence;
using Interface::Location;
using Interface::Player;
using std::make_shared;
using std::shared_ptr;

/*
 * The main program should initialize the game and open the main window, or
 * delegate these tasks elsewhere.
 */
int main(int argc, char* argv[])
{
    QVector<shared_ptr<Location>> locations;

    QApplication a(argc, argv);

    // create a game object
    shared_ptr<Game> game = make_shared<Game>();
    {
        // create and initialize a location, and add it to the game
        foreach(Options::locationDataUnit locationInfo, Options::locations) {
            shared_ptr<Location> location = make_shared<Location>(1, locationInfo.name);
            location->initialize();
            game->addLocation(location);
            locations.push_back(location);
        }

        // set up cards for the location deck
        {
            // create an influence card and add it to location deck
            /*shared_ptr<Influence> influence1 = make_shared<Influence>(location1->name() + " Influence", location1, 1);
            location1->deck()->addCard(influence1);

            // TODO: create more cards

            // shuffle the deck
            location1->deck()->shuffle();*/
        }

        // TODO: create more locations
    }

    // set up players
    game->addPlayer("Player 1");
    game->addPlayer("Player 2");

    ActionHandler *actionHandler;
    MainWindow mainWin;

    // Dependency injections
    mainWin.setActionHandler(actionHandler);
    actionHandler->setUI(&mainWin);
    actionHandler->setGameEngine(&game);

    mainWin.show();
    game->setActive(true);

    a.exec();
    a.quitOnLastWindowClosed();
    return 0;
}
