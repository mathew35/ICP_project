/**
 * @brief MainWindow class file
 *
 * @author Matúš Vráblik (xvrabl05)
 */

#include "mainwindow.h"

#define FIELDSIZE 200

mainwindow::mainwindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qApp->installEventFilter(this);
	connect(&keyPressTimer, &QTimer::timeout, this, &mainwindow::processKeyPressEvent);
	connect(&moveGhostsTimer, &QTimer::timeout, this, &mainwindow::moveGhosts);

	ui.mainMenuWidget->setVisible(true);
	ui.newGameWidget->setVisible(false);
	ui.gameWidget->setVisible(false);

	// mainMenuWidget
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(exitButtonClicked()));
	connect(ui.newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));
	connect(ui.loadGameLogButton, SIGNAL(clicked()), this, SLOT(loadGameLogButtonClicked()));

	// newGameWidget
	connect(ui.loadMapButton, SIGNAL(clicked()), this, SLOT(loadMapButtonClicked()));
	connect(ui.playMapButton, SIGNAL(clicked()), this, SLOT(playMapButtonClicked()));
	connect(ui.backToMainMenuButton, SIGNAL(clicked()), this, SLOT(backToMainMenuButtonClicked()));

	gameInterface = new GameInterface(this);
	wall = new QPixmap(":/wall");
	player = new QPixmap(":/player");
	playerEmpty = new QPixmap(":/playerEmpty");
	ghost = new QPixmap(":/ghost");
}

mainwindow::~mainwindow() {
	delete gameInterface;
}

void mainwindow::updateMap(tuple<int, int> from, tuple<int, int> to)
{
	QGraphicsScene* scene = new QGraphicsScene();
	drawGhosts(scene);
	drawPlayer(scene);
	drawWalls(scene);
	ui.gamePane->setScene(scene);
	ui.gamePane->fitInView(0, 0, scene->width(), scene->height(), Qt::KeepAspectRatio);
	ui.gamePane->repaint();
}

void mainwindow::updateLives()
{
	QGraphicsScene* scene = new QGraphicsScene();
	drawLives(scene);
	ui.gameScorePane->setScene(scene);
	//ui.gameScorePane->setAlignment(Qt::AlignTop);
	ui.gameScorePane->fitInView(0, 0, scene->width(), scene->height(), Qt::KeepAspectRatio);
	ui.gameScorePane->repaint();
}


void mainwindow::newGameButtonClicked()
{
	ui.mainMenuWidget->setVisible(false);
	ui.newGameWidget->setVisible(true);
}

void mainwindow::loadGameLogButtonClicked()
{
	QString file = QFileDialog::getOpenFileName(this, "Choose map file", "C://", "Text file (*.txt)");
	//guard no file selected
	if (file == NULL) { return; }
	//TODO
}

void mainwindow::exitButtonClicked()
{
	this->close();
}

void mainwindow::loadMapButtonClicked()
{
	QString file = QFileDialog::getOpenFileName(this, "Choose map file", "C://", "Text file (*.txt)");
	//guard no file selected
	if (file == NULL) { return; }
	gameInterface->loadMap(file.toStdString());
	this->playGame();
}

void mainwindow::playMapButtonClicked()
{
	this->playGame();
}

void mainwindow::backToMainMenuButtonClicked()
{
	ui.newGameWidget->setVisible(false);
	ui.mainMenuWidget->setVisible(true);
}

void mainwindow::playGame()
{
	ui.newGameWidget->setVisible(false);
	ui.gameWidget->setVisible(true);

	//TODO - add selection from gridPane to loadMap arguments
	gameInterface->loadMap();

	int paneHeight = ui.gamePane->height();
	int paneWidth = ui.gamePane->width();
	QGraphicsScene* newSceneMain = new QGraphicsScene();

	this->drawWalls(newSceneMain);
	this->drawPlayer(newSceneMain);
	this->drawGhosts(newSceneMain);
	ui.gamePane->setScene(newSceneMain);
	ui.gamePane->fitInView(0, 0, newSceneMain->width(), newSceneMain->height(), Qt::KeepAspectRatio);

	QGraphicsScene* newSceneRightSide = new QGraphicsScene();
	this->drawLives(newSceneRightSide);
	ui.gameScorePane->setScene(newSceneRightSide);
	ui.gameScorePane->setAlignment(Qt::AlignTop);
	ui.gameScorePane->fitInView(0, 0, newSceneRightSide->width(), newSceneRightSide->height(), Qt::KeepAspectRatio);
	ui.gamePane->repaint();
	ui.gameScorePane->repaint();
	ui.gamePane->setFocus();
	this->moveGhostsTimer.start(500);
	QThread::sleep(1);

	//this->startGame();
	//gameInterface->startGame();
}
void mainwindow::startGame()
{
	//for (int i = 0; i < 10; i++) {
		//gameInterface->ghostsMove();
	//}
}

void mainwindow::updateEndGame()
{
	this->keyPressTimer.stop();
	this->moveGhostsTimer.stop();

	ui.gameWidget->setVisible(false);
	ui.mainMenuWidget->setVisible(true);
}

void mainwindow::drawWalls(QGraphicsScene* scene)
{
	QPen pen;
	pen.setWidth(1);
	for (auto wall : gameInterface->getWalls())
	{
		scene->addRect(QRectF(std::get<1>(wall) * FIELDSIZE, std::get<0>(wall) * FIELDSIZE, FIELDSIZE, FIELDSIZE), pen, QBrush(this->wall->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

void mainwindow::drawPlayer(QGraphicsScene* scene)
{
	tuple<int, int> player = gameInterface->getPlayer();
	scene->addRect(QRectF(std::get<1>(player) * FIELDSIZE, std::get<0>(player) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->player->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
}

void mainwindow::drawGhosts(QGraphicsScene* scene)
{
	for (auto ghost : gameInterface->getGhosts())
	{
		scene->addRect(QRectF(std::get<1>(ghost) * FIELDSIZE, std::get<0>(ghost) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->ghost->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

void mainwindow::drawLives(QGraphicsScene* scene)
{
	for (int i = 0; i < gameInterface->getLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->player->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
	for (int i = gameInterface->getLives(); i < gameInterface->getMaxLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->playerEmpty->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

bool mainwindow::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		if (obj == ui.gamePane)
		{
			//this->keyPressTimer.start(500);
			this->pendingKey = static_cast<QKeyEvent*>(event)->key();
		}
	}
	return QObject::eventFilter(obj, event);
}

void mainwindow::processKeyPressEvent()
{
	int keyEvent = this->pendingKey;
	if (keyEvent != 0) {
		//QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent == Qt::Key_Right) {
			gameInterface->movePlayer(2);
		}
		if (keyEvent == Qt::Key_Left) {
			gameInterface->movePlayer(0);
		}
		if (keyEvent == Qt::Key_Up) {
			gameInterface->movePlayer(1);
		}
		if (keyEvent == Qt::Key_Down) {
			gameInterface->movePlayer(3);
		}
		pendingKey = 0;
	}
}

void mainwindow::moveGhosts()
{
	gameInterface->startGame();
	processKeyPressEvent();
}

