#ifndef _H_GEOMETRY_3D_
#define _H_GEOMETRY_3D_

#include "vectors.h"
#include "matrices.h"

#ifndef NO_EXTRAS
#include <ostream>
#endif 

typedef vec3 Point;

typedef struct Line {
	Point start;
	Point end;

	inline Line() {}
	inline Line(const Point& s, const Point& e) :
		start(s), end(e) { }
} Line;

typedef struct Ray {
	Point origin;
	vec3 direction;

	inline Ray() : direction(0.0f, 0.0f, 1.0f) {}
	inline Ray(const Point& o, const vec3& d) :
		origin(o), direction(d) {
		NormalizeDirection();
	}
	inline void NormalizeDirection() {
		Normalize(direction);
	}
} Ray;

typedef struct Sphere {
	Point position;
	float radius;

	inline Sphere() : radius(1.0f) { }
	inline Sphere(const Point& p, float r) :
		position(p), radius(r) { }
} Sphere;

typedef struct AABB {
	Point position;
	vec3 size; // HALF SIZE!

	inline AABB() : size(1, 1, 1) { }
	inline AABB(const Point& p, const vec3& s) :
		position(p), size(s) { }
} AABB;

typedef struct OBB {
	Point position;
	vec3 size; // HALF SIZE!
	mat3 orientation;

	inline OBB() : size(1, 1, 1) { }
	inline OBB(const Point& p, const vec3& s) :
		position(p), size(s) { }
	inline OBB(const Point& p, const vec3& s, const mat3& o) :
		position(p), size(s), orientation(o) { }
} OBB;

typedef struct Plane {
	vec3 normal;
	float distance;

	inline Plane() : normal(1, 0, 0) { }
	inline Plane(const vec3& n, float d) :
		normal(n), distance(d) { }
} Plane;

typedef struct Triangle {
	union {
		struct {
			Point a;
			Point b;
			Point c;
		};
#ifndef NO_EXTRAS
		struct {
			Point p1;
			Point p2;
			Point p3;
		};
#endif 

		Point points[3];
		float values[9];
	};
	
	inline Triangle() { }
	inline Triangle(const Point& _p1, const Point& _p2, const Point& _p3) :
		a(_p1), b(_p2), c(_p3) { }
} Triangle;

#ifndef NO_EXTRAS
typedef vec3 Point3D;
typedef Line Line3D;
typedef Ray Ray3D;
typedef AABB Rectangle3D;
#endif

#ifndef NO_EXTRAS
std::ostream& operator<<(std::ostream& os, const Line& shape);
std::ostream& operator<<(std::ostream& os, const Ray& shape);
std::ostream& operator<<(std::ostream& os, const Sphere& shape);
std::ostream& operator<<(std::ostream& os, const AABB& shape);
std::ostream& operator<<(std::ostream& os, const OBB& shape);
std::ostream& operator<<(std::ostream& os, const Plane& shape);
std::ostream& operator<<(std::ostream& os, const Triangle& shape);
#endif 

float Length(const Line& line);
float LengthSq(const Line& line);
Ray FromPoints(const Point& from, const Point& to);
vec3 GetMin(const AABB& aabb);
vec3 GetMax(const AABB& aabb);
AABB FromMinMax(const vec3& min, const vec3& max);
float PlaneEquation(const Point& point, const Plane& plane);
#ifndef NO_EXTRAS
float PlaneEquation(const Plane& plane, const Point& point);
#endif

bool PointInSphere(const Point& point, const Sphere& sphere);
bool PointInAABB(const Point& point, const AABB& aabb);
bool PointInOBB(const Point& point, const OBB& obb);
bool PointOnPlane(const Point& point, const Plane& plane);
bool PointOnLine(const Point& point, const Line& line);
bool PointOnRay(const Point& point, const Ray& ray);

// TODO!
#ifndef NO_EXTRAS
bool PointInPlane(const Point& point, const Plane& plane);
bool PointInLine(const Point& point, const Line& line);
bool PointInRay(const Point& point, const Ray& ray);
bool ContainsPoint(const Sphere& sphere, const Point& point);
bool ContainsPoint(const Point& point, const Sphere& sphere);
bool ContainsPoint(const AABB& aabb, const Point& point);
bool ContainsPoint(const Point& point, const AABB& aabb);
bool ContainsPoint(const Point& point, const OBB& obb);
bool ContainsPoint(const OBB& obb, const Point& point);
bool ContainsPoint(const Point& point, const Plane& plane);
bool ContainsPoint(const Plane& plane, const Point& point);
bool ContainsPoint(const Point& point, const Line& line);
bool ContainsPoint(const Line& line, const Point& point);
bool ContainsPoint(const Point& point, const Ray& ray);
bool ContainsPoint(const Ray& ray, const Point& point);
#endif

Point ClosestPoint(const Sphere& sphere, const Point& point);
Point ClosestPoint(const AABB& aabb, const Point& point);
Point ClosestPoint(const OBB& obb, const Point& point);
Point ClosestPoint(const Plane& plane, const Point& point);
Point ClosestPoint(const Line& line, const Point& point);
Point ClosestPoint(const Ray& ray, const Point& point);

// TODO!
#ifndef NO_EXTRAS
Point ClosestPoint(const Point& point, const Sphere& sphere);
Point ClosestPoint(const Point& point, const AABB& aabb);
Point ClosestPoint(const Point& point, const OBB& obb);
Point ClosestPoint(const Point& point, const Plane& plane);
Point ClosestPoint(const Point& point, const Line& line);
Point ClosestPoint(const Point& point, const Ray& ray);
#endif

#endif