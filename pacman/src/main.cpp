/**
* @brief The entry point for the application.
*
* @author Matus Vrablik(xvrabl05)
*
*/

#include "mainwindow.h"
#include <QtWidgets/QApplication>

/*int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	mainwindow w;
	w.show();
	return a.exec();
}*/

#include <string>
#include "ReplyMode.h"
int main() {
	std::string file = "C:/Users/adrih/source/repos/mathew35/ICP_project/pacman/out/Log";
	ReplyMode replyMode(file, false);
	for (int i = 0; i < 10; i++)
	{
		replyMode.parseLogsFromTurn(true);
		std::cout << "END" << std::endl;
	}


}
