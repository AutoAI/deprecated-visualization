// histogram_cluster.h

#pragma once

#include <stdint.h>

class HistogramCluster{
public:
	HistogramCluster(int x_resolution, int y_resolution, int block_dimension, int num_blocks_x, int num_blocks_y, int num_bins);
	uint16_t *doCluster(uint8_t *frame_buffer, float closeness_threshold, int blindness_threshold);
	
private:
	int x_resolution;
	int y_resolution;
	int block_dimension;
	int num_blocks_x;
	int num_blocks_y;
	int num_bins;

	int increment_x;
	int increment_y;
	// first index indicates which histogram, second indicates which bin
	uint16_t **histograms;
	// cluster map - each block gets a unit16_t to identify which cluster it belongs to
	uint16_t *cluster_map;
	float chiSquareDifference(uint16_t *histogram_P, uint16_t *histogram_Q);
};
