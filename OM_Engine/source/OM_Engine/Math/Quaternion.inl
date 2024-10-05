#pragma once

#include "OM_Engine/Math/Vector_3.hpp"
#include "OM_Engine/Math/Matrix_4x4.hpp"
#include "OM_Engine/Utils.hpp"

namespace Math
{
    inline Quaternion::Quaternion(const float x, const float y, const float z, const float w)
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_w(w)
    {
    }

    inline Quaternion::Quaternion(const Vector_3& vector, const float scalar)
        : m_x(vector.m_x)
        , m_y(vector.m_y)
        , m_z(vector.m_z)
        , m_w(scalar)
    {
    }

    inline Quaternion::Quaternion(const Quaternion& other)
        : m_x(other.m_x)
        , m_y(other.m_y)
        , m_z(other.m_z)
        , m_w(other.m_w)
    {
    }

    inline Quaternion Quaternion::Identity()
    {
        return { 0.f, 0.f, 0.f, 1.f };
    }

    inline Quaternion Quaternion::Normalize() const
    {
        float length = this->Length();

        if (length < Utils::WEAK_ESPILON)
        {
            length = 1.0f;
        }

        float inverse_length = 1.0f / length;

        return {
                m_x * inverse_length,
                m_y * inverse_length,
                m_z * inverse_length,
                m_w * inverse_length
        };
    }

    inline float Quaternion::Length() const
    {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
    }

    inline Quaternion Quaternion::Conjugate() const
    {
        return Quaternion(-m_x, -m_y, -m_z, m_w);
    }

    inline Quaternion Quaternion::Invert() const
    {
        Quaternion result = *this;
        float length = this->Length();
        float length_squared = length * length;

        if (length_squared != 0.0)
        {
            float inverse = 1.0f / length_squared;

            result.m_x *= -inverse;
            result.m_y *= -inverse;
            result.m_z *= -inverse;
            result.m_w *= inverse;
        }

        return result;
    }

    inline Matrix_4x4 Quaternion::Quatertion_To_Matrix_4x4(const Quaternion& quaternion)
    {
        quaternion.Normalize();

        return {
                2.f * (quaternion.m_w * quaternion.m_w + quaternion.m_x * quaternion.m_x) - 1.f,    2.f * (quaternion.m_x * quaternion.m_y - quaternion.m_z * quaternion.m_w),          2.f * (quaternion.m_x * quaternion.m_z + quaternion.m_y * quaternion.m_w),          0.f,
                2.f * (quaternion.m_x * quaternion.m_y + quaternion.m_z * quaternion.m_w),          2.f * (quaternion.m_w * quaternion.m_w + quaternion.m_y * quaternion.m_y) - 1.f,    2.f * (quaternion.m_y * quaternion.m_z - quaternion.m_x * quaternion.m_w),          0.f,
                2.f * (quaternion.m_x * quaternion.m_z - quaternion.m_y * quaternion.m_w),          2.f * (quaternion.m_y * quaternion.m_z + quaternion.m_x * quaternion.m_w),          2.f * (quaternion.m_w * quaternion.m_w + quaternion.m_z * quaternion.m_z) - 1.f,    0.f,
                0.f,                                            0.f,                                            0.f,                                            1.f
        };
    }


    inline Quaternion Quaternion::Quaternion_From_Euler(const float& x, const float& y, const float& z)
    {
        const float cr = cosf(Utils::DEG_TO_RAD * x * 0.5f);
        const float sr = sinf(Utils::DEG_TO_RAD * x * 0.5f);
        const float cp = cosf(Utils::DEG_TO_RAD * y * 0.5f);
        const float sp = sinf(Utils::DEG_TO_RAD * y * 0.5f);
        const float cy = cosf(Utils::DEG_TO_RAD * z * 0.5f);
        const float sy = sinf(Utils::DEG_TO_RAD * z * 0.5f);

        Quaternion quaternion;
        quaternion.m_w = cr * cp * cy + sr * sp * sy;
        quaternion.m_x = sr * cp * cy - cr * sp * sy;
        quaternion.m_y = cr * sp * cy + sr * cp * sy;
        quaternion.m_z = cr * cp * sy - sr * sp * cy;

        return quaternion;
    }

    inline Quaternion Quaternion::Quaternion_From_Euler(const Vector_3& euler_rad_angles)
    {
        return Quaternion_From_Euler(euler_rad_angles.m_x, euler_rad_angles.m_y, euler_rad_angles.m_z);
    }

