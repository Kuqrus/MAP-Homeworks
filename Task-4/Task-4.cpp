#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include <vector>
#include <algorithm>

class AngulagObject {
private:
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> z;

	int type = 0;

	static const int line = 0;
	static const int sqr = 1;
	static const int cube = 2;

	double volume = 0.0;
	double square = 0.0;

	void SetScale() {
		// стороны фигуры
		int a = abs(x[0] - x[1]);
		int b = abs(y[0] - y[1]);
		int c = abs(z[0] - z[1]);		

		// считаем площадь фигуры		
		switch (type)
		{
		case line:
			square = 0;
			break;
		case sqr:
			square = a * b;
			break;
		case cube:
			square = 2 * a * b + 2 * a * c + 2 * b * c;
			break;
		default:
			break;
		}

		// считаем объем фигуры
		volume = a * b * c;
	}

public:
	AngulagObject(int _type, std::vector<int> _x, std::vector<int> _y, std::vector<int> _z = { 0, 0 })
	{
		type = _type;

		// заполняем координаты фигуры		
		x = _x;
		y = _y;
		z = _z;

		SetScale();
	}

	void Shift(int _x, int _y, int _z)
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

	void Scale(int s)
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
		SetScale();
	}

	void ScaleX(int _x) {
		std::for_each(x.begin(), x.end(), [&](int& i) {
			i *= _x;
			});
		SetScale();
	};
	void ScaleY(int _y)	{
		std::for_each(y.begin(), y.end(), [&](int& i) {
			i *= _y;
			});
		SetScale();
	};
	void ScaleZ(int _z) {
		std::for_each(z.begin(), z.end(), [&](int& i) {
			i *= _z;
			});
		SetScale();
	};

	double GetVolume() {
		return volume;
	}
	double GetSquare() {
		return square;
	}
};

class RoundObject {
private:
	int x;
	int y;

	double volume = 0.0;
	double square = 0.0;
	double height = 0.0;
	double radius = 0.0;

	void SetScale() {
		// считаем площадь фигуры
		square = M_PI * radius * radius + 2 * radius * height; // if H == 0 -> M_PI * R * R

		// считаем объем фигуры		
		volume = M_PI * radius * radius * height;
	}

public:
	RoundObject(int _x, int _y, double R, double H = 0)
	{
		// заполняем координаты фигуры		
		x = _x;
		y = _y;
		radius = R;
		height = H;

		SetScale();
	}

	void Shift(int _x, int _y)
	{
		x += _x;
		y += _y;
	}
	void Scale(double R, double H = 1)
	{
		radius /= R;
		if (height > 0) {
			height /= H;
		}

		SetScale();
	}

	double GetVolume() {
		return volume;
	}
	double GetSquare() {
		return square;
	}
	double GetHeight() {
		return height;
	}
	double GetRadius() {
		return radius;
	}
};

int main()
{	

	std::vector<int> x{ 10,40 };
	std::vector<int> y{ 20,50 };
	std::vector<int> z{ 30,15 };

	AngulagObject a_2d(1, x, y);					// Square
	std::cout << a_2d.GetSquare() << std::endl;
	a_2d.Scale(2);
	std::cout << a_2d.GetSquare() << std::endl;

	RoundObject r_2d(21, 25, 2.2);					// Circle
	std::cout << r_2d.GetSquare() << std::endl;
	r_2d.Scale(1.2);
	std::cout << r_2d.GetSquare() << std::endl;

	RoundObject r_3d(21, 25, 2.2, 5.4);				// Cylinder
	std::cout << r_3d.GetSquare() << std::endl;
	r_3d.Scale(1.2, 1);
	std::cout << r_3d.GetSquare() << std::endl;


}