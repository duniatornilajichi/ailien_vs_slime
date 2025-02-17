#ifndef TEXTCONTROLLER_H
#define TEXTCONTROLLER_H
#include "Controller.h"

class TextController : public Controller
{
    Q_OBJECT
public:
    TextController(QMainWindow *mw);
    void readInput() override;
    void textCommand(QString input);
};

#endif // TEXTCONTROLLER_H
