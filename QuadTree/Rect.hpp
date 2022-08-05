#pragma once
#include "Point.hpp"

class Rect
{
public:
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	Point LT;
	Point RB;

public:
	Rect() {};
	Rect(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		LT.x = _x;
		LT.y = _y;
		RB.x = _x + _w;
		RB.y = _y + _h;
	}

	bool ptInRect(const Point _pt) const
	{
		if (_pt.x < LT.x) return false;
		if (_pt.y < LT.y) return false;
		if (_pt.x > RB.x) return false;
		if (_pt.y > RB.y) return false;

		return true;
	}

	bool rectInRect(const Rect _rect)
	{
		if (ptInRect(_rect.LT) && ptInRect(_rect.RB))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};