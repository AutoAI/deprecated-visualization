#include <QApplication>

#include "VisualizationWindow.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	VisualizationWindow vw;

	if (!vw.initFrames()) {
		return 0;
	}

	vw.resize(300, 300);
	vw.show();

	return a.exec();
}
