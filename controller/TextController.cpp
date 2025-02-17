#include "TextController.h"
#include "iostream"
#include "qapplication.h"
#include "model/direction.h"
#include "ui_mainwindow.h"
#include "view/mainwindow.h"

TextController::TextController(QMainWindow* mainWindow) : Controller(mainWindow){}

void TextController::readInput()
{
    qApp->installEventFilter(this); //install EF to app
}

void TextController::textCommand(QString input) {
    if (((MainWindow*)mw)->getUI()->textBrowser->isVisible()) {
        ((MainWindow*)mw)->getUI()->textBrowser->setVisible(false);
    }
    if (input == "up" || input == "u") {
        emit Controller::movePlayer(Direction::UP);
    } else if (input == "down" || input == "d") {
        emit Controller::movePlayer(Direction::DOWN);
    } else if (input == "left" || input == "l") {
        emit Controller::movePlayer(Direction::LEFT);
    } else if (input == "right" || input == "r") {
        emit Controller::movePlayer(Direction::RIGHT);
    } else if (input == "attack" || input == "a") {
        emit Controller::interactPlayer();
    } else if (input == "autoplay" || input == "p") {
        ((MainWindow*)mw)->getGUIController()->startAutoPlay();
    } else if (input == "help" || input == "h") {
        ((MainWindow*)mw)->getUI()->textBrowser->setVisible(true);
    } else {
        std::cout << "Invalid input" << std::endl;
    }
}
