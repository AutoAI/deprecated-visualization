// frame_buffer_tester.cc

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

#include "frame_buffer.h"
#include "bitmap_loader.h"
#include "histogram_cluster.h"
#include "cluster_hash.h"

const bool buffer_test = false;
const bool cluster_test = true;
const bool hash_test = false;

int main(int argc, char *argv[]) {
	// make sure the input is valid
	if(argc != 4) {
		std::cout << "Invalid number of arguments: arguments are file_name, x_resolution, and y_resolution" << std::endl;
		return 1;
	}

	if(std::atoi(argv[2]) < 1 || std::atoi(argv[3]) < 1) {
		std::cout << "Resolution arguments must be positive integers." << std::endl;
		return 1;
	}

	// read in arguments
	std::string file_name = argv[1];
	int x_resolution = std::atoi(argv[2]);
	int y_resolution = std::atoi(argv[3]);

	if(buffer_test){
		std::cout << "Buffer Test:" << std::endl;
		// start timing the program
		std::clock_t program_start_time = std::clock();

		FrameBuffer fb(file_name, x_resolution, y_resolution, 1);

		while(fb.hasNext()) {
			fb.next8();
		}

		// print the program's run duration
		double program_duration = (std::clock() - program_start_time) / (double) CLOCKS_PER_SEC;
		std::cout << "Loaded " << fb.numFrames() << " frames in " << program_duration << " seconds (" << fb.numFrames() / program_duration << " frames per second)." << std::endl << std::endl;
	}

	if(cluster_test) {
		std::cout << "Cluster Test:" << std::endl;
		// start timing the program
		std::clock_t program_start_time = std::clock();

		BitmapLoader bl("road.bmp", x_resolution, y_resolution, 1);
		HistogramCluster hc(x_resolution, y_resolution, 1, 15, x_resolution/80, y_resolution/40, 24);
		uint16_t *clusters = hc.doCluster(bl.next8(), 200, 100);

		// print the program's run duration
		double program_duration = (std::clock() - program_start_time) / (double) CLOCKS_PER_SEC;
		std::cout << "Clustered " << x_resolution * y_resolution / 6400 << " blocks in " << program_duration << " seconds (" << x_resolution * y_resolution / (6400 * program_duration) << " blocks per second)." << std::endl << std::endl;
	}

	if(hash_test) {
		std::cout << "Hash Test:" << std::endl;
		// start timing the program
		std::clock_t program_start_time = std::clock();

		ClusterHash hc;
		hc.addEquality(0,4);
		hc.addEquality(4,8);
		hc.addEquality(8,9);

		hc.addEquality(1,5);
		hc.addEquality(5,10);
		hc.addEquality(10,11);
		hc.addEquality(11,1);

		hc.addEquality(12,2);
		hc.addEquality(2,6);
		hc.addEquality(13,2);

		hc.addEquality(3,7);
		hc.addEquality(3,14);
		hc.addEquality(3,16);
		hc.addEquality(3,15);
		hc.addEquality(7,14);
		hc.addEquality(7,16);
		hc.addEquality(7,15);
		hc.addEquality(14,16);
		hc.addEquality(14,15);
		hc.addEquality(16,15);
		std::unordered_map<int, int> um = hc.genMap();
		for(int i = 0; i < 17; i++) {
			std::cout << i << " -> " << um[i] << std::endl;
		}

		// print the program's run duration
		double program_duration = (std::clock() - program_start_time) / (double) CLOCKS_PER_SEC;
		std::cout << "Clustered all blocks in " << program_duration << " seconds." << std::endl << std::endl;
	}

	return 0;
}