    inline Vector_3 Quaternion::Quaternion_To_Euler() const
    {
        Vector_3 euler;

        double sqw = m_w * m_w;
        double sqx = m_x * m_x;
        double sqy = m_y * m_y;
        double sqz = m_z * m_z;
        double unit = sqx + sqy + sqz + sqw;
        double test = m_x * m_y + m_z * m_w;
        if (test > 0.499 * unit)
        {
            euler.m_y = static_cast<float>(2.0 * atan2(m_x, m_w));
            euler.m_z = static_cast<float>(M_PI / 2.0);
            euler.m_x = static_cast<float>(0.0);
            return euler * Utils::RAD_TO_DEG;
        }
        if (test < -0.499 * unit) { // singularity at south pole
            euler.m_y = static_cast<float>(-2.0 * atan2(m_x, m_w));
            euler.m_z = static_cast<float>(-M_PI / 2.0);
            euler.m_x = static_cast<float>(0.0);
            return euler * Utils::RAD_TO_DEG;
        }
        euler.m_y = static_cast<float>(atan2(2.0 * m_y * m_w - 2.0 * m_x * m_z, sqx - sqy - sqz + sqw));
        euler.m_z = static_cast<float>(asin(2.0 * test / unit));
        euler.m_x = static_cast<float>(atan2(2.0 * m_x * m_w - 2.0 * m_y * m_z, -sqx + sqy - sqz + sqw));

        return euler * Utils::RAD_TO_DEG;
    }

    inline Quaternion Quaternion::Quaternion_From_Axis_Angle(const Vector_3& axis, float rad_angle)
    {
        Quaternion result = Identity();

        if (Math::Vector_3::Magnitude(axis) != 0.0f)
        {
            rad_angle *= 0.5f;
        }
        Vector_3 new_axis = Math::Vector_3::Normalize(axis);

        float cosres = cos(rad_angle * Utils::DEG_TO_RAD);
        float sinres = sin(rad_angle * Utils::DEG_TO_RAD);

        result.m_x = new_axis.m_x * sinres;
        result.m_y = new_axis.m_y * sinres;
        result.m_z = new_axis.m_z * sinres;
        result.m_w = cosres;

        return result.Normalize();
    }

    inline void Quaternion::Quaternion_To_Axis_Angle(Vector_3& out_axis, float& out_angle)
    {
        if (Utils::Absolute(m_w) > 1.0f)
        {
            *this = this->Normalize();
        }

        Vector_3 res_axis = { 0.0f, 0.0f, 0.0f };
        float res_angle = 2.0f * acos(m_w);
        float den = sqrt(1.0f - m_w * m_w);

        if (den > 0.0001f)
        {
            res_axis.m_x = m_x / den;
            res_axis.m_y = m_y / den;
            res_axis.m_z = m_z / den;
        }
        else
        {
            res_axis.m_x = m_x;
            res_axis.m_y = m_y;
            res_axis.m_z = m_z;
        }

        out_axis = res_axis;
        out_angle = res_angle;
    }

    inline Quaternion Quaternion::Vector_3_To_Vector_3(const Vector_3& from, const Vector_3& to)
    {
        Quaternion result = { 0.f, 0.f, 0.f, 0.f };

        float dot_product = Vector_3::Dot_Product(from, to);
        Vector_3 cross_product = Vector_3::Cross_Product(from, to);

        result.m_x = cross_product.m_x;
        result.m_y = cross_product.m_y;
        result.m_z = cross_product.m_z;
        result.m_w = 1.0f + dot_product;

        return result.Normalize();
    }

    inline std::string Quaternion::To_String()
    {
        return "[ " + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + " ]";
    }

    inline float Quaternion::Angle(const Quaternion& quaternion_1, const Quaternion& quaternion_2)
    {
        float inner_prod = quaternion_1.m_x * quaternion_2.m_x + quaternion_1.m_y * quaternion_2.m_y + quaternion_1.m_z * quaternion_2.m_z + quaternion_1.m_w * quaternion_2.m_w;
        return acos((2 * inner_prod * inner_prod) - 1.f) * Utils::RAD_TO_DEG;
    }

