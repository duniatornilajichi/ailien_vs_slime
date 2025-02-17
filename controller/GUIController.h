#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H
#include "controller/Controller.h"

class GUIController : public Controller
{
    Q_OBJECT
public:

    GUIController(QMainWindow *mw);
    ~GUIController() = default;
    void readInput() override;
    void onKeyPress(QKeyEvent *event);
    void onWheelEvent(QWheelEvent *event);

    std::queue<Direction> convertDirections(std::vector<int> path) const;
    void setupAutoPlayTimer();
    inline QTimer* getAutoPlayTimer() const { return autoPlayTimer; }
    void startAutoPlay();
public slots:
    void handleAutoPlayStep();
    void startMovesAfterHighlight();
    void onPathCalculated(std::vector<int> path) {
        currentPath = path;
        pendingMoves = convertDirections(path);
        emit visualisePath(pendingMoves);
    }

signals:
    void requestPath();
    void requestMove(const Direction);
    void visualisePath(const std::queue<Direction> pendingMoves);
private:
    QMainWindow *mw;
    QTimer* autoPlayTimer{nullptr};
    std::vector<int> currentPath;
    std::queue<Direction> pendingMoves;

};

#endif // GUICONTROLLER_H
