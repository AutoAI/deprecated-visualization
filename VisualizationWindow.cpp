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

bool VisualizationWindow::initFrames() {
	srand(time(NULL));
	BitmapLoader fb("/home/parthmehrotra/Visualization/road.bmp", width, height);
	
	uint8_t *reversedGrayData = fb.next();
	grayData = new uint8_t[width*height];
	
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			grayData[x + y * width] = reversedGrayData[x + (height-y) * width];
		}
	}


	//HistogramCluster cluster(width, height, 15, 128, 72, 16);
	//clusters = cluster.doCluster(grayData, 0.00001, 100);
	clusters = new uint16_t[width/10 * height/10];
	for (uint16_t x = 0; x < width/10; x++) {
		for (uint16_t y = 0; y < height/10; y++) {
			clusters[x + y*width/10] = rand() % 10000 + 1;
			cout << clusters[x + y * width/10] << endl;
		}
	}

	return true;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(0, height);
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, grayData);

	glColor4f(1, 0, 0, 1);
	for (int x = 0; x < width/10; x++) {
		for (int y = 0; y < height / 10; y++) {
			glColor4f(1, 0, 0, 1);
			glBegin(GL_QUADS);
				glVertex2f(x + (x * width), y + (y * height));
				glVertex2f((x + (x * width)) + width/10, y + (y * height));
				glVertex2f((x + (x * width)) + width/10, (y + (y * height)) + height/10);
				glVertex2f(x + (x * width), (y + (y * height)) + height/10);
			glEnd();
		}
	}

	glFlush();
}
