/**
* Header file for main window of application.
*
* @author Matúš Vráblik(xvrabl05)
*
*/
#pragma once

#include <iostream>
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget* parent = nullptr);
	~mainwindow();

private:
	Ui::mainwindowClass ui;
};

