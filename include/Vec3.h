#pragma once

#include <cmath>
#include <stdexcept>
#include <iostream>


class Vec3 {
private:
	bool is_zero() const {
		return x == 0 && y == 0 && z == 0;
	}
public:
	double x, y, z;

	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	Vec3() : x(), y(), z() {}

	double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	static double distance(const Vec3& v1, const Vec3& v2) {
		return (v2 - v1).length();
	}

	static double dot(const Vec3& v1, const Vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static Vec3 cross(const Vec3& v1, const Vec3& v2) {
		return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
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
		double len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	Vec3 operator + (const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	Vec3 operator - () const {
		return Vec3(-x, -y, -z);
	}

	Vec3 operator - (const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 operator * (double a) const {
		return Vec3(x * a, y * a, z * a);
	}

	Vec3 operator / (double a) const {
		if (a == 0.0) {
			throw new std::overflow_error("division by zero");
		}
		return Vec3(x / a, y / a, z / a);
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

