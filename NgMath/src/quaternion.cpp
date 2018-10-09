#include "quaternion.h"

float ngm::Quaternion::getX() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(0, 0, 0, 0)));
}

float ngm::Quaternion::getY() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(1, 1, 1, 1)));
}

float ngm::Quaternion::getZ() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(2, 2, 2, 2)));
}

float ngm::Quaternion::getW() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(3, 3, 3, 3)));
}

ngm::Quaternion::Quaternion()
{
	_mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
}

ngm::Quaternion::Quaternion(float scalar)
{
	_mm_set_ps(scalar, scalar, scalar, scalar);
}

ngm::Quaternion::Quaternion(float x, float y, float z, float w)
{
	_mm_set_ps(w, z, y, x);
}

ngm::Quaternion::Quaternion(const Quaternion & Quaternion)
{
	row = Quaternion.row;
}

ngm::Quaternion & ngm::Quaternion::add(const Quaternion & other)
{
	row = _mm_add_ps(row, other.row);
	return *this;
}

ngm::Quaternion & ngm::Quaternion::operator+=(const Quaternion & other)
{
	return add(other);
}

ngm::Quaternion & ngm::Quaternion::sub(const Quaternion & other)
{
	row = _mm_sub_ps(row, other.row);
	return *this;
}

ngm::Quaternion & ngm::Quaternion::operator-=(const Quaternion & other)
{
	return sub(other);
}

ngm::Quaternion & ngm::Quaternion::mul(const Quaternion & other)
{
	Quaternion ret;
	ret.row = _mm_mul_ps(_mm_set_ps(getW(), getW(), getW(), getW()), _mm_set_ps(other.getW(), other.getZ(), other.getY(), other.getX()));
	__m128 temp = _mm_mul_ps(_mm_set_ps(-1.0f * getX(), getZ(), getY(), getX()), _mm_set_ps(other.getX(), other.getW(), other.getW(), other.getW()));
	ret.row = _mm_add_ps(ret.row, temp);
	temp = _mm_mul_ps(_mm_set_ps(-1.0f * getY(), getX(), getZ(), getY()), _mm_set_ps(other.getY(), other.getY(), other.getX(), other.getZ()));
	ret.row = _mm_add_ps(ret.row, temp);
	temp = _mm_mul_ps(_mm_set_ps(getZ(), getY(), getX(), getZ()), _mm_set_ps(other.getZ(), other.getX(), other.getZ(), other.getY()));
	ret.row = _mm_sub_ps(ret.row, temp);
	ret.normalize();
	row = ret.row;
	return *this;
}

ngm::Quaternion & ngm::Quaternion::operator*=(const Quaternion & other)
{
	return mul(other);
}

/*
ngm::Quaternion ngm::Quaternion::operator*(const Quaternion & right)
{
	return mul(right);
}
*/

ngm::Quaternion & ngm::Quaternion::setRotation(const Vec3f & rotationAxis, float angle)
{
	float sinAngle = sin(angle*0.5);
	row = _mm_set_ps(
		cos(angle*0.5),
		rotationAxis.z * sinAngle,
		rotationAxis.y * sinAngle,
		rotationAxis.x * sinAngle
	);
	return *this;
}

ngm::Quaternion ngm::Quaternion::getQuaternion(const Vec3f & rotationAxis, float angle)
{
	Quaternion quat;
	float sinAngle = sin(angle*0.5);
	quat.row = _mm_set_ps(
		cos(angle*0.5),
		rotationAxis.z * sinAngle,
		rotationAxis.y * sinAngle,
		rotationAxis.x * sinAngle
	);
	return quat;
}

ngm::Quaternion & ngm::Quaternion::setFromEulerAngles(const Vec3f & eulerAngles)
{
	Quaternion pitch(1.0, 0.0, 0.0, eulerAngles.x);
	Quaternion yaw(0.0, 1.0, 0.0, eulerAngles.y);
	Quaternion roll(0.0, 0.0, 1.0, eulerAngles.z);
	row = (pitch * yaw * roll).row;
	return *this;
}

ngm::Vec3f ngm::Quaternion::getEulerAngles()
{
	return Vec3f(
		atan2(2.0f * (getX() * getY() + getZ() * getW()), 1.0f - 2.0f * (getY() * getY() + getZ() * getZ()))
		, asin(2.0f * (getX() * getW() + getY() * getZ()))
		, atan2(2.0f * (getX() * getW() + getY() * getZ()), 1.0f - 2.0f * (getZ() * getZ() + getW() * getW()))
		);
}

ngm::Vec3f ngm::Quaternion::getEulerAngles(const Quaternion & quat)
{
	return Vec3f(
		atan2(2.0f * (quat.getX() * quat.getY() + quat.getZ() * quat.getW()), 1.0f - 2.0f * (quat.getY() * quat.getY() + quat.getZ() * quat.getZ()))
		, asin(2.0f * (quat.getX() * quat.getW() + quat.getY() * quat.getZ()))
		, atan2(2.0f * (quat.getX() * quat.getW() + quat.getY() * quat.getZ()), 1.0f - 2.0f * (quat.getZ() * quat.getZ() + quat.getW() * quat.getW()))
	);
}

