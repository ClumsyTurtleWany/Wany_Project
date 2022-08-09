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
		if ((LT == _rect.LT) && (RB == _rect.RB))
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
		if ((LT != _rect.LT) || (RB != _rect.RB))
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
	T width()		const { return static_cast<T>(fabs(RB.x - LT.x + 1)); }
	T height()		const { return static_cast<T>(fabs(RB.y - LT.y + 1)); }
	T area()		const { return width() * height(); }
	T cx()			const {	return ((RB.x + LT.x) / 2.0f); }
	T cy()			const {	return ((RB.y + LT.y) / 2.0f); }
	Point_<T> center() const { return Point_<T>(cx(), cy()); }

	void offset(const Point_<T>& _offset)
	{
		LT += _offset;
		RB += _offset;
	}

	void offset(const T& _x, const T& _y)
	{
		LT += (_x, _y);
		RB += (_x, _y);
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

template <typename T>
class Rect3D_
{
public:
	Point3D_<T> corner[4];
	float theta = 0.0f;
	float pi = 0.0f;
	T width;
	T height;
	Point3D_<T> center;
	

public:
	Rect3D_() {};
	Rect3D_(Point3D_<T> _c1, Point3D_<T> _c2, Point3D_<T> _c3, Point3D_<T> _c4)
	{
		corner[0] = _c1;
		corner[1] = _c2;
		corner[2] = _c3;
		corner[3] = _c4;
	}

	Rect3D_(Point3D_<T> _c, T _width, T _height, float _theta = 0.0f, float _pi = 0.0f)
	{
		//corner[0] = _c
	}

	bool operator ==(const Rect3D_<T>& _rect)
	{
		
	}

	bool operator !=(const Rect_<T>& _rect)
	{
		
	}

	T left()		const { return LT.x; }
	T right()		const { return RB.x; }
	T top()			const { return LT.y; }
	T bottom()		const { return RB.y; }
	T width()		const { return static_cast<T>(fabs(RB.x - LT.x + 1)); }
	T height()		const { return static_cast<T>(fabs(RB.y - LT.y + 1)); }
	T area()		const { return width() * height(); }
	T cx()			const { return ((RB.x + LT.x) / 2.0f); }
	T cy()			const { return ((RB.y + LT.y) / 2.0f); }
	Point_<T> center() const { return Point_<T>(cx(), cy()); }

	void offset(const Point_<T>& _offset)
	{
		LT += _offset;
		RB += _offset;
	}

	void offset(const T& _x, const T& _y)
	{
		LT += (_x, _y);
		RB += (_x, _y);
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