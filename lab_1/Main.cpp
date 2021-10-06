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

void demonstrate_queue();
void demonstrate_stack();
void demonstrate_deque();
void demonstrate_priority_queue();
void demonstrate_graph();
void demonstrate_geometry();

int main() {
	std::cout << "Hello!!!\n";

	std::cout << "\n\n\nTASK 1.3:";
	demonstrate_queue();
	demonstrate_stack();
	demonstrate_deque();

	std::cout << "\n\n\nTASK 1.5:";
	demonstrate_priority_queue();
	
	std::cout << "\n\n\nTASK 1.8 + 1.8.1:";
	demonstrate_graph();

	std::cout << "\n\n\nTASK 2.2:";
	demonstrate_geometry();

	return 0;
}

void demonstrate_queue() {
	std::cout << "\n\n\n==========   QUEUE   ==========\n\n";
	std::cout << "Result of tests on INT:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "\nResult of tests on DOUBLE:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<double>, double>([]() { return get_random_double(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<double>, double>([]() { return get_random_double(); }) << std::endl;

	std::cout << "\nResult of tests on STD::STRING:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;

	std::cout << "\nResult of tests on STD::VECTOR:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;

	std::cout << "\nResult of tests on CIRCLE:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;

	std::cout << "\nResult of tests on LINE:\n";
	std::cout << "TestQueue (array): " << TestQueue<ArrayQueue<Line>, Line>([]() { return get_random_line(); }) << std::endl;
	std::cout << "TestQueue (linked): " << TestQueue<LinkedQueue<Line>, Line>([]() { return get_random_line(); }) << std::endl;
}

void demonstrate_stack() {
	std::cout << "\n\n\n==========   STACK   ==========\n\n";
	std::cout << "Result of tests on INT:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "\nResult of tests on DOUBLE:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<double>, double>([]() { return get_random_double(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<double>, double>([]() { return get_random_double(); }) << std::endl;

	std::cout << "\nResult of tests on STD::STRING:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;

	std::cout << "\nResult of tests on STD::VECTOR:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;

	std::cout << "\nResult of tests on CIRCLE:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;

	std::cout << "\nResult of tests on LINE:\n";
	std::cout << "TestStack (array): " << TestStack<ArrayStack<Line>, Line>([]() { return get_random_line(); }) << std::endl;
	std::cout << "TestStack (linked): " << TestStack<LinkedStack<Line>, Line>([]() { return get_random_line(); }) << std::endl;
}

void demonstrate_deque() {
	std::cout << "\n\n\n==========   DEQUE   ==========\n\n";
	std::cout << "Result of tests on INT:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "\nResult of tests on DOUBLE:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<double>, double>([]() { return get_random_double(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<double>, double>([]() { return get_random_double(); }) << std::endl;

	std::cout << "\nResult of tests on STD::STRING:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;

	std::cout << "\nResult of tests on STD::VECTOR:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;

	std::cout << "\nResult of tests on CIRCLE:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;

	std::cout << "\nResult of tests on LINE:\n";
	std::cout << "TestDeque (array): " << TestDeque<ArrayDeque<Line>, Line>([]() { return get_random_line(); }) << std::endl;
	std::cout << "TestDeque (linked): " << TestDeque<LinkedDeque<Line>, Line>([]() { return get_random_line(); }) << std::endl;
}

void demonstrate_priority_queue() {
	std::cout << "\n\n\n==========   PRIORITY QUEUE   ==========\n\n";
	std::cout << "Result of tests on INT:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<int>, int>([]() { return get_random_int(); }) << std::endl;

	std::cout << "\nResult of tests on DOUBLE:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<double>, double>([]() { return get_random_double(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<double>, double>([]() { return get_random_double(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<double>, double>([]() { return get_random_double(); }) << std::endl;

	std::cout << "\nResult of tests on STD::STRING:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<std::string>, std::string>([]() { return get_random_string(); }) << std::endl;

	std::cout << "\nResult of tests on STD::VECTOR:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<std::vector<int>>, std::vector<int>>([]() { return get_random_vector(); }) << std::endl;

	std::cout << "\nResult of tests on CIRCLE:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<Circle>, Circle>([]() { return get_random_circle(); }) << std::endl;

	std::cout << "\nResult of tests on LINE:\n";
	std::cout << "TestPriorityQueue (array): " << TestPriorityQueue<ArrayPriorityQueue<Line>, Line>([]() { return get_random_line(); }) << std::endl;
	std::cout << "TestPriorityQueue (linked): " << TestPriorityQueue<LinkedPriorityQueue<Line>, Line>([]() { return get_random_line(); }) << std::endl;
	std::cout << "TestPriorityQueue (tree): " << TestPriorityQueue<TreePriorityQueue<Line>, Line>([]() { return get_random_line(); }) << std::endl;
}

void demonstrate_graph() {
	std::cout << "\n\n\n==========   GRAPH   ==========\n\n";
	std::cout << "Generate random graph:\n";
	Graph<int, int> graph = get_random_graph<int, int>(8, 18, []() {return get_random_int(); }, []() {return get_random_int(); });
	graph.print();

	std::cout << "\n\nAdd vertices and some edges:\n\n";
	graph.add_vertex(8, 5);
	graph.add_vertex(9, 100);

	graph.add_edge(1, 8, 2343);
	graph.add_edge(6, 8, 678);
	graph.add_edge(8, 9, 4634);
	graph.print();

	std::cout << "\n\nChange some data of vertices and edges:\n\n";
	graph.change_vertice_data(8, 10);
	graph.change_vertice_data(9, 12);
	graph.change_edge_data(1, 8, 600);
	graph.change_edge_data(8, 9, 1000);
	graph.print();

	std::cout << "\n\nRemove some edges and vertices:\n\n";
	graph.remove_edge(1, 8);
	graph.remove_edge(8, 9);
	graph.remove_vertex(9);
	graph.remove_vertex(8);
	graph.print();

	 //spanning trees
	std::cout << "\n\nSpanning forest:\n";
	graph.spanning_tree().print();

	std::cout << "\n\nMin spanning forest:\n";
	graph.min_spanning_tree().print();
}

void demonstrate_geometry() {
	std::cout << "\n\n\n==========   GEOMETRY SHAPES   ==========\n\n";
	std::cout << "\n\nGenerate random points, lines and circles:\n";
	Point point1 = get_random_point();
	Point point2 = get_random_point();
	Line line1 = get_random_line();
	Line line2 = get_random_line();
	Circle circle1 = get_random_circle();
	Circle circle2 = get_random_circle();
	std::cout << point1 << ",   " << point2 << "\n" << line1 << ",   " << line2 << "\n" << circle1 << ",   " << circle2 << "\n\n";

	std::cout << "Intersection of " << line1 << " and " << line2 << ":   ";
	std::pair<bool, std::vector <Point>> result1 = Intersection(line1, line2);
	if (result1.first) {
		std::cout << "this lines are overlap\n";
	}
	else if (result1.second.size() == 0) {
		std::cout << "no intersection\n";
	}
	else {
			for (auto& point : result1.second) {
				std::cout << point << "  ";
			}
			std::cout << std::endl;
	}

	
	std::cout << "\n\nIntersection of " << line1 << " and " << circle1 << ":   ";
	std::vector <Point> result2 = Intersection(circle1, line1);

	if (result2.size() == 0) {
		std::cout << "no intersection\n";
	}
	else {
		for (auto& point : result2) {
			std::cout << point << "  ";
		}
		std::cout << std::endl;
	}

	std::cout << "Intersect of two circles: " << circle1 << " and " << circle2 << ":   ";
		
	
	std::pair<bool, std::vector <Point>> result3 = Intersection(circle1, circle2);
	if (result3.first) {
		std::cout << "this circles are overlap\n";
	}
	else if (result3.second.size() == 0) {
		std::cout << "no intersection\n";
	}
	else {
		for (auto& point : result3.second) {
			std::cout << point << "   ";
		}
		std::cout << std::endl;
	}

	std::cout << "\n\nPerpendicular line equation to " << line2 << " via " << point1 << ":   ";
	std::cout << get_perpendicular_line(line2, point1);

	std::cout << "\n\nProjection " << point2 << " on " << line2 << ":   ";
	std::cout << get_projection_on_line(line2, point2);

	std::cout << "\n\nDistance between " << point1 << " and " << point2 << ":   ";
	std::cout << get_distance(point1, point2);

	std::cout << "\n\nChose 3 different point from line " << line1 << ":   ";
	std::vector<Point> result4 = chose_points(line1, 3);
	std::cout << result4[0] << " " << result4[1] << " " << result4[2] << std::endl;

	std::cout << "\n\nBuild line by two points:\n";
	Point p1(32, 56);
	Point p2(83, 101);
	std::cout << "line by " << p1 << " and " << p2 << ":   " << build_line(p1, p2);

	std::cout << "\n\n\nSymmetric:\n";
	std::cout << point2 << " symmetric via " << line2 << ":   " << get_reflection_by_line(line2, point2) << std::endl;
	std::cout << line1 << " symmetric via " << line2 << ":   " << get_reflection_by_line(line2, line1) << std::endl;
	std::cout << circle1 << " symmetric via " << line2 << ":   " << get_reflection_by_line(line2, circle1) << std::endl;

	std::cout << "\n\n\nInversion:\n";
	std::cout << "Invert " << point1 << " by " << circle1 << ":   " << Inversion(circle1, p1) << std::endl;
	std::cout << "Invert " << line1 << " by " << circle1 << ":   " << Inversion(circle1, line1) << std::endl;
		
}