#include "Triangle.h"

bool Triangle::intersects_by_segment(const Segment& segment) const noexcept {
	Vec3 r = segment.begin;
	Vec3 d = segment.end - segment.begin;
	Vec3 normal = Vec3::cross(v2 - v0, v1 - v0);

	if (Vec3::dot(r, normal) * Vec3::dot(segment.end - v0, normal) > 0) {
		return false;
	}

	Vec3 e1 = v1 - v0;
	Vec3 e2 = v2 - v0;
	Vec3 to = r - v0;
	Vec3 p = Vec3::cross(d, e2);
	Vec3 q = Vec3::cross(to, e1);
	double _dot = Vec3::dot(p, e1);

	if (_dot == 0) {
		if (Vec3::dot(r - v0, normal) == 0 && Vec3::dot(segment.end - v0, normal) == 0) {
			for (const auto& s : get_segments()) {
				if (segment.intersects(s)) {
					return true;
				}
			}
		}
		return false;
	}

	double t = Vec3::dot(q, e2) / _dot;
	double u = Vec3::dot(p, to) / _dot;
	double v = Vec3::dot(q, d) / _dot;

	if (u + v < 0 || u + v > 1 || u < 0 || u > 1 || v < 0 || v > 1) {
		return false;
	}
	if (t < 0 || t > 1) {
		return false;
	}
	return true;
}