#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include "game.h"

using std::shared_ptr;
using Interface::Game;

class MainWindow;
#include "mainwindow.h"

class ActionHandler
{
public:
    ActionHandler();

    void setGameEngine(shared_ptr<Game> *game);
    void setUI(MainWindow *ui);
    void say();

private:
    shared_ptr<Game> *game_;
    MainWindow *ui_;
};

#endif // ACTIONHANDLER_H
