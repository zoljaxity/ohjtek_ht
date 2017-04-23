#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "actionhandler.h"
#include "cardinterface.h"
#include "locationdata.h"
#include "player.h"
#include <QMainWindow>
#include <vector>

using Interface::CardInterface;
using std::shared_ptr;

class ActionHandler;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setActionHandler(ActionHandler *actionHandler);
    void setPlayerView(std::shared_ptr<Interface::Player> player);
    ~MainWindow();

private:
    ActionHandler *actionHandler;

private slots:
    void onLocationClicked(QString locationName);
    void on_endTurnButton_clicked();
    void on_exitGameButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
