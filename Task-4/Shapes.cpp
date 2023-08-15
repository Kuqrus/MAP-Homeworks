#include "Shapes.h"

std::vector<int> Shape::GetX() { return x; }
std::vector<int> Shape::GetY() { return y; }
std::vector<int> Shape::GetZ() { return z; }

void Shape::SetVolume(double V) { volume = V; }
void Shape::SetSquare(double S) { square = S; }
void Shape::SetHeight(double H) { height = H; }
void Shape::SetRadius(double R) { radius = R; }

void Shape::Shift(int _x, int _y, int _z)
{
	std::for_each(x.begin(), x.end(), [&](int& x) {
		x += _x;
		});
	std::for_each(y.begin(), y.end(), [&](int& y) {
		y += _y;
		});
	std::for_each(z.begin(), z.end(), [&](int& z) {
		z += _z;
		});
}

void Shape::Scale(int s)
{
	std::for_each(x.begin(), x.end(), [&](int& x) {
		x /= s;
		});
	std::for_each(y.begin(), y.end(), [&](int& y) {
		y /= s;
		});
	std::for_each(z.begin(), z.end(), [&](int& z) {
		z /= s;
		});
}

void Shape::RoundScale(double R, double H)
{
	radius /= R;
	if (H > 0) {
		height /= H;
	}
}

void Shape::ScaleX(int _x) {
	std::for_each(x.begin(), x.end(), [&](int& i) {
		i *= _x;
		});
};
void Shape::ScaleY(int _y) {
	std::for_each(y.begin(), y.end(), [&](int& i) {
		i *= _y;
		});
};
void Shape::ScaleZ(int _z) {
	std::for_each(z.begin(), z.end(), [&](int& i) {
		i *= _z;
		});
};

Shape::Shape(std::vector<int> _x, std::vector<int> _y) : x{ _x }, y{ _y } {};
Shape::Shape(std::vector<int> _x, std::vector<int> _y, std::vector<int> _z) : x{ _x }, y{ _y }, z{ _z } {};

Shape::Shape(int _x, int _y, double R) : radius{ R } {
	x.push_back(_x);
	y.push_back(_y);
};
Shape::Shape(int _x, int _y, double H, double R) : height{ H }, radius{ R } {
	x.push_back(_x);
	y.push_back(_y);
};

double Shape::GetVolume() { return volume; }
double Shape::GetSquare() { return square; }
double Shape::GetHeight() { return height; }
double Shape::GetRadius() { return radius; }



void Line::SetScale() {
	std::vector<int> x = Shape::GetX();
	std::vector<int> y = Shape::GetY();

	int a = abs(x[0] - x[1]);
	int b = abs(y[0] - y[1]);

	Shape::SetSquare(0);
	Shape::SetVolume(0);
}
Line::Line(std::vector<int> _x, std::vector<int> _y) : Shape(_x, _y) {
	SetScale();
}
void Line::Shift(int _x, int _y) {
	Shape::Shift(_x, _y, 0);
}
void Line::Scale(int x) {
	Shape::Scale(x);
	SetScale();
}
void Line::ScaleX(int x) {
	Shape::ScaleX(x);
	SetScale();
}
void Line::ScaleY(int y) {
	Shape::ScaleY(y);
	SetScale();
}



void Square::SetScale() {
	std::vector<int> x = Shape::GetX();
	std::vector<int> y = Shape::GetY();

	int a = abs(x[0] - x[1]);
	int b = abs(y[0] - y[1]);

	Shape::SetSquare(a * b);
	Shape::SetVolume(0);
}
Square::Square(std::vector<int> _x, std::vector<int> _y) : Shape(_x, _y) {
	SetScale();
}
void Square::Shift(int _x, int _y) {
	Shape::Shift(_x, _y, 0);
}
void Square::Scale(int x) {
	Shape::Scale(x);
	SetScale();
}
void Square::ScaleX(int x) {
	Shape::ScaleX(x);
	SetScale();
}
void Square::ScaleY(int y) {
	Shape::ScaleY(y);
	SetScale();
}



void Cube::SetScale() {
	std::vector<int> x = Shape::GetX();
	std::vector<int> y = Shape::GetY();
	std::vector<int> z = Shape::GetZ();

	int a = abs(x[0] - x[1]);
	int b = abs(y[0] - y[1]);
	int c = abs(z[0] - z[1]);

	Shape::SetSquare(2 * a * b + 2 * a * c + 2 * b * c);
	Shape::SetVolume(a * b * c);
}
Cube::Cube(std::vector<int> _x, std::vector<int> _y, std::vector<int> _z) : Shape(_x, _y, _z) {
	SetScale();
}
void Cube::Shift(int _x, int _y, int _z) {
	Shape::Shift(_x, _y, _z);
}
void Cube::Scale(int x) {
	Shape::Scale(x);
	SetScale();
}
void Cube::ScaleX(int x) {
	Shape::ScaleX(x);
	SetScale();
}
void Cube::ScaleY(int y) {
	Shape::ScaleY(y);
	SetScale();
}
void Cube::ScaleZ(int z) {
	Shape::ScaleZ(z);
	SetScale();
}



void Circle::SetScale() {
	double R = Shape::GetRadius();
	Shape::SetSquare(M_PI * R * R);
	Shape::SetVolume(0);
}
Circle::Circle(int _x, int _y, double R) : Shape(_x, _y, R) {
	SetScale();
}
void Circle::Shift(int _x, int _y) {
	Shape::Shift(_x, _y, 0);
}
void Circle::Scale(double R) {
	Shape::RoundScale(R, 0);
	SetScale();
}



void Culinder::SetScale() {
	double R = Shape::GetRadius();
	double H = Shape::GetHeight();
	double S = M_PI * R * R + 2 * R * H;
	double V = M_PI * R * R * H;

	Shape::SetSquare(S);
	Shape::SetVolume(V);
}
Culinder::Culinder(int _x, int _y, double H, double R) : Shape(_x, _y, H, R) {
	SetScale();
}
void Culinder::Shift(int _x, int _y) {
	Shape::Shift(_x, _y, 0);
}
void Culinder::Scale(double R, double H) {
	Shape::RoundScale(R, H);
	SetScale();
}