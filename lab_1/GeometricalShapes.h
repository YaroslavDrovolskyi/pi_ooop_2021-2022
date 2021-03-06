#pragma once


#ifndef _GEOMETRICAL_SHAPES_
#define _GEOMETRICAL_SHAPES_


#include <cassert>
#include <vector>
#include <cmath>
#include <limits>



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

double get_measure(Point& point) {
	return point.x + point.y;
}

Point get_random_point() {
	return Point(rand() % 50, rand() % 50);
}

std::ostream& operator<< (std::ostream& out, const Point& point) {
	out << "(";
	if (point.x == std::numeric_limits<double>::infinity()) {
		out << "infinity";
	}
	else {
		out << point.x;
	}
	out << ", ";
	if (point.y == std::numeric_limits<double>::infinity()) {
		out << "infinity";
	}
	else {
		out << point.y;
	}
		
	out << ")";
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
	friend bool operator==(const Circle& a, const Circle& b);

public:
	Circle();
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

Circle::Circle() {
	this->centre = Point(0, 0);
	this->radius = 1;
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

double get_measure(Circle& c) {
	return std::pow(c.get_radius(), 2) * 3.14; // square of circle
}

Circle get_random_circle() {
	return Circle(get_random_point(), rand() % 25 + 1);
}

class Line {
private:
	double a;
	double b;
	double c;

	friend std::ostream& operator<< (std::ostream& out, const Line& line);
	friend bool operator==(const Line& x, const Line& y);
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

double get_measure(Line& line) {
	return line.get_a() + line.get_b() + line.get_c();
}

Line get_random_line() {
	return Line(rand() % 50 + 1, rand() % 50 + 1, rand() % 50);
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


std::pair<bool, std::vector<Point>>Intersection(Circle& circle1, Circle& circle2) {
	bool is_inf_solutions = false;
	std::vector<Point>intersect_points;
	double x1 = circle1.get_centre().x;
	double y1 = circle1.get_centre().y;
	double x2 = circle2.get_centre().x;
	double y2 = circle2.get_centre().y;
	double r1 = circle1.get_radius();
	double r2 = circle2.get_radius();
	if (x1 == x2 && y1 == y2) {
		if (r1 == r2) {
			is_inf_solutions = true;
		}
	}
	else {
		// algorithm: https://e-maxx.ru/algo/circles_intersection
		double A = 2 * (x1 - x2); // form coefficients for line equation (after substitution)
		double B = 2 * (y1 - y2);
		double C = std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2) + r1 * r1 - r2 * r2;

		Circle c(Point(0, 0), r1);
		Line l(A, B, C);
		std::vector<Point> points = Intersection(c, l);
		for (Point& point : points) { // go back from sustitution
			point.x += x1;
			point.y += y1;
		}
		intersect_points = points;
	}
	return std::make_pair(is_inf_solutions, intersect_points);
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


Point get_projection_on_line(Line& line, Point& point) {
	Line perpendicular = get_perpendicular_line(line, point);
	std::pair<bool, std::vector<Point>> intersection = Intersection(line, perpendicular);
	assert(!intersection.first); // lines musn't be overlapped
	assert(intersection.second.size() == 1);
	Point projection = intersection.second[0];

	return projection;
}


Point get_reflection_by_line(Line& pivot_line, Point& point) {
	Point middle = get_projection_on_line(pivot_line, point);
	double new_point_x = 2 * middle.x - point.x;
	double new_point_y = 2 * middle.y - point.y;

	Point new_point(new_point_x, new_point_y);
	return new_point;
}

Line build_line(Point& p1, Point& p2) {
	assert(p1.x != p2.x || p1.y != p2.y && "Impossible to build a line by one point");

	double a = p1.y - p2.y;
	double b = p2.x - p1.x;
	double c = p1.x * p2.y - p2.x * p1.y;

	return Line(a, b, c);
}

std::vector<Point> chose_points(Line& line, std::size_t count) {
	assert(count > 0);

	std::vector<Point> result;

	double a = line.get_a();
	double b = line.get_b();
	double c = line.get_c();

	if (b == 0) {
		double x = (-1) * c / a;
		for (std::size_t i = 0; i < count; i++) {
			double y = i;
			result.push_back(Point(x, y));
		}
	}
	else {
		for (std::size_t i = 0; i < count; i++) {
			double x = i;
			double y = (-1) * (a * x / b) - (c / b);
			result.push_back(Point(x, y));
		}
	}
	

	return result;
}

Line get_reflection_by_line(Line& pivot_line, Line& line) {
	std::vector<Point> points_on_line = chose_points(line, 2);
	assert(points_on_line.size() == 2);
	for (Point& point : points_on_line) {
		point = get_reflection_by_line(pivot_line, point);
	}
	return build_line(points_on_line[0], points_on_line[1]);
}

Circle get_reflection_by_line(Line& pivot_line, Circle& circle) {
	Point center = circle.get_centre();
	double radius = circle.get_radius();
	Point new_center = get_reflection_by_line(pivot_line, center);

	return Circle(new_center, radius);
}



Point Inversion(Circle& pivot_circle, Point& point) {
	double x = point.x;
	double y = point.y;
	double x0 = pivot_circle.get_centre().x;
	double y0 = pivot_circle.get_centre().y;
	double r = pivot_circle.get_radius();

	if (point.x == pivot_circle.get_centre().x && point.y == pivot_circle.get_centre().y) {
		return Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	}
	else if (x == std::numeric_limits<double>::infinity() && y == std::numeric_limits<double>::infinity()) {
		return pivot_circle.get_centre();
	}
	else {
		double new_x = x0 + (r * r * (x - x0)) / (std::pow(x - x0, 2) + std::pow(y - y0, 2));
		double new_y = y0 + (r * r * (y - y0)) / (std::pow(x - x0, 2) + std::pow(y - y0, 2));

		return Point(new_x, new_y);
	}
}

double get_distance(Point& a, Point& b) {
	return sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

class GeometricalShape {
private:
	std::size_t id; // 0 - circle, 1 - line
	Circle circle;
	Line line;

	friend std::ostream& operator<< (std::ostream& out, const GeometricalShape& shape);
public:
	GeometricalShape(const Circle& circle) {
		this->circle = circle;
		this->id = 0;
	}

	GeometricalShape(const Line& line) {
		this->line = line;
		this->id = 1;
	}

	Circle get_circle() {
		assert(this->id == 0);
		return this->circle;
	}

	Line get_line() {
		assert(this->id == 1);
		return this->line;
	}

	std::size_t what_shape() {
		return this->id;
	}
};

std::ostream& operator<< (std::ostream& out, const GeometricalShape& shape) {
	if (shape.id == 0) {
		out << shape.circle;
	}
	else if (shape.id == 1) {
		out << shape.line;
	}

	return out;
}

GeometricalShape Inversion(Circle& pivot_circle, Line& line) {
	double x0 = pivot_circle.get_centre().x;
	double y0 = pivot_circle.get_centre().y;

	if ((line.get_a() * x0 + line.get_b() * y0 + line.get_c()) == 0) { // if lcenter of circle is on ine 
		return line;
	}
	else {
		Point pivot_center = pivot_circle.get_centre();;
		Point projection = get_projection_on_line(line, pivot_center);
		projection = Inversion(pivot_circle, projection);

		double new_center_x = (pivot_center.x + projection.x) / 2;
		double new_center_y = (pivot_center.y + projection.y) / 2;
		double new_radius = get_distance(pivot_center, projection) / 2;

		return GeometricalShape(Circle(Point(new_center_x, new_center_y), new_radius));
	}
}

bool operator==(const Point& a, const Point& b) {
	return (a.x == b.x) && (a.y == b.y);
}

bool operator==(const Line& x, const Line& y) {
	return (x.a == y.a) && (x.b == y.b) && (x.c == y.c);
}

bool operator==(const Circle& a, const Circle& b) {
	return (a.centre == b.centre) && (a.radius == b.radius);
}






#endif _GEOMETRICAL_SHAPES_
