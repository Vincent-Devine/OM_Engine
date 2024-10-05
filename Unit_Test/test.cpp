#include "pch.h"

#include "../OM_Engine/source/OM_Engine/Math/Vector_2.hpp"
#include "../OM_Engine/source/OM_Engine/Math/Vector_3.hpp"
#include "../OM_Engine/source/OM_Engine/Math/Vector_4.hpp"
#include "../OM_Engine/source/OM_Engine/Math/Matrix_4x4.hpp"
#include "../OM_Engine/source/OM_Engine/Math/Quaternion.hpp"

using namespace Math;

#pragma region Vector_2

TEST(Vector_2, Equal)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);
	Vector_2 vector_2 = Vector_2(vector_1);
	EXPECT_EQ(vector_1, vector_2);
	EXPECT_EQ(vector_2, vector_1);

	Vector_2 vector_3 = vector_2;
	EXPECT_EQ(vector_3, vector_2);

	EXPECT_EQ(vector_3 == vector_2, true);
	EXPECT_EQ(vector_3 != vector_2, false);
}

TEST(Vector_2, Sum)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);
	Vector_2 vector_2 = Vector_2(2.f, 3.f);

	EXPECT_EQ(vector_1 + vector_2, Vector_2(3.f, 5.f));
	EXPECT_EQ(vector_1 + vector_2, vector_1 + vector_2);

	Vector_2 vector_3 = vector_1;
	vector_3 += vector_2;

	EXPECT_EQ(vector_3, Vector_2(3.f, 5.f));
}

TEST(Vector_2, Difference)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);

	Vector_2 vector_2 = Vector_2(2.f, 3.f);

	EXPECT_EQ(-vector_1, Vector_2(-1.f, -2.f));

	EXPECT_EQ(vector_1 - vector_2, Vector_2(-1.f, -1.f));

	EXPECT_EQ(vector_2 - vector_1, Vector_2(1.f, 1.f));

	Vector_2 vector_3 = vector_1;
	vector_3 -= vector_2;

	EXPECT_EQ(vector_3, Vector_2(-1.f, -1.f));
}

TEST(Vector_2, Product)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);
	Vector_2 vector_2 = Vector_2(2.f, 3.f);

	EXPECT_EQ(vector_1 * vector_2, Vector_2(2.f, 6.f));
	EXPECT_EQ(vector_2 * vector_1, Vector_2(2.f, 6.f));
	EXPECT_EQ(vector_1 * 2.f, Vector_2(2.f, 4.f));

	Vector_2 vector_3 = vector_1;
	vector_3 *= vector_2;

	EXPECT_EQ(vector_3, Vector_2(2.f, 6.f));

	Vector_2 vector_4 = vector_1;
	vector_4 *= 2.f;

	EXPECT_EQ(vector_4, Vector_2(2.f, 4.f));
}

TEST(Vector_2, Quotient)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);
	Vector_2 vector_2 = Vector_2(2.f, 3.f);

	EXPECT_EQ(vector_1 / vector_2, Vector_2(0.5f, 2.f / 3.f));
	EXPECT_EQ(vector_2 / vector_1, Vector_2(2.f, 1.5f));
	EXPECT_EQ(vector_1 / 2.f, Vector_2(0.5f, 1.f));

	Vector_2 vector_3 = vector_1;
	vector_3 /= vector_2;

	EXPECT_EQ(vector_3, Vector_2(0.5f, 2.f / 3.f));

	Vector_2 vector_4 = vector_1;
	vector_4 /= 2.f;

	EXPECT_EQ(vector_4, Vector_2(0.5f, 1.f));
}

TEST(Vector_2, Special_Operator)
{
	Vector_2 vector_1 = Vector_2(1.f, 2.f);
	Vector_2 vector_2 = Vector_2(2.f, 3.f);

	EXPECT_EQ(Vector_2::Dot_Product(vector_1, vector_2), 8.f);
	EXPECT_EQ(Vector_2::Magnitude(vector_1), sqrtf(5.f));
	EXPECT_EQ(Vector_2::Normalize(vector_1), Vector_2(1.f, 2.f) / sqrtf(5.f));
}

#pragma endregion

#pragma region Vector_3
TEST(Vector_3, Equal)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);
	Vector_3 vector_2 = Vector_3(vector_1);

	EXPECT_EQ(vector_1, vector_2);
	EXPECT_EQ(vector_2, vector_1);

	Vector_3 vector_3 = vector_2;

	EXPECT_EQ(vector_3, vector_2);
	EXPECT_EQ(vector_2 == vector_3, true);
	EXPECT_EQ(vector_1 != vector_3, false);
}

