#include "Vec3i.h"

ngm::Vec3i::Vec3i()
{

}

ngm::Vec3i::Vec3i(int32 scalar)
	: x(scalar), y(scalar), z(scalar)
{

}

ngm::Vec3i::Vec3i(int32 x, int32 y, int32 z)
	: x(x), y(y), z(z)
{

}

ngm::Vec3i & ngm::Vec3i::add(const Vec3i & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::sub(const Vec3i & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::mul(const Vec3i & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::div(const Vec3i & other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::mul(const int32 & other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::div(const int32 & other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

ngm::Vec3i & ngm::Vec3i::operator+=(const Vec3i & other)
{
	return add(other);
}

ngm::Vec3i & ngm::Vec3i::operator-=(const Vec3i & other)
{
	return sub(other);
}

ngm::Vec3i & ngm::Vec3i::operator*=(const Vec3i & other)
{
	return mul(other);
}

ngm::Vec3i & ngm::Vec3i::operator/=(const Vec3i & other)
{
	return div(other);
}

std::ostream & ngm::operator<<(std::ostream & stream, const Vec3i & vector)
{
	stream << "Vec3i: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}
