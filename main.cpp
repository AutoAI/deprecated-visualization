#include <QApplication>

#include "VisualizationWindow.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	
	VisualizationWindow vw;

	vw.resize(WIDTH, HEIGHT);
	vw.show();
	vw.update();

	return a.exec();
}
