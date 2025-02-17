#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "model/gameworld.h"
#include "view/graphicsItem/playergraphicsitem.h"
#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    using QGraphicsScene::QGraphicsScene;
    ~GameScene() = default;
    void createScene();
    inline PlayerGraphicsItem* getPlayerView() const { return v_player;};
    inline void setPlayerView (PlayerGraphicsItem* new_v_player) {
        if (!new_v_player) return;
        v_player = new_v_player;
    }
    inline void setWorld(QSharedPointer<GameWorld> world) { gameWorld = world; };
    inline QSharedPointer<GameWorld> getWorld() const { return gameWorld;}
    void setViewType(int newType);
    inline int getViewType() const { return viewType; };
    inline std::queue<Direction> getPath() const { return path; }
    inline bool isShowingHighlights() const { return showingHighlights; }
    inline int getXStart() const {return x_start;}
    inline int getYStart() const {return y_start;}

signals:
    void highlightDone();
    void update();
public slots:
    void updateWorld(QSharedPointer<GameWorld> world);
    void highlightPath(std::queue<Direction> currentPath);
    void breakAutoPlay() {showingHighlights = false;};

private:
    QSharedPointer<GameWorld> gameWorld;
    PlayerGraphicsItem* v_player{};
    int viewType{0};

    const int margin{95}; // margin for adjusting the view

    bool showingHighlights{false};
    const int TILE_SIZE = 40;

    int x_start;
    int y_start;
    std::queue<Direction> path;
};

#endif // GAMESCENE_H
