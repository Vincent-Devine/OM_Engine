#pragma once

#include <cmath>
#include "OM_Engine/Math/Vector_2.hpp"
#include "OM_Engine/Math/Vector_3.hpp"

namespace Math
{
	inline Vector_4::Vector_4(const float x, const float y, const float z, const float w)
		: m_x(x)
		, m_y(y)
		, m_z(z)
		, m_w(w)
	{
	}

	inline Vector_4::Vector_4(const Vector_2& copy, const float z, const float w)
		: m_x(copy.m_x)
		, m_y(copy.m_y)
		, m_z(z)
		, m_w(w)
	{
	}

	inline Vector_4::Vector_4(const Vector_3& copy, const float w)
		: m_x(copy.m_x)
		, m_y(copy.m_y)
		, m_z(copy.m_z)
		, m_w(w)
	{
	}

	inline Vector_4::Vector_4(const Vector_4& copy)
		: m_x(copy.m_x)
		, m_y(copy.m_y)
		, m_z(copy.m_z)
		, m_w(copy.m_w)
	{
	}

	inline const float Vector_4::Dot_Product(const Vector_4& a, const Vector_4& b)
	{
		return a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z + a.m_w * b.m_w;
	}

	inline const float Vector_4::Magnitude(const Vector_4& vector)
	{
		return sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y + vector.m_z * vector.m_z + vector.m_w * vector.m_w);
	}

	inline const Vector_4 Vector_4::Normalize(const Vector_4& vector)
	{
		float magnitude = Magnitude(vector);
		Vector_4 vectorNormalize = vector;
		if (magnitude != 0.f)
		{
			vectorNormalize.m_x /= magnitude;
			vectorNormalize.m_y /= magnitude;
			vectorNormalize.m_z /= magnitude;
			vectorNormalize.m_w /= magnitude;
		}
		return vectorNormalize;
	}

	inline const Vector_4 Vector_4::Homogenize(const Vector_4& vector)
	{
		Vector_4 vectorHomogenize = vector;
		if (vectorHomogenize.m_w != 0.f)
		{
			vectorHomogenize.m_x /= vectorHomogenize.m_w;
			vectorHomogenize.m_y /= vectorHomogenize.m_w;
			vectorHomogenize.m_z /= vectorHomogenize.m_w;
			vectorHomogenize.m_w /= vectorHomogenize.m_w;
		}
		return vectorHomogenize;
	}

	inline Vector_3 Vector_4::To_Vector_3() const
	{
		return { m_x, m_y, m_z };
	}

	inline std::string Vector_4::To_String() const
	{
		return "[ " + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + " ]";
	}

	inline Vector_4 Vector_4::operator+(const Vector_4& right) const
	{
		return Vector_4(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z, m_w + right.m_w);
	}

	inline Vector_4 Vector_4::operator-(const Vector_4& right) const
	{
		return Vector_4(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z, m_w - right.m_w);
	}

	inline Vector_4 Vector_4::operator-() const
	{
		return Vector_4(-m_x, -m_y, -m_z, -m_w);
	}

	inline Vector_4 Vector_4::operator*(const Vector_4& right) const
	{
		return Vector_4(m_x * right.m_x, m_y * right.m_y, m_z * right.m_z, m_w * right.m_w);
	}

	inline Vector_4 Vector_4::operator*(const float multiplier) const
	{
		return Vector_4(m_x * multiplier, m_y * multiplier, m_z * multiplier, m_w * multiplier);
	}

	inline Vector_4 Vector_4::operator/(const Vector_4& right) const
	{
		return Vector_4(m_x / right.m_x, m_y / right.m_y, m_z / right.m_z, m_w / right.m_w);
	}

	inline Vector_4 Vector_4::operator/(const float divider) const
	{
		return Vector_4(m_x / divider, m_y / divider, m_z / divider, m_w / divider);
	}

	inline void Vector_4::operator+=(const Vector_4& right)
	{
		*this = *this + right;
	}

	inline void Vector_4::operator-=(const Vector_4& right)
	{
		*this = *this - right;
	}

	inline void Vector_4::operator*=(const Vector_4& right)
	{
		*this = *this * right;
	}

	inline void Vector_4::operator*=(const float multiplier)
	{
		*this = *this * multiplier;
	}

	inline void Vector_4::operator/=(const Vector_4& right)
	{
		*this = *this / right;
	}

	inline void Vector_4::operator/=(const float divider)
	{
		*this = *this / divider;
	}

	inline Vector_4 operator*(const float left, const Vector_4& right)
	{
		return right * left;
	}

	inline bool operator==(const Vector_4& left, const Vector_4& right)
	{
		if (left.m_x <= right.m_x + 0.001f && left.m_x >= right.m_x - 0.001f &&
			left.m_y <= right.m_y + 0.001f && left.m_y >= right.m_y - 0.001f &&
			left.m_z <= right.m_z + 0.001f && left.m_z >= right.m_z - 0.001f &&
			left.m_w <= right.m_w + 0.001f && left.m_w >= right.m_w - 0.001f)
		{
			return true;
		}
		return false;
	}

	inline bool operator!=(const Vector_4& left, const Vector_4& right)
	{
		return !(left == right);
	}
}