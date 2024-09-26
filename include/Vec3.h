#pragma once

#include <cmath>
#include <stdexcept>
#include <iostream>

/**
 * @class Vec3
 * @brief Class for 3-dimensional vector.
 */
class Vec3 {
	bool is_zero() const {
		return x == float_t() && y == float_t() && z == float_t();
	}
public:
	using float_t = long double;

	float_t x, y, z;

	Vec3(float_t x, float_t y, float_t z) : x(x), y(y), z(z) {}

	Vec3() : x(), y(), z() {}

	float_t length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	static float_t distance(const Vec3& v1, const Vec3& v2) {
		return (v2 - v1).length();
	}

	static float_t dot(const Vec3& v1, const Vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static Vec3 cross(const Vec3& v1, const Vec3& v2) {
		return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	static bool are_perpendicular(const Vec3& v1, const Vec3& v2) {
		return Vec3::dot(v1, v2) == 0;
	}

	static float_t area(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
		return cross(v2 - v1, v3 - v1).length() / 2;
	}

	Vec3 get_normalized() const {
		if (is_zero()) {
			return *this;
		}
		return *this / length();
	}

	void normalize() {
		if (is_zero()) {
			return;
		}
		float_t len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	bool operator == (const Vec3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	Vec3& operator += (const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3 operator + (const Vec3& other) const {
		return Vec3(*this) += other;
	}

	Vec3& operator -= (const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3 operator - (const Vec3& other) const {
		return Vec3(*this) -= other;
	}

	Vec3 operator - () const {
		return Vec3(-x, -y, -z);
	}

	Vec3& operator *= (float_t a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vec3 operator * (float_t a) const {
		return Vec3(*this) *= a;
	}

	Vec3& operator /= (float_t a) {
		if (a == float_t()) {
			throw std::invalid_argument("division by zero");
		}
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	Vec3 operator / (float_t a) const {
		return Vec3(*this) /= a;
	}

	friend std::istream& operator >> (std::istream& cin, Vec3& v)
	{
		cin >> v.x >> v.y >> v.z;
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Vec3& v)
	{
		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return cout;
	}
};