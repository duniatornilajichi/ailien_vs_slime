#include "GUIController.h"
#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include "controller/Controller.h"
#include "model/direction.h"
#include "qtimer.h"

GUIController::GUIController(QMainWindow* mainWindow) : Controller(mainWindow), autoPlayTimer(new QTimer(this)) {
    connect(autoPlayTimer, &QTimer::timeout, this, &GUIController::handleAutoPlayStep);
    autoPlayTimer->setInterval(200);
}

void GUIController::readInput()
{
    qApp->installEventFilter(this); //install EF to app

}

void GUIController::onKeyPress(QKeyEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        switch (event->key()) {
        case Qt::Key_W:
            //qDebug() << "Controller detect key W";
            emit Controller::movePlayer(Direction::UP);
            emit updateProtagonistSprite(7);
            break;
        case Qt::Key_S:
            //qDebug() << "Controller detect key S";
            emit Controller::movePlayer(Direction::DOWN);
            emit Controller::updateProtagonistSprite(7);
            break;
        case Qt::Key_A:
            //qDebug() << "Controller detect key A";
            emit Controller::movePlayer(Direction::LEFT);
            emit Controller::updateProtagonistSprite(7);
            break;
        case Qt::Key_D:
            //qDebug() << "Controller detect key D";
            emit Controller::movePlayer(Direction::RIGHT);
            emit updateProtagonistSprite(7);
            break;
        case Qt::Key_Space:
            emit Controller::interactPlayer();
            emit updateProtagonistSprite(8);
            break;
        case Qt::Key_P:
            startAutoPlay();
            break;
        default:
            break;
        }
    } else {
        // qDebug() << "Controller event filter cannot handle:"
        //          << event->type(); //if cannot filter return to default filter for target obj
    }
}

void GUIController::startAutoPlay() {
    if (!autoPlayTimer) {
        autoPlayTimer = new QTimer(this);
        connect(autoPlayTimer, &QTimer::timeout,
                this, &GUIController::handleAutoPlayStep);
        autoPlayTimer->setInterval(200);
    }
    autoPlayTimer->start();
    emit requestPath();
}

void GUIController::onWheelEvent(QWheelEvent *event) {
    if (event->type() == QEvent::Wheel) {
        emit zoomScene(event);
    }
}

std::queue<Direction> GUIController::convertDirections(std::vector<int> path) const {
    std::queue<Direction> moves;

    for (auto& direction : path) {
        switch(direction) {
        case 0:  // UP
            moves.push(Direction::UP);
            break;
        case 1:  // UP_RIGHT
            moves.push(Direction::UP);
            moves.push(Direction::RIGHT);
            break;
        case 2:  // RIGHT
            moves.push(Direction::RIGHT);
            break;
        case 3:  // DOWN_RIGHT
            moves.push(Direction::DOWN);
            moves.push(Direction::RIGHT);
            break;
        case 4:  // DOWN
            moves.push(Direction::DOWN);
            break;
        case 5:  // DOWN_LEFT
            moves.push(Direction::DOWN);
            moves.push(Direction::LEFT);
            break;
        case 6:  // LEFT
            moves.push(Direction::LEFT);
            break;
        case 7:  // UP_LEFT
            moves.push(Direction::UP);
            moves.push(Direction::LEFT);
            break;
        }
    }
    return moves;
}

void GUIController::startMovesAfterHighlight() {
    autoPlayTimer->start();
}


void GUIController::handleAutoPlayStep() {
    if (!pendingMoves.empty()) {
        Direction moveDir = pendingMoves.front();
        pendingMoves.pop();
        emit requestMove(moveDir);
    } else {
        autoPlayTimer->stop();
    }
}
