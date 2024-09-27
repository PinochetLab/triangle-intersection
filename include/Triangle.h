#pragma once

#include <vector>
#include <iostream>

#include "Vec3.h"
#include "Segment.h"

/**
 * @class Triangle.
 * @brief Class for trangle.
 */
class Triangle
{
	/**
	 * @brief Method for getting segments (v0, v1), (v, v2), (v2, v0).
	 * @return Vector of segments.
	 */
	std::vector<Segment> get_segments() const
	{
		return {{v0, v1}, {v1, v2}, {v2, v0}};
	}

	/**
	 * @brief Method for checking if triangle if intersected by segment.
	 * @param segment Segmeent.
	 * @return True if intersected.
	 */
	bool intersected_by_segment(const Segment &segment) const;

	/**
	 * @brief Method for checking if other segments intersects this triangle.
	 * @param other Another triangle.
	 * @return True if intersects.
	 */
	bool intersected_by_triangle_segments(const Triangle &other) const;

	/**
	 * @brief Method for checking if point is inside triangle.
	 * @param point Point.
	 * @return True if inside.
	 */
	bool is_point_inside(Vec3 point) const;

	/**
	 * @brief Method for checking if triangle is degenerative point.
	 * @param point Vec3 ref for getting point.
	 * @return True if triangle is degenerative point.
	 */
	bool is_degenerative_point(Vec3 &point) const;

	/**
	 * @brief Method for checking if triangle is degenerative segment.
	 * @param segment Vec3 ref for getting segment.
	 * @return True if triangle is degenerative segment.
	 */
	bool is_degenerative_segment(Segment &segment) const;

public:
	/**
	 * @brief Vertex 0.
	 */
	Vec3 v0;

	/**
	 * @brief Vertex 1.
	 */
	Vec3 v1;

	/**
	 * @brief Vertex 2.
	 */
	Vec3 v2;

	/**
	 * @brief Class constructor.
	 * @param v0 Vertex 0.
	 * @param v0 Vertex 1.
	 * @param v0 Vertex 2.
	 */
	Triangle(Vec3 v0, Vec3 v1, Vec3 v2) : v0(v0), v1(v1), v2(v2) {}

	/**
	 * @brief Default constructor.
	 */
	Triangle() = default;

	/**
	 * @brief Method for checking if triangles intersect.
	 * @param other Another triangle.
	 * @return True if triangles intersect.
	 */
	bool intersects(const Triangle &other) const;

	/**
	 * @brief Triangle input for reading from file.
	 */
	friend std::istream &operator>>(std::istream &cin, Triangle &t)
	{
		cin >> t.v0 >> t.v1 >> t.v2;
		return cin;
	}

	/**
	 * @brief Triangle output for debugging.
	 */
	friend std::ostream &operator<<(std::ostream &cout, const Triangle &t)
	{
		cout << "Triangle( v0 = " << t.v0 << "; v1 = " << t.v1 << "; v2 = " << t.v2 << " )";
		return cout;
	}
};
