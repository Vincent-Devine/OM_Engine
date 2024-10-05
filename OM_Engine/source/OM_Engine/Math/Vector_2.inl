#pragma once

#include <cmath>

namespace Math
{
	// Behavior
	inline Vector_2::Vector_2(const float x, const float y)
		: m_x(x), m_y(y)
	{
	}

	inline Vector_2::Vector_2(const Vector_2& copy)
		: m_x(copy.m_x), m_y(copy.m_y)
	{
	}

	// Vector manipulation
	inline const float Vector_2::Dot_Product(const Vector_2& a, const Vector_2 b)
	{
		return a.m_x * b.m_x + a.m_y * b.m_y;
	}

	inline const float Vector_2::Magnitude(const Vector_2& vector)
	{
		return std::sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y);
	}

	inline const Vector_2& Vector_2::Normalize(const Vector_2& vector)
	{
		float magnitude = Magnitude(vector);
		if (magnitude > 0.f)
			return Vector_2(vector.m_x / magnitude, vector.m_y / magnitude);
		return Vector_2();
	}

	// Utils
	inline std::string Vector_2::To_String() const
	{
		return "[ " + std::to_string(m_x) + ", " + std::to_string(m_y) + " ]";
	}

	// Operator
	inline Vector_2 Vector_2::operator+(const Vector_2& right) const
	{
		return Vector_2(m_x + right.m_x, m_y + right.m_y);
	}

	inline Vector_2 Vector_2::operator-(const Vector_2& right) const
	{
		return Vector_2(m_x - right.m_x, m_y - right.m_y);
	}

	inline Vector_2 Vector_2::operator-() const
	{
		return Vector_2(-m_x, -m_y);
	}

	inline Vector_2 Vector_2::operator*(const Vector_2& right) const
	{
		return Vector_2(m_x * right.m_x, m_y * right.m_y);
	}

	inline Vector_2 Vector_2::operator*(const float right) const
	{
		return Vector_2(m_x * right, m_y * right);
	}

	inline Vector_2 Vector_2::operator/(const Vector_2& right) const
	{
		return Vector_2(m_x / right.m_x, m_y / right.m_y);
	}

	inline Vector_2 Vector_2::operator/(const float right) const
	{
		return Vector_2(m_x / right, m_y / right);
	}

	inline void Vector_2::operator+=(const Vector_2& right)
	{
		m_x += right.m_x;
		m_y += right.m_y;
	}

	inline void Vector_2::operator-=(const Vector_2& right)
	{
		m_x -= right.m_x;
		m_y -= right.m_y;
	}

	inline void Vector_2::operator*=(const Vector_2& right)
	{
		m_x *= right.m_x;
		m_y *= right.m_y;
	}

	inline void Vector_2::operator*=(const float right)
	{
		m_x *= right;
		m_y *= right;
	}

	inline void Vector_2::operator/=(const Vector_2& right)
	{
		m_x /= right.m_x;
		m_y /= right.m_y;
	}

	inline void Vector_2::operator/=(const float right)
	{
		m_x /= right;
		m_y /= right;
	}

	// Friends
	inline Vector_2 operator*(const float left, const Vector_2& right)
	{
		return left * right;
	}

	inline bool operator==(const Vector_2& left, const Vector_2& right)
	{
		if (left.m_x <= right.m_x + .001f && left.m_x >= right.m_x - .001f && left.m_y <= right.m_y + .001f && left.m_y >= right.m_y - .001f)
			return true;
		return false;
	}

	inline bool operator!=(const Vector_2& left, const Vector_2& right)
	{
		return !(left == right);
	}
}