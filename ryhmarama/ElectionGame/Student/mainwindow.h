#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "actionhandler.h"
#include "cardinterface.h"
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
    void refreshCards(std::vector<shared_ptr<CardInterface> > cards);
    ~MainWindow();

private:
    ActionHandler *actionHandler;

private slots:
    void onLocationClicked(QString locationName);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
