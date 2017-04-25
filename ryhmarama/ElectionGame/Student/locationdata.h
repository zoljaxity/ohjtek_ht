#ifndef LOCATIONDATA_H
#define LOCATIONDATA_H

#include <QString>
#include <QVector>

namespace Options {

    // Struct to store location's name and coordinates on the canvas
    struct locationDataUnit {
        QString name;
        int buttonRow;
        int buttonCol;

        locationDataUnit(
            QString name,
            int buttonRow,
            int buttonCol
        ):name(name),
          buttonRow(buttonRow),
          buttonCol(buttonCol) {}
    };

    struct influenceStats {
        unsigned short influencePoints;
        unsigned short influenceCards;
        unsigned short influenceTotal;
    };

    struct electionResultRow {
        QString locationName;
        std::map<QString, influenceStats> stats;
        QString electionWinner;
    };

    // The game canvas resolution
    const int canvasColumnCount = 200;
    const int canvasRownCount = 200;

    const int playerCount = 2;
    const int gameRounds = 10;
    const QString agentTypeName = "Agent";
    const QVector<QString> agentButtons = {
        "setAgent", "relations", "collect", "negotiate", "withdraw"
    };
    const QVector<QString> agentActionButtons = {
        "relations", "collect", "negotiate", "withdraw"
    };
    const std::map<QString, QString> buttonLabels = {
        {"setAgent",  "Set agent"},
        {"relations", "Public relations"},
        {"collect",   "Collect resources"},
        {"negotiate", "Negotiate"},
        {"withdraw",  "Withdraw agent"}
    };

    // List of locations' names and their buttons'
    // locations on the game canvas
    const QVector<locationDataUnit> locations = {
        locationDataUnit("Blacksmiths' Guild", 20,  50),
        locationDataUnit("Sewers' Guild",      55,  18),
        locationDataUnit("Traders' Guild",     62,  82),
        locationDataUnit("Baker's Guild",      150, 70),
        locationDataUnit("Shoemaker's Guild",  150, 120),
        locationDataUnit("Rangers' Guild",     120, 160),
        locationDataUnit("Swordsmen's Guild",  20,  120),
        locationDataUnit("Riders' Guild",      110,  20),
        locationDataUnit("Priests' Guild",     40,  160)
    };
}

#endif // LOCATIONDATA_H
