#include <iostream>

#include "VisualizationWindow.h"

#include "sandbox/Travis/frame_buffer.h"
#include "sandbox/Travis/histogram_cluster.h"

using namespace std;

VisualizationWindow::VisualizationWindow(QWidget *p) : QGLWidget(p) {
	width = 1280;
	height = 720;
	grayData = NULL;
}

bool VisualizationWindow::initFrames() {
	FrameBuffer fb("/home/parthmehrotra/Visualization/random.dat", width, height);
	
	grayData = fb.next();

	HistogramCluster cluster(width, height, 15, 128, 72, 16);
	uint16_t *clusters = cluster.doCluster(grayData, 10, 100);

	for (int y = 0; y < 72; y++) {
		for (int x = 0; x < 128; x++) {
			cout << unsigned(clusters[x+y*128]) << endl;
		}
	}

	return true;
}

void VisualizationWindow::initializeGL() {
	makeCurrent();
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void VisualizationWindow::resizeGL(int w, int h) {
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void VisualizationWindow::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(0, 0);
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, grayData);

	glColor4f(1, 0, 0, 0.5);
	glBegin(GL_QUADS);
		glVertex2f(5, 5);
		glVertex2f(100, 5);
		glVertex2f(100, 100);
		glVertex2f(5, 100);
	glEnd();

	glFlush();
}
