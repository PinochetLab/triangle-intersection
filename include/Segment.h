#pragma once

#include <ostream>

#include "Vec3.h"

/**
 * @class Segment.
 * @brief Class for line segment with Vec3 begin and end.
 */
class Segment
{
	/**
	 * @brief Method for check if segment intersects line set by segment.
	 * @param other ref for readed string value.
	 * @return True if сcould to read (file is not ended).
	 */
	bool intersects_line(const Segment &other) const
	{
		Vec3 v0 = other.begin;
		Vec3 d = other.end - other.begin;
		// If dot of crosses < 0 current segment begin and end are from the other sides of line.
		return Vec3::dot(Vec3::cross(d, begin - v0), Vec3::cross(d, end - v0)) < 0;
	}

public:
	/**
	 * @brief Begin of segment.
	 */
	Vec3 begin;

	/**
	 * @brief End of segment.
	 */
	Vec3 end;

	/**
	 * @brief Class constructor.
	 * @param begin Begin.
	 * @param end End.
	 */
	Segment(Vec3 begin, Vec3 end) : begin(begin), end(end) {}

	/**
	 * @brief Default constructor.
	 */
	Segment() = default;

	/**
	 * @brief Method for check if segment intersects with another segment.
	 * @param other Another segment.
	 * @return True if intersects.
	 */
	bool intersects(const Segment &other) const
	{
		/*
		If segment1 intersects segment2 line and segment2 intersects segment1 line, segments intersect. 
		Check that one segment point is on another segment or every segment intersects another segment line.
		*/
		return is_point_on(other.begin) || is_point_on(other.end) || other.is_point_on(begin) || other.is_point_on(end) ||
			   (intersects_line(other) && other.intersects_line(*this));
	}

	/**
	 * @brief Method for check if point is on segment.
	 * @param p Point.
	 * @return True if point is on segment.
	 */
	bool is_point_on(const Vec3 &p) const
	{
		// The point r is on segment (a, b) when dist(a, b) = dist(a, r) + dist(r, b)
		return Vec3::distance(begin, p) + Vec3::distance(p, end) == Vec3::distance(begin, end);
	}

	/**
	 * @brief Segment output for debugging.
	 */
	friend std::ostream &operator<<(std::ostream &cout, const Segment &s)
	{
		cout << "Segment( begin = " << s.begin << "; end = " << s.end << " )";
		return cout;
	}
};
