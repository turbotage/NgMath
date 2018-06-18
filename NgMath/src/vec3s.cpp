#include "Vec3s.h"

ngm::Vec3s::Vec3s()
{
}

ngm::Vec3s::Vec3s(int16 scalar)
	: x(scalar), y(scalar), z(scalar)
{

}

ngm::Vec3s::Vec3s(int16 x, int16 y, int32 z)
	: x(x), y(y), z(z)
{

}

ngm::Vec3s & ngm::Vec3s::add(const Vec3s & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

ngm::Vec3s & ngm::Vec3s::sub(const Vec3s & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

ngm::Vec3s & ngm::Vec3s::mul(const Vec3s & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

ngm::Vec3s & ngm::Vec3s::div(const Vec3s & other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

bool ngm::Vec3s::operator==(const Vec3s other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool ngm::Vec3s::operator!=(const Vec3s other) const
{
	return (x != other.x) || (y != other.y) || (z != other.z);
}

bool ngm::Vec3s::operator<(const Vec3s & other) const 
{
	return (x < other.x) && (y < other.y) && (z < other.z);
}

bool ngm::Vec3s::operator>(const Vec3s & other) const
{
	return (x > other.x) && (y > other.y) && (z > other.z);
}

bool ngm::Vec3s::operator<=(const Vec3s & other) const
{
	return (x <= other.x) && (y <= other.y) && (z <= other.z);
}

bool ngm::Vec3s::operator>=(const Vec3s & other) const
{
	return (x >= other.x) && (y >= other.y) && (z >= other.z);
}
