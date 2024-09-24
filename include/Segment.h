#pragma once

#include "Vec3.h"

class Segment {
public:
	Vec3 begin, end;
	Segment(Vec3 begin, Vec3 end) : begin(begin), end(end) {};

	friend std::ostream& operator << (std::ostream& cout, const Segment& s)
	{
		cout << "Segment( begin = " << s.begin << "; end = " << s.end << " )";
		return cout;
	}
};
