#include <cstdlib>
#include <QApplication>
#include <iostream>

#include "VisualizationWindow.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main(int argc, char *argv[]) {
	if (argc != 9) {
		std::cout << "usage:\t./Visualization WIDTH HEIGHT BLOCK_DIMENSIONS NUM_BLOCKS_X NUM_BLOCKS_Y NUM_BINS CLOSENESS_THRESHOLD BLINDNESS_THRESHOLD" << std::endl;
		std::cout << "example:\t./Visualization 1280 720 10 128 72 24 7 1000" << std::endl;
		return 1;
	}

	// int width = atoi(argv[1]);
	// int height = atoi(argv[2]);
	int block_dimensions = atoi(argv[3]);
	int num_blocks_x = atoi(argv[4]);
	int num_blocks_y = atoi(argv[5]);
	int num_bins = atoi(argv[6]);
	float closeness_threshold = atof(argv[7]);
	int blindness_threshold = atoi(argv[8]);
		
	QApplication a(argc, argv);
	
	VisualizationWindow vw;

	vw.resize(WIDTH, HEIGHT);

	vw.createValues(block_dimensions, num_blocks_x, num_blocks_y, num_bins, closeness_threshold, blindness_threshold);
	vw.show();
	vw.update();

	return a.exec();
}
