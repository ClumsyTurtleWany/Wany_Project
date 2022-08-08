#pragma once
#include "Point.hpp"

class Rect
{
public:
	Point LT;
	Point RB;

public:
	Rect() {};
	Rect(int _x, int _y, int _w, int _h)
	{
		LT.x = _x;
		LT.y = _y;
		RB.x = _x + _w - 1;
		RB.y = _y + _h - 1;
	}

	Rect(Point _LT, Point _RB)
	{
		LT = _LT;
		RB = _RB;
	}

	bool operator ==(const Rect _rect)
	{
		if ((LT == _rect.LT) &&	(RB == _rect.RB))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Rect _rect)
	{
		if ((LT != _rect.LT) ||	(RB != _rect.RB))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int left()		const { return LT.x; }
	int right()		const { return RB.x; }
	int top()		const { return LT.y; }
	int bottom()	const { return RB.y; }
	int width()		const { return RB.x - LT.x; }
	int height()	const { return RB.y - LT.y; }
	int area()		const { return width() * height(); }

	void offset(const Point _offset)
	{
		LT += _offset;
		RB += _offset;
	}

	bool PtInRect(const Point _pt) const
	{
		if (_pt.x < LT.x) return false;
		if (_pt.y < LT.y) return false;
		if (_pt.x > RB.x) return false;
		if (_pt.y > RB.y) return false;

		return true;
	}

	bool PtInRect(const int _x, const int _y) const
	{
		if (_x < LT.x) return false;
		if (_y < LT.y) return false;
		if (_x > RB.x) return false;
		if (_y > RB.y) return false;

		return true;
	}

	bool RectInRect(const Rect _rect)
	{
		if (PtInRect(_rect.LT) && PtInRect(_rect.RB))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool intersectRect(const Rect _rect, Rect* _dst = nullptr)
	{
		Point unionLT, unionRB;
		unionLT.x = LT.x < _rect.left() ? LT.x : _rect.left();
		unionLT.y = LT.y < _rect.top() ? LT.y : _rect.top();
		unionRB.x = RB.x < _rect.right() ? _rect.right() : RB.x;
		unionRB.y = RB.y < _rect.bottom() ? _rect.bottom() : RB.y;

		Rect unionRect(unionLT, unionRB);
		if ((unionRect.width() < (width() + _rect.width())) && (unionRect.height() < (height() + _rect.height())))
		{
			if (_dst != nullptr)
			{
				// intersection
				_dst->LT.x = LT.x < _rect.left() ? _rect.left() : LT.x;
				_dst->LT.y = LT.y < _rect.top() ? _rect.top() : LT.y;
				_dst->RB.x = RB.x < _rect.right() ? RB.x : _rect.right();
				_dst->RB.y = RB.y < _rect.bottom() ? RB.y : _rect.bottom();
			}
			return true;
		}
		else
		{
			return false;
		}
		
	}
};