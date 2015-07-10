#include "VisualizationWindow.h"
#include <iostream>

VisualizationWindow::VisualizationWindow(QWidget *p) : QGLWidget(p) {
	
}

bool VisualizationWindow::initFrames() {
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
	glViewport(0, 0, 1280, 720);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 1280, 0, 720, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void VisualizationWindow::paintGL() {
	std::cout << "paint" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLineWidth(30);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1, 1);
		glVertex2f(5, 5);
		glVertex2f(10, 10);
		glVertex2f(100, 100);
	glEnd();

	glFlush();
}