TEST(Vector_3, Sum)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);

	Vector_3 vector_2 = Vector_3(2.f, 3.f, 4.f);

	EXPECT_EQ(vector_1 + vector_2, Vector_3(3.f, 5.f, 7.f));
	EXPECT_EQ(vector_1 + vector_2, vector_2 + vector_1);

	Vector_3 vector_3 = vector_1;
	vector_3 += vector_2;

	EXPECT_EQ(vector_3, Vector_3(3.f, 5.f, 7.f));
}

TEST(Vector_3, Difference)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);
	Vector_3 vector_2 = Vector_3(2.f, 3.f, 4.f);

	EXPECT_EQ(-vector_1, Vector_3(-1.f, -2.f, -3.f));
	EXPECT_EQ(vector_1 - vector_2, Vector_3(-1.f, -1.f, -1.f));
	EXPECT_EQ(vector_2 - vector_1, Vector_3(1.f, 1.f, 1.f));

	Vector_3 vector_3 = vector_1;
	vector_3 -= vector_2;

	EXPECT_EQ(vector_3, Vector_3(-1.f, -1.f, -1.f));
}

TEST(Vector_3, Product)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);
	Vector_3 vector_2 = Vector_3(2.f, 3.f, 4.f);

	EXPECT_EQ(vector_1 * vector_2, Vector_3(2.f, 6.f, 12.f));
	EXPECT_EQ(vector_2 * vector_1, Vector_3(2.f, 6.f, 12.f));
	EXPECT_EQ(2.f * vector_1, Vector_3(2.f, 4.f, 6.f));
	EXPECT_EQ(vector_1 * 2.f, Vector_3(2.f, 4.f, 6.f));

	Vector_3 vector_3 = vector_1;
	vector_3 *= vector_2;

	EXPECT_EQ(vector_3, Vector_3(2.f, 6.f, 12.f));

	Vector_3 vector_4 = vector_1;
	vector_4 *= 2.f;

	EXPECT_EQ(vector_4, Vector_3(2.f, 4.f, 6.f));
}

TEST(Vector_3, Quotient)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);
	Vector_3 vector_2 = Vector_3(2.f, 3.f, 4.f);

	EXPECT_EQ(vector_1 / vector_2, Vector_3(0.5f, 2.f / 3.f, 0.75f));
	EXPECT_EQ(vector_2 / vector_1, Vector_3(2.f, 1.5f, 4.f / 3.f));
	EXPECT_EQ(vector_1 / 2.f, Vector_3(0.5f, 1.f, 1.5f));

	Vector_3 vector_3 = vector_1;
	vector_3 /= vector_2;

	EXPECT_EQ(vector_3, Vector_3(0.5f, 2.f / 3.f, 0.75f));

	Vector_3 vector_4 = vector_1;
	vector_4 /= 2.f;

	EXPECT_EQ(vector_4, Vector_3(0.5f, 1.f, 1.5f));
}

TEST(Vector_3, Special_Operator)
{
	Vector_3 vector_1 = Vector_3(1.f, 2.f, 3.f);
	Vector_3 vector_2 = Vector_3(2.f, 3.f, 4.f);

	EXPECT_EQ(Vector_3::Dot_Product(vector_1, vector_2), 20.f);
	EXPECT_EQ(Vector_3::Cross_Product(vector_1, vector_2), Vector_3(-1.f, 2.f, -1.f));
	EXPECT_EQ(Vector_3::Magnitude(vector_1), sqrtf(14.f));
	EXPECT_EQ(Vector_3::Normalize(vector_1), Vector_3(1.f, 2.f, 3.f) / sqrtf(14.f));
}
#pragma endregion

#pragma region Vector_4
TEST(Vector_4, Equal)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);
	Vector_4 vector_2 = Vector_4(vector_1);

	EXPECT_EQ(vector_1, vector_2);
	EXPECT_EQ(vector_2, vector_1);

	Vector_4 vector_3 = vector_2;

	EXPECT_EQ(vector_3, vector_2);
	EXPECT_EQ(vector_2 == vector_3, true);
	EXPECT_EQ(vector_1 != vector_3, false);
}

