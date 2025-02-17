#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller/GUIController.h"
#include "controller/TextController.h"
#include "controller/Controller.h"
#include "gamescene.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

// class GUIController;
// class TextController;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    inline GameScene *getScene() const { return scene; };
    inline QTimer *getTimer() const { return timer; };
    inline GUIController *getGUIController() const { return guiController; }
    inline TextController *getTextController() const { return textController; }
    inline Ui::MainWindow *getUI() const { return ui; }
    void gameStart();


protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
public slots:
    void setView(int view) const;
    void textCommand() const;
    void zoom(QWheelEvent *event);
    void checkVisibleView();
    void showLoadingScreen();
    void startGame();
    void gameEnd(bool win);
    void updateBars();

signals:
    void breakAutoPlay();

private:
    Ui::MainWindow *ui;
    GUIController* guiController;
    TextController* textController;
    QGraphicsView *graphicsView;
    GameScene *scene;
    Controller  *controller;
    QTimer *timer;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
