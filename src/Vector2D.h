/*
 * Vector2D.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <math.h>

class Vector2D
{
public:
	Vector2D()
	{
		m_x = 0;
		m_y = 0;
	}

	Vector2D(float x, float y): m_x(x), m_y(y) {}

	const float getX() { return m_x; }
	const float getY() { return m_y; }

	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	int length() { return sqrt(m_x * m_x + m_y * m_y); }

	Vector2D operator+(const Vector2D& v2) const { return Vector2D(m_x + v2.m_x, m_y + v2.m_y); }
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;

		return v1;
	}

	Vector2D operator-(const Vector2D& v2) const { return Vector2D(m_x - v2.m_x, m_y - v2.m_y); }
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}


	Vector2D operator*(float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}

	Vector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}

	Vector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}

	void toIsometric()
	{
		float x = m_x;
		float y = m_y;

		m_x = x - y;
		m_y = (x + y) / 2;
	}

	void toCartesian()
	{
		float x = m_x;
		float y = m_y;

		m_x = (2 * y + x) / 2;
		m_y = (2 * y - x) / 2;
	}

	void screenToWorld()
	{
		float x = m_x;
		float y = m_y;
		m_x = roundf(((x / 32) + (y / 16)) / 2);
		m_y = roundf(((y / 16) - (x / 32)) / 2);
	}

	void worldToScreen()
	{
		float x = m_x;
		float y = m_y;
		m_x = (x - y) * 32;
		m_y = (x + y) * 16;
	}

	void normalize()
	{
		double l = length();
		if ( l > 0)
		{
			(*this) *= 1 / l;
		}
	}

	float m_x;
	float m_y;
};




#endif /* VECTOR2D_H_ */
