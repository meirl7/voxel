#pragma once

#include <cmath>

namespace gm
{
    template <typename T>
    struct vec3
    {
        T x, y, z;

        constexpr vec3() : x(0), y(0), z(0) {}
        constexpr vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        constexpr explicit vec3(T n) : x(n), y(n), z(n) {}

        constexpr vec3<T> operator+(const vec3<T>& o)
        {
            return { x + o.x, y + o.y, z + o.z };
        }
        constexpr vec3<T> operator-(const vec3<T>& o)
        {
            return { x - o.x, y - o.y, z - o.z };
        }

        constexpr vec3<T> operator*(float s)
        {
            return { x * s, y * s, z * s };
        }
        constexpr vec3<T> operator/(float s)
        {
            return { x / s, y / s, z / s };
        }

        constexpr vec3<T>& operator+=(const vec3<T>& o)
        {
            x += o.x;
            y += o.y;
            z += o.z;
            return *this;
        }
        constexpr vec3<T>& operator-=(const vec3<T>& o)
        {
            x -= o.x;
            y -= o.y;
            z -= o.z;
            return *this;
        }

        constexpr vec3<T>& operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        constexpr vec3<T>& operator/=(float s)
        {
            x /= s;
            y /= s;
            z /= s;
            return *this;
        }

        constexpr float lengthSq()
        {
            return x * x + y * y + z * z;
        }

        float length()
        {
            return std::sqrt(lengthSq());
        }

        vec3<T> normalized()
        {
            float len = length();
            return (len != 0.0f) ? (*this * (1.0f / len)) : vec3<T>{};
        }

        void normalize()
        {
            float len = length();
            if (len != 0.0f)
            {
                float inv = 1.0f / len;
                x *= inv; y *= inv; z *= inv;
            }
        }

        constexpr bool operator==(const vec3<T>& o)
        {
            return x == o.x && y == o.y && z == o.z;
        }
        constexpr bool operator!=(const vec3<T>& o)
        {
            return !(*this == o);
        }
    };

    constexpr float dot(const vec3<float>& a, const vec3<float>& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    constexpr float dot(const vec3<int>& a, const vec3<int>& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    vec3<float> cross(const vec3<float>& a, const vec3<float>& b)
    {
        return
        {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    using vec3f = vec3<float>;
    using vec3i = vec3<int>;
}