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

#include "GeometricalShapes.h"


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

//	ArrayQueue<int> st = get_random_queue<ArrayQueue<int>>(10, []() {return get_random_int(); });
//	st.print();

//	LinkedPriorityQueue<int>q = get_random_priority_queue<LinkedPriorityQueue<int>>(10, []() {return get_random_int(); });
//	q.print();

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

	/*
	std::cout << "Geometry shapes:\n";
	Line line1(5, 6, 7);
	Line line2(10, 12, 14);

	std::cout << line1 << std::endl << line2 << std::endl;
	std::pair<bool, std::vector <Point>> result = Intersection(line1, line2);
	if (result.first) {
		std::cout << "This lines are overlap\n";
	}
	else if (result.second.size() == 0) {
		std::cout << "No intersection\n";
	}
	else {
		std::cout << "intersection:\n";
			for (auto& point : result.second) {
				std::cout << point << std::endl;
			}
	}
	*/

	std::cout << "Geometry shapes:\n";
	Line line1(0, 1, -1);
	Circle circle1(Point(0, 0), 1);

	std::cout << line1 << std::endl << circle1 << std::endl;
	std::vector <Point> result = Intersection(circle1, line1);

	if (result.size() == 0) {
		std::cout << "No intersection\n";
	}
	else {
		std::cout << "intersection:\n";
		for (auto& point : result) {
			std::cout << point << std::endl;
		}
	}

	std::cout << "\n\n\nPerpendicualr line:\n";
	Point p1(1, 1);
	Line line2(5, 10, 12);
	std::cout << "Perpendicular to " << line2 << " via " << p1 << ":\n";
	std::cout << get_perpendicular_line(line2, p1) << std::endl << std::endl << std::endl;

	std::cout << "Projection " << p1 << " on " << line2 << ":\n";
	std::cout << get_projection_on_line(line2, p1);


	std::cout << "\n\n\nSymmetric:\n";
	std::cout << p1 << " symmetric via " << line2 << " = " << get_reflection_by_line(line2, p1) << std::endl;

	std::cout << "\n\n\nBuild line:\n";
	Point p2(32, 56);
	Point p3(83, 101);
	std::cout << "line via " << p2 << " " << p3 << " = " << build_line(p2, p3);

	/*
	std::cout << "\n\n\nSymmetric:\n";
	for (std::size_t i = 0; i < 15; i++) {
		Line l1(rand() % 50, rand() % 50, rand() % 50), l2(rand() % 50, rand() % 50, rand() % 50);
		std::cout << "(" << l1 << ") symmetric via (" << l2 << ") : (" << get_reflection_by_line(l2, l1) << ")" << std::endl;
	}
	*/

	/*
	std::cout << "\n\n\nSymmetric:\n";
	Line l1(1, 1, 0), l2(-1, 1, 0);
	std::cout << "(" << l1 << ") symmetric via (" << l2 << ") : (" << get_reflection_by_line(l2, l1) << ")" << std::endl;
	*/

	/*
	std::cout << "\n\n\nSymmetric:\n";
	for (std::size_t i = 0; i < 15; i++) {
		Circle c1(Point(rand() % 50, rand() % 50), rand() % 50);
		Line l2(rand() % 50, rand() % 50, rand() % 50);
		std::cout << "(" << c1 << ") symmetric via (" << l2 << ") : (" << get_reflection_by_line(l2, c1) << ")" << std::endl;
	}
	*/

	
	Circle c1(Point(0 ,0), rand() % 50);
	Line l2(1, 1, 0);
	std::cout << "\n\n\n(" << c1 << ") symmetric via (" << l2 << ") : (" << get_reflection_by_line(l2, c1) << ")" << std::endl;
	

	return 0;
}

