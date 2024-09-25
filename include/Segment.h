#pragma once

#include <ostream>

#include "Vec3.h"

class Segment {
	bool intersects_line(const Segment& other) const {
		Vec3 v0 = other.begin;
		Vec3 d = other.end - other.begin;
		return Vec3::dot(Vec3::cross(d, begin - v0), Vec3::cross(d, end - v0)) <= 0;
	}
public:
	Vec3 begin, end;

	Segment(Vec3 begin, Vec3 end) : begin(begin), end(end) {};

	bool intersects(const Segment& other) const {
		return intersects_line(other) && other.intersects_line(*this);
	}

	friend std::ostream& operator << (std::ostream& cout, const Segment& s)
	{
		cout << "Segment( begin = " << s.begin << "; end = " << s.end << " )";
		return cout;
	}
};
