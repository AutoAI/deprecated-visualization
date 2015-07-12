#include <iostream>

#include "VisualizationWindow.h"

#include "sandbox/Travis/bitmap_loader.h"
#include "sandbox/Travis/histogram_cluster.h"

#include <stdlib.h>

#include <stdio.h>
#include <time.h>

#include <functional>

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
	
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			grayData[x + y * width] = reversedGrayData[x + (height-y) * width];
		}
	}


	HistogramCluster cluster(width, height, 15, 128, 72, 24);
	clusters = cluster.doCluster(grayData, 10, 100000);
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

void getColorFromID(float* r, float* g, float* b, uint16_t value) {
	srand(value);
	*r = float(rand() % 256) / 256;
	*g = float(rand() % 256) / 256;
	*b = float(rand() % 256) / 256;
}

void VisualizationWindow::paintGL() {
	createValues();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(0, height);
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, grayData);

	//std::hash<uint16_t> hash;

	int x = 0;
	int y = 0;
	int w = 10;
	int h = 10;
	for (int _y = 0; _y < height / 10; _y++) {
		for (int _x = 0; _x < width/10; _x++) {

			int x = _x * 10; 
			int y = _y * 10;

			int w = 10;
			int h = 10;

			size_t value = clusters[_x + _y * w];

			cout <<"x: " << x << ", y: " << y <<" " <<  value << endl;
	
			float red, green, blue;
			getColorFromID(&red, &green, &blue, value);

			glColor4f(red, green, blue, 0.5);
			
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
