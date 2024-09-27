#include "Triangle.h"

bool Triangle::is_point_inside(Vec3 p) const
{
	Vec3 normal = Vec3::cross(v2 - v0, v1 - v0);
	// Check that p lies on triangle plane.
	if (!Vec3::are_perpendicular(p - v0, normal))
	{
		return false;
	}
	// Compare areas.
	auto area = Vec3::area(v0, v1, v2);
	auto area0 = Vec3::area(v0, v1, p);
	auto area1 = Vec3::area(v1, v2, p);
	auto area2 = Vec3::area(v0, v2, p);
	return area0 + area1 + area2 == area;
}

bool Triangle::intersected_by_triangle_segments(const Triangle &other) const
{
	for (const auto &segment : other.get_segments())
	{
		if (intersected_by_segment(segment))
		{
			return true;
		}
	}
	return false;
}

bool Triangle::is_degenerative_point(Vec3 &point) const
{
	// Check that all vertices are equal.
	if (v0 == v1 && v0 == v2)
	{
		point = v0;
		return true;
	}
	return false;
}

bool Triangle::is_degenerative_segment(Segment &segment) const
{
	Vec3 point;
	// Check that it is not point.
	if (is_degenerative_point(point))
	{
		return false;
	}
	// If area > 0, it is not segment.
	if (Vec3::area(v0, v1, v2) > 0)
	{
		return false;
	}
	// Find the farest points (all points are on one line).
	auto d1 = Vec3::distance(v0, v1);
	auto d2 = Vec3::distance(v0, v2);
	auto d3 = Vec3::distance(v1, v2);
	if (d1 >= d2 && d1 >= d3)
	{
		segment = Segment(v0, v1);
	}
	else if (d2 >= d1 && d2 >= d3)
	{
		segment = Segment(v0, v2);
	}
	else
	{
		segment = Segment(v1, v2);
	}
	return true;
}

bool Triangle::intersected_by_segment(const Segment &segment) const
{
	Vec3 r = segment.begin;
	Vec3 d = segment.end - segment.begin;
	Vec3 normal = Vec3::cross(v2 - v0, v1 - v0);

	// Check if both segment ends are from one side.
	if (Vec3::dot(r, normal) * Vec3::dot(segment.end - v0, normal) > 0)
	{
		return false;
	}

	// Use classic formula
	Vec3 e1 = v1 - v0;
	Vec3 e2 = v2 - v0;
	Vec3 to = r - v0;
	Vec3 p = Vec3::cross(d, e2);
	Vec3 q = Vec3::cross(to, e1);
	auto _dot = Vec3::dot(p, e1);

	// Check if segment is parallel to plane.
	if (_dot == 0)
	{
		// Check  that segment is in triangle plane, else no intersection.
		if (Vec3::dot(r - v0, normal) == 0)
		{
			// Chech if segment end is in triangle, so we can process case then segment is completely in triangle.
			if (is_point_inside(segment.begin) || is_point_inside(segment.end))
			{
				return true;
			}
			// Check intersections between segments.
			for (const auto &s : get_segments())
			{
				if (segment.intersects(s))
				{
					return true;
				}
			}
		}
		return false;
	}

	/*
	t - coefficient in r + t * v.
	u, v - triangle weighted areas.
	*/
	auto t = Vec3::dot(q, e2) / _dot;
	auto u = Vec3::dot(p, to) / _dot;
	auto v = Vec3::dot(q, d) / _dot;

	/*
	If t not in range (0, 1) intersection point not on segment.
	u, v, u + v must be in range (0, 1).
	*/
	if (u + v < 0 || u + v > 1 || u < 0 || u > 1 || v < 0 || v > 1)
	{
		return false;
	}
	if (t < 0 || t > 1)
	{
		return false;
	}
	return true;
}

bool Triangle::intersects(const Triangle &other) const
{
	Vec3 point1;
	Segment segment1;
	// Check different degenerative cases.
	if (is_degenerative_point(point1))
	{
		Vec3 point2;
		// If both triangles are points, compare points.
		if (other.is_degenerative_point(point2))
		{
			return point1 == point2;
		}
		Segment segment2;
		// Check if point is on segment.
		if (other.is_degenerative_segment(segment2))
		{
			return segment2.is_point_on(point1);
		}
		// Check if point is in triangle.
		return other.is_point_inside(point1);
	}
	else if (is_degenerative_segment(segment1))
	{
		Vec3 point2;
		// Check if point is on segment.
		if (other.is_degenerative_point(point2))
		{
			return segment1.is_point_on(point2);
		}
		Segment segment2;
		// Check if segments intersect.
		if (other.is_degenerative_segment(segment2))
		{
			return segment1.intersects(segment2);
		}
		// Check if segemnt intersects triangle.
		return other.intersected_by_segment(segment1);
	}
	else
	{
		Vec3 point2;
		// Check if point is in triangle.
		if (other.is_degenerative_point(point2))
		{
			return is_point_inside(point2);
		}
		Segment segment2;
		// Check if segemnt intersects triangle.
		if (other.is_degenerative_segment(segment2))
		{
			return intersected_by_segment(segment2);
		}
		// Check if triangles have common points (segment intersections and triangle in triangle).
		return intersected_by_triangle_segments(other) || other.intersected_by_triangle_segments(*this);
	}
}