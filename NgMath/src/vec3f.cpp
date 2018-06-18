#include "Vec3f.h"

ngm::Vec3f::Vec3f()
	: x(0), y(0), z(0)
{

}

ngm::Vec3f::Vec3f(float scalar)
	: x(scalar), y(scalar), z(scalar)
{
}

ngm::Vec3f::Vec3f(float x, float y, float z)
	: x(x), y(y), z(z)
{

}

ngm::Vec3f & ngm::Vec3f::add(const Vec3f & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::sub(const Vec3f & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::mul(const Vec3f & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::div(const Vec3f & other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::mul(const float & other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::div(const float & other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::normalize()
{
	float lenght = sqrt(x*x + y*y + z*z);
	x /= lenght;
	y /= lenght;
	z /= lenght;
	return *this;
}

ngm::Vec3f ngm::Vec3f::normalized(const Vec3f & other)
{
	Vec3f ret = other;
	float lenght = sqrt(ret.x*ret.x + ret.y * ret.y + ret.z * ret.z);
	ret /= lenght;
	return ret;
}

float ngm::Vec3f::norm()
{
	return sqrt(x*x + y*y + z*z);
}

ngm::Vec3f & ngm::Vec3f::setLength(float length)
{
	normalize();
	mul(length);
	return *this;
}

ngm::Vec3f ngm::Vec3f::cross(const Vec3f & other)
{
	ngm::Vec3f ret;
	ret.x = ((y * other.z) - (z * other.y));
	ret.y = -1 * ((x * other.z) - (z * other.x));
	ret.z = ((x * other.y) - (y * other.x));
	return ret;
}

bool ngm::Vec3f::operator==(const Vec3f & other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool ngm::Vec3f::operator!=(const Vec3f & other) const
{
	return (x != other.x) || (y != other.y) || (z != other.z);
}

bool ngm::Vec3f::operator<(const Vec3f & other) const
{
	return (x < other.x) && (y < other.y) && (z < other.z);
}

bool ngm::Vec3f::operator>(const Vec3f & other) const
{
	return (x > other.x) && (y > other.y) && (z > other.z);
}

bool ngm::Vec3f::operator<=(const Vec3f & other) const
{
	return (x <= other.x) && (y <= other.y) && (z <= other.z);
}

bool ngm::Vec3f::operator>=(const Vec3f & other) const
{
	return (x >= other.x) && (y >= other.y) && (z >= other.z);
}

ngm::Vec3f & ngm::Vec3f::operator+=(const Vec3f & other)
{
	return add(other);
}

ngm::Vec3f & ngm::Vec3f::operator-=(const Vec3f & other)
{
	return sub(other);
}

ngm::Vec3f & ngm::Vec3f::operator*=(const Vec3f & other)
{
	return mul(other);;
}

ngm::Vec3f & ngm::Vec3f::operator/=(const Vec3f & other)
{
	return div(other);
}

ngm::Vec3f & ngm::Vec3f::operator+=(float other)
{
	x += other;
	y += other;
	z += other;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::operator-=(float other)
{
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::operator*=(float other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

ngm::Vec3f & ngm::Vec3f::operator/=(float other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

ngm::Vec3f ngm::operator+(Vec3f left, const Vec3f & right)
{
	return left.add(right);
}

ngm::Vec3f ngm::operator-(Vec3f left, const Vec3f & right)
{
	return left.sub(right);
}

ngm::Vec3f ngm::operator*(Vec3f left, const Vec3f & right)
{
	return left.mul(right);
}

ngm::Vec3f ngm::operator/(Vec3f left, const Vec3f & right)
{
	return left.div(right);
}

ngm::Vec3f ngm::operator*(const float& left, Vec3f right)
{
	return right.mul(left);
}

ngm::Vec3f ngm::operator/(Vec3f left, const float & right)
{
	return left.div(right);
}

std::ostream & ngm::operator<<(std::ostream & stream, const Vec3f & vector)
{
	stream << "Vec3f: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}
