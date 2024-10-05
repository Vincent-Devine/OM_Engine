#pragma once

#include "OM_Engine/Base.hpp"
#include <string>

namespace Math
{
	class Vector_2;
	class Vector_3;
	class OM_ENGINE_API Vector_4
	{
		// Behavior
	public:
		Vector_4(const float x = 0.f, const float y = 0.f, const float z = 0.f, const float w = 0.f);
		Vector_4(const Vector_2& copy, const float z = 0.f, const float w = 0.f);
		Vector_4(const Vector_3& copy, const float w = 0.f);
		Vector_4(const Vector_4& copy);
		float m_x, m_y, m_z, m_w;

		Vector_3 To_Vector_3() const;

		// Vector manipulation
		static const float Dot_Product(const Vector_4& a, const Vector_4& b);
		static const float Magnitude(const Vector_4& vector);
		static const Vector_4 Normalize(const Vector_4& vector);
		static const Vector_4 Homogenize(const Vector_4& vector);

		// Utils
		std::string To_String() const;

		// Operator
		Vector_4 operator+(const Vector_4& right) const;
		Vector_4 operator-(const Vector_4& right) const;
		Vector_4 operator-() const;
		Vector_4 operator*(const Vector_4& right) const;
		Vector_4 operator*(const float right) const;
		Vector_4 operator/(const Vector_4& right) const;
		Vector_4 operator/(const float right) const;

		void operator+=(const Vector_4& right);
		void operator-=(const Vector_4& right);
		void operator*=(const Vector_4& right);
		void operator*=(const float right);
		void operator/=(const Vector_4& right);
		void operator/=(const float right);

		friend Vector_4 operator*(const float left, const Vector_4& right);
		friend bool operator==(const Vector_4& left, const Vector_4& right);
		friend bool operator!=(const Vector_4& left, const Vector_4& right);
	};
}
#include "Vector_4.inl"