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

	ui.mainMenuWidget->setVisible(true);
	ui.newGameWidget->setVisible(false);
	ui.gameWidget->setVisible(false);

	// mainMenuWidget
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(exitButtonClicked()));
	connect(ui.newGameButton, SIGNAL(clicked()), this, SLOT(newButtonClicked()));
	connect(ui.loadGameButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));

	// newGameWidget
	connect(ui.loadMapButton, SIGNAL(clicked()), this, SLOT(loadMapButtonClicked()));
	connect(ui.playMapButton, SIGNAL(clicked()), this, SLOT(playMapButtonClicked()));
	connect(ui.backToMainMenuButton, SIGNAL(clicked()), this, SLOT(backToMainMenuButtonClicked()));

	gameInterface = new GameInterface();
}

mainwindow::~mainwindow() {
}


void mainwindow::newButtonClicked()
{
	ui.mainMenuWidget->setVisible(false);
	ui.newGameWidget->setVisible(true);
}

void mainwindow::loadButtonClicked()
{
}

void mainwindow::exitButtonClicked()
{
	this->close();
}

void mainwindow::loadMapButtonClicked()
{
	gameInterface->loadMap();
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
	QGraphicsScene* newScene = new QGraphicsScene();

	QPixmap pix(":/wall");
	QPen pen;
	pen.setWidth(1);
	for (auto wall : gameInterface->getWalls())
	{
		newScene->addRect(QRectF(std::get<1>(wall) * FIELDSIZE, std::get<0>(wall) * FIELDSIZE, FIELDSIZE, FIELDSIZE), pen, QBrush(pix.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}

	tuple<int, int> player = gameInterface->getPlayer();
	QPixmap pixPlayer(":/player");
	newScene->addRect(QRectF(std::get<1>(player) * FIELDSIZE, std::get<0>(player) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixPlayer.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));

	QPixmap pixGhost(":/ghost");
	for (auto ghost : gameInterface->getGhosts())
	{
		newScene->addRect(QRectF(std::get<1>(ghost) * FIELDSIZE, std::get<0>(ghost) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixGhost.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}

	ui.gamePane->setScene(newScene);
	ui.gamePane->fitInView(0, 0, newScene->width(), newScene->height(), Qt::KeepAspectRatio);
	//ui.gamePane->update();
}

