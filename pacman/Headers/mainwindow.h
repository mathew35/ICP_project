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
#include "ui_mainwindow.h"
#include "GameInterface.h"

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget* parent = nullptr);
	~mainwindow();

private slots:
	void newGameButtonClicked();
	void loadGameLogButtonClicked();
	void exitButtonClicked();
	void loadMapButtonClicked();
	void playMapButtonClicked();
	void backToMainMenuButtonClicked();

private:
	Ui::mainwindowClass ui;

	void playGame();
	void drawWalls(QGraphicsScene* scene);
	void drawPlayer(QGraphicsScene* scene);
	void drawGhosts(QGraphicsScene* scene);
	void drawLives(QGraphicsScene* scene);

protected:
	GameInterface* gameInterface;
};

