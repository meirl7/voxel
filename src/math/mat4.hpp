#pragma once

#include "vec3.hpp"

namespace gm
{
	
	struct Mat4
	{
		float m[16];

		constexpr Mat4() : m{0} {}
		
		constexpr explicit Mat4(float d) : m{
			d, 0.f, 0.f, 0.f,
			0.f, d, 0.f, 0.f,
			0.f, 0.f, d, 0.f,
			0.f, 0.f, 0.f, d
			} { }

		constexpr Mat4(
			float m0, float m1, float m2, float m3,
			float m4, float m5, float m6, float m7,
			float m8, float m9, float m10, float m11,
			float m12, float m13, float m14, float m15
		) : m
			{
				m0, m1, m2, m3, 
				m4, m5, m6, m7, 
				m8, m9, m10, m11, 
				m12, m13, m14, m15
			} { }

		constexpr Mat4 operator+(const Mat4& o)
		{
			return
			{
				m[0] + o.m[0], m[1] + o.m[1], m[2] + o.m[2], m[3] + o.m[3],
				m[4] + o.m[4], m[5] + o.m[5], m[6] + o.m[6], m[7] + o.m[7],
				m[8] + o.m[8], m[9] + o.m[9], m[10] + o.m[10], m[11] + o.m[11],
				m[12] + o.m[12], m[13] + o.m[13], m[14] + o.m[14], m[15] + o.m[15]
			};
		}
		constexpr Mat4 operator+(const Mat4& o)
		{
			return
			{
				m[0] - o.m[0], m[1] - o.m[1], m[2] - o.m[2], m[3] - o.m[3],
				m[4] - o.m[4], m[5] - o.m[5], m[6] - o.m[6], m[7] - o.m[7],
				m[8] - o.m[8], m[9] - o.m[9], m[10] - o.m[10], m[11] - o.m[11],
				m[12] - o.m[12], m[13] - o.m[13], m[14] - o.m[14], m[15] - o.m[15]
			};
		}
		constexpr Mat4 operator*(const Mat4& o)
		{
			return
			{
				m[0] * o.m[0] + m[1] * o.m[4] + m[2] * o.m[8] + m[3] * o.m[12],
				m[0] * o.m[1] + m[1] * o.m[5] + m[2] * o.m[9] + m[3] * o.m[13],
				m[0] * o.m[2] + m[1] * o.m[6] + m[2] * o.m[10] + m[3] * o.m[14],
				m[0] * o.m[3] + m[1] * o.m[7] + m[2] * o.m[11] + m[3] * o.m[15],

				m[4] * o.m[0] + m[5] * o.m[4] + m[6] * o.m[8] + m[7] * o.m[12],
				m[4] * o.m[1] + m[5] * o.m[5] + m[6] * o.m[9] + m[7] * o.m[13],
				m[4] * o.m[2] + m[5] * o.m[6] + m[6] * o.m[10] + m[7] * o.m[14],
				m[4] * o.m[3] + m[5] * o.m[7] + m[6] * o.m[11] + m[7] * o.m[15],

				m[8] * o.m[0] + m[9] * o.m[4] + m[10] * o.m[8] + m[11] * o.m[12],
				m[8] * o.m[1] + m[9] * o.m[5] + m[10] * o.m[9] + m[11] * o.m[13],
				m[8] * o.m[2] + m[9] * o.m[6] + m[10] * o.m[10] + m[11] * o.m[14],
				m[8] * o.m[3] + m[9] * o.m[7] + m[10] * o.m[11] + m[11] * o.m[15],

				m[12] * o.m[0] + m[13] * o.m[4] + m[14] * o.m[8] + m[15] * o.m[12],
				m[12] * o.m[1] + m[13] * o.m[5] + m[14] * o.m[9] + m[15] * o.m[13],
				m[12] * o.m[2] + m[13] * o.m[6] + m[14] * o.m[10] + m[15] * o.m[14],
				m[12] * o.m[3] + m[13] * o.m[7] + m[14] * o.m[11] + m[15] * o.m[15]
			};
		}
	};

	Mat4 perspective(float fov, float aspect, float near, float far)
	{
		const float halfTan = tan(fov) / 2.f;
		Mat4 matrix{};
		matrix.m[0] = 1.f / (aspect * halfTan);
		matrix.m[5] = 1.f / halfTan;
		matrix.m[10] = -(far + near) / (far - near);
		matrix.m[11] = -(2.f * far * near) / (far - near);
		matrix.m[14] = -1.f;
		return matrix;
	}

	Mat4 lookAt(vec3f& eye, vec3f& center, const vec3f& up)
	{
		Mat4 matrix(1.f);
		vec3f fwd = (center - eye).normalized();
		vec3f u = cross(fwd, up);

	}
}