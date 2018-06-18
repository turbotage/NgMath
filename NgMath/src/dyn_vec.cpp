#include "dyn_vec.h"
#include <limits>
#include <string>
#include <ostream>

template<typename T>
void ngm::DynVec<T>::init(uint16 w)
{
	width = w;
	elements = new T[w];
}

template<typename T>
void ngm::DynVec<T>::cleanup()
{
	if (elements != nullptr) {
		delete[] elements;
		elements = nullptr;
	}
}

template<typename T>
void ngm::DynVec<T>::setNaN()
{
	for (short i = 0; i < width; ++i) {
		elements[i] = std::numeric_limits<float>::quiet_NaN();
	}
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::operator=(DynVec<T> & other)
{
	if (width != other.width) {
		setNaN();
	}
	else {
		memcpy(elements, other.elements, width * sizeof(float));
	}
	return *this;
}

template<typename T>
ngm::DynVec<T>::DynVec()
{

}

template<typename T>
ngm::DynVec<T>::DynVec(uint16 w)
{
	init(w);
}

template<typename T>
ngm::DynVec<T>::~DynVec()
{

}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::add(const DynVec<T> & other)
{
	if (width == other.width) {
		for (short i = 0; i < width; ++i) {
			elements[i] += other.elements[i];
		}
	}
	else {
		for (short i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
	}
	return *this;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::sub(const DynVec<T> & other)
{
	if (width == other.width) {
		for (short i = 0; i < width; ++i) {
			elements[i] -= other.elements[i];
		}
	}
	else {
		for (short i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
	}
	return *this;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::mul(const DynVec<T> & other)
{
	if (width == other.width) {
		for (short i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
	}
	else {
		for (short i = 0; i < width; ++i) {
			elements[i] *= other.elements[i];
		}
	}
	return *this;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::mul(float multiplier)
{
	for (short i = 0; i < this->width; ++i) {
		this->elements[i] *= multiplier;
	}
	return *this;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::div(float multiplier)
{
	for (short i = 0; i < this->width; ++i) {
		this->elements[i] /= multiplier;
	}
	return *this;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::div(const DynVec<T> & other)
{
	if (width == other.width) {
		for (int i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
	}
	else {
		for (int i = 0; i < width; ++i) {
			elements[i] /= other.elements[i];
		}
	}
	return *this;
}

template<typename T>
float ngm::DynVec<T>::dot(const DynVec<T> & other)
{
	if (width != other.width) {
		for (int i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
		return std::numeric_limits<float>::quiet_NaN();
	}
	float ret = 0;
	for (int i = 0; i < width; ++i) {
		ret += elements[i] * other.elements[i];
	}
	return ret;
}

template<typename T>
bool ngm::DynVec<T>::operator==(const DynVec<T> & other) const
{
	if (width == other.width) {
		for (int i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
		return false;
	}
	bool returner = elements[0] == other.elements[0];
	for (short i = 1; i < width; ++i) {
		returner = elements[i] == other.elements[0];
	}
	return returner;
}

template<typename T>
bool ngm::DynVec<T>::operator!=(const DynVec<T> & other) const
{
	if (width == other.width) {
		for (int i = 0; i < width; ++i) {
			elements[i] = std::numeric_limits<float>::quiet_NaN();
		}
		return false;
	}
	for (int i = 0; i < width; ++i) {
		if (elements[i] != other.elements[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::operator+=(const DynVec<T> & other)
{
	return add(other);
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::operator-=(const DynVec<T> & other)
{
	return sub(other);
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::operator*=(const DynVec<T> & other)
{
	return mul(other);
}

template<typename T>
ngm::DynVec<T> & ngm::DynVec<T>::operator/=(const DynVec<T> & other)
{
	return div(other);
}

template<typename T>
ngm::DynVec<T> operator+(ngm::DynVec<T> left, const ngm::DynVec<T> & right)
{
	return left.add(right);
}

template<typename T>
ngm::DynVec<T> operator-(ngm::DynVec<T> left, const ngm::DynVec<T> & right)
{
	return left.sub(right);
}

template<typename T>
ngm::DynVec<T> operator*(ngm::DynVec<T> left, const ngm::DynVec<T> & right)
{
	return left.mul(right);
}

template<typename T>
ngm::DynVec<T> operator/(ngm::DynVec<T> left, const ngm::DynVec<T> & right)
{
	return left.div(right);
}

template<typename T>
ngm::DynVec<T> operator*(const float & left, ngm::DynVec<T> right)
{
	return right.mul(left);
}

template<typename T>
ngm::DynVec<T> operator/(ngm::DynVec<T> left, const float & right)
{
	return left.div(right);
}

template<typename T>
std::ostream & operator<<(std::ostream & stream, const ngm::DynVec<T> & vector)
{
	stream << "DynVec: (";
	for (int i = 0; i < vector.width - 1; ++i) {
		stream << vector.elements[i] << ", ";
	}
	stream << vector.elements[vector.width - 1] << ")";
	return stream;
}

