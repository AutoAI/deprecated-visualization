#include <iostream>

#include "VisualizationWindow.h"

#include "bitmap_loader.h"
#include "histogram_cluster.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <functional>

VisualizationWindow::VisualizationWindow(QWidget *p) : QGLWidget(p) {
	width = 1280;
	height = 720;
	image = NULL;
	clusters = NULL;
}

void VisualizationWindow::createValues(int block_dimension, int num_blocks_x, int num_blocks_y, int num_bins, float closeness_threshold, int blindness_threshold) {
	this -> block_dimension = block_dimension;
	this -> num_blocks_x = num_blocks_x;
	this -> num_blocks_y = num_blocks_y;
	this -> num_bins = num_bins;
	this -> closeness_threshold = closeness_threshold;
	this -> blindness_threshold = blindness_threshold;

	srand(time(NULL));
	BitmapLoader fb("road.bmp", width, height);
	
	image = fb.next32();

	clusters = new uint16_t[num_blocks_x*num_blocks_y];
	HistogramCluster cluster(width, height, block_dimension, num_blocks_x, num_blocks_y, num_bins);

	uint16_t *reversed_clusters = cluster.doCluster(image, closeness_threshold, blindness_threshold);
	for(int y = 0; y < num_blocks_y; y++) {
		for(int x = 0; x < num_blocks_x; x++) {
			clusters[y * num_blocks_x + x] = reversed_clusters[x + (num_blocks_y - 1 - y) * num_blocks_x];
		}
	}
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
	*r = (rand() % 256) / 256.0; 
	*g = (rand() % 256) / 256.0; 
	*b = (rand() % 256) / 256.0; 
}

void VisualizationWindow::paintGL() {

	// for(int y = 0; y < num_blocks_y; y++) {
	// 	std::cout << clusters[y * num_blocks_x];
	// 	for(int x = 1; x < num_blocks_x; x++) {
	// 		std::cout << "\t" << clusters[x + y * num_blocks_x];
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2i(0, height);

	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, image);

	for(int x = 0; x < num_blocks_x; x++) {
		for(int y = 0; y < num_blocks_y; y++) {

			int _x = x * width / num_blocks_x; 
			int _y = y * height / num_blocks_y; 

			size_t value = clusters[y * num_blocks_x + x];

			float red, green, blue;
			getColorFromID(&red, &green, &blue, value);

			glColor4f(red, green, blue, 0.5);
			
			glBegin(GL_LINE_LOOP);
				glVertex2f(_x, _y);
				glVertex2f(_x + width / num_blocks_x, _y);
				glVertex2f(_x + width / num_blocks_x, _y + height/num_blocks_y);
				glVertex2f(_x, _y + height/num_blocks_y);
			glEnd();
			glBegin(GL_QUADS);
				glVertex2f(_x, _y);
				glVertex2f(_x + width / num_blocks_x, _y);
				glVertex2f(_x + width / num_blocks_x, _y + height / num_blocks_y);
				glVertex2f(_x, _y + height / num_blocks_y);
			glEnd();
		}
	}

	glFlush();
}

