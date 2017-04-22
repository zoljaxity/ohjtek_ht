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

    // The game canvas resolution
    const int canvasColumnCount = 200;
    const int canvasRownCount = 200;

    // List of locations' names and their buttons'
    // locations on the game canvas
    const QVector<locationDataUnit> locations = {
        locationDataUnit("Blacksmiths' Guild", 20,  50),
        locationDataUnit("Sewers' Guild",      60,  25),
        locationDataUnit("Traders' Guild",     60,  80),
        locationDataUnit("Baker's Guild",      150, 70),
        locationDataUnit("Shoemaker's Guild",  150, 120),
        locationDataUnit("Rangers' Guild",     120, 160),
        locationDataUnit("Swordsmen's Guild",  20,  120),
        locationDataUnit("Riders' Guild",      110,  20),
        locationDataUnit("Priests' Guild",     40,  160)
    };
}

#endif // LOCATIONDATA_H
