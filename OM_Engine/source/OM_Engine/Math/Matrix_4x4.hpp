#pragma once

#include "OM_Engine/Base.hpp"
#include "OM_Engine/Utils.hpp"

namespace Math
{
	class Vector_3;
	class Vector_4;
	class Quaternion;
	class OM_ENGINE_API Matrix_4x4 //line then column
	{
		// Behavior
	public:
		Matrix_4x4(const float value = 0);
		Matrix_4x4(const Matrix_4x4& other);
		Matrix_4x4(const float f1, const float f2, const float f3, const float f4,
			const float f5, const float f6, const float f7, const float f8,
			const float f9, const float f10, const float f11, const float f12,
			const float f13, const float f14, const float f15, const float f16);
		float m_data[4][4];

		// Matrix transformation
		static Matrix_4x4 Identity();
		Matrix_4x4 Transpose();
		Matrix_4x4 Get_Inverse() const;
		float Determinant() const;
		Matrix_4x4 Cofactor_Matrix() const;

		// Create transformation matrix
		static Matrix_4x4 Create_Translation_Matrix(const Vector_3& translation);
		static Matrix_4x4 Create_Scale_Matrix(const Vector_3& scale);
		static Matrix_4x4 Create_X_Rotation_Matrix(float angle_degree);
		static Matrix_4x4 Create_Y_Rotation_Matrix(float angle_degree);
		static Matrix_4x4 Create_Z_Rotation_Matrix(float angle_degree);

		static Matrix_4x4 Create_Rotation_Matrix(const Vector_3& angle_degree);
		static Matrix_4x4 Create_Transformation_Matrix(const Vector_3& translation, const Vector_3& scale, const Vector_3& rotation_degree);
		static Matrix_4x4 Create_Transformation_Matrix(const Vector_3& translation, const Vector_3& scale, const Quaternion& rotation);

		// Get camera matrix
		static Matrix_4x4 Get_Perspective_Projection(const float aspect = 1920.f / 1080.f, const float FOV = Utils::DEG_TO_RAD * 90.f, const float near = 0.1f, const float far = 1000.f);
		static Matrix_4x4 Get_Orthographic_Projection(const float right = 1920.f / 2.f, const float left = -1920.f / 2.f, const float top = 1080.f / 2.f, const float bottom = -1080.f / 2.f, const float near = -500.f, const float far = 500.f);
		static Matrix_4x4 Get_Orthographic_Projection_Without_Near_Far(const float right = 1920.f / 2.f, const float left = -1920.f / 2.f, const float top = 1080.f / 2.f, const float bottom = -1080.f / 2.f);

		// Utils
		const std::string ToString() const;
		static Matrix_4x4 Look_At(const Vector_3& eye, const Vector_3& center, const Vector_3& up);
		void Decompose(const Matrix_4x4& transform, Math::Vector_3& translation, Math::Vector_3& rotation, Math::Vector_3& scale);

		// Operator
		Matrix_4x4 operator+(const Matrix_4x4& right) const;
		Matrix_4x4 operator-(const Matrix_4x4& right) const;
		Matrix_4x4 operator-() const;
		Matrix_4x4 operator*(const Matrix_4x4& right) const;
		Matrix_4x4 operator*(const float right) const;
		Vector_4 operator*(const Vector_4& right) const;

		void operator+=(const Matrix_4x4& right);
		void operator-=(const Matrix_4x4& right);
		void operator*=(const Matrix_4x4& right);
		void operator*=(const float right);

		friend Matrix_4x4 operator*(const float left, const Matrix_4x4& matrix);
		friend Vector_4 operator*(const Vector_4& left, const Matrix_4x4& matrix);
		friend bool operator==(const Matrix_4x4& left, const Matrix_4x4& right);
	};
}
#include "OM_Engine/Math/Matrix_4x4.inl"