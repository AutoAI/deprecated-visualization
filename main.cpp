#include <QApplication>

#include "VisualizationWindow.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	VisualizationWindow vw;

	if (!vw.initFrames()) {
		return 0;
	}

	vw.resize(1280, 720);
	vw.show();

	return a.exec();
}
