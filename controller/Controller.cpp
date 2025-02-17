#include "Controller.h"
#include "view/mainwindow.h"
#include <QDebug>

Controller::Controller(QMainWindow* mainWindow) : mw(mainWindow) {};

void Controller::newWorld(QString filename, float pRatio) {
    QSharedPointer<GameWorld> newWorld;
    if (currWorld == 0){
        newWorld = QSharedPointer<GameWorld>::create(filename, Level::L1, pRatio);
    }else if (currWorld == 1){
        newWorld = QSharedPointer<GameWorld>::create(filename, Level::L2, pRatio);
    }else if (currWorld == 2){
        newWorld = QSharedPointer<GameWorld>::create(filename, Level::L3, pRatio);
    }else if (currWorld == 3){
        emit gameEndSignal(true);
        gameEnd();
        return;
    } else {
        qDebug() << "Invalid world value";
        return;
    }
    worldList.append(newWorld);
    ((MainWindow*)mw)->getTimer()->start(2000);
}

void Controller::gameStart(Level level, float pRatio){
    worldList.clear();
    currWorld = 0;
    newWorld(LevelInfo::getLevelFile(level), pRatio);
    connectAll();
}

void Controller::portalNext(QString filename, float pRatio){
    if(currWorld == 2) {
        disconnectAll();
        currWorld++;
        gameEnd();
        return;
    }
    disconnectAll();
    currWorld++;
    if (worldList.length() == currWorld) {
        newWorld(filename, pRatio);
    }
    connectAll();

    ((MainWindow*)mw)->getScene()->updateWorld(getCurrWorld());
    ((MainWindow*)mw)->checkVisibleView();
}

void Controller::portalBack()
{
    if (currWorld <= 0) return;
    disconnectAll();
    currWorld--;
    connectAll();

    ((MainWindow*)mw)->getScene()->updateWorld(getCurrWorld());
}

void Controller::connectAll() {
    if (getCurrWorld()->getPortalFoward())
        connect(getCurrWorld()->getPortalFoward().data(), SIGNAL(portalNext(QString,float)), this, SLOT(portalNext(QString,float)));
    if (getCurrWorld()->getPortalBack())
        connect(getCurrWorld()->getPortalBack().data(), SIGNAL(portalBack()), this, SLOT(portalBack()));
    connect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), mw, SLOT(checkVisibleView()));
    connect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), ((MainWindow*)mw)->getScene(), SLOT(updateWorld(QSharedPointer<GameWorld>)));
    connect(this, SIGNAL(movePlayer(Direction)), getCurrWorld().data(), SLOT(movePlayer(Direction)));
    connect(this, SIGNAL(interactPlayer()), getCurrWorld().data(), SLOT(interactPlayer()));
    connect(((MainWindow*)mw)->getTimer(), SIGNAL(timeout()), getCurrWorld().data(), SLOT(refresh()));
    connect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), (MainWindow*)mw, SLOT(checkVisibleView()));
    connect(((MainWindow*)mw)->getGUIController(), SIGNAL(requestPath()), getCurrWorld().data(), SLOT(findPath()));
    connect(((MainWindow*)mw)->getGUIController(), SIGNAL(requestMove(Direction)), getCurrWorld().data(), SLOT(movePlayer(Direction)));
    connect(getCurrWorld().data(),SIGNAL(pathFound(std::vector<int>)),
            ((MainWindow*)mw)->getGUIController(),
            SLOT(onPathCalculated(std::vector<int>)));
    connect(((MainWindow*)mw)->getGUIController(), SIGNAL(visualisePath(std::queue<Direction>)), ((MainWindow*)mw)->getScene(), SLOT(highlightPath(std::queue<Direction>)));
    connect(getCurrWorld()->getPlayer().data(), SIGNAL(died()), this, SLOT(gameEnd()));
}
void Controller::disconnectAll() {
    if (getCurrWorld()->getPortalFoward())
        disconnect(getCurrWorld()->getPortalFoward().data(), SIGNAL(portalNext(QString,float)), this, SLOT(portalNext(QString,float)));
    if (getCurrWorld()->getPortalBack())
        disconnect(getCurrWorld()->getPortalBack().data(), SIGNAL(portalBack()), this, SLOT(portalBack()));
    disconnect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), mw, SLOT(checkVisibleView()));
    disconnect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), ((MainWindow*)mw)->getScene(), SLOT(updateWorld(QSharedPointer<GameWorld>)));
    disconnect(this, SIGNAL(movePlayer(Direction)), getCurrWorld().data(), SLOT(movePlayer(Direction)));
    disconnect(this, SIGNAL(interactPlayer()), getCurrWorld().data(), SLOT(interactPlayer()));
    disconnect(((MainWindow*)mw)->getTimer(), SIGNAL(timeout()), getCurrWorld().data(), SLOT(refresh()));
    disconnect(((MainWindow*)mw)->getGUIController(), SIGNAL(requestPath()), getCurrWorld().data(), SLOT(findPath()));
    disconnect(((MainWindow*)mw)->getGUIController(), SIGNAL(requestMove(Direction)), getCurrWorld().data(), SLOT(movePlayer(Direction)));
    disconnect(getCurrWorld().data(),SIGNAL(pathFound(std::vector<int>)),
            ((MainWindow*)mw)->getGUIController(),
            SLOT(onPathCalculated(std::vector<int>)));
    disconnect(((MainWindow*)mw)->getGUIController(), SIGNAL(visualisePath(std::queue<Direction>)), ((MainWindow*)mw)->getScene(), SLOT(highlightPath(std::queue<Direction>)));
    disconnect(getCurrWorld().data(), SIGNAL(updateWorld(QSharedPointer<GameWorld>)), (MainWindow*)mw, SLOT(checkVisibleView()));
    disconnect(getCurrWorld()->getPlayer().data(), SIGNAL(died()), this, SLOT(gameEnd()));
}

