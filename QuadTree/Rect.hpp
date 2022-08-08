#pragma once
#include "Point.hpp"

template <typename T>
class Rect_
{
public:
	Point_<T> LT;
	Point_<T> RB;

public:
	Rect_() {};
	Rect_(T _x, T _y, T _w, T _h)
	{
		LT.x = _x;
		LT.y = _y;
		RB.x = _x + _w - 1;
		RB.y = _y + _h - 1;
	}

	Rect_(Point_<T> _LT, Point_<T> _RB)
	{
		LT = _LT;
		RB = _RB;
	}

	bool operator ==(const Rect_<T>& _rect)
	{
		//if ((LT == _rect.LT) && (RB == _rect.RB))
		if ((fabs(LT - _rect.LT) < 0.001) && (fabs(RB - _rect.RB) < 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Rect_<T>& _rect)
	{
		//if ((LT != _rect.LT) || (RB != _rect.RB))
		if ((fabs(LT - _rect.LT) > 0.001) || (fabs(RB - _rect.RB) > 0.001))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	T left()		const { return LT.x; }
	T right()		const { return RB.x; }
	T top()			const { return LT.y; }
	T bottom()		const { return RB.y; }
	T width()		const { return RB.x - LT.x + 1; }
	T height()		const { return RB.y - LT.y + 1; }
	T area()		const { return width() * height(); }

	void offset(const Point_<T> _offset)
	{
		LT += _offset;
		RB += _offset;
	}

	bool PtInRect(const Point_<T> _pt) const
	{
		if (_pt.x < LT.x) return false;
		if (_pt.y < LT.y) return false;
		if (_pt.x > RB.x) return false;
		if (_pt.y > RB.y) return false;

		return true;
	}

	bool PtInRect(const T _x, const T _y) const
	{
		if (_x < LT.x) return false;
		if (_y < LT.y) return false;
		if (_x > RB.x) return false;
		if (_y > RB.y) return false;

		return true;
	}

	bool RectInRect(const Rect_<T> _rect)
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
	
	bool intersectRect(const Rect_<T> _rect, Rect_<T>* _dst = nullptr)
	{
		Point_<T> unionLT, unionRB;
		unionLT.x = LT.x < _rect.left() ? LT.x : _rect.left();
		unionLT.y = LT.y < _rect.top() ? LT.y : _rect.top();
		unionRB.x = RB.x < _rect.right() ? _rect.right() : RB.x;
		unionRB.y = RB.y < _rect.bottom() ? _rect.bottom() : RB.y;

		Rect_<T> unionRect(unionLT, unionRB);
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

using Rect = Rect_<int>;