void ngm::Quaternion::rotate(Vec3f & vec)
{
	Quaternion temp;
	
	temp.row = _mm_sub_ps
		(
			_mm_add_ps(
				_mm_mul_ps(_mm_set_ps(getX(), getW(), getW(), getW()), _mm_set_ps(vec.x, vec.z, vec.y, vec.x)),
				_mm_mul_ps(_mm_set_ps(getY(), getX(), getZ(), getY()), _mm_set_ps(vec.y, vec.y, vec.x, vec.z))
			), 
			_mm_mul_ps(_mm_set_ps(-1.0f*getZ(), getY(), getX(), getZ()), _mm_set_ps(vec.z, vec.x, vec.z, vec.y))
		);

	temp.row = _mm_add_ps(
		_mm_add_ps
		(
			_mm_mul_ps
			(
				_mm_set_ps(0.0f, temp.getW(), temp.getW(), temp.getW()),
				_mm_set_ps(0.0f, getZ(), getY(), getX())
			),
			_mm_mul_ps
			(
				_mm_set_ps(0.0f, temp.getZ(), temp.getY(), temp.getX()),
				_mm_set_ps(0.0f, getW(), getW(), getW())
			)
		), 
		_mm_sub_ps
		(
			_mm_mul_ps
			(
				_mm_set_ps(0.0f, temp.getY(), temp.getX(), temp.getZ()),
				_mm_set_ps(0.0f, getX(), getZ(), getY())
			),
			_mm_mul_ps
			(
				_mm_set_ps(0.0f, temp.getX(), temp.getZ(), temp.getY()),
				_mm_set_ps(0.0f, getY(), getX(), getZ())
			)
		)
	);

	vec.x = temp.getX();
	vec.y = temp.getY();
	vec.z = temp.getZ();
}

ngm::Vec3f ngm::Quaternion::getRotation(const Quaternion & quat, const Vec3f & vec)
{
	__m128 temp1 = _mm_mul_ps(_mm_set_ps(quat.getX(), quat.getW(), quat.getW(), quat.getW()), _mm_set_ps(vec.x, vec.z, vec.y, vec.x));
	__m128 temp2 = _mm_mul_ps(_mm_set_ps(quat.getY(), quat.getX(), quat.getZ(), quat.getY()), _mm_set_ps(vec.y, vec.y, vec.x, vec.z));
	__m128 temp3 = _mm_mul_ps(_mm_set_ps(-quat.getZ(), quat.getY(), quat.getX(), quat.getZ()), _mm_set_ps(vec.z, vec.x, vec.z, vec.y));
	temp1 = _mm_add_ps(temp1, temp2);
	temp1 = _mm_sub_ps(temp1, temp3);
	ALIGN(16) float temps[4];
	_mm_store_ps(temps, temp1);

	temp1 = _mm_set_ps(0.0f, temps[0], temps[0], temps[0]);
	temp2 = _mm_set_ps(0.0f, quat.getZ(), quat.getY(), quat.getX());
	temp1 = _mm_mul_ps(temp1, temp2);

	temp2 = _mm_set_ps(0.0f, temps[1], temps[2], temps[3]);
	temp3 = _mm_set_ps(0.0f, quat.getW(), quat.getW(), quat.getW());
	temp2 = _mm_mul_ps(temp2, temp3);

	temp1 = _mm_add_ps(temp1, temp2);

	temp2 = _mm_set_ps(0.0f, temps[3], temps[1], temps[2]);
	temp3 = _mm_set_ps(0.0f, quat.getY(), quat.getX(), quat.getZ());
	temp2 = _mm_mul_ps(temp2, temp3);

	temp1 = _mm_sub_ps(temp1, temp2);

	temp2 = _mm_set_ps(0.0f, temps[2], temps[3], temps[1]);
	temp3 = _mm_set_ps(0.0f, quat.getX(), quat.getZ(), quat.getY());
	temp2 = _mm_mul_ps(temp2, temp3);

	temp1 = _mm_add_ps(temp1, temp2);
	_mm_store_ps(temps, temp1);
	return Vec3f(temps[3], temps[2], temps[1]);
}

