#pragma once

class Point
{
public:
	int x = 0;
	int y = 0;

public:
	Point() {};
	Point(int _x, int _y) : x(_x), y(_y) {};
	
	void operator =(const Point _pt)
	{
		x = _pt.x;
		y = _pt.y;
	}

	Point operator +(const Point _pt)
	{
		return Point(x + _pt.x, y + _pt.y);
	}

	void operator +=(const Point _pt)
	{
		x += _pt.x;
		y += _pt.y;
	}

	Point operator -(const Point _pt)
	{
		return Point(x - _pt.x, y - _pt.y);
	}

	void operator -=(const Point _pt)
	{
		x -= _pt.x;
		y -= _pt.y;
	}

	bool operator ==(const Point _pt)
	{
		if ((x == _pt.x) && (y == _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Point _pt)
	{
		if ((x != _pt.x) || (y != _pt.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Point3D
{
public:
	int x = 0;
	int y = 0;
	int z = 0;

public:
	Point3D() {};
	Point3D(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {};

	void operator =(const Point3D _pt)
	{
		x = _pt.x;
		y = _pt.y;
		z = _pt.z;
	}

	Point3D operator +(const Point3D _pt)
	{
		return Point3D(x + _pt.x, y + _pt.y, z + _pt.z);
	}

	void operator +=(const Point3D _pt)
	{
		x += _pt.x;
		y += _pt.y;
		z += _pt.z;
	}

	Point3D operator -(const Point3D _pt)
	{
		return Point3D(x - _pt.x, y - _pt.y, z - _pt.z);
	}

	void operator -=(const Point3D _pt)
	{
		x -= _pt.x;
		y -= _pt.y;
		z -= _pt.z;
	}

	bool operator ==(const Point3D _pt)
	{
		if ((x == _pt.x) && (y == _pt.y) && (z == _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const Point3D _pt)
	{
		if ((x != _pt.x) || (y != _pt.y) || (z != _pt.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};