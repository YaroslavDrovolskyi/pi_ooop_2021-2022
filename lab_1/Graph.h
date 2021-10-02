#pragma once

#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>
#include <cmath> // for fabs()
#include <algorithm>

double get_measure(int a) {
	return (double)abs(a);
}

double get_measure(double a) {
	return fabs(a);
}

template <typename V, typename E>
class Graph {
private:
	class Edge {
	public:
		bool is_exist;
		E edge_data;

		Edge(bool is_exist = false) {
			this->is_exist = is_exist;
		}
	};

	std::vector<std::vector<Edge>> matrix;
	std::vector<V> vertices;
	std::size_t size;

	void depth_search_impl(std::size_t start_vertex, bool* already_visited);
	void spanning_tree_impl(std::size_t start_vertex, bool* already_visited, Graph<V, E>& spanning_graph);
	std::vector<std::pair<std::size_t, std::size_t>> capture_edges();
	bool compare_edges(const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b);

//	template <typename V, typename E, typename CallVertex, typename CallEdge>
//	friend Graph<V, E> get_random_graph(std::size_t vertices_number, std::size_t edge_number, CallVertex get_rand_vertex, CallEdge get_rand_edge);

public:
	Graph();
	void add_vertex(const std::size_t index, const V& vertex_data);
	void add_edge(std::size_t start, std::size_t end, const E& edge_data);
	void remove_vertex(std::size_t index);
	void remove_edge(std::size_t start, std::size_t end);
	void change_vertice_data(std::size_t index, const V& new_data);
	void change_edge_data(std::size_t start, std::size_t end, const E& new_data);
	void print();
	Graph<V, E> spanning_tree();
	std::size_t count_components();
	Graph<V, E> min_spanning_tree();
	bool is_edge(std::size_t start, std::size_t end);
};


template <typename V, typename E>
Graph<V, E>::Graph() {
	this->size = 0;
}
template <typename V, typename E>
void Graph<V, E>::add_vertex(const std::size_t index, const V& vertex_data) {
	assert(index <= this->size);

	this->vertices.insert(this->vertices.begin() + index, V(vertex_data)); // insert vertex in structure for vertices

	this->matrix.insert(this->matrix.begin() + index, std::vector<Edge>(this->size, Edge())); // insert row

// insert column (insert cells into all rows)
for (auto& t : this->matrix) {
	t.insert(t.begin() + index, Edge());
}

this->size++;
}

template <typename V, typename E>
void Graph<V, E>::add_edge(std::size_t start, std::size_t end, const E& edge_data) {
	assert(start < this->size&& end < this->size);
	assert(!this->matrix[start][end].is_exist && !this->matrix[end][start].is_exist);

	this->matrix[start][end].is_exist = this->matrix[end][start].is_exist = true;
	this->matrix[start][end].edge_data = this->matrix[end][start].edge_data = edge_data;
}

template <typename V, typename E>
void Graph<V, E>::remove_vertex(std::size_t index) {
	assert(index < this->size);

	this->vertices.erase(this->vertices.begin() + index); // remove vertex from structure for vertices

	this->matrix.erase(this->matrix.begin() + index); // remove row

	// remove column (remove cells from all rows)
	for (auto& t : this->matrix) {
		t.erase(t.begin() + index);
	}

	this->size--;
}

template <typename V, typename E>
void Graph<V, E>::remove_edge(std::size_t start, std::size_t end) {
	assert(start < this->size&& end < this->size);
	assert(this->matrix[start][end].is_exist && this->matrix[end][start].is_exist);

	this->matrix[start][end].is_exist = this->matrix[end][start].is_exist = false; // mark this edges as not exist
}

template <typename V, typename E>
void Graph<V, E>::change_vertice_data(std::size_t index, const V& new_data) {
	assert(index < this->size);
	this->vertices[index] = new_data;
}

template <typename V, typename E>
void Graph<V, E>::change_edge_data(std::size_t start, std::size_t end, const E& new_data) {
	assert(start < this->size&& end < this->size);
	assert(this->matrix[start][end].is_exist && this->matrix[end][start].is_exist);

	this->matrix[start][end].edge_data = this->matrix[end][start].edge_data = new_data;
}

