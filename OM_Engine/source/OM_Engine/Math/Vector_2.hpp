#pragma once

#include "OM_Engine/Base.hpp"
#include <string>

namespace Math
{
	class OM_ENGINE_API Vector_2
	{
		// Behavior
	public:
		float m_x, m_y;
		Vector_2(const float x = 0.f, const float y = 0.f);
		Vector_2(const Vector_2& copy);

		// Vector manipulation
		static const float Dot_Product(const Vector_2& a, const Vector_2 b);
		static const float Magnitude(const Vector_2& vector);
		static const Vector_2& Normalize(const Vector_2& vector);

		// Utils
		std::string To_String() const;

		// Operator
		Vector_2 operator+(const Vector_2& right) const;
		Vector_2 operator-(const Vector_2& right) const;
		Vector_2 operator-() const;
		Vector_2 operator*(const Vector_2& right) const;
		Vector_2 operator*(const float right) const;
		Vector_2 operator/(const Vector_2& right) const;
		Vector_2 operator/(const float right) const;

		void operator+=(const Vector_2& right);
		void operator-=(const Vector_2& right);
		void operator*=(const Vector_2& right);
		void operator*=(const float right);
		void operator/=(const Vector_2& right);
		void operator/=(const float right);

		friend Vector_2 operator*(const float left, const Vector_2& right);
		friend bool operator==(const Vector_2& left, const Vector_2& right);
		friend bool operator!=(const Vector_2& left, const Vector_2& right);
	};
}
#include "Vector_2.inl"