#include <QGLWidget>
#include <QWidget>

#if !defined(_VISUALIZATIONWINDOW_H)
#define _VISUALIZATIONWINDOW_H

class VisualizationWindow : public QGLWidget {
Q_OBJECT

public:
	VisualizationWindow(QWidget *p = 0);
	void createValues(int block_dimension, int num_blocks_x, int num_blocks_y, int num_bins, float closeness_threshold, int blindness_threshold);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	uint32_t width;
	uint32_t height;

	uint8_t *grayData;
	uint16_t *clusters;

	int block_dimension; 
	int num_blocks_x; 
	int num_blocks_y; 
	int num_bins; 
	float closeness_threshold; 
	int blindness_threshold;
};

#endif			// _VISUALIZATIONWINDOW_H

