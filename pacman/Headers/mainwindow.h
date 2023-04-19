// pacman.h : Include file for standard system include files,
// or project specific include files.
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

