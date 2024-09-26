#pragma once

#include <vector>
#include <iostream>

#include "Vec3.h"
#include "Segment.h"

class Triangle {
	std::vector<Segment> get_segments() const {
		return { {v0, v1}, {v1, v2}, {v2, v0} };
	}

	bool intersects_by_segment(const Segment& segment) const;

	bool intersects_by_triangle_segments(const Triangle& other) const;

	bool is_point_inside(Vec3 point) const;

	bool is_degenerative_point(Vec3& point) const;

	bool is_degenerative_segment(Segment& segment) const;
public:
	Vec3 v0, v1, v2;

	Triangle(Vec3 v0, Vec3 v1, Vec3 v2) : v0(v0), v1(v1), v2(v2) {}

	Triangle() = default;

	bool intersects(const Triangle& other) const;

	friend std::istream& operator >> (std::istream& cin, Triangle &t)
	{
		cin >> t.v0 >> t.v1 >> t.v2;
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Triangle& t)
	{
		cout << "Triangle( v0 = " << t.v0 << "; v1 = " << t.v1 << "; v2 = " << t.v2 << " )";
		return cout;
	}
};
