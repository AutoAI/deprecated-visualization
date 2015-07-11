#include <iostream>

#include "VisualizationWindow.h"
#include "sandbox/Travis/frame_buffer.h"

using namespace std;

VisualizationWindow::VisualizationWindow(QWidget *p) : QGLWidget(p) {
	width = 1280;
	height = 720;
	grayData = NULL;
}

bool VisualizationWindow::initFrames() {
	FrameBuffer fb("/home/parthmehrotra/Visualization/random.dat", width, height);
	
	uint16_t *grayData16 = fb.next();
	uint8_t *grayData8 = new uint8_t[fb.bufferSize()/sizeof(uint8_t)];
	for(int i = 0; i < fb.bufferSize() / 2; i++) {
		grayData8[i] = (uint8_t)grayData16[i];
	}

	grayData = grayData8;

	return true;
}

void VisualizationWindow::initializeGL() {
	makeCurrent();
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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

	glFlush();
}
