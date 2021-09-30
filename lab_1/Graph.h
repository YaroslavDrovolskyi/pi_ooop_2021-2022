#pragma once

#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>
#include <cmath> // for fabs()

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


public:
	Graph();
	void add_vertex(const std::size_t index, const V& vertex_data);
	void add_edge(std::size_t start, std::size_t end, const E& edge_data);
	void remove_vertex(std::size_t index);
	void remove_edge(std::size_t start, std::size_t end);
	void change_vertice_data(std::size_t index, const V& new_data);
	void change_edge_data(std::size_t start, std::size_t end, const E& new_data);
	void print();
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
	assert(start < this->size && end < this->size);
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
	assert(start < this->size && end < this->size);
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






#endif // _GRAPH_
