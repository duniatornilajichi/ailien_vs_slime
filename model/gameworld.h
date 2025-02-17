#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QImage>
#include "pathfinderadapter.h"
#include "direction.h"
#include "block.h"
#include "player.h"
#include "level.h"
#include "entity/entity.h"
#include "entity/portalentity.h"


class GameWorld : public QObject, public QEnableSharedFromThis<GameWorld>
{
    Q_OBJECT
public:
    GameWorld(QString filename, Level level, float pRatio = 0.25, float xRatio = 0.1);
    ~GameWorld() = default;

    inline QSharedPointer<Player> getPlayer() const { return player; };
    inline QList<QList<QSharedPointer<Block>>> getMatrixBlocks() const { return matrixBlocks; };
    inline QList<QSharedPointer<Entity>> getEntities() const { return listEntities; };
    inline void setId(int id) { this->id = id; };
    inline int getId() const { return id; };

    QSharedPointer<Block> getBlock(int x, int y) const;
    inline QSharedPointer<PortalEntity> getPortalFoward() const { return portalFoward; };
    inline QSharedPointer<PortalEntity> getPortalBack() const { return portalBack; };
    QList<QSharedPointer<Block>> getExpandingBlocks(int x, int y, int layer) const;
    bool isInBounds(int x, int y) const;
    void addEntity(QSharedPointer<Entity> entity);

    void toBinary(QDataStream& out) const;
    void fromBinary(QDataStream& in);
signals:
    void updateWorld(QSharedPointer<GameWorld> world); //signal to view to update
    void pathFound(const std::vector<int>& path);
public slots:
    void movePlayer(Direction direction);
    void interactPlayer();
    void refresh();
    void findPath();
private:
    GameWorld();
    static QSharedPointer<GameWorld> world; //GameWorld is new version of World
    QSharedPointer<Player> player; //Player is new version of Protagonist
    int id;

    Level currentLevel;
    QList<QList<QSharedPointer<Block>>> matrixBlocks; //Blocks is new version of Tiles
    QList<QSharedPointer<Entity>> listEntities;
    QSharedPointer<PortalEntity> portalFoward;
    QSharedPointer<PortalEntity> portalBack;

    QSharedPointer<PathFinderAdapter> pathFinder{nullptr};


};

#endif // GAMEWORLD_H
