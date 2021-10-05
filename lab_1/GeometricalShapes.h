#pragma once


#ifndef _GEOMETRICAL_SHAPES_
#define _GEOMETRICAL_SHAPES_


#include <cassert>
#include <vector>
#include <cmath>

struct Point {
	double x;
	double y;

	Point() {
		this->x = 0;
		this->y = 0;
	}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

std::ostream& operator<< (std::ostream& out, const Point& point) {
	out << "(" << point.x << ", " << point.y << ")";
	return out;
}

bool compare(const Point& a, const Point& b) {
	if (a.x < b.x) {
		return true;
	}
	else if (a.x == b.x) {
		return a.y < b.y;
	}
	else {
		return false;
	}
}

class Circle {
private:
	Point centre;
	double radius;


	friend std::ostream& operator<< (std::ostream& out, const Circle& circle);

public:
	Circle(const Point& centre, double radius);
	Point get_centre();
	double get_radius();
	void set_centre(const Point& centre);
	void set_radius(double radius);

};

std::ostream& operator<< (std::ostream& out, const Circle& circle) {
	out << "(x - " << circle.centre.x << ")^2 + " << "(y - " << circle.centre.y << ")^2 = " << circle.radius << "^2";

	return out;
}

Circle::Circle(const Point& centre, double radius) {
	assert(radius > 0 && "radius must be  > 0");
	this->centre = centre;
	this->radius = radius;
}

void Circle::set_centre(const Point& centre) {
	this->centre = centre;
}

void Circle::set_radius(double radius) {
	assert(radius > 0 && "radius must be  > 0");
	this->radius = radius;
}

Point Circle::get_centre() {
	return this->centre;
}

double Circle::get_radius() {
	return this->radius;
}


class Line {
private:
	double a;
	double b;
	double c;

	friend std::ostream& operator<< (std::ostream& out, const Line& line);

public:
	Line(double a = 1, double b = 1, double c = 1);
	double get_a();
	double get_b();
	double get_c();
};

Line::Line(double a, double b, double c) {
	assert(a != 0 || b != 0);
	this->a = a;
	this->b = b;
	this->c = c;
}

double Line::get_a() {
	return this->a;
}

double Line::get_b() {
	return this->b;
}

double Line::get_c() {
	return this->c;
}

std::ostream& operator<< (std::ostream& out, const Line& line) {
	out << line.a << "x + " << line.b << "y + " << line.c << " = 0";

	return out;
}

std::vector<Point> solve_equation_system(double a1, double b1, double c1, double a2, double b2, double c2, bool& is_inf_solutions) {
	is_inf_solutions = false;
	std::vector<Point> result;
	double main_determinant = a1 * b2 - a2 * b1;
	if (main_determinant == 0) {
		if (b2 != 0 && c2 != 0 && c1 / c2 == b1 / b2) { // check if this two lines overlap
			is_inf_solutions = true;
			return result;
		}
	}
	else { // Cramer's method
		double first_determinant = c1 * b2 - c2 * b1;
		double second_determinant = a1 * c2 - a2 * c1;

		double x = first_determinant / main_determinant;
		double y = second_determinant / main_determinant;

		result.push_back(Point(x, y));
	}
	return result; // if not solution, then retur empty vector
}

std::pair<bool, std::vector<Point>>Intersection(Line& line1, Line& line2) {
	bool is_inf_solutions = false;
	std::vector<Point> solutions = solve_equation_system(line1.get_a(), line1.get_b(), (-1) * line1.get_c(), line2.get_a(), line2.get_b(), (-1) * line2.get_c(), is_inf_solutions);
	std::sort(solutions.begin(), solutions.end(), compare);
	return std::make_pair(is_inf_solutions, solutions);
}

std::vector<double> solve_quadratic_equation(double a, double b, double c) {
	assert(a != 0);
	std::vector<double> result;
	double discriminant = b * b - 4 * a * c;
	if (discriminant == 0) {
		result.push_back(((-1) * b + sqrt(discriminant)) / (2 * a));
	}
	else if (discriminant > 0) {
		result.push_back(((-1) * b + sqrt(discriminant)) / (2 * a));
		result.push_back(((-1) * b - sqrt(discriminant)) / (2 * a));
	}

	return result;
}


std::vector<Point>Intersection(Circle& circle, Line& line) {
	double a = line.get_a();
	double b = line.get_b();
	double c = line.get_c();
	double r = circle.get_radius();
	double x0 = circle.get_centre().x;
	double y0 = circle.get_centre().y;

	std::vector<Point>result;

	if (b == 0) {
		std::vector<double>equation_solutions = solve_quadratic_equation(1, (-2) * y0, pow((c / a + x0), 2) + y0 * y0 - r * r);
		double x = (-1) * c / a; // x coordinate of intersection points (if they exist)
		for (double solution : equation_solutions) {
			result.push_back(Point(x, solution));
		}
	}
	else {
		// form coefficients for quadratic equation
		double A = 1 + (a / b) * (a / b);
		double B = (2 * a * c + 2 * a * y0 * b - 2 * x0 * b * b) / (b * b);
		double C = x0 * x0 + y0 * y0 + (c / b) * (c / b) + (2 * c * y0) / b - r * r;

		std::vector<double>equation_solutions = solve_quadratic_equation(A,B,C);

		for (double solution : equation_solutions) {
			double x = solution;
			double y = (-1) * ((a * x) / b + c / b);
			result.push_back(Point(x, y));
		}
	}

	std::sort(result.begin(), result.end(), compare);
	return result;
}



Line get_perpendicular_line(Line& line, Point& pivot_point) {
	double a = line.get_a();
	double b = line.get_b();
	double c = line.get_c();

	double new_a = (-1) * b;
	double new_b = a;
	double new_c = (-1) * new_a * pivot_point.x - new_b * pivot_point.y;

	return Line(new_a, new_b, new_c);
}












#endif _GEOMETRICAL_SHAPES_
