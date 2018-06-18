#include "Vec2f.h"

ngm::Vec2f::Vec2f()
{

}

ngm::Vec2f::Vec2f(float scalar)
	: x(scalar), y(scalar)
{

}

ngm::Vec2f::Vec2f(float x, float y)
	: x(x), y(y)
{

}

ngm::Vec2f & ngm::Vec2f::add(const Vec2f & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::sub(const Vec2f & other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::mul(const Vec2f & other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::div(const Vec2f & other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::mul(const float & other)
{
	x *= other;
	y *= other;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::div(const float & other)
{
	x /= other;
	y /= other;
	return *this;
}

bool ngm::Vec2f::operator==(const Vec2f & other) const
{
	return (x == other.x) && (y == other.y);
}

bool ngm::Vec2f::operator!=(const Vec2f & other) const
{
	return (x != other.x) || (y != other.y);
}

bool ngm::Vec2f::operator<(const Vec2f & other) const
{
	return (x < other.x) && (y < other.y);
}

bool ngm::Vec2f::operator>(const Vec2f & other) const
{
	return (x > other.x) && (y > other.y);
}

bool ngm::Vec2f::operator<=(const Vec2f & other) const
{
	return (x <= other.x) && (y <= other.y);
}

bool ngm::Vec2f::operator>=(const Vec2f & other) const
{
	return (x >= other.x) && (y >= other.y);
}

ngm::Vec2f & ngm::Vec2f::operator+=(const Vec2f & other)
{
	return add(other);
}

ngm::Vec2f & ngm::Vec2f::operator-=(const Vec2f & other)
{
	return sub(other);
}

ngm::Vec2f & ngm::Vec2f::operator*=(const Vec2f & other)
{
	return mul(other);
}

ngm::Vec2f & ngm::Vec2f::operator/=(const Vec2f & other)
{
	return div(other);
}

ngm::Vec2f & ngm::Vec2f::operator+=(float other)
{
	x += other;
	y += other;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::operator-=(float other)
{
	x -= other;
	y -= other;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::operator*=(float other)
{
	x *= other;
	y *= other;
	return *this;
}

ngm::Vec2f & ngm::Vec2f::operator/=(float other)
{
	x /= other;
	y /= other;
	return *this;
}

ngm::Vec2f ngm::operator+(Vec2f left, const Vec2f & right)
{
	return left.add(right);
}

ngm::Vec2f ngm::operator-(Vec2f left, const Vec2f & right)
{
	return left.sub(right);
}

ngm::Vec2f ngm::operator*(Vec2f left, const Vec2f & right)
{
	return left.mul(right);
}

ngm::Vec2f ngm::operator/(Vec2f left, const Vec2f & right)
{
	return left.div(right);
}

ngm::Vec2f ngm::operator*(const float & left, Vec2f right)
{
	return right.mul(left);
}

ngm::Vec2f ngm::operator/(Vec2f left, const float & rigth)
{
	return left.div(rigth);
}

std::ostream & ngm::operator<<(std::ostream & stream, const Vec2f & vector)
{
	stream << "Vec2f: (" << vector.x << ", " << vector.y << ", " << ")";
	return stream;
}
