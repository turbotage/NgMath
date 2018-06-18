#pragma once

#include "mathdef.h"
#include "vec3f.h"
#include "vec4f.h"
#include "mat4f.h"

namespace ngm {

	/**  Representation, in memory xi + yj + zk + w where   **/
	ALIGN(16) class Quaternion
	{
	public:

		__m128 row;

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		Quaternion();
		Quaternion(float scalar);
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Quaternion& Quaternion);
		
		Quaternion& add(const Quaternion& other);
		Quaternion& operator+=(const Quaternion& other);
		Quaternion& sub(const Quaternion& other);
		Quaternion& operator-=(const Quaternion& other);
		Quaternion& mul(const Quaternion& other);
		Quaternion& operator*=(const Quaternion& other);
		//Quaternion operator*(const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Quaternion& right);

		Quaternion& setRotation(const Vec3f& rotationAxis, float angle);
		static Quaternion getQuaternion(const Vec3f& rotationAxis, float angle);

		Quaternion& setFromEulerAngles(const Vec3f& eulerAngles);
		Vec3f getEulerAngles();
		static Vec3f getEulerAngles(const Quaternion& quat);

		void rotate(Vec3f& vec);
		static Vec3f getRotation(const Quaternion& quat, const Vec3f& vec);

		void rotate4(Vec3f& v1, Vec3f& v2, Vec3f& v3, Vec3f& v4);

		float norm();
		static float norm(const Quaternion& quat);

		float length();
		static float length(const Quaternion& quat);

		Quaternion& normalize();
		static Quaternion normalized(const Quaternion& quat);

		~Quaternion();

	};
}
