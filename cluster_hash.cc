// cluster_hash.cc

#include "cluster_hash.h"

#include <iostream>

ClusterHash::ClusterHash() {
	num_equalities = 0;
	num_nodes = 0;
}

void ClusterHash::addEquality(int a, int b) {
	// first, lets find out if either of these is already in the list
	bool a_exists = false;
	bool b_exists = false;

	for(auto it = adjacency_matrix_ids.begin(); it != adjacency_matrix_ids.end(); ++it) {
    	if(it -> first == a) {
    		a_exists = true;
    	}
    	if(it -> first == b) {
    		b_exists = true;
    	}
    }

	// if either of them don't exist, add them to the table
	if(!a_exists) {
		// add a to the map of ids
		adjacency_matrix_ids[a] = num_nodes;
		num_nodes++;
		// add a list that will store a's neighbors
		adjacency_matrix.push_back(new std::queue<int>);
	}

	if(!b_exists) {
		// add a to the map of ids
		adjacency_matrix_ids[b] = num_nodes;
		num_nodes++;
		// add a list that will store a's neighbors
		adjacency_matrix.push_back(new std::queue<int>);
	}

	// okay, now we'll just add a link between the values
	adjacency_matrix[adjacency_matrix_ids[a]] -> push(b);

	int b_id = adjacency_matrix_ids[b];
	adjacency_matrix[adjacency_matrix_ids[b]] -> push(a);

	num_equalities+=2;
}

std::unordered_map<int, int> ClusterHash::genMap() {
	std::unordered_map<int, int> result;
	int num_equalities_copy = num_equalities;
	bool found_an_element = false;
	int temp;
	// until our table is empty...
	while(num_equalities_copy > 0) {
		// find any element
		bfs_result.clear();
		found_an_element = false;
		for(int i = 0; i < adjacency_matrix.size(); i++) {
			if(!adjacency_matrix[i] -> empty()) {
				bfs_result.push_back(adjacency_matrix[i] -> front());
				found_an_element = true;
				break;
			}
		}

		// if we don't find a single element even though num_equalities > 0, something went wrong
		if(!found_an_element) {
			//std::cout << "We thought we had some equalities but we actually didn't! <cluster_hash.cc>" << std::endl;
		}
		// extract all things connected to this element and put them in bfs_result and the resulting map
		for(int i = 0; i < bfs_result.size(); i++) 
		{
			// get the list of things adjacent to the first element
			std::queue<int> *temp_queue = adjacency_matrix[adjacency_matrix_ids[bfs_result[i]]];
			// for all the things in that list...
			while(!(temp_queue -> empty())) {
				// add it to our list
				temp = temp_queue -> front();
				bfs_result.push_back(temp);
				result[temp] = bfs_result[0];
				temp_queue -> pop();
				num_equalities_copy--;
			}
		}
	}
	return result;
}

void ClusterHash::printMatrix() {
	//std::cout << std::endl << "-----------------------------------------------------" << std::endl;
	//std::cout << "matrix ids:" << std::endl;
	for(auto it = adjacency_matrix_ids.begin(); it != adjacency_matrix_ids.end(); ++it){
    	//std::cout << it -> first << " -> " << it -> second << std::endl;
    }
	//std::cout << std::endl << "matrix:" << std::endl;
	int temp;
	std::queue<int>* temp_queue;
	for(int i = 0; i < adjacency_matrix.size(); i++) {
		temp_queue = adjacency_matrix[i];
		//std::cout << i << "|";
		if(!temp_queue -> empty()) {
			temp = temp_queue -> front();
			temp_queue -> pop();
			temp_queue -> push(temp);
			//std::cout << temp;
		} else {
			//std::cout << std::endl;
			break;
		}
		for(int j = 0; j < temp_queue -> size() - 1; j++) {
			temp = temp_queue -> front();
			temp_queue -> pop();
			temp_queue -> push(temp);
			//std::cout << ", " << temp;
		}
		//std::cout << std::endl;
	}
	//std::cout << "-----------------------------------------------------" << std::endl;
	//std::cout << std::endl;
}
