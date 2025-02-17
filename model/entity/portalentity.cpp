#include "portalentity.h"
#include <QDebug>

void PortalEntity::interactBy(QSharedPointer<Player> player,
                              QList<QSharedPointer<Block>> affectedBlocks,
                              QList<QSharedPointer<Entity>>& entityList){
    //TO DO the maps should be decided based on level in controller
    if(foward){
        LevelInfo levelInfo = LevelInfo::getLevelInfo(level);
        Level newlevel = levelInfo.incrementLevel(level);
        emit portalNext(levelInfo.getLevelFile(newlevel), 0.5);
    }
    else{
        emit portalBack();
    }
}