    inline Quaternion Quaternion::Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor)
    {
        factor = Utils::Clamp(factor, 0.f, 1.f);
        return {
                quaternion_1.m_x + factor * (quaternion_2.m_x - quaternion_1.m_x),
                quaternion_1.m_y + factor * (quaternion_2.m_y - quaternion_1.m_y),
                quaternion_1.m_z + factor * (quaternion_2.m_z - quaternion_1.m_z),
                quaternion_1.m_w + factor * (quaternion_2.m_w - quaternion_1.m_w)
        };
    }

    inline Quaternion Quaternion::N_Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor)
    {
        factor = Utils::Clamp(factor, 0.f, 1.f);

        Quaternion result = Lerp(quaternion_1, quaternion_2, factor);

        return result.Normalize();
    }

    inline Quaternion Quaternion::S_Lerp(const Quaternion& quaternion_1, const Quaternion& quaternion_2, float factor)
    {
        if (factor > 1.f)
        {
            return quaternion_2;
        }
        float cos_half_omega = quaternion_1.m_x * quaternion_2.m_x + quaternion_1.m_y * quaternion_2.m_y + quaternion_1.m_z * quaternion_2.m_z + quaternion_1.m_w * quaternion_2.m_w;

        Quaternion tto = quaternion_2;
        if (cos_half_omega < 0.f)
        {
            tto = { -tto.m_x, -tto.m_y, -tto.m_z, -tto.m_w };
            cos_half_omega = -cos_half_omega;
        }

        if (Utils::Absolute(cos_half_omega) >= 1.0f)
        {
            return quaternion_1;
        }
        else
        {
            float half_omega = acos(cos_half_omega);
            float sin_half_omega = sqrt(1.f - cos_half_omega * cos_half_omega);

            float ratio_a = (sin((1.f - factor) * half_omega) / sin_half_omega);
            float ratio_b = (sin(factor * half_omega) / sin_half_omega);
            return { (quaternion_1.m_x * ratio_a + tto.m_x * ratio_b),
                (quaternion_1.m_y * ratio_a + tto.m_y * ratio_b),
                (quaternion_1.m_z * ratio_a + tto.m_z * ratio_b),
                (quaternion_1.m_w * ratio_a + tto.m_w * ratio_b) };
        }
    }

    inline Quaternion Quaternion::operator+(const Quaternion& quaternion) const
    {
        return
        {
                m_x + quaternion.m_x,
                m_y + quaternion.m_y,
                m_z + quaternion.m_z,
                m_w + quaternion.m_w
        };
    }

    inline Quaternion Quaternion::operator-(const Quaternion& quaternion) const
    {
        return
        {
                m_x - quaternion.m_x,
                m_y - quaternion.m_y,
                m_z - quaternion.m_z,
                m_w - quaternion.m_w
        };
    }

    inline Quaternion Quaternion::operator-() const
    {
        return Quaternion(-m_x, -m_y, -m_z, -m_w);
    }

    inline Quaternion Quaternion::operator*(const Quaternion& quaternion) const
    {
        return
        {
                m_w * quaternion.m_x + m_x * quaternion.m_w + m_y * quaternion.m_z - m_z * quaternion.m_y,
                m_w * quaternion.m_y + m_y * quaternion.m_w + m_z * quaternion.m_x - m_x * quaternion.m_z,
                m_w * quaternion.m_z + m_z * quaternion.m_w + m_x * quaternion.m_y - m_y * quaternion.m_x,
                m_w * quaternion.m_w - m_x * quaternion.m_x - m_y * quaternion.m_y - m_z * quaternion.m_z
        };
    }

    inline Quaternion Quaternion::operator*(const float s) const
    {
        return Quaternion(m_x * s, m_y * s, m_z * s, m_w * s);
    }

    inline Quaternion Quaternion::operator/(const float s) const
    {
        return Quaternion(m_x / s, m_y / s, m_z / s, m_w / s);
    }

    inline void Quaternion::operator+=(const Quaternion& quaternion)
    {
        *this = *this + quaternion;
    }

    inline void Quaternion::operator-=(const Quaternion& quaternion)
    {
        *this = *this - quaternion;
    }

    inline void Quaternion::operator*=(const Quaternion& quaternion)
    {
        *this = *this * quaternion;
    }

    inline void Quaternion::operator*=(const float s)
    {
        *this = *this * s;
    }

    inline void Quaternion::operator/=(const float s)
    {
        *this = *this / s;
    }

    inline bool operator==(const Quaternion& quaternion, const Quaternion& right)
    {
        return (
            Utils::Absolute(quaternion.m_x - right.m_x) <= Utils::WEAK_ESPILON &&
            Utils::Absolute(quaternion.m_y - right.m_y) <= Utils::WEAK_ESPILON &&
            Utils::Absolute(quaternion.m_z - right.m_z) <= Utils::WEAK_ESPILON &&
            Utils::Absolute(quaternion.m_w - right.m_w) <= Utils::WEAK_ESPILON
            );
    }

    inline std::ostream& operator<<(std::ostream& o, const Quaternion& quaternion)
    {
        return o << "x = " << quaternion.m_x << ", y = " << quaternion.m_y << ", z = " << quaternion.m_z << ", w = " << quaternion.m_w;
    }
}