TEST(Vector_4, Sum)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);

	Vector_4 vector_2 = Vector_4(2.f, 3.f, 4.f, 5.f);

	EXPECT_EQ(vector_1 + vector_2, Vector_4(3.f, 5.f, 7.f, 9.f));
	EXPECT_EQ(vector_1 + vector_2, vector_2 + vector_1);

	Vector_4 vector_3 = vector_1;
	vector_3 += vector_2;

	EXPECT_EQ(vector_3, Vector_4(3.f, 5.f, 7.f, 9.f));
}

TEST(Vector_4, Difference)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);

	Vector_4 vector_2 = Vector_4(2.f, 3.f, 4.f, 5.f);

	EXPECT_EQ(-vector_1, Vector_4(-1.f, -2.f, -3.f, -4.f));
	EXPECT_EQ(vector_1 - vector_2, Vector_4(-1.f, -1.f, -1.f, -1.f));
	EXPECT_EQ(vector_2 - vector_1, Vector_4(1.f, 1.f, 1.f, 1.f));

	Vector_4 vector_3 = vector_1;
	vector_3 -= vector_2;

	EXPECT_EQ(vector_3, Vector_4(-1.f, -1.f, -1.f, -1.f));
}

TEST(Vector_4, Product)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);
	Vector_4 vector_2 = Vector_4(2.f, 3.f, 4.f, 5.f);

	EXPECT_EQ(vector_1 * vector_2, Vector_4(2.f, 6.f, 12.f, 20.f));
	EXPECT_EQ(vector_2 * vector_1, Vector_4(2.f, 6.f, 12.f, 20.f));

	EXPECT_EQ(2.f * vector_1, Vector_4(2.f, 4.f, 6.f, 8.f));
	EXPECT_EQ(vector_1 * 2.f, Vector_4(2.f, 4.f, 6.f, 8.f));

	Vector_4 vector_3 = vector_1;
	vector_3 *= vector_2;

	EXPECT_EQ(vector_3, Vector_4(2.f, 6.f, 12.f, 20.f));

	Vector_4 vector_4 = vector_1;
	vector_4 *= 2.f;

	EXPECT_EQ(vector_4, Vector_4(2.f, 4.f, 6.f, 8.f));
}

TEST(Vector_4, Quotient)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);
	Vector_4 vector_2 = Vector_4(2.f, 3.f, 4.f, 5.f);

	EXPECT_EQ(vector_1 / vector_2, Vector_4(0.5f, 2.f / 3.f, 0.75f, 0.8f));
	EXPECT_EQ(vector_2 / vector_1, Vector_4(2.f, 1.5f, 4.f / 3.f, 1.25f));
	EXPECT_EQ(vector_1 / 2.f, Vector_4(0.5f, 1.f, 1.5f, 2.f));

	Vector_4 vector_3 = vector_1;
	vector_3 /= vector_2;

	EXPECT_EQ(vector_3, Vector_4(0.5f, 2.f / 3.f, 0.75f, 0.8f));

	Vector_4 vector_4 = vector_1;
	vector_4 /= 2.f;

	EXPECT_EQ(vector_4, Vector_4(0.5f, 1.f, 1.5f, 2.f));
}

TEST(Vector_4, SpecialOperator)
{
	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);
	Vector_4 vector_2 = Vector_4(2.f, 3.f, 4.f, 5.f);

	EXPECT_EQ(Vector_4::Dot_Product(vector_1, vector_2), 40.f);
	EXPECT_EQ(Vector_4::Magnitude(vector_1), sqrtf(30.f));
	EXPECT_EQ(Vector_4::Normalize(vector_1), Vector_4(1.f, 2.f, 3.f, 4.f) / sqrtf(30.f));
	EXPECT_EQ(Vector_4::Homogenize(vector_1), Vector_4(0.25f, 0.5f, 0.75f, 1.f));
	EXPECT_EQ(vector_1.To_Vector_3(), Vector_3(1.f, 2.f, 3.f));
}
#pragma endregion

#pragma region Matrix_4x4
TEST(Matrix_4x4, Equal)
{
	Matrix_4x4 matrix_1 = Matrix_4x4(
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f
	);

	Matrix_4x4 matrix_2 = Matrix_4x4(matrix_1);

	EXPECT_EQ(matrix_1, matrix_2);
	EXPECT_EQ(matrix_2, matrix_1);

	Matrix_4x4 matrix_3 = matrix_2;

	EXPECT_EQ(matrix_3, matrix_2);
	EXPECT_EQ(matrix_2 == matrix_3, true);
}

