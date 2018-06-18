#include "Vec4f.h"

float ngm::Vec4f::getX() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(0, 0, 0, 0)));
}

float ngm::Vec4f::getY() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(1, 1, 1, 1)));
}

float ngm::Vec4f::getZ() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(2, 2, 2, 2)));
}

float ngm::Vec4f::getW() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(row, row, _MM_SHUFFLE(3, 3, 3, 3)));
}

ngm::Vec4f::Vec4f()
{
	_mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
}

ngm::Vec4f::Vec4f(float scalar)
{
	_mm_set_ps(scalar, scalar, scalar, scalar);
}

ngm::Vec4f::Vec4f(float x, float y, float z, float w)
{
	_mm_set_ps(w, z, y, x);
}

ngm::Vec4f & ngm::Vec4f::add(const Vec4f& other)
{
	row = _mm_add_ps(row, other.row);
	return *this;
}

ngm::Vec4f & ngm::Vec4f::sub(const Vec4f & other)
{
	row = _mm_sub_ps(row, other.row);
	return *this;
}

ngm::Vec4f & ngm::Vec4f::mul(const Vec4f & other)
{
	row = _mm_mul_ps(row, other.row);
	return *this;
}

ngm::Vec4f & ngm::Vec4f::div(const Vec4f & other)
{
	row = _mm_div_ps(row, other.row);
	return *this;
}

bool ngm::Vec4f::operator==(const Vec4f & other) const
{
	return (getX() == other.getX()) && (getY() == other.getY()) && (getZ() == other.getZ()) && (getW() == other.getW());
}

bool ngm::Vec4f::operator!=(const Vec4f & other) const
{
	return (getX() != other.getX()) || (getY() != other.getY()) || (getZ() != other.getZ()) || (getW() != other.getW());
}

ngm::Vec4f & ngm::Vec4f::operator+=(const Vec4f & other)
{
	return add(other);
}

ngm::Vec4f & ngm::Vec4f::operator-=(const Vec4f & other)
{
	return sub(other);
}

ngm::Vec4f & ngm::Vec4f::operator*=(const Vec4f & other)
{
	return mul(other);
}

ngm::Vec4f & ngm::Vec4f::operator/=(const Vec4f & other)
{
	return div(other);
}

ngm::Vec4f ngm::operator+(Vec4f left, const Vec4f & right)
{
	return left.add(right);
}

ngm::Vec4f ngm::operator-(Vec4f left, const Vec4f & right)
{
	return left.sub(right);
}

ngm::Vec4f ngm::operator*(Vec4f left, const Vec4f & right)
{
	return left.mul(right);
}

ngm::Vec4f ngm::operator/(Vec4f left, const Vec4f & right)
{
	return left.div(right);
}

std::ostream & ngm::operator<<(std::ostream & stream, const Vec4f & vector)
{
	stream << "Vec4f: (" << vector.getX() << ", " << vector.getX() << ", " << vector.getZ() << ", " << vector.getW() << ")";
	return stream;
}
