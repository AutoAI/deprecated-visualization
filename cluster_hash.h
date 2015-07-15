// cluster_hash.h

#pragma once

#include <unordered_map>
#include <vector>
#include <queue>

class ClusterHash {
public:
	ClusterHash();
	void addEquality(int a, int b);
	std::unordered_map<int, int> genMap();

private:
	std::vector<std::queue<int>*> adjacency_matrix;
	std::unordered_map<int, int> adjacency_matrix_ids;
	std::vector<int> bfs_result;
	int num_equalities;
	int num_nodes;

	void printMatrix();
};