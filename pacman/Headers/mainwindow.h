/**
* @brief Header file for main window of application.
*
* @author Matus Vrablik(xvrabl05)
*
*/
#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsRectItem>
#include <QPixmap>
#include <QFileDialog>
#include <QThread>
#include <QKeyEvent>
#include <QTimer>
#include "ui_mainwindow.h"
#include "GameInterface.h"

using namespace std;
class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget* parent = nullptr);
	~mainwindow();
	void updateMap(std::tuple<int, int> from, std::tuple<int, int>to);
	void updateLives();
	void updateEndGame();

private slots:
	void newGameButtonClicked();
	void loadGameLogButtonClicked();
	void exitButtonClicked();
	void loadMapButtonClicked();
	void playMapButtonClicked();
	void backToMainMenuButtonClicked();
	void processKeyPressEvent();
	void moveGhosts();

private:
	Ui::mainwindowClass ui;

	void playGame();
	void startGame();
	bool updatePlayerItem();
	void updateGhostItems();
	void drawLives(QGraphicsScene* scene);
	void updateDoorItem();

	QPixmap wall;
	QPixmap player;
	QPixmap playerEmpty;
	QPixmap ghost;
	QPixmap doorOpen;
	QPixmap doorClosed;
	map<tuple<int, int>, QGraphicsItem*> wallItems;
	QGraphicsRectItem* playerItem;
	map<tuple<int, int>, QGraphicsItem*> ghostItems;
	QGraphicsRectItem* doorItem;
	map<tuple<int, int>, QGraphicsItem*> keyItems;

	QTimer keyPressTimer;
	int pendingKey;
	QTimer moveGhostsTimer;

protected:
	bool eventFilter(QObject* obj, QEvent* event);
	GameInterface* gameInterface;
};