QSharedPointer<GameWorld> Controller::getCurrWorld() const noexcept{
    if (currWorld >= 0 && currWorld < worldList.size()) {
        return worldList[currWorld];
    }
    return nullptr;
}


void Controller::gameEnd(){
    if(currWorld == 3){
        emit gameEndSignal(true);
    }
    else{
        emit gameEndSignal(false);
        disconnectAll();
    }
    worldList.clear();
    currWorld = -1;
    /*
     * game over screen (restart btn, back to menu back)
     * c
     */
}

void Controller::gameLoad(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "FIle open failed:" << fileName;
        return;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_7);

    in >> currWorld;

    int worldCount;
    in >> worldCount;
    worldList.clear();
    for (int i = 0; i < worldCount; ++i) {
        QSharedPointer<GameWorld> world = QSharedPointer<GameWorld>::create(fileName, Level::L1);
        world->fromBinary(in);
        worldList.append(world);
    }

    file.close();
    qDebug() << "Game world loaded from" << fileName;

    if (currWorld >= 0 && currWorld < worldList.size()) {
        auto w = getCurrWorld();
        emit w->updateWorld(w);
    } else {
        qDebug() << "Invalid world index";
    }
}

void Controller::gameSave() {
    if (worldList.isEmpty()) {
        qDebug() << "No worlds to save.";
        return;
    }
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = QString("game_save_at_%1.dat").arg(timestamp);
    QString saveFolder = QDir::currentPath() + "/GameSaves"; // Folder name
    QDir dir;
    if (!dir.exists(saveFolder)) {
        if (!dir.mkpath(saveFolder)) {
            qDebug() << "Failed to create save folder!";
            return;
        }
    }
    QString filePath = saveFolder + "/" + fileName;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed:" << filePath;
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_7);
    out << currWorld;
    out << worldList.size();
    for (int i = 0; i < worldList.size(); ++i) {
        QSharedPointer<GameWorld> world = worldList[i];
        world->toBinary(out);
    }
    file.close();
    savedGames.append(filePath);
    qDebug() << "Game world saved to" << filePath;
}

void Controller::deleteGame(const QString& fileName) {
    if (savedGames.contains(fileName)) {
        QFile file(fileName);
        if (file.exists()) {
            if (file.remove()) {
                qDebug() << "Game file deleted:" << fileName;
                savedGames.removeAll(fileName);
            } else {
                qDebug() << "Deleting game file failed:" << fileName;
            }
        }
    } else {
        qDebug() << "Game file not found:" << fileName;
    }
}

void Controller::movePlayerSlot(Direction d) {
    if(getCurrWorld()){
         getCurrWorld()->movePlayer(d);
    }
}
void Controller::interactPlayerSlot() {
    if(getCurrWorld()){
        getCurrWorld()->interactPlayer();
    }
}
void Controller::findPathSlot() {
    if(getCurrWorld()){
        getCurrWorld()->findPath();
    }
}

void Controller::gamePause(){
    ((MainWindow*)mw)->getTimer()->stop();
    disconnectAll();
}
void Controller::gameResume(){
    ((MainWindow*)mw)->getTimer()->start(2000);
    connectAll();
}
