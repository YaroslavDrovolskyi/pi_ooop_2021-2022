#include <iostream>
#include <vector>

#include "ArrayStack.h"
#include "LinkedStack.h"

#include "ArrayQueue.h"
#include "LinkedQueue.h"

#include "ArrayDeque.h"
#include"LinkedDeque.h"

#include "ArrayPriorityQueue.h"
#include "LinkedPriorityQueue.h"
#include "TreePriorityQueue.h"

#include "Graph.h"

#include"Tests.h"




int main() {
	/*
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "TestStack (array): " << TestStack<ArrayStack<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	*/

	ArrayQueue<int> st = get_random_queue<ArrayQueue<int>>(10, []() {return get_random_int(); });
	st.print();


	/*
	Graph<double, double> graph1;
	graph1.print();
	graph1.add_vertex(0, 5);
	graph1.add_vertex(1, 10);
	graph1.add_vertex(2, 15);
	graph1.add_vertex(1, 150);
	graph1.add_vertex(2, 100);

	graph1.add_edge(1, 0, -15.6);
	graph1.add_edge(2, 3, 100.1);
	graph1.add_edge(1, 4, 60.1);
	graph1.add_edge(3, 4, 1000);
	graph1.add_edge(1, 3, 59);

	graph1.print();
	*/

	/*
	graph1.add_edge(1, 0, -15.6);
	graph1.add_edge(2, 3, 100.1);
	graph1.add_edge(1, 4, 60.1);
	graph1.print();

	graph1.remove_edge(0, 1);
	graph1.print();

	graph1.remove_vertex(0);
	graph1.print();

	graph1.remove_vertex(1);
	graph1.print();

	graph1.add_edge(1, 0, -15.6);
	graph1.add_edge(2, 3, 100.1);
	graph1.add_edge(1, 4, 60.1);
	graph1.add_vertex(0, 63);
	graph1.print();
	*/

	/* spanning trees
	std::cout << "\n\n\nSpanning tree:\n";
	Graph<double, double> spanning_graph = graph1.spanning_tree();
	spanning_graph.print();

	std::cout << "\n\n\nMin spanning tree:\n";
	Graph<double, double> min_spanning_graph = graph1.min_spanning_tree();
	min_spanning_graph.print();

	std::cout << "\n\n\nRandom generate graph: \n";
	Graph<int, int> graph2 = get_random_graph<int, int>(8, 18, []() {return generate_random(); }, []() {return generate_random(); });
	graph2.print();
	std::cout << "\n\n\nSpanning tree:\n";
	graph2.spanning_tree().print();
	std::cout << "\n\n\nMin spanning tree:\n";
	graph2.min_spanning_tree().print();
	*/
	return 0;
}

