#include "view/mainwindow.h"
#include "controller/GUIController.h"
#include "controller/TextController.h"
#include "controller/Controller.h"
#include "qevent.h"
#include "view/gamescene.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , guiController(new GUIController(this))
    , textController(new TextController(this))
    , graphicsView(new QGraphicsView(this))
    , scene(new GameScene(this))
    , controller(new Controller(this))
    , timer(new QTimer(this))
    , stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    // Start Screen 0
    QWidget *startScreen = new QWidget(this);
    startScreen->setStyleSheet("background-color: #F5F5DC;");
    QVBoxLayout *layout = new QVBoxLayout(startScreen);
    ui->gameLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(ui->gameLabel);

    ui->newGameBtn->setMinimumSize(200, 100);
    layout->addWidget(ui->newGameBtn, 0, Qt::AlignCenter);

    ui->loadGameBtn->setMinimumSize(200, 100);
    layout->addWidget(ui->loadGameBtn, 0, Qt::AlignCenter);

    ui->quitBtn->setMinimumSize(200, 100);
    layout->addWidget(ui->quitBtn, 0, Qt::AlignCenter);

    layout->setSpacing(20);
    startScreen->setLayout(layout);

    //Loading Screen 1
    QWidget *loadingScreen = new QWidget(this);
    loadingScreen->setStyleSheet("background-color: #F5F5DC;");
    QVBoxLayout *loadingLayout = new QVBoxLayout(loadingScreen);
    QLabel *loadingLabel = ui->loadingLabel;
    loadingLayout->addWidget(loadingLabel, 0, Qt::AlignCenter);
    loadingScreen->setLayout(loadingLayout);

    //Game pause 2
    ui->pauseWidget->setGeometry(0,0,1900,1200); //475,100,950,600 for test
    ui->pauseWidget->setVisible(false);
    QVBoxLayout *pauseLayout = new QVBoxLayout(ui->pauseWidget);
    ui->conBtn->setMinimumSize(200, 75);
    pauseLayout->addWidget( ui->conBtn,0, Qt::AlignCenter);
    ui->newGamePauseBtn->setMinimumSize(200, 75);
    pauseLayout->addWidget( ui->newGamePauseBtn,0, Qt::AlignCenter);
    ui->saveBtn->setMinimumSize(200, 75);
    pauseLayout->addWidget( ui->saveBtn,0, Qt::AlignCenter);
    ui->quitBtnPause->setMinimumSize(200, 75);
    pauseLayout->addWidget(ui->quitBtnPause,0, Qt::AlignCenter);
    pauseLayout->setSpacing(20);
    pauseLayout->setAlignment(Qt::AlignCenter);
    ui->pauseWidget->setLayout(pauseLayout);

    // Game save 3
    ui->saveWidget->setGeometry(0, 0, 1900, 1200);
    QVBoxLayout *saveLayout = new QVBoxLayout(ui->saveWidget);
    saveLayout->setAlignment(Qt::AlignTop);
    saveLayout->setSpacing(20);
    QList<QString> savedGames = {"Save 1", "Save 2", "Save 3"};
    QScrollArea *scrollArea = new QScrollArea(ui->saveWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("border: 1px solid;");
    QWidget *scrollContent = new QWidget(scrollArea);
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setAlignment(Qt::AlignTop);

    if (savedGames.isEmpty()) {
        QLabel *placeholder = new QLabel("No saved game", scrollContent);
        placeholder->setAlignment(Qt::AlignCenter);
        scrollLayout->addWidget(placeholder);
    } else {
        for (const QString &save : savedGames) {
            QPushButton *saveButton = new QPushButton(save, scrollContent);
            saveButton->setStyleSheet(
                "QPushButton {"
                "   border: none;"
                "   color: white;"
                "   font: 700 16pt 'Segoe Script';"
                "   background-color: rgb(124, 45, 14);"
                "   border-radius: 20px;"
                "}"
                "QPushButton:hover {"
                "   background-color: rgb(118, 78, 46);"
                "}"
                );
            saveButton->setMinimumSize(200, 50);
            scrollLayout->addWidget(saveButton, 0, Qt::AlignHCenter);
            connect(saveButton, &QPushButton::clicked, this, [this, save]() {
                qDebug() << "continue";
            });
        }
    }
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);
    saveLayout->addWidget(scrollArea, 1);
    ui->backBtnSave->setMinimumSize(150, 75);
    saveLayout->addWidget(ui->backBtnSave, 0, Qt::AlignHCenter);
    ui->saveWidget->setLayout(saveLayout);

    //Game end 4
    QWidget *endScreen = new QWidget(this);
    endScreen->setStyleSheet("background-color: #F5F5DC;");
    endScreen->setGeometry(0,0,1900,1200);
    QVBoxLayout *endLayout = new QVBoxLayout(endScreen);

    ui->endLabel->setText("End");
    ui->endLabel->setStyleSheet("font: 700 30pt 'Segoe Script';");
    endLayout->addWidget(ui->endLabel,0,Qt::AlignCenter);

    QPushButton *newGameEnd = new QPushButton(this);
    newGameEnd->setText("New Game");
    newGameEnd->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   color: white;"
        "   font: 700 16pt 'Segoe Script';"
        "   background-color: rgb(124, 45, 14);"
        "   border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(118, 78, 46);"
        "}"
    );
    newGameEnd->setMinimumSize(200, 100);
    endLayout->addWidget(newGameEnd,0,Qt::AlignCenter);

    QPushButton *toMenu = new QPushButton(this);
    toMenu->setText("To Game Menu");
    toMenu->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   color: white;"
        "   font: 700 16pt 'Segoe Script';"
        "   background-color: rgb(124, 45, 14);"
        "   border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(118, 78, 46);"
        "}"
        );
    toMenu->setMinimumSize(200, 100);
    endLayout->addWidget(toMenu,0,Qt::AlignCenter);

    QPushButton *quitEnd = new QPushButton(this);
    quitEnd->setText("Quit");
    quitEnd->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   color: white;"
        "   font: 700 16pt 'Segoe Script';"
        "   background-color: rgb(124, 45, 14);"
        "   border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(118, 78, 46);"
        "}"
        );
    quitEnd->setMinimumSize(200, 100);
    endLayout->addWidget(quitEnd,0,Qt::AlignCenter);

    endLayout->setSpacing(100);
    endLayout->setAlignment(Qt::AlignCenter);
    endScreen->setLayout(endLayout);

    //to stack
    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(loadingScreen);
    stackedWidget->addWidget(ui->gameWidget); //Game Screen 2
    stackedWidget->addWidget(ui->saveWidget);
    stackedWidget->addWidget(endScreen);


    setCentralWidget(stackedWidget);

    setView(0);

    QSize availableSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    width *= 0.9;
    height *= 0.9;
    QSize newSize(width, height);

    ui->graphicsView->setFixedSize(newSize);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

    ui->textBrowser->setVisible(false);

    ui->pauseButton->setFocusPolicy(Qt::NoFocus);
    ui->comboBoxView->setFocusPolicy(Qt::NoFocus);

    ui->healthBar->setRange(0, 100);
    ui->energyBar->setRange(0, 100);
    ui->healthBar->setFormat("HP: %p%");
    ui->energyBar->setFormat("Energy: %p%");

    ui->healthBar->setStyleSheet("\
            QProgressBar {\
                border: 2px solid grey;\
                border-radius: 5px;\
                text-align: center;\
            }\
            QProgressBar::chunk { \
                background-color: #FF362F; \
            }");

    ui->energyBar->setStyleSheet("\
            QProgressBar {\
                border: 2px solid grey;\
                border-radius: 5px;\
                text-align: center;\
            }\
            QProgressBar::chunk { \
                background-color: yellow; \
            }");

    connect(scene, SIGNAL(update()), this, SLOT(updateBars()));
    connect(guiController, SIGNAL(movePlayer(Direction)), controller, SLOT(movePlayerSlot(Direction)));
    connect(textController, SIGNAL(movePlayer(Direction)), controller, SLOT(movePlayerSlot(Direction)));
    connect(guiController,   SIGNAL(interactPlayer()),      controller, SLOT(interactPlayerSlot()));
    connect(ui->comboBoxView, SIGNAL(currentIndexChanged(int)), this, SLOT(setView(int)));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(textCommand()));
    connect(controller, SIGNAL(gameEndSignal(bool)), this, SLOT(gameEnd(bool)));
    connect(guiController, SIGNAL(zoomScene(QWheelEvent*)), this, SLOT(zoom(QWheelEvent*)));
    connect(ui->pauseButton, &QPushButton::released, this, [this]() {
        ui->pauseWidget->setVisible(true);
    });
    connect(ui->pauseButton, SIGNAL(released()), controller, SLOT(gamePause()));
    //menu window
    connect(ui->newGameBtn, &QPushButton::clicked, this, &MainWindow::showLoadingScreen);
    connect(ui->newGameBtn, &QPushButton::clicked, this, &MainWindow::gameStart);
    connect(ui->loadGameBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(ui->saveWidget);
    });
    connect(ui->quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
    //pause window
    connect(ui->conBtn, &QPushButton::clicked, this, [this]() {
        ui->pauseWidget->setVisible(false);
    });
    connect(ui->conBtn, SIGNAL(released()), controller, SLOT(gameResume()));
    connect(ui->newGamePauseBtn, &QPushButton::clicked, this, [this]() {
        ui->pauseWidget->setVisible(false);
    });
    connect(ui->newGamePauseBtn, &QPushButton::clicked, this, &MainWindow::gameStart);
    connect(ui->quitBtnPause, &QPushButton::clicked, qApp, &QApplication::quit);
    //save window
    connect(ui->backBtnSave, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    //end window
    connect(newGameEnd, &QPushButton::clicked, this, &MainWindow::showLoadingScreen);
    connect (newGameEnd, &QPushButton::clicked,this,&MainWindow::gameStart);
    connect (toMenu, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    connect(quitEnd, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(this, SIGNAL(breakAutoPlay()), scene, SLOT(breakAutoPlay()));
    connect(this, SIGNAL(breakAutoPlay()), guiController->getAutoPlayTimer(), SLOT(stop()));
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (scene->getViewType() != 1) {
        emit breakAutoPlay();
        return guiController->onKeyPress(event);
    }
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (scene->getViewType() != 1) {
        return guiController->onWheelEvent(event);
    }
}

void MainWindow::textCommand() const {
    textController->textCommand(ui->lineEdit->text());
}

void MainWindow::setView(int view) const {
    scene->setViewType(view);
    switch (view) {
    case 0:
        ui->lineEdit->hide();
        break;
    case 1:
        ui->lineEdit->show();
        break;
    case 2:
        ui->lineEdit->hide();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkVisibleView() {
    if (scene->getViewType() == 1) return;

    PlayerGraphicsItem* v_player = scene->getPlayerView();
    if (!v_player) return;
    const int margin = 520;

    QRectF playerRect = v_player->sceneBoundingRect();

    ui->graphicsView->ensureVisible(playerRect, margin, margin);
}

void MainWindow::zoom(QWheelEvent *event) {
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    const qreal detail = QStyleOptionGraphicsItem::levelOfDetailFromTransform(
        ui->graphicsView->transform()
        );

    if ((detail < 1 && event->angleDelta().y() > 0) ||  // Zoom in limit
        (detail > 1 && event->angleDelta().y() < 0)) {   // Zoom out limit
        qreal scale = 1.1;
        if (event->angleDelta().y() < 0) {
            scale = 1.0 / scale;
        }
        ui->graphicsView->scale(scale, scale);
    }
}

void MainWindow::showLoadingScreen() {
    stackedWidget->setCurrentIndex(1);
    QTimer::singleShot(1000, this, &MainWindow::startGame); //1sec
}

void MainWindow::startGame() {
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::gameStart(){
    controller->gameStart(Level::L1, 0.25);
    scene->updateWorld(controller->getCurrWorld());
    checkVisibleView();
}

void MainWindow::gameEnd(bool win){
    emit breakAutoPlay();
    if (win) {
        ui->endLabel->setText("Congratulations! You Win!");
    } else {
        ui->endLabel->setText("GAME OVER");
    }
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::updateBars() {
    ui->healthBar->setValue(controller->getCurrWorld()->getPlayer()->getHealth());
    ui->energyBar->setValue(controller->getCurrWorld()->getPlayer()->getEnergy());
}

