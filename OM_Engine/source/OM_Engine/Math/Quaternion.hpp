#pragma once

#include "OM_Engine/Base.hpp"
#include <string>

namespace Math
{
    class Vector_3;
    class Matrix_4x4;
	class Quaternion
	{
        // Behavior
    public:
        Quaternion(const float x = 0.f, const float y = 0.f, const float z = 0.f, const float w = 1.f);
        Quaternion(const Vector_3& vector, const float scalar);
        Quaternion(const Quaternion& copy);
        float m_x, m_y, m_z, m_w;

        // Quaternion modification
        static Quaternion Identity();
        Quaternion Normalize() const;
        float Length() const;
        Quaternion Conjugate() const;
        Quaternion Invert() const;

        // Transformation
        static Matrix_4x4 Quatertion_To_Matrix_4x4(const Quaternion& quaternion);
        static Quaternion Quaternion_From_Euler(const float& yaw, const float& pitch, const float& roll);
        static Quaternion Quaternion_From_Euler(const Vector_3& euler_rad_angles);
        Vector_3 Quaternion_To_Euler() const;
        static Quaternion Quaternion_From_Axis_Angle(const Vector_3& axis, float rad_angle);
        void Quaternion_To_Axis_Angle(Vector_3& out_axis, float& out_angle);
        static Quaternion Vector_3_To_Vector_3(const Vector_3& from, const Vector_3& to);

        // Utils
        std::string To_String();
        static float Angle(const Quaternion& quaternion_1, const Quaternion& quaternion_2);
        static Quaternion Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor);
        static Quaternion N_Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor);
        static Quaternion S_Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor);

        // Operators 
        Quaternion operator+(const Quaternion& quaternion) const;
        Quaternion operator-(const Quaternion& quaternion) const;
        Quaternion operator-() const;
        Quaternion operator*(const Quaternion& quaternion) const;
        Quaternion operator*(const float s) const;
        Quaternion operator/(const float s) const;
        void operator+=(const Quaternion& quaternion);
        void operator-=(const Quaternion& quaternion);
        void operator*=(const Quaternion& quaternion);
        void operator*=(const float s);
        void operator/=(const float s);
        friend bool operator==(const Quaternion& left, const Quaternion& right);
    };
    std::ostream& operator<<(std::ostream& o, const Quaternion& q);
}
#include "OM_Engine/Math/Quaternion.inl"