#include "deckinterface.h"
#include "game.h"
#include "influence.h"
#include "location.h"

#include <QApplication>

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
    QApplication a(argc, argv);

    // create a game object
    shared_ptr<Game> game = make_shared<Game>();

    // set up locations of the board
    {
        // create and initialize a location, and add it to the game
        shared_ptr<Location> location1 = make_shared<Location>(1, "First Location");
        location1->initialize();
        game->addLocation(location1);

        // set up cards for the location deck
        {
            // create an influence card and add it to location deck
            shared_ptr<Influence> influence1 = make_shared<Influence>(location1->name() + " Influence", location1, 1);
            location1->deck()->addCard(influence1);

            // TODO: create more cards

            // shuffle the deck
            location1->deck()->shuffle();
        }

        // TODO: create more locations
    }

    // set up players
    {
        // add a player to the game
        shared_ptr<Player> player1 = game->addPlayer("Player 1");

        // TODO: perform other player setup as necessary

        // TODO: create more players
    }

    // TODO: open the main window

    a.exec();
}
