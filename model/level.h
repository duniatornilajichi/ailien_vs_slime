#ifndef LEVEL_H
#define LEVEL_H

#include <QString>

enum class Level{
    L1,L2,L3
};

struct LevelInfo {
    Level level;
    unsigned int nHealthpacks;
    unsigned int nEnemies;
    LevelInfo(Level lvl, unsigned int healthpacks, unsigned int enemies)
        : level(lvl), nHealthpacks(healthpacks), nEnemies(enemies) {}

    static LevelInfo getLevelInfo(Level level) { // change lv info later
        switch (level) {
        case Level::L1:
            return LevelInfo(Level::L1, 15, 30);
            break;
        case Level::L2:
            return LevelInfo(Level::L2, 20, 50);
            break;
        case Level::L3:
            return LevelInfo(Level::L3, 150, 300);
            break;
        default:
            return LevelInfo(Level::L1, 50, 300);
        }
    }
    static QString getLevelFile(Level lvl){
        switch (lvl) {
        case Level::L1:{
            QString filename = ":/image_003";
            return filename;
        }
        case Level::L2:{
            QString filename = ":/image_002";
            return filename;
        }
        case Level::L3:{
            QString filename = ":/image_001";
            return filename;
        }
        default:{
            QString filename = ":/image_001";
            return filename;
        }
        }
    }
    static Level incrementLevel(Level currentLevel) {
        int nextLevel = static_cast<int>(currentLevel) + 1;
        return static_cast<Level>(nextLevel);
    }

    // Decrement Level
    static Level decrementLevel(Level currentLevel) {
        int prevLevel = static_cast<int>(currentLevel) - 1;
        if (prevLevel < static_cast<int>(Level::L1)) {
            throw std::out_of_range("Cannot decrement below L1");
        }
        return static_cast<Level>(prevLevel);
    }
};

#endif // LEVEL_H
