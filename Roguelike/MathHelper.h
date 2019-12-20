#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <vector>

struct Point {
	int tileX;
	int tileY;

	Point(int x = 0, int y = 0) {
		tileX = x;
		tileY = y;
	}

	Point(const Point& other) {
		tileX = other.tileX;
		tileY = other.tileY;
	}

	friend bool operator==(const Point& leftPoint, const Point& rightPoint)
	{
		return leftPoint.tileX == rightPoint.tileX && leftPoint.tileY == rightPoint.tileY;
	}

	friend bool operator<(const Point& leftPoint, const Point& rightPoint)
	{
		if (leftPoint.tileX != rightPoint.tileX)
			return (leftPoint.tileX < rightPoint.tileX);
		else
			return (leftPoint.tileY < rightPoint.tileY);
	}
};

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

//Bresenham's line drawing algorithm
inline std::vector<Point> GetLine(const Point& from, const Point& to)
{
	std::vector<Point> line;

	int x = from.tileX;
	int y = from.tileY;

	int dx = to.tileX - from.tileX;
	int dy = to.tileY - from.tileY;

	bool inverted = false;
	int step = sgn(dx);
	int gradientStep = sgn(dy);

	int longest = abs(dx);
	int shortest = abs(dy);

	if (longest < shortest)
	{
		inverted = true;
		longest = abs(dy);
		shortest = abs(dx);
		step = sgn(dy);
		gradientStep = sgn(dx);
	}

	int gradientAccumulation = longest / 2;
	for (int i = 0; i < longest; i++)
	{
		line.push_back(Point(x, y));

		if (inverted)
			y += step;
		else
			x += step;

		gradientAccumulation += shortest;
		if (gradientAccumulation >= longest)
		{
			if (inverted)
				x += gradientStep;
			else
				y += gradientStep;

			gradientAccumulation -= longest;
		}
	}

	return line;
}

inline float GetDistance(Point a, Point b)
{
	int distancex = (b.tileX - a.tileX) * (b.tileX - a.tileX);
	int distancey = (b.tileY - a.tileY) * (b.tileY - a.tileY);

	float distance = sqrt(distancex + distancey);

	return distance;
}

#endif