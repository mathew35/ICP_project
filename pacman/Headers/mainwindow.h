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
	void drawWalls(QGraphicsScene* scene);
	void drawPlayer(QGraphicsScene* scene);
	void drawGhosts(QGraphicsScene* scene);
	void drawLives(QGraphicsScene* scene);
	void drawDoors(QGraphicsScene* scene);

	QPixmap wall;
	QPixmap player;
	QPixmap playerEmpty;
	QPixmap ghost;
	QPixmap doorOpen;
	QPixmap doorClosed;

	QTimer keyPressTimer;
	int pendingKey;
	QTimer moveGhostsTimer;

protected:
	bool eventFilter(QObject* obj, QEvent* event);
	GameInterface* gameInterface;
};
