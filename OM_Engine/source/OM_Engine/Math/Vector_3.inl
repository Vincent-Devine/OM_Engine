#pragma once

#include <cmath>
#include "OM_Engine/Math/Vector_2.hpp"

namespace Math
{
	// Behavior
	inline Vector_3::Vector_3(const float x, const float y, const float z)
		: m_x(x), m_y(y), m_z(z)
	{
	}

	inline Vector_3::Vector_3(const Vector_3& copy)
		: m_x(copy.m_x), m_y(copy.m_y), m_z(copy.m_z)
	{
	}

	inline Vector_3::Vector_3(const Vector_2& copy, const float z)
		: m_x(copy.m_x), m_y(copy.m_y), m_z(z)
	{
	}

	// Vector manipulation
	inline const float Vector_3::Dot_Product(const Vector_3& a, const Vector_3& b)
	{
		return a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z;
	}

	inline const float Vector_3::Magnitude(const Vector_3& vector)
	{
		return sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y + vector.m_z * vector.m_z);
	}

	inline const Vector_3 Vector_3::Cross_Product(const Vector_3& a, const Vector_3& b)
	{
		return
		{
			a.m_y * b.m_z - a.m_z * b.m_y,
			a.m_z* b.m_x - a.m_x * b.m_z,
			a.m_x * b.m_y - a.m_y * b.m_x
		};
	}

	inline const Vector_3 Vector_3::Normalize(const Vector_3& vector)
	{
		float magnitude = Magnitude(vector);
		Vector_3 vectorNormalize = vector;
		if (magnitude != 0.f)
		{
			vectorNormalize.m_x /= magnitude;
			vectorNormalize.m_y /= magnitude;
			vectorNormalize.m_z /= magnitude;
		}
		return vectorNormalize;
	}

	// Utils
	inline std::string Vector_3::To_String() const
	{
		return "[ " + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + " ]";
	}

	// Operator
	inline Vector_3 Vector_3::operator+(const Vector_3& right) const
	{
		return Vector_3(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z);
	}

	inline Vector_3 Vector_3::operator-(const Vector_3& right) const
	{ 
		return Vector_3(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z);
	}

	inline Vector_3 Vector_3::operator-() const
	{ 
	return Vector_3(-m_x, -m_y, -m_z);
	}

	inline Vector_3 Vector_3::operator*(const Vector_3& right) const
	{ 
	return Vector_3(m_x * right.m_x, m_y * right.m_y, m_z * right.m_z);
	}

	inline Vector_3 Vector_3::operator*(const float right) const
	{
		return Vector_3(m_x * right, m_y * right, m_z * right);
	}

	inline Vector_3 Vector_3::operator/(const Vector_3& right) const
	{ 
	return Vector_3(m_x / right.m_x, m_y / right.m_y, m_z / right.m_z);
	}

	inline Vector_3 Vector_3::operator/(const float right) const
	{
		return Vector_3(m_x / right, m_y / right, m_z / right);
	}

	inline void Vector_3::operator+=(const Vector_3& right)
	{ 
	*this = *this + right;
	}

	inline void Vector_3::operator-=(const Vector_3& right)
	{ 
	*this = *this - right;
	}

	inline void Vector_3::operator*=(const Vector_3& right)
	{ 
	*this = *this * right;
	}

	inline void Vector_3::operator*=(const float right)
	{
		*this = *this * right;
	}

	inline void Vector_3::operator/=(const Vector_3& right)
	{ 
	*this = *this / right;
	}

	inline void Vector_3::operator/=(const float right)
	{
		*this = *this / right;
	}

	// Friends
	inline Vector_3 operator*(const float left, const Vector_3& right)
	{ 
	return right * left;
	}

	inline bool operator==(const Vector_3& left, const Vector_3& right)
	{
		if (left.m_x <= right.m_x + 0.001f && left.m_x >= right.m_x - 0.001f &&
			left.m_y <= right.m_y + 0.001f && left.m_y >= right.m_y - 0.001f &&
			left.m_z <= right.m_z + 0.001f && left.m_z >= right.m_z - 0.001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool operator!=(const Vector_3& left, const Vector_3& right)
	{
		return !(left == right);
	}
}