#pragma once

#include <Log_System/Log.hpp>
#include "OM_Engine/Math/Vector_3.hpp"
#include "OM_Engine/Math/Vector_4.hpp"
#include "OM_Engine/Math/Quaternion.hpp"
#include "OM_Engine/Utils.hpp"

namespace Math
{
	inline Matrix_4x4::Matrix_4x4(const float value)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				m_data[i][j] = value;
			}
		}
	}

	inline Matrix_4x4::Matrix_4x4(const Matrix_4x4& other)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				m_data[i][j] = other.m_data[i][j];
			}
		}
	}

	inline Matrix_4x4::Matrix_4x4(const float f1, const float f2, const float f3, const float f4,
		const float f5, const float f6, const float f7, const float f8,
		const float f9, const float f10, const float f11, const float f12,
		const float f13, const float f14, const float f15, const float f16)
	{
		m_data[0][0] = f1;  m_data[0][1] = f2;  m_data[0][2] = f3;  m_data[0][3] = f4;
		m_data[1][0] = f5;  m_data[1][1] = f6;  m_data[1][2] = f7;  m_data[1][3] = f8;
		m_data[2][0] = f9;  m_data[2][1] = f10; m_data[2][2] = f11; m_data[2][3] = f12;
		m_data[3][0] = f13; m_data[3][1] = f14; m_data[3][2] = f15; m_data[3][3] = f16;
	}

	inline Matrix_4x4 Matrix_4x4::Identity()
	{
		Matrix_4x4 identity;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					identity.m_data[i][j] = 1;
			}
		}
		return identity;
	}

	inline Matrix_4x4 Matrix_4x4::Transpose()
	{
		Matrix_4x4 transpose;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transpose.m_data[i][j] = m_data[j][i];
			}
		}
		return transpose;
	}

	inline Matrix_4x4 Matrix_4x4::Get_Inverse() const
	{
		Matrix_4x4 inverse;
		float determinant = Determinant();
		if (determinant == 0)
		{
			return Matrix_4x4::Identity();
		}
		Matrix_4x4 cofactor_matrix = Cofactor_Matrix();
		cofactor_matrix.Transpose();
		cofactor_matrix = cofactor_matrix * (1.f / determinant);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverse.m_data[i][j] = cofactor_matrix.m_data[i][j];
			}
		}
		return inverse;
	}

	inline float Matrix_4x4::Determinant() const
	{
		return m_data[0][0] * (m_data[1][1] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[1][2] * (m_data[2][1] * m_data[3][3] - m_data[3][1] * m_data[2][3]) + m_data[1][3] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]))
			- m_data[0][1] * (m_data[1][0] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[1][2] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[1][3] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]))
			+ m_data[0][2] * (m_data[1][0] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[1][3] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]))
			- m_data[0][3] * (m_data[1][0] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][2] - m_data[3][0] * m_data[2][2]) + m_data[1][2] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));
	}

	inline Matrix_4x4 Matrix_4x4::Cofactor_Matrix() const
	{
		Matrix_4x4 Cofactor;

		Cofactor.m_data[0][0] = m_data[1][1] * (m_data[2][2] * m_data[3][3] - m_data[3][2] * m_data[2][3]) - m_data[1][2] * (m_data[2][1] * m_data[3][3] - m_data[3][1] * m_data[2][3]) + m_data[1][3] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]);
		Cofactor.m_data[0][1] = -(m_data[1][0] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[1][2] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[1][3] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]));
		Cofactor.m_data[0][2] = m_data[1][0] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[1][3] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]);
		Cofactor.m_data[0][3] = -(m_data[1][0] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][2] - m_data[3][0] * m_data[2][2]) + m_data[1][2] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));

		Cofactor.m_data[1][0] = -(m_data[0][1] * (m_data[2][2] * m_data[3][3] - m_data[3][2] * m_data[2][3]) - m_data[0][2] * (m_data[2][1] * m_data[3][3] - m_data[3][1] * m_data[2][3]) + m_data[0][3] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]));
		Cofactor.m_data[1][1] = m_data[0][0] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[0][2] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[0][3] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]);
		Cofactor.m_data[1][2] = -(m_data[0][0] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1]) - m_data[0][1] * (m_data[2][0] * m_data[3][3] - m_data[3][0] * m_data[2][3]) + m_data[0][3] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));
		Cofactor.m_data[1][3] = m_data[0][0] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]) - m_data[0][1] * (m_data[2][0] * m_data[3][2] - m_data[3][0] * m_data[2][2]) + m_data[0][2] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]);
		Cofactor.m_data[2][0] = m_data[0][1] * (m_data[1][2] * m_data[3][3] - m_data[3][2] * m_data[1][3]) - m_data[0][2] * (m_data[1][1] * m_data[3][3] - m_data[3][1] * m_data[1][3]) + m_data[0][3] * (m_data[1][1] * m_data[3][2] - m_data[1][2] * m_data[3][1]);
		Cofactor.m_data[2][1] = -(m_data[0][0] * (m_data[1][2] * m_data[3][3] - m_data[1][3] * m_data[3][2]) - m_data[0][2] * (m_data[1][0] * m_data[3][3] - m_data[3][0] * m_data[1][3]) + m_data[0][3] * (m_data[1][0] * m_data[3][2] - m_data[1][2] * m_data[3][0]));
		Cofactor.m_data[2][2] = m_data[0][0] * (m_data[1][1] * m_data[3][3] - m_data[1][3] * m_data[3][1]) - m_data[0][1] * (m_data[1][0] * m_data[3][3] - m_data[3][0] * m_data[1][3]) + m_data[0][3] * (m_data[1][0] * m_data[3][1] - m_data[1][1] * m_data[3][0]);
		Cofactor.m_data[2][3] = -(m_data[0][0] * (m_data[1][1] * m_data[3][2] - m_data[1][2] * m_data[3][1]) - m_data[0][1] * (m_data[1][0] * m_data[3][2] - m_data[3][0] * m_data[1][2]) + m_data[0][2] * (m_data[1][0] * m_data[3][1] - m_data[1][1] * m_data[3][0]));

		Cofactor.m_data[3][0] = -(m_data[0][1] * (m_data[1][2] * m_data[2][3] - m_data[2][2] * m_data[1][3]) - m_data[0][2] * (m_data[1][1] * m_data[2][3] - m_data[2][1] * m_data[1][3]) + m_data[0][3] * (m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1]));
		Cofactor.m_data[3][1] = m_data[0][0] * (m_data[1][2] * m_data[2][3] - m_data[1][3] * m_data[2][2]) - m_data[0][2] * (m_data[1][0] * m_data[2][3] - m_data[2][0] * m_data[1][3]) + m_data[0][3] * (m_data[1][0] * m_data[2][2] - m_data[1][2] * m_data[2][0]);
		Cofactor.m_data[3][2] = -(m_data[0][0] * (m_data[1][1] * m_data[2][3] - m_data[1][3] * m_data[2][1]) - m_data[0][1] * (m_data[1][0] * m_data[2][3] - m_data[2][0] * m_data[1][3]) + m_data[0][3] * (m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0]));
		Cofactor.m_data[3][3] = m_data[0][0] * (m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1]) - m_data[0][1] * (m_data[1][0] * m_data[2][2] - m_data[2][0] * m_data[1][2]) + m_data[0][2] * (m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0]);

		return Cofactor;
	}

	inline Matrix_4x4 Matrix_4x4::Create_Translation_Matrix(const Vector_3& translation)
	{
		Matrix_4x4 translation_matrix = Matrix_4x4::Identity();
		if (translation.m_x != 0.f)
		{
			translation_matrix.m_data[0][3] = translation.m_x;
		}
		if (translation.m_y != 0.f)
		{
			translation_matrix.m_data[1][3] = translation.m_y;
		}
		if (translation.m_z != 0.f)
		{
			translation_matrix.m_data[2][3] = translation.m_z;
		}
		return translation_matrix;
	}

	inline Matrix_4x4 Matrix_4x4::Create_Scale_Matrix(const Vector_3& scale)
	{
		Matrix_4x4 scale_matrix;
		scale_matrix.m_data[0][0] = scale.m_x;
		scale_matrix.m_data[1][1] = scale.m_y;
		scale_matrix.m_data[2][2] = scale.m_z;
		scale_matrix.m_data[3][3] = 1.f;
		return scale_matrix;
	}

	inline Matrix_4x4 Matrix_4x4::Create_X_Rotation_Matrix(float angle_degree)
	{
		angle_degree *= (float)M_PI / 180.f;
		Matrix_4x4 x_rotation_matrix = Matrix_4x4::Identity();
		x_rotation_matrix.m_data[1][1] = cosf(angle_degree);
		x_rotation_matrix.m_data[1][2] = -sinf(angle_degree);
		x_rotation_matrix.m_data[2][1] = sinf(angle_degree);
		x_rotation_matrix.m_data[2][2] = cosf(angle_degree);
		return x_rotation_matrix;
	}

	inline Matrix_4x4 Matrix_4x4::Create_Y_Rotation_Matrix(float angle_degree)
	{
		angle_degree *= (float)M_PI / 180.f;
		Matrix_4x4 y_rotation_matrix = Matrix_4x4::Identity();
		y_rotation_matrix.m_data[0][0] = cosf(angle_degree);
		y_rotation_matrix.m_data[0][2] = sinf(angle_degree);
		y_rotation_matrix.m_data[2][0] = -sinf(angle_degree);
		y_rotation_matrix.m_data[2][2] = cosf(angle_degree);
		return y_rotation_matrix;
	}

	inline Matrix_4x4 Matrix_4x4::Create_Z_Rotation_Matrix(float angle_degree)
	{
		angle_degree *= (float)M_PI / 180.f;
		Matrix_4x4 z_rotation_matrix = Matrix_4x4::Identity();
		z_rotation_matrix.m_data[0][0] = cosf(angle_degree);
		z_rotation_matrix.m_data[0][1] = -sinf(angle_degree);
		z_rotation_matrix.m_data[1][0] = sinf(angle_degree);
		z_rotation_matrix.m_data[1][1] = cosf(angle_degree);
		return z_rotation_matrix;
	}

	inline Matrix_4x4 Matrix_4x4::Create_Rotation_Matrix(const Vector_3& angle_degree)
	{
		return Create_Y_Rotation_Matrix(angle_degree.m_y) * Create_X_Rotation_Matrix(angle_degree.m_x) * Create_Z_Rotation_Matrix(angle_degree.m_z);
	}

	inline Matrix_4x4 Matrix_4x4::Create_Transformation_Matrix(const Vector_3& translation, const Vector_3& scale, const Vector_3& rotation_degree)
	{
		return Create_Translation_Matrix(translation) * Create_Rotation_Matrix(rotation_degree) * Create_Scale_Matrix(scale);
	}

	inline Matrix_4x4 Matrix_4x4::Create_Transformation_Matrix(const Vector_3& translation, const Vector_3& scale, const Quaternion& rotation)
	{
		return Create_Translation_Matrix(translation) * Quaternion::Quatertion_To_Matrix_4x4(rotation) * Create_Scale_Matrix(scale);
	}

	inline Matrix_4x4 Matrix_4x4::Get_Perspective_Projection(const float aspect, const float FOV, const float near_value, const float far_value)
	{
		const float tan_Half_FOV = tanf(FOV / 2.f);

		Matrix_4x4 resultat;
		resultat.m_data[0][0] = 1.f / (aspect * tan_Half_FOV);
		resultat.m_data[1][1] = 1.f / (tan_Half_FOV);
		resultat.m_data[2][2] = -(far_value + near_value) / (far_value - near_value);
		resultat.m_data[3][2] = -1.f;
		resultat.m_data[2][3] = -(2.f * far_value * near_value) / (far_value - near_value);

		return resultat;
	}

	inline Matrix_4x4 Matrix_4x4::Get_Orthographic_Projection(const float right, const float left, const float top, const float bottom, const float near_value, const float far_value)
	{
		Matrix_4x4 resultat = Identity();
		resultat.m_data[0][0] = 2.f / (right - left);
		resultat.m_data[1][1] = 2.f / (top - bottom);
		resultat.m_data[2][2] = -2.f / (far_value - near_value);
		resultat.m_data[0][3] = -(left + right) / (right - left);
		resultat.m_data[1][3] = -(top + bottom) / (top - bottom);
		resultat.m_data[2][3] = -(far_value + near_value) / (far_value - near_value);
		return resultat;
	}

	inline Matrix_4x4 Matrix_4x4::Get_Orthographic_Projection_Without_Near_Far(const float right, const float left, const float top, const float bottom)
	{
		Matrix_4x4 resultat = Identity();
		resultat.m_data[0][0] = 2.f / (right - left);
		resultat.m_data[1][1] = 2.f / (top - bottom);
		resultat.m_data[2][2] = -1.f;
		resultat.m_data[0][3] = -(left + right) / (right - left);
		resultat.m_data[1][3] = -(top + bottom) / (top - bottom);
		return resultat;
	}

	inline const std::string Matrix_4x4::ToString() const
	{
		std::string result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result += "| ";
			for (unsigned int j = 0; j < 4; j++)
			{
				result += std::to_string(m_data[i][j]) + " ";
			}
			result += "|\n";
		}
		return result;
	}

	inline Matrix_4x4 Matrix_4x4::Look_At(const Vector_3& eye, const Vector_3& center, const Vector_3& up)
	{
		Vector_3 f = Vector_3::Normalize(center - eye);
		Vector_3 s = Vector_3::Normalize(Vector_3::Cross_Product(f, up));
		Vector_3 u = Vector_3::Cross_Product(s, f);

		Matrix_4x4 resultat = Identity();

		resultat.m_data[0][0] = s.m_x;
		resultat.m_data[1][0] = s.m_y;
		resultat.m_data[2][0] = s.m_z;
		resultat.m_data[0][1] = u.m_x;
		resultat.m_data[1][1] = u.m_y;
		resultat.m_data[2][1] = u.m_z;
		resultat.m_data[0][2] = -f.m_x;
		resultat.m_data[1][2] = -f.m_y;
		resultat.m_data[2][2] = -f.m_z;
		resultat.m_data[3][0] = -Vector_3::Dot_Product(s, eye);
		resultat.m_data[3][1] = -Vector_3::Dot_Product(u, eye);
		resultat.m_data[3][2] = Vector_3::Dot_Product(f, eye);

		resultat = resultat.Transpose();
		return resultat;
	}

	inline Math::Vector_3 Scale(Math::Vector_3& vector, float desired_lenght)
	{
		return vector * desired_lenght / Math::Vector_3::Magnitude(vector);
	}

	inline void Matrix_4x4::Decompose(const Matrix_4x4& transform, Math::Vector_3& translation, Math::Vector_3& rotation, Math::Vector_3& scale)
	{
		Matrix_4x4 local_matrix(transform);
		if (local_matrix.m_data[3][3] <= 0.001f && local_matrix.m_data[3][3] >= -0.001f)
		{
			LOG_WARNING("Decompose error");
			return;
		}

		translation = Math::Vector_3(local_matrix.m_data[3][0], local_matrix.m_data[3][1], local_matrix.m_data[3][2]);

		Math::Vector_3 row[3], pdum3;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				switch (j)
				{
				case 0:
					row[i].m_x = local_matrix.m_data[i][j];
					break;
				case 1:
					row[i].m_y = local_matrix.m_data[i][j];
					break;
				case 2:
					row[i].m_z = local_matrix.m_data[i][j];
					break;
				default:
					break;
				}
			}
		}

		scale.m_x = Math::Vector_3::Magnitude(row[0]);
		row[0] = Scale(row[0], 1);
		scale.m_y = Math::Vector_3::Magnitude(row[1]);
		row[1] = Scale(row[1], 1);
		scale.m_z = Math::Vector_3::Magnitude(row[2]);
		row[2] = Scale(row[2], 1);

		pdum3 = Math::Vector_3::Cross_Product(row[1], row[2]);
		if (Math::Vector_3::Dot_Product(row[0], pdum3) < 0)
		{
			scale.m_x *= -1.f;
			row[0] *= -1.f;
			scale.m_y *= -1.f;
			row[1] *= -1.f;
			scale.m_z *= -1.f;
			row[2] *= -1.f;
		}

		rotation.m_y = asin(-row[0].m_z);
		if (cos(rotation.m_y) != 0)
		{
			rotation.m_x = atan2(row[1].m_z, row[2].m_z);
			rotation.m_z = atan2(row[0].m_y, row[0].m_x);
		}
		else
		{
			rotation.m_x = atan2(-row[2].m_x, row[1].m_y);
			rotation.m_z = 0.f;
		}
	}

	inline Matrix_4x4 Matrix_4x4::operator+(const Matrix_4x4& right) const
	{
		Matrix_4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.m_data[i][j] = m_data[i][j] + right.m_data[i][j];
			}
		}
		return result;
	}


	inline Matrix_4x4 Matrix_4x4::operator-(const Matrix_4x4& right) const
	{
		Matrix_4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.m_data[i][j] = m_data[i][j] - right.m_data[i][j];
			}
		}
		return result;
	}

	inline Matrix_4x4 Matrix_4x4::operator-() const
	{
		Matrix_4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.m_data[i][j] = -m_data[i][j];
			}
		}
		return result;
	}

	inline Matrix_4x4 Matrix_4x4::operator*(const Matrix_4x4& other) const
	{
		Matrix_4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				for (unsigned int k = 0; k < 4; k++)
				{
					result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
				}
			}
		}
		return result;
	}

	inline Matrix_4x4 Matrix_4x4::operator*(const float right) const
	{
		Matrix_4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.m_data[i][j] = m_data[i][j] * right;
			}
		}
		return result;
	}

	inline Vector_4 Matrix_4x4::operator*(const Vector_4& right) const
	{
		Vector_4 result;
		result.m_x = m_data[0][0] * right.m_x + m_data[0][1] * right.m_y + m_data[0][2] * right.m_z + m_data[0][3] * right.m_w;
		result.m_y = m_data[1][0] * right.m_x + m_data[1][1] * right.m_y + m_data[1][2] * right.m_z + m_data[1][3] * right.m_w;
		result.m_z = m_data[2][0] * right.m_x + m_data[2][1] * right.m_y + m_data[2][2] * right.m_z + m_data[2][3] * right.m_w;
		result.m_w = m_data[3][0] * right.m_x + m_data[3][1] * right.m_y + m_data[3][2] * right.m_z + m_data[3][3] * right.m_w;
		return result;
	}

	inline void Matrix_4x4::operator+=(const Matrix_4x4& right)
	{
		*this = *this + right;
	}

	inline void Matrix_4x4::operator-=(const Matrix_4x4& right)
	{
		*this = *this - right;
	}

	inline void Matrix_4x4::operator*=(const Matrix_4x4& other)
	{
		*this = *this * other;
	}

	inline void Matrix_4x4::operator*=(const float right)
	{
		*this = *this * right;
	}

	inline Matrix_4x4 operator*(const float left, const Matrix_4x4& matrix)
	{
		return matrix * left;
	}

	inline Vector_4 operator*(const Vector_4& left, const Matrix_4x4& matrix)
	{
		Vector_4 result;
		result.m_x = matrix.m_data[0][0] * left.m_x + matrix.m_data[1][0] * left.m_y + matrix.m_data[2][0] * left.m_z + matrix.m_data[3][0] * left.m_w;
		result.m_y = matrix.m_data[0][1] * left.m_x + matrix.m_data[1][1] * left.m_y + matrix.m_data[2][1] * left.m_z + matrix.m_data[3][1] * left.m_w;
		result.m_z = matrix.m_data[0][2] * left.m_x + matrix.m_data[1][2] * left.m_y + matrix.m_data[2][2] * left.m_z + matrix.m_data[3][2] * left.m_w;
		result.m_w = matrix.m_data[0][3] * left.m_x + matrix.m_data[1][3] * left.m_y + matrix.m_data[2][3] * left.m_z + matrix.m_data[3][3] * left.m_w;
		return result;
	}

	inline bool operator==(const Matrix_4x4& left, const Matrix_4x4& right)
	{
		bool result = true;

		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4; ++j)
			{
				if (left.m_data[i][j] > right.m_data[i][j] + Utils::WEAK_ESPILON || left.m_data[i][j] < right.m_data[i][j] - Utils::WEAK_ESPILON)
				{
					result = false;
					break;
				}
			}
			if (!result)
			{
				break;
			}
		}
		return result;
	}
}