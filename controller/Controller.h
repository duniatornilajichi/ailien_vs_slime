#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QSharedPointer>
#include "model/gameworld.h"
#include "qmainwindow.h"
#include "model/gameworld.h"
#include "model/direction.h"
#include <QVector>
#include <QFile>
#include <QDir>

class Controller : public QObject
{
    Q_OBJECT
public:
    QMainWindow *mw;
    QVector<QSharedPointer<GameWorld>> worldList;
    int currWorld;
    QList<QString> savedGames;

    Controller(QMainWindow *mw);
    virtual void readInput() {};
    ~Controller() = default;

    QSharedPointer<GameWorld> getCurrWorld() const noexcept;
    void gameStart(Level level, float pRatio);
    void connectAll();
    void disconnectAll();
    void newWorld(QString filename, float pRatio);

public slots:
    //slots when interact with portal from gameworld
    void portalNext(QString filename, float pRatio);
    void portalBack();
    void gameSave();
    void gameLoad(QString gameFile);
    void deleteGame(const QString& fileName);
    void movePlayerSlot(Direction d);
    void interactPlayerSlot();
    void findPathSlot();
    void gameEnd();
    void gamePause();
    void gameResume();

signals:
    void movePlayer(Direction direction);
    void interactPlayer();
    void updateProtagonistSprite(int index);
    void zoomScene(QWheelEvent *event);
    void pathFound(std::vector<int> path);
    void gameEndSignal(bool win);
};

#endif // CONTROLLER_H