template <typename V, typename E>
void Graph<V, E>::print() {
	if (this->size == 0) {
		std::cout << "Graph is empty" << std::endl;
		return;
	}

	std::cout << "Measure of vertices:   ";
	for (auto& t : this->vertices) {
		std::cout << get_measure(t) << " ";
	}
	std::cout << "\nMatrix (measure of edges):\n";
	for (auto& row : this->matrix) {
		for (auto& edge : row) {
			if (edge.is_exist) {
				std::cout << get_measure(edge.edge_data) << "\t";
			}
			else {
				std::cout << -1 << '\t';
			}

		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

template <typename V, typename E>
void Graph<V, E>::spanning_tree_impl(std::size_t start_vertex, bool* already_visited, Graph<V, E>& spanning_graph) {
	already_visited[start_vertex] = true;
	for (std::size_t i = 0; i < this->size; i++) {
		if (this->matrix[start_vertex][i].is_exist) {
			if (!already_visited[i]) {
				assert(!spanning_graph.matrix[start_vertex][i].is_exist && !spanning_graph.matrix[i][start_vertex].is_exist);
				spanning_graph.add_edge(start_vertex, i, this->matrix[start_vertex][i].edge_data);
				spanning_tree_impl(i, already_visited, spanning_graph);
			}
		}
	}
}

template <typename V, typename E>
Graph<V, E> Graph<V, E>::spanning_tree() {
	Graph<V, E> spanning_graph; // copy to spanning graph all, except edges
	spanning_graph.size = this->size;
	spanning_graph.vertices = this->vertices;
	for (std::size_t i = 0; i < spanning_graph.size; i++) {
		spanning_graph.matrix.push_back(std::vector<Edge>(this->size, Edge()));
	}
	///
	bool* already_visited = new bool[this->size];
	for (std::size_t i = 0; i < this->size; i++) {
		already_visited[i] = false;
	}

	for (std::size_t i = 0; i < this->size; i++) { // this loop is to build spanning forest, if graph is unconnected
		if (!already_visited[i]) {
			spanning_tree_impl(i, already_visited, spanning_graph);
		}
	}


	delete[] already_visited;
	return spanning_graph;
}


template <typename V, typename E>
void Graph<V, E>::depth_search_impl(std::size_t start_vertex, bool* already_visited) {
	already_visited[start_vertex] = true;
	for (std::size_t i = 0; i < this->size; i++) {
		if (this->matrix[start_vertex][i].is_exist) {
			if (!already_visited[i]) {
				depth_search_impl(i, already_visited);
			}
		}
	}
}

template <typename V, typename E>
std::size_t Graph<V, E>::count_components() {
	bool* already_visited = new bool[this->size];
	for (std::size_t i = 0; i < this->size; i++) {
		already_visited[i] = false;
	}

	std::size_t count = 0;
	for (std::size_t i = 0; i < this->size; i++) {
		if (!already_visited[i]) {
			depth_search_impl(i, already_visited);
			count++;
		}
	}

	delete[]already_visited;
	return count;
}

template <typename V, typename E>
Graph<V, E> Graph<V, E>::min_spanning_tree() { // reverse deleted algorithm
	std::vector<std::pair<std::size_t, std::size_t>> edges = capture_edges();
	std::sort(edges.begin(), edges.end(), [this](const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b) {return compare_edges(a, b); });// sort in decreasing order

	Graph<V, E> min_spanning_tree = *this;

	std::size_t comp_number = count_components();
	for (std::size_t i = 0; i < edges.size(); i++) {
		std::size_t begin = edges[i].first;
		std::size_t end = edges[i].second;
		min_spanning_tree.matrix[begin][end].is_exist = min_spanning_tree.matrix[end][begin].is_exist = false;
		if (comp_number != min_spanning_tree.count_components()) {
			min_spanning_tree.matrix[begin][end].is_exist = min_spanning_tree.matrix[end][begin].is_exist = true;
		}
	}

	return min_spanning_tree;
}

template <typename V, typename E>
std::vector<std::pair<std::size_t, std::size_t>> Graph<V, E>::capture_edges() {
	std::vector<std::pair<std::size_t, std::size_t>> edges;
	for (std::size_t i = 0; i < this->size; i++) {
		for (std::size_t j = i; j < this->size; j++) {
			if (this->matrix[i][j].is_exist) {
				edges.push_back(std::make_pair(i, j));
			}
		}
	}

	return edges;
}

template <typename V, typename E>
bool Graph<V, E>::compare_edges(const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b) {
	return get_measure(this->matrix[a.first][a.second].edge_data) > get_measure(this->matrix[b.first][b.second].edge_data);
}

template <typename V, typename E>
bool Graph<V, E>::is_edge(std::size_t begin, std::size_t end) {
	assert(this->matrix[begin][end].is_exist == this->matrix[end][begin].is_exist);
	return this->matrix[begin][end].is_exist;
}


// using the breadth search
/*
void spanning_tree_impl(std::size_t start_vertex, bool* already_visited, Graph& spanning_graph) {
	ArrayQueue<std::size_t> to_visit;
	to_visit.push(start_vertex);
	already_visited[start_vertex] = true;

	while (!to_visit.is_empty()) {
		std::size_t current_vertex = to_visit.pop();

		for (std::size_t j = 0; j < this->size; j++) {
			if (this->matrix[current_vertex][j].is_exist) {
				if (already_visited[j] == false) {
					to_visit.push(j);
					already_visited[j] = true;

					assert(!spanning_graph[current_vertex][j].is_exist && !spanning_graph[j][current_vertex].is_exist);
					spanning_graph.add_edge(current_vertex, j, this->matrix[current_vertex][j].edge_data);
				}
			}

		}
	}
}
*/






#endif // _GRAPH_
