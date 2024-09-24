#pragma once

#include <vector>

#include "Vec3.h"
#include "Segment.h"

class Triangle {
public:
	Vec3 v0, v1, v2;

	Triangle(Vec3 v0, Vec3 v1, Vec3 v2) : v0(v0), v1(v1), v2(v2) {};

	Triangle() : v0(), v1(), v2() {};

	std::vector<Segment> get_segments() const {
		return { {v0, v1}, {v1, v2}, {v2, v0} };
	}

	bool intersects_by_segment(const Segment& segment) const;

	bool intersects_by_triangle_segments(const Triangle& other) const {
		for (const auto& segment : other.get_segments()) {
			if (intersects_by_segment(segment)) {
				return true;
			}
		}
		return false;
	}

	static bool intersect(const Triangle& t1, const Triangle& t2) {
		return t1.intersects_by_triangle_segments(t2) || t2.intersects_by_triangle_segments(t1);
	}

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