TEST(Matrix_4x4, Sum)
{
	Matrix_4x4 matrix_1 = Matrix_4x4(
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f
	);

	Matrix_4x4 matrix_2 = Matrix_4x4(
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f
	);

	Matrix_4x4 matRes = Matrix_4x4(
		3.f, 5.f, 7.f, 9.f,
		3.f, 5.f, 7.f, 9.f,
		3.f, 5.f, 7.f, 9.f,
		3.f, 5.f, 7.f, 9.f
	);

	EXPECT_EQ(matrix_1 + matrix_2, matRes);
	EXPECT_EQ(matrix_1 + matrix_2, matrix_2 + matrix_1);

	Matrix_4x4 matrix_3 = matrix_1;
	matrix_3 += matrix_2;

	EXPECT_EQ(matrix_3, matRes);
}

TEST(Matrix_4x4, Difference)
{
	Matrix_4x4 matrix_1 = Matrix_4x4(
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f
	);

	Matrix_4x4 matrix_2 = Matrix_4x4(
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f
	);

	Matrix_4x4 matrix_resultat_1 = Matrix_4x4(
		-1.f, -2.f, -3.f, -4.f,
		-1.f, -2.f, -3.f, -4.f,
		-1.f, -2.f, -3.f, -4.f,
		-1.f, -2.f, -3.f, -4.f
	);

	EXPECT_EQ(-matrix_1, matrix_resultat_1);

	Matrix_4x4 matrix_resultat_2 = Matrix_4x4(
		-1.f, -1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f, -1.f
	);

	EXPECT_EQ(matrix_1 - matrix_2, matrix_resultat_2);

	Matrix_4x4 matrix_resultat_3 = Matrix_4x4(
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f
	);

	EXPECT_EQ(matrix_2 - matrix_1, matrix_resultat_3);

	Matrix_4x4 matrix_3 = matrix_1;
	matrix_3 -= matrix_2;

	EXPECT_EQ(matrix_3, matrix_resultat_2);
}

TEST(Matrix_4x4, Product)
{
	Matrix_4x4 matrix_1 = Matrix_4x4(
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f
	);

	Matrix_4x4 matrix_2 = Matrix_4x4(
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f,
		2.f, 3.f, 4.f, 5.f
	);

	Matrix_4x4 matrix_resultat_1 = Matrix_4x4(
		20.f, 30.f, 40.f, 50.f,
		20.f, 30.f, 40.f, 50.f,
		20.f, 30.f, 40.f, 50.f,
		20.f, 30.f, 40.f, 50.f
	);

	EXPECT_EQ(matrix_1 * matrix_2, matrix_resultat_1);

	Matrix_4x4 matrix_resultat_2 = Matrix_4x4(
		14.f, 28.f, 42.f, 56.f,
		14.f, 28.f, 42.f, 56.f,
		14.f, 28.f, 42.f, 56.f,
		14.f, 28.f, 42.f, 56.f
	);

	EXPECT_EQ(matrix_2 * matrix_1, matrix_resultat_2);

	Matrix_4x4 matrix_resultat_3 = Matrix_4x4(
		2.f, 4.f, 6.f, 8.f,
		2.f, 4.f, 6.f, 8.f,
		2.f, 4.f, 6.f, 8.f,
		2.f, 4.f, 6.f, 8.f
	);

	EXPECT_EQ(2.f * matrix_1, matrix_resultat_3);
	EXPECT_EQ(matrix_1 * 2.f, matrix_resultat_3);

	Matrix_4x4 matrix_3 = matrix_1;
	matrix_3 *= matrix_2;

	EXPECT_EQ(matrix_3, matrix_resultat_1);

	Matrix_4x4 matrixe_4 = matrix_1;
	matrixe_4 *= 2.f;

	EXPECT_EQ(matrixe_4, matrix_resultat_3);

	Vector_4 vector_1 = Vector_4(1.f, 2.f, 3.f, 4.f);
	Vector_4 vector_result = Vector_4(30.f, 30.f, 30.f, 30.f);

	EXPECT_EQ(matrix_1 * vector_1, vector_result);

	Vector_4 vector_2 = Vector_4(10.f, 20.f, 30.f, 40.f);

	EXPECT_EQ(vector_1 * matrix_1, vector_2);
}

