#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include <vector>
#include <algorithm>

class Shape {
private:
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> z;

	double volume = 0.0;
	double square = 0.0;

	double height = 0.0;
	double radius = 0.0;

protected:
	std::vector<int> GetX();
	std::vector<int> GetY();
	std::vector<int> GetZ();

	void SetVolume(double V);
	void SetSquare(double S);
	void SetHeight(double H);
	void SetRadius(double R);

	void Shift(int _x, int _y, int _z);

	void Scale(int s);

	void RoundScale(double R, double H);

	void ScaleX(int _x);
	void ScaleY(int _y);
	void ScaleZ(int _z);

public:
	Shape(std::vector<int> _x, std::vector<int> _y);
	Shape(std::vector<int> _x, std::vector<int> _y, std::vector<int> _z);

	Shape(int _x, int _y, double R);
	Shape(int _x, int _y, double H, double R);

	double GetVolume();
	double GetSquare();
	double GetHeight();
	double GetRadius();
};

class Line : public Shape {
private:
	void SetScale();
public:
	Line(std::vector<int> _x, std::vector<int> _y);

	void Shift(int _x, int _y);
	void Scale(int x);
	void ScaleX(int x);
	void ScaleY(int y);
};

class Square : public Shape {
private:
	void SetScale();
public:
	Square(std::vector<int> _x, std::vector<int> _y);

	void Shift(int _x, int _y);
	void Scale(int x);
	void ScaleX(int x);
	void ScaleY(int y);
};

class Cube : public Shape {
private:
	void SetScale();
public:
	Cube(std::vector<int> _x, std::vector<int> _y, std::vector<int> _z);

	void Shift(int _x, int _y, int _z);
	void Scale(int x);
	void ScaleX(int x);
	void ScaleY(int y);
	void ScaleZ(int z);
};

class Circle : public Shape {
private:
	void SetScale();
public:
	Circle(int _x, int _y, double R);

	void Shift(int _x, int _y);
	void Scale(double R);
};

class Culinder : public Shape {
private:
	void SetScale();
public:
	Culinder(int _x, int _y, double H, double R);

	void Shift(int _x, int _y);
	void Scale(double R, double H);
};
