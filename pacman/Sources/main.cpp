// main.cpp : Defines the entry point for the application.
//

#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	std::cout << "Hello world in HEEEELLLL!!!!";
	QApplication a(argc, argv);


	mainwindow w;
	w.show();
	return a.exec();
}
