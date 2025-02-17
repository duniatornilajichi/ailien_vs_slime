#ifndef PORTALENTITY_H
#define PORTALENTITY_H

#include "entity.h"
#include "model/level.h"

class PortalEntity:  public QObject, public Entity
{
    Q_OBJECT

public:
    PortalEntity() = default;
    ~PortalEntity() = default;
    PortalEntity(int x, int y, Level lev, bool fwd):Entity(x,y), level{lev}, foward{fwd}{};

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override {};
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override;
    inline EntityType getType() const override {return EntityType::PORTAL; };

    inline Level getLevel() const { return level; };

signals:
    void portalNext(QString filename, float pRatio);
    void portalBack();
private:
    Level level;
    bool foward;
};

#endif // PORTALENTITY_H
