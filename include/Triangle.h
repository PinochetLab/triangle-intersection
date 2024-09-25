#pragma once

#include <vector>

#include "Vec3.h"
#include "Segment.h"

class Triangle {
private:
	std::vector<Segment> get_segments() const {
		return { {v0, v1}, {v1, v2}, {v2, v0} };
	}

	bool intersects_by_segment(const Segment& segment) const noexcept;

	bool intersects_by_triangle_segments(const Triangle& other) const {
		for (const auto& segment : other.get_segments()) {
			if (intersects_by_segment(segment)) {
				return true;
			}
		}
		return false;
	}
public:
	Vec3 v0, v1, v2;

	Triangle(Vec3 v0, Vec3 v1, Vec3 v2) : v0(v0), v1(v1), v2(v2) {}

	Triangle() : v0(), v1(), v2() {}

	bool intersects(const Triangle& other) const {
		return intersects_by_triangle_segments(other) || other.intersects_by_triangle_segments(*this);
	}

	friend std::istream& operator >> (std::istream& cin, Triangle &t)
	{
		if (!(cin >> t.v0 >> t.v1 >> t.v2)) {
			cin.setstate(std::ios::failbit);
		}
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Triangle& t)
	{
		cout << "Triangle( v0 = " << t.v0 << "; v1 = " << t.v1 << "; v2 = " << t.v2 << " )";
		return cout;
	}
};