void ngm::Quaternion::rotate4(Vec3f & v1, Vec3f & v2, Vec3f & v3, Vec3f & v4)
{
	__m128 tempX;
	{
		tempX = _mm_mul_ps(_mm_set_ps1(getW()), _mm_set_ps(v4.x, v3.x, v2.x, v1.x));
		tempX = _mm_add_ps(tempX, _mm_mul_ps(_mm_set_ps1(getY()), _mm_set_ps(v4.z, v3.z, v2.z, v1.z)));
		tempX = _mm_sub_ps(tempX, _mm_mul_ps(_mm_set_ps1(getZ()), _mm_set_ps(v4.y, v3.y, v2.y, v1.y)));
	}
	__m128 tempY;
	{
		tempY = _mm_mul_ps(_mm_set_ps1(getW()), _mm_set_ps(v4.y, v3.y, v2.y, v1.y));
		tempY = _mm_add_ps(tempY, _mm_mul_ps(_mm_set_ps1(getZ()), _mm_set_ps(v4.x, v3.x, v2.x, v1.x)));
		tempY = _mm_sub_ps(tempY, _mm_mul_ps(_mm_set_ps1(getX()), _mm_set_ps(v4.z, v3.z, v2.z, v1.z)));
	}
	__m128 tempZ;
	{
		tempZ = _mm_mul_ps(_mm_set_ps1(getW()), _mm_set_ps(v4.z, v3.z, v2.z, v1.z));
		tempZ = _mm_add_ps(tempZ, _mm_mul_ps(_mm_set_ps1(getX()), _mm_set_ps(v4.y, v3.y, v2.y, v1.y)));
		tempZ = _mm_sub_ps(tempZ, _mm_mul_ps(_mm_set_ps1(getY()), _mm_set_ps(v4.x, v3.x, v2.x, v1.x)));
	}
	__m128 tempW;
	{
		tempW = _mm_mul_ps(_mm_set_ps1(getX()), _mm_set_ps(v4.x, v3.x, v2.x, v1.x));
		tempW = _mm_add_ps(tempW, _mm_mul_ps(_mm_set_ps1(getY()), _mm_set_ps(v4.y, v3.y, v2.y, v1.y)));
		tempW = _mm_add_ps(tempW, _mm_mul_ps(_mm_set_ps1(getZ()), _mm_set_ps(v4.z, v3.z, v2.z, v1.z)));
	}
	__m128 X;
	{
		X = _mm_add_ps(_mm_mul_ps(tempW, _mm_set_ps1(getX())), _mm_mul_ps(tempX, _mm_set_ps1(getW())));
		X = _mm_sub_ps(X, _mm_mul_ps(tempY, _mm_set_ps1(getZ())));
		X = _mm_add_ps(X, _mm_mul_ps(tempZ, _mm_set_ps1(getY())));
	}
	__m128 Y;
	{
		Y = _mm_add_ps(_mm_mul_ps(tempW, _mm_set_ps1(getY())), _mm_mul_ps(tempY, _mm_set_ps1(getW())));
		Y = _mm_sub_ps(Y, _mm_mul_ps(tempZ, _mm_set_ps1(getX())));
		Y = _mm_add_ps(Y, _mm_mul_ps(tempX, _mm_set_ps1(getZ())));
	}
	__m128 Z;
	{
		Z = _mm_add_ps(_mm_mul_ps(tempW, _mm_set_ps1(getZ())), _mm_mul_ps(tempZ, _mm_set_ps1(getW())));
		Z = _mm_sub_ps(Z, _mm_mul_ps(tempX, _mm_set_ps1(getY())));
		Z = _mm_add_ps(Z, _mm_mul_ps(tempY, _mm_set_ps1(getX())));
	}
	float xFloats[4];
	float yFloats[4];
	float zFloats[4];
	_mm_store_ps(xFloats, X);
	_mm_store_ps(yFloats, Y);
	_mm_store_ps(zFloats, Z);
	v1.x = xFloats[0];
	v1.y = yFloats[0];
	v1.z = zFloats[0];

	v2.x = xFloats[1];
	v2.y = yFloats[1];
	v2.z = zFloats[1];

	v3.x = xFloats[2];
	v3.y = yFloats[2];
	v3.z = zFloats[2];

	v4.x = xFloats[3];
	v4.y = yFloats[3];
	v4.z = zFloats[3];
}

float ngm::Quaternion::norm()
{
	Quaternion q;
	q.row = _mm_dp_ps(row, row, 0xFFFF);
	return q.getX();
}

float ngm::Quaternion::norm(const Quaternion & quat)
{
	Quaternion q;
	q.row = _mm_dp_ps(quat.row, quat.row, 0xFFFF);
	return q.getX();
}

float ngm::Quaternion::length()
{
	return sqrt(norm());
}

float ngm::Quaternion::length(const Quaternion & quat)
{
	return sqrt(norm(quat));
}

ngm::Quaternion & ngm::Quaternion::normalize()
{
	Quaternion q;
	q.row = _mm_dp_ps(row, row, 0xFFFF);
	q.row = _mm_rsqrt_ps(q.row);
	row = _mm_mul_ps(q.row, row);
	return *this;
}

ngm::Quaternion ngm::Quaternion::normalized(const Quaternion & quat)
{
	Quaternion q;
	q.row = _mm_dp_ps(quat.row, quat.row, 0xFFFF);
	q.row = _mm_rsqrt_ps(q.row);
	q.row = _mm_mul_ps(q.row, quat.row);
	return q;
}

ngm::Quaternion::~Quaternion()
{
	
}

ngm::Quaternion ngm::operator*(Quaternion left, const Quaternion & right)
{
	return left.mul(right);
}
