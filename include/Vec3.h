#pragma once

#include <cmath>
#include <stdexcept>
#include <iostream>

/**
 * @class Vec3Base
 * @brief Class for 3-dimensional vector.
 */
template<class T>
class Vec3Base {
	static_assert(std::is_arithmetic<T>::value);
	bool is_zero() const {
		return x == T() && y == T() && z == T();
	}
public:
	using type = T;

	T x, y, z; // Coordinate

	Vec3Base(T x, T y, T z) : x(x), y(y), z(z) {}

	Vec3Base() : x(), y(), z() {}

	T length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	static T distance(const Vec3Base& v1, const Vec3Base& v2) {
		return (v2 - v1).length();
	}

	static T dot(const Vec3Base& v1, const Vec3Base& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static Vec3Base cross(const Vec3Base& v1, const Vec3Base& v2) {
		return Vec3Base(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	Vec3Base get_normalized() const {
		if (is_zero()) {
			return *this;
		}
		return *this / length();
	}

	void normalize() {
		if (is_zero()) {
			return;
		}
		T len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	Vec3Base& operator += (const Vec3Base& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3Base operator + (const Vec3Base& other) const {
		return Vec3Base(*this) += other;
	}

	Vec3Base& operator -= (const Vec3Base& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3Base operator - (const Vec3Base& other) const {
		return Vec3Base(*this) -= other;
	}

	Vec3Base operator - () const {
		return Vec3Base(-x, -y, -z);
	}

	Vec3Base& operator *= (T a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vec3Base operator * (T a) const {
		return Vec3Base(*this) *= a;
	}

	Vec3Base& operator /= (T a) {
		if (a == T()) {
			throw std::invalid_argument("division by zero");
		}
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	Vec3Base operator / (T a) const {
		return Vec3Base(*this) /= a;
	}

	friend std::istream& operator >> (std::istream& cin, Vec3Base& v)
	{
		cin >> v.x >> v.y >> v.z;
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Vec3Base& v)
	{
		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return cout;
	}
};

using Vec3 = Vec3Base<long double>;