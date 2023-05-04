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
	connect(ui.newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));
	connect(ui.loadGameLogButton, SIGNAL(clicked()), this, SLOT(loadGameLogButtonClicked()));

	// newGameWidget
	connect(ui.loadMapButton, SIGNAL(clicked()), this, SLOT(loadMapButtonClicked()));
	connect(ui.playMapButton, SIGNAL(clicked()), this, SLOT(playMapButtonClicked()));
	connect(ui.backToMainMenuButton, SIGNAL(clicked()), this, SLOT(backToMainMenuButtonClicked()));

	gameInterface = new GameInterface(this);
}

mainwindow::~mainwindow() {
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
}
void mainwindow::drawWalls(QGraphicsScene* scene)
{
	QPixmap pix(":/wall");
	QPen pen;
	pen.setWidth(1);
	for (auto wall : gameInterface->getWalls())
	{
		scene->addRect(QRectF(std::get<1>(wall) * FIELDSIZE, std::get<0>(wall) * FIELDSIZE, FIELDSIZE, FIELDSIZE), pen, QBrush(pix.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

void mainwindow::drawPlayer(QGraphicsScene* scene)
{
	tuple<int, int> player = gameInterface->getPlayer();
	QPixmap pixPlayer(":/player");
	scene->addRect(QRectF(std::get<1>(player) * FIELDSIZE, std::get<0>(player) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixPlayer.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
}

void mainwindow::drawGhosts(QGraphicsScene* scene)
{
	QPixmap pixGhost(":/ghost");
	for (auto ghost : gameInterface->getGhosts())
	{
		scene->addRect(QRectF(std::get<1>(ghost) * FIELDSIZE, std::get<0>(ghost) * FIELDSIZE, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixGhost.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

void mainwindow::drawLives(QGraphicsScene* scene)
{
	QPixmap pixLive(":/player");
	for (int i = 0; i < gameInterface->getLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixLive.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
	QPixmap pixNoLive(":/playerEmpty");
	for (int i = gameInterface->getLives(); i < gameInterface->getMaxLives(); i++)
	{
		scene->addRect(QRectF(i * FIELDSIZE, 0, FIELDSIZE, FIELDSIZE), Qt::NoPen, QBrush(pixNoLive.scaled(FIELDSIZE, FIELDSIZE, Qt::KeepAspectRatio)));
	}
}

