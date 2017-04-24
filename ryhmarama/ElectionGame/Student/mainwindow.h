#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialogButtonBox>
#include <QMainWindow>
#include <vector>
#include <QSignalMapper>

#include "actionhandler.h"
#include "cardinterface.h"
#include "locationdata.h"
#include "player.h"

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
    void initializeActionDialog();
    void disableActionDialogButtons();
    void enableActionButtons();
    ActionHandler *actionHandler_;
    QDialogButtonBox *buttonBox_;
    QSignalMapper* actionSignalMapper_;
    std::map<QString, QPushButton*> dialogButtons_;
    QString currentLocation_;

private slots:
    void onLocationClicked(QString locationName);
    void onCommitAction(QString action);
    void closeDialog();
    void on_endTurnButton_clicked();
    void on_exitGameButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