TEST(Matrix_4x4, Special_Operator)
{
	Matrix_4x4 matrix_1 = Matrix_4x4(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	EXPECT_EQ(matrix_1, Matrix_4x4::Identity());

	Matrix_4x4 matrix_2 = Matrix_4x4(
		1.f, 0.f, 3.f, 7.f,
		0.f, 9.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 5.f,
		0.f, 0.f, 0.f, 1.f
	);

	Matrix_4x4 matrix_resultat_1 = Matrix_4x4(
		1.f, 0.f, 0.f, 0.f,
		0.f, 9.f, 0.f, 0.f,
		3.f, 0.f, 1.f, 0.f,
		7.f, 0.f, 5.f, 1.f
	);

	EXPECT_EQ(matrix_2.Transpose(), matrix_resultat_1);

	Matrix_4x4 matrix_3 = Matrix_4x4(
		1.f, 2.f, 3.f, 4.f,
		2.f, 3.f, 4.f, 1.f,
		3.f, 4.f, 1.f, 2.f,
		4.f, 1.f, 2.f, 3.f
	);

	EXPECT_EQ(matrix_3.Determinant(), 160.f);

	Matrix_4x4 matrix_resultat_2 = (1.f / 40.f) *
		Matrix_4x4(
			-9.f, 1.f, 1.f, 11.f,
			1.f, 1.f, 11.f, -9.f,
			1.f, 11.f, -9.f, 1.f,
			11.f, -9.f, 1.f, 1.f
		);

	EXPECT_EQ(matrix_3.Get_Inverse(), matrix_resultat_2);
	EXPECT_EQ(matrix_3.Get_Inverse() * matrix_3, Matrix_4x4::Identity());
	EXPECT_EQ(matrix_3 * matrix_3.Get_Inverse(), Matrix_4x4::Identity());
}

TEST(Matrix_4x4, Transformation)
{
	Matrix_4x4 matrix_1 = Matrix_4x4::Create_Translation_Matrix(Vector_3(1.f, 2.f, -5.f));
	Vector_4 vector_test = Vector_4(1.f, 2.f, 3.f, 1.f);

	EXPECT_EQ((matrix_1 * vector_test).To_Vector_3(), Vector_3(2.f, 4.f, -2.f));

	Matrix_4x4 matrix_2 = Matrix_4x4::Create_Rotation_Matrix(Vector_3(0.f, 180.f, 0.f));

	EXPECT_EQ((matrix_2 * vector_test).To_Vector_3(), Vector_3(-1.f, 2.f, -3.f));

	Matrix_4x4 matrix_3 = Matrix_4x4::Create_Scale_Matrix(Vector_3(1.f, 2.f, 3.f));

	EXPECT_EQ((matrix_3 * vector_test).To_Vector_3(), Vector_3(1.f, 4.f, 9.f));

	Matrix_4x4 matrixe_4 = Matrix_4x4::Create_Transformation_Matrix(Vector_3(1.f, 2.f, -5.f), Vector_3(1.f, 2.f, 3.f), Vector_3(0.f, 180.f, 0.f));
	Matrix_4x4 matrix_5 = matrix_1 * matrix_2 * matrix_3;

	EXPECT_EQ(matrixe_4 * vector_test, matrix_5 * vector_test);


}
#pragma endregion

#pragma region Quaternion
TEST(Quaternion, Equal)
{
	Quaternion quaternion_1 = Quaternion(1.f, 2.f, 3.f, 4.f);
	Quaternion quaternion_2 = Quaternion(quaternion_1);

	EXPECT_EQ(quaternion_1, quaternion_2);
	EXPECT_EQ(quaternion_2, quaternion_1);

	Quaternion quaternion_3 = quaternion_2;

	EXPECT_EQ(quaternion_3, quaternion_2);
	EXPECT_EQ(quaternion_2 == quaternion_3, true);
}

TEST(Quaternion, Sum)
{
	Quaternion quaternion_1 = Quaternion(1.f, 2.f, 3.f, 4.f);
	Quaternion quaternion_2 = Quaternion(2.f, 3.f, 4.f, 5.f);
	Quaternion quaternion_resultat = Quaternion(3.f, 5.f, 7.f, 9.f);

	EXPECT_EQ(quaternion_1 + quaternion_2, quaternion_resultat);
	EXPECT_EQ(quaternion_1 + quaternion_2, quaternion_2 + quaternion_1);

	Quaternion quaternion_3 = quaternion_1;
	quaternion_3 += quaternion_2;

	EXPECT_EQ(quaternion_3, quaternion_resultat);
}

TEST(Quaternion, Difference)
{
	Quaternion quaternion_1 = Quaternion(1.f, 2.f, 3.f, 4.f);
	Quaternion quaternion_2 = Quaternion(2.f, 3.f, 4.f, 5.f);
	Quaternion quaternion_resultat1 = Quaternion(-1.f, -2.f, -3.f, -4.f);

	EXPECT_EQ(-quaternion_1, quaternion_resultat1);

	Quaternion quaternion_resultat2 = Quaternion(-1.f, -1.f, -1.f, -1.f);

	EXPECT_EQ(quaternion_1 - quaternion_2, quaternion_resultat2);

	Quaternion quaternion_resultat3 = Quaternion(1.f, 1.f, 1.f, 1.f);

	EXPECT_EQ(quaternion_2 - quaternion_1, quaternion_resultat3);

	Quaternion quaternion_3 = quaternion_1;
	quaternion_3 -= quaternion_2;

	EXPECT_EQ(quaternion_3, quaternion_resultat2);
}

TEST(Quaternion, Product)
{
	Quaternion quaternion_1 = Quaternion(1.f, 2.f, 3.f, 4.f);
	Quaternion quaternion_2 = Quaternion(2.f, 3.f, 4.f, 5.f);
	Quaternion quaternion_resultat1 = Quaternion(12.f, 24.f, 30.f, 0.f);

	EXPECT_EQ(quaternion_1 * quaternion_2, quaternion_resultat1);

	Quaternion quaternion_resultat2 = Quaternion(14.f, 20.f, 32.f, 0.f);

	EXPECT_EQ(quaternion_2 * quaternion_1, quaternion_resultat2);

	Quaternion quaternion_resultat3 = Quaternion(2.f, 4.f, 6.f, 8.f);

	EXPECT_EQ(quaternion_1 * 2.f, quaternion_resultat3);

	Quaternion quaternion_3 = quaternion_1;
	quaternion_3 *= quaternion_2;

	EXPECT_EQ(quaternion_3, quaternion_resultat1);

	Quaternion quaternion_4 = quaternion_1;
	quaternion_4 *= 2.f;

	EXPECT_EQ(quaternion_4, quaternion_resultat3);
}

TEST(Quaternion, Quotient)
{
	Quaternion quaternion_1 = Quaternion(1.f, 2.f, 3.f, 4.f);
	Quaternion quaternion_resultat = Quaternion(0.5f, 1.f, 1.5f, 2.f);

	EXPECT_EQ(quaternion_1 / 2.f, quaternion_resultat);

	Quaternion quaternion_2 = quaternion_1;
	quaternion_2 /= 2.f;

	EXPECT_EQ(quaternion_2, quaternion_resultat);
}

TEST(Quaternion, Special_Operator)
{
	Quaternion quaternion_1 = Quaternion(0.f, 0.f, 0.f, 1.f);

	EXPECT_EQ(quaternion_1, Quaternion::Identity());

	Quaternion quaternion_2 = Quaternion(1.f, 2.f, 3.f, 4.f);

	EXPECT_EQ(quaternion_2.Conjugate(), Quaternion(-1.f, -2.f, -3.f, 4.f));
	EXPECT_EQ(quaternion_2.Length(), sqrtf(30.f));
	EXPECT_EQ(quaternion_2.Normalize(), quaternion_2 / sqrtf(30.f));
	EXPECT_EQ(quaternion_2.Invert() * quaternion_2, Quaternion::Identity());
	EXPECT_EQ(quaternion_2 * quaternion_2.Invert(), Quaternion::Identity());
	EXPECT_EQ(Quaternion::Quaternion_From_Axis_Angle(Vector_3(1.f, 0.f, 1.f), 45.f), Quaternion(0.270598f, 0.f, 0.270598f, 0.92388f));
	EXPECT_EQ(Quaternion::Quaternion_From_Euler(0.f, 90.f, 0.f), Quaternion(0.f, 0.707107f, 0.f, 0.707107f));
	EXPECT_EQ(Quaternion(0.f, 0.707107f, 0.f, 0.707107f).Quaternion_To_Euler(), Vector_3(0.f, 90.f, 0.f));
	
	Matrix_4x4 matrix_resutlat = Matrix_4x4(
		-1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, -1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
	
	EXPECT_EQ(Quaternion::Quatertion_To_Matrix_4x4(Quaternion(0.f, 1.f, 0.f, 0.f)), matrix_resutlat);
}
#pragma endregion