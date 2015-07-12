#include <iostream>

#include "VisualizationWindow.h"

#include "sandbox/Travis/bitmap_loader.h"
#include "sandbox/Travis/histogram_cluster.h"

#include <stdlib.h>

#include <stdio.h>
#include <time.h>

using namespace std;

VisualizationWindow::VisualizationWindow(QWidget *p) : QGLWidget(p) {
	width = 1280;
	height = 720;
	grayData = NULL;
	clusters = NULL;
}

void VisualizationWindow::createValues() {
	srand(time(NULL));
	BitmapLoader fb("/home/parthmehrotra/Visualization/road.bmp", width, height);
	
	uint8_t *reversedGrayData = fb.next();
	grayData = new uint8_t[width*height];
	
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			grayData[x + y * width] = reversedGrayData[x + (height-y) * width];
		}
	}


	HistogramCluster cluster(width, height, 15, 128, 72, 16);
	clusters = cluster.doCluster(grayData, 0, 100);

	cout << "created" << endl;
}

void VisualizationWindow::initializeGL() {
	makeCurrent();
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void VisualizationWindow::resizeGL(int w, int h) {
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void VisualizationWindow::paintGL() {
	createValues();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(0, height);
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, grayData);

	for (int _x = 0; _x < width/10; _x++) {
		for (int _y = 0; _y < height / 10; _y++) {

			int x = _x * 10; 
			int y = _y * 10;

			int w = width / 10;
			int h = height / 10;

			cout << "this shit happened" << endl;
			float value = clusters[_x + _y * w];

			cout << "this shit happened" << endl;
			glColor4f(1, 1, 1, value);
			
			glBegin(GL_QUADS);
				glVertex2f(x, y);
				glVertex2f(x + w, y);
				glVertex2f(x + w, y + h);
				glVertex2f(x, y + h);
			glEnd();
		}
	}

	glFlush();
}
