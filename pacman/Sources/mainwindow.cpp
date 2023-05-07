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
	keyPressTimer.stop();
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
	QPixmap* map = new QPixmap(":/wall");
	wall = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	map = new QPixmap(":/player");
	player = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	map = new QPixmap(":/playerOutline");
	playerEmpty = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	map = new QPixmap(":/ghost");
	ghost = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	map = new QPixmap(":/doorOpen");
	doorOpen = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	map = new QPixmap(":/doorClosed");
	doorClosed = map->scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio);
	delete map;
	ui.gamePane->setScene(new QGraphicsScene());
	ui.gameScorePane->setScene(new QGraphicsScene());
	ui.gameScorePane->setAlignment(Qt::AlignTop);

	this->playerItem = nullptr;
	this->doorItem = nullptr;
}

mainwindow::~mainwindow() {
	delete gameInterface;
	//TODO  delete maps
}

void mainwindow::updateMap(tuple<int, int> from, tuple<int, int> to)
{
	updateGhostItems();
	updatePlayerItem();
	updateDoorItem();
	//updateKeyItems():
	ui.gamePane->repaint();
	//drawGhosts(scene);
	//drawPlayer(scene);
	//drawWalls(scene);
	//drawDoors(scene);
}

void mainwindow::updateLives()
{
	QGraphicsScene* scene = new QGraphicsScene();
	drawLives(scene);
	delete ui.gameScorePane->scene();
	ui.gameScorePane->setScene(scene);
	ui.gameScorePane->fitInView(0, 0, scene->width(), scene->height(), Qt::KeepAspectRatio);
	ui.gameScorePane->update();
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
	int z = 0;
	for (auto& wall : gameInterface->getWalls())
	{
		int x = std::get<1>(wall);
		int y = std::get<0>(wall);
		QGraphicsItem* wallItem = ui.gamePane->scene()->addRect(QRectF(x * FIELDSIZE, y * FIELDSIZE, FIELDSIZE, FIELDSIZE), QPen(), QBrush(this->wall));
		wallItem->setZValue(z);
		this->wallItems[wall] = wallItem;
	}
	auto door = gameInterface->getDoor();
	int x = std::get<1>(door);
	int y = std::get<0>(door);
	QGraphicsRectItem* doorItem = ui.gamePane->scene()->addRect(QRectF(x * FIELDSIZE, y * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->doorClosed));
	doorItem->setZValue(z);
	this->doorItem = doorItem;
	//TODO keys

	updatePlayerItem();
	updateGhostItems();

	ui.gamePane->fitInView(0, 0, ui.gamePane->scene()->width(), ui.gamePane->scene()->height(), Qt::KeepAspectRatio);
	ui.gamePane->update();
	ui.gamePane->setFocus();

	auto lives = gameInterface->getLives();
	auto maxLives = gameInterface->getMaxLives();
	for (int i = 0; i < lives; i++)
	{
		QGraphicsItem* liveItem = ui.gameScorePane->scene()->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->player));
	}
	for (int i = lives; i < maxLives; i++)
	{
		QGraphicsItem* noLiveItem = ui.gameScorePane->scene()->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->playerEmpty));
	}
	ui.gameScorePane->fitInView(0, 0, ui.gameScorePane->scene()->width(), ui.gameScorePane->scene()->height(), Qt::KeepAspectRatio);
	ui.gameScorePane->update();

	this->moveGhostsTimer.start(500);
	// TODO keypresstimer - doesnt work properly

	//gameInterface->startGame();
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

bool mainwindow::updatePlayerItem()
{
	int z = 1;
	auto player = gameInterface->getPlayer();
	int x = std::get<1>(player);
	int y = std::get<0>(player);
	if (this->playerItem == nullptr)
	{
		QGraphicsRectItem* playerItem = ui.gamePane->scene()->addRect(QRectF(0, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->player));
		playerItem->setPos(x * FIELDSIZE, y * FIELDSIZE);
		playerItem->setZValue(z);
		this->playerItem = playerItem;
		return true;
	}
	if (this->playerItem->pos().x() / FIELDSIZE == x && this->playerItem->pos().y() / FIELDSIZE == y)
	{
		return false;
	}

	this->playerItem->setPos(x * FIELDSIZE, y * FIELDSIZE);
	return true;
}

void mainwindow::updateGhostItems()
{
	int z = 2;
	if (this->ghostItems.empty())
	{
		for (auto ghost : gameInterface->getGhosts())
		{
			int x = std::get<1>(ghost);
			int y = std::get<0>(ghost);
			QGraphicsItem* ghostItem = ui.gamePane->scene()->addRect(QRectF(0, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(this->ghost));
			ghostItem->setPos(x * FIELDSIZE, y * FIELDSIZE);
			ghostItem->setZValue(z);
			this->ghostItems[tuple(x, y)] = ghostItem;
		}
		return;
	}
	list<tuple<int, int>> ghosts = gameInterface->getGhosts();
	list<tuple<int, int>> toRemove;
	for (auto& ghostItem : this->ghostItems)
	{
		int x = std::get<1>(ghostItem.first);
		int y = std::get<0>(ghostItem.first);
		bool found = false;
		for (auto ghost : ghosts)
		{
			if (ghost == tuple(x, y)) {
				ghosts.remove(ghost);
				found = true;
				break;
			}
		}
		if (!found)
		{
			toRemove.push_back(ghostItem.first);
		}
	}
	for (auto key : toRemove)
	{
		QGraphicsItem* tmp = this->ghostItems.find(key)->second;
		this->ghostItems.erase(key);
		int x = std::get<1>(ghosts.back());
		int y = std::get<0>(ghosts.back());
		ghosts.pop_back();
		tmp->setPos(x * FIELDSIZE, y * FIELDSIZE);
		this->ghostItems[tuple(x, y)] = tmp;
	}
}

void mainwindow::drawLives(QGraphicsScene* scene)
{
	for (int i = 0; i < gameInterface->getLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(player));
	}
	for (int i = gameInterface->getLives(); i < gameInterface->getMaxLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(playerEmpty));
	}
}

void mainwindow::updateDoorItem()
{
	if (this->doorItem == nullptr) { return; }
	int x = std::get<1>(gameInterface->getDoor());
	int y = std::get<0>(gameInterface->getDoor());
	if (gameInterface->isDoorOpen())
	{
		this->doorItem->setBrush(QBrush(this->doorOpen));
	}
	else
	{
		this->doorItem->setBrush(QBrush(this->doorClosed));
	}
}

bool mainwindow::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		if (obj == ui.gamePane)
		{
			this->keyPressTimer.start(500);
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
}

