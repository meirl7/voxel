#pragma once

#include <cmath>

namespace gm
{
    template <typename T>
    struct vec4
    {
        T x, y, z, w;

        constexpr vec4() : x(0), y(0), z(0), w(0) {}
        constexpr vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        constexpr explicit vec4(T n) : x(n), y(n), z(n), w(n) {}

        constexpr vec4<T> operator+(const vec4<T>& o)
        {
            return { x + o.x, y + o.y, z + o.z, w + o.w };
        }
        constexpr vec4<T> operator-(const vec4<T>& o)
        {
            return { x - o.x, y - o.y, z - o.z, w - o.w };
        }

        constexpr vec4<T> operator*(float s)
        {
            return { x * s, y * s, z * s, w * s };
        }
        constexpr vec4<T> operator/(float s)
        {
            return { x / s, y / s, z / s, w * s };
        }

        constexpr vec4<T>& operator+=(const vec4<T>& o)
        {
            x += o.x;
            y += o.y;
            z += o.z;
            w += o.w;
            return *this;
        }
        constexpr vec4<T>& operator-=(const vec4<T>& o)
        {
            x -= o.x;
            y -= o.y;
            z -= o.z;
            w -= o.w;
            return *this;
        }

        constexpr vec4<T>& operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }
        constexpr vec4<T>& operator/=(float s)
        {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
            return *this;
        }

        constexpr float lengthSq()
        {
            return x * x + y * y + z * z + w * w;
        }

        float length()
        {
            return std::sqrt(lengthSq());
        }

        vec4<T> normalized()
        {
            float len = length();
            return (len != 0.0f) ? (*this * (1.0f / len)) : vec4<T>{};
        }

        void normalize()
        {
            float len = length();
            if (len != 0.0f)
            {
                float inv = 1.0f / len;
                x *= inv;
                y *= inv;
                z *= inv;
                w *= inv;
            }
        }

        constexpr bool operator==(const vec4<T>& o)
        {
            return x == o.x && y == o.y && z == o.z && w == o.w;
        }
        constexpr bool operator!=(const vec4<T>& o)
        {
            return !(*this == o);
        }
    };

    using vec4f = vec4<float>;
    using vec4i = vec4<int>;
}