#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialogButtonBox>
#include <QMainWindow>
#include <vector>
#include <QSignalMapper>
#include <QLabel>

#include "actionhandler.h"
#include "cardinterface.h"
#include "locationdata.h"
#include "location.h"
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
    void setPlayerView(
        std::shared_ptr<Interface::Player> player,
        QVector<shared_ptr<Interface::Location>> locationList,
        std::map<QString, std::map<QString, float>> locationPlayerRelationsMultiplier,
        std::vector<std::shared_ptr<Interface::Player>> players
    );
    ~MainWindow();

private:
    void initializeActionDialog();
    void refreshButtonOptions();
    ActionHandler *actionHandler_;
    QDialogButtonBox *buttonBox_;
    QSignalMapper* actionSignalMapper_;
    std::map<QString, QPushButton*> dialogButtons_;
    std::map<QString, QLabel*> locationInfluenceLabels_;
    QString currentLocation_;

    // Usage: locationPlayerStats[locationName][playerName] returns stats label
    std::map<QString, std::map<QString, QLabel*>> locationPlayerStats_;

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
