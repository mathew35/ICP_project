/**
 * @brief MainWindow class file
 *
 * @author Matúš Vráblik (xvrabl05)
 */

#include "mainwindow.h"

#define picSize 200

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

	int paneHeight = ui.gamePane->height();
	int paneWidth = ui.gamePane->width();
	QGraphicsScene* newScene = new QGraphicsScene();
	for (auto wall : gameInterface->getWalls())
	{
		QPixmap pix(":/playerFull.webp");
		newScene->addRect(QRectF(std::get<1>(wall) * picSize, std::get<0>(wall) * picSize, picSize, picSize), QPen(), QBrush(pix.scaled(picSize, picSize, Qt::KeepAspectRatio)));
	}
	ui.gamePane->setScene(newScene);
	ui.gamePane->fitInView(0, 0, newScene->width(), newScene->height(), Qt::KeepAspectRatio);
	//ui.gamePane->update();
}

