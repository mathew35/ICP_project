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
	void newButtonClicked();
	void loadButtonClicked();
	void exitButtonClicked();
	void loadMapButtonClicked();
	void playMapButtonClicked();
	void backToMainMenuButtonClicked();

private:
	Ui::mainwindowClass ui;

	void playGame();

protected:
	GameInterface* gameInterface;
};

