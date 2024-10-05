#pragma once

#include "OM_Engine/Base.hpp"
#include <string>

namespace Math
{
	class Vector_2;
	class OM_ENGINE_API Vector_3
	{
		// Behavior
	public:
		Vector_3(const float x = 0.f, const float y = 0.f, const float z = 0.f);
		Vector_3(const Vector_3& copy);
		Vector_3(const Vector_2& copy, const float z = 0.f);
		float m_x, m_y, m_z;

		// Vector manipulation
		static const float Dot_Product(const Vector_3& a, const Vector_3& b);
		static const float Magnitude(const Vector_3& vector3);
		static const Vector_3 Cross_Product(const Vector_3& a, const Vector_3& b);
		static const Vector_3 Normalize(const Vector_3& vector3);

		// Utils
		std::string To_String() const;

		// Operator
		Vector_3 operator+(const Vector_3& right) const;
		Vector_3 operator-(const Vector_3& right) const;
		Vector_3 operator-() const;
		Vector_3 operator*(const Vector_3& right) const;
		Vector_3 operator*(const float right) const;
		Vector_3 operator/(const Vector_3& right) const;
		Vector_3 operator/(const float right) const;

		void operator+=(const Vector_3& right);
		void operator-=(const Vector_3& right);
		void operator*=(const Vector_3& right);
		void operator*=(const float right);
		void operator/=(const Vector_3& right);
		void operator/=(const float right);

		friend Vector_3 operator*(const float left, const Vector_3& right);
		friend bool operator==(const Vector_3& left, const Vector_3& right);
		friend bool operator!=(const Vector_3& left, const Vector_3& right);
	};
}
#include "Vector_3.inl"