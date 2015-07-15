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
  grayData = NULL;
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
//  BitmapLoader fb("/home/parthmehrotra/Visualization/road.bmp", width, height);
  BitmapLoader fb("road.bmp", width, height);
  
  uint8_t *reversedGrayData = fb.next();
  grayData = new uint8_t[width*height];
  
  for (uint32_t y = 0; y < height; y++) {
    for (uint32_t x = 0; x < width; x++) {
      grayData[x + y * width] = reversedGrayData[x + (height-y) * width];
    }
  }


  clusters = new uint16_t[num_blocks_x*num_blocks_y];
  HistogramCluster cluster(width, height, block_dimension, num_blocks_x, num_blocks_y, num_bins);

  uint16_t *reversed_clusters = cluster.doCluster(grayData, closeness_threshold, blindness_threshold);
  for (uint32_t y = 0; y < num_blocks_y; y++) {
    for (uint32_t x = 0; x < num_blocks_x; x++) {
      clusters[y * num_blocks_x + x] = reversed_clusters[x + (num_blocks_y - y) * num_blocks_x];
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRasterPos2i(0, height);
  glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, grayData);

  int num_blocks_x = width / block_dimension;
  int num_blocks_y = height / block_dimension;

  for (int x = 0; x < num_blocks_x; x++) {
    for (int y = 0; y < num_blocks_y; y++) {

      int _x = x * block_dimension; 
      int _y = y * block_dimension;

      size_t value = clusters[y * num_blocks_x + x];

      float red, green, blue;
      getColorFromID(&red, &green, &blue, value);

      glColor4f(red, green, blue, 0.5);
      
      glBegin(GL_LINE_LOOP);
        glVertex2f(_x, _y);
        glVertex2f(_x + block_dimension, _y);
        glVertex2f(_x + block_dimension, _y + block_dimension);
        glVertex2f(_x, _y + block_dimension);
      glEnd();
      glBegin(GL_QUADS);
        glVertex2f(_x, _y);
        glVertex2f(_x + block_dimension, _y);
        glVertex2f(_x + block_dimension, _y + block_dimension);
        glVertex2f(_x, _y + block_dimension);
      glEnd();
    }
  }

  glFlush();
}

