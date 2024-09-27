#pragma once

#include <cmath>
#include <stdexcept>
#include <iostream>

/**
 * @class Vec3
 * @brief Class for 3-dimensional vector.
 */
class Vec3
{
	/**
	 * @brief Method for checking if vector is zero.
	 * @return True if vector is zero.
	 */
	bool is_zero() const
	{
		return x == float_t() && y == float_t() && z == float_t();
	}

public:
	/**
	 * @brief Float type for coordinates and metrics.
	 */
	using float_t = long double;

	/**
	 * @brief X coordinate.
	 */
	float_t x;

	/**
	 * @brief Y coordinate.
	 */
	float_t y;

	/**
	 * @brief Z coordinate.
	 */
	float_t z;

	/**
	 * @brief Class constructor.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 * @param z Z coordinate.
	 */
	Vec3(float_t x, float_t y, float_t z) : x(x), y(y), z(z) {}

	/**
	 * @brief Default constructor.
	 */
	Vec3() : x(), y(), z() {}

	/**
	 * @brief Method for vector length.
	 * @return Vector length.
	 */
	float_t length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	/**
	 * @brief Method for calculating distance between points.
	 * @param v1 Point 1.
	 * @param v2 Point 2.
	 * @return Distance.
	 */
	static float_t distance(const Vec3 &v1, const Vec3 &v2)
	{
		return (v2 - v1).length();
	}

	/**
	 * @brief Method for calculating dot of vectors.
	 * @param v1 Vector 1.
	 * @param v2 Vector 2.
	 * @return Dot.
	 */
	static float_t dot(const Vec3 &v1, const Vec3 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	/**
	 * @brief Method for calculating cross of vectors.
	 * @param v1 Vector 1.
	 * @param v2 Vector 2.
	 * @return Cross.
	 */
	static Vec3 cross(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	/**
	 * @brief Method for check if vectors are perpendicular.
	 * @param v1 Vector 1.
	 * @param v2 Vector 2.
	 * @return True if vectors are perperdicular.
	 */
	static bool are_perpendicular(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3::dot(v1, v2) == 0;
	}

	/**
	 * @brief Method for calculating area based on 3 points.
	 * @param v1 Point 1.
	 * @param v2 Point 2.
	 * @param v2 Point 2.
	 * @return Area.
	 */
	static float_t area(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
	{
		return cross(v2 - v1, v3 - v1).length() / 2;
	}

	/**
	 * @brief Method for getting normalized vector.
	 *
	 * If vector is zero, normalized vector is zero too.
	 * @return Normalized vector.
	 */
	Vec3 get_normalized() const
	{
		Vec3 normalized(*this);
		normalized.normalize();
		return normalized;
	}

	/**
	 * @brief Method for normalize vector.
	 *
	 * If vector is zero, it will be zero.
	 * @param v1 Vector 1.
	 */
	void normalize()
	{
		if (is_zero())
		{
			return;
		}
		float_t len = length();
		x /= len;
		y /= len;
		z /= len;
	}

	/**
	 * @brief Operator == for vectors.
	 */
	bool operator==(const Vec3 &other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	/**
	 * @brief Operator += for vectors.
	 */
	Vec3 &operator+=(const Vec3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	/**
	 * @brief Operator + for vectors.
	 */
	Vec3 operator+(const Vec3 &other) const
	{
		return Vec3(*this) += other;
	}

	/**
	 * @brief Operator -= for vectors.
	 */
	Vec3 &operator-=(const Vec3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	/**
	 * @brief Operator - for vectors.
	 */
	Vec3 operator-(const Vec3 &other) const
	{
		return Vec3(*this) -= other;
	}

	/**
	 * @brief Unary operator - for vector.
	 */
	Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}

	/**
	 * @brief Operator *= for vector.
	 */
	Vec3 &operator*=(float_t a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	/**
	 * @brief Operator * for vector.
	 */
	Vec3 operator*(float_t a) const
	{
		return Vec3(*this) *= a;
	}

	/**
	 * @brief Operator /= for vector.
	 * @throw Division by zero.
	 */
	Vec3 &operator/=(float_t a)
	{
		if (a == float_t())
		{
			throw std::invalid_argument("division by zero");
		}
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	/**
	 * @brief Operator / for vector.
	 * @throw Division by zero.
	 */
	Vec3 operator/(float_t a) const
	{
		return Vec3(*this) /= a;
	}

	/**
	 * @brief Vector input for reading from file.
	 */
	friend std::istream &operator>>(std::istream &cin, Vec3 &v)
	{
		cin >> v.x >> v.y >> v.z;
		return cin;
	}

	/**
	 * @brief Vector output for debugging.
	 */
	friend std::ostream &operator<<(std::ostream &cout, const Vec3 &v)
	{
		cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return cout;
	}
};