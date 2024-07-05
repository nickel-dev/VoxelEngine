/* date = April 19th 2024 10:52 pm */

#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_types.h"

union Vec2
{
	Vec2(F32 p) : a(p), b(p) {};
	Vec2(F32 p1, F32 p2) : a(p1), b(p2) {};
	
	struct { F32 a, b; };
	struct { F32 one, two; };
	struct { F32 x, y; };
	struct { F32 u, v; };
	
	Vec2 operator+(Vec2 other) { return Vec2(this->a + other.a, this->b + other.b); };
	Vec2 operator-(Vec2 other) { return Vec2(this->a - other.a, this->b - other.b); };
	Vec2 operator*(Vec2 other) { return Vec2(this->a * other.a, this->b * other.b); };
	Vec2 operator/(Vec2 other) { return Vec2(this->a / other.a, this->b / other.b); };
	
	Vec2 operator+=(Vec2 other) { this->a += other.a; this->b += other.b; return *this; };
	Vec2 operator-=(Vec2 other) { this->a -= other.a; this->b -= other.b; return *this; };
	Vec2 operator*=(Vec2 other) { this->a *= other.a; this->b *= other.b; return *this; };
	Vec2 operator/=(Vec2 other) { this->a /= other.a; this->b /= other.b; return *this; };
	
	Vec2 operator+(F32 other) { return Vec2(this->a + other, this->b + other); };
	Vec2 operator-(F32 other) { return Vec2(this->a - other, this->b - other); };
	Vec2 operator*(F32 other) { return Vec2(this->a * other, this->b * other); };
	Vec2 operator/(F32 other) { return Vec2(this->a / other, this->b / other); };
	
	Vec2 operator+=(F32 other) { this->a += other; this->b += other; return *this; };
	Vec2 operator-=(F32 other) { this->a -= other; this->b -= other; return *this; };
	Vec2 operator*=(F32 other) { this->a *= other; this->b *= other; return *this; };
	Vec2 operator/=(F32 other) { this->a /= other; this->b /= other; return *this; };
};

union Vec3
{
	Vec3(F32 p) : a(p), b(p), c(p) {};
	Vec3(F32 p1, F32 p2, F32 p3) : a(p1), b(p2), c(p3) {};
	
	struct { F32 a, b, c; };
	struct { F32 one, two, three; };
	struct { F32 x, y, z; };
	struct { F32 pitch, yaw, roll; };
	struct { F32 r, g, b; };
	struct { F32 h, s, v; };
	
	Vec3 operator+(Vec3 other) { return Vec3(this->a + other.a, this->b + other.b, this->c + other.c); };
	Vec3 operator-(Vec3 other) { return Vec3(this->a - other.a, this->b - other.b, this->c - other.c); };
	Vec3 operator*(Vec3 other) { return Vec3(this->a * other.a, this->b * other.b, this->c * other.c); };
	Vec3 operator/(Vec3 other) { return Vec3(this->a / other.a, this->b / other.b, this->c / other.c); };
	
	Vec3 operator+=(Vec3 other) { this->a += other.a; this->b += other.b; this->c += other.c; return *this; };
	Vec3 operator-=(Vec3 other) { this->a -= other.a; this->b -= other.b; this->c -= other.c; return *this; };
	Vec3 operator*=(Vec3 other) { this->a *= other.a; this->b *= other.b; this->c *= other.c; return *this; };
	Vec3 operator/=(Vec3 other) { this->a /= other.a; this->b /= other.b; this->c /= other.c; return *this; };
	
	Vec3 operator+(F32 other) { return Vec3(this->a + other, this->b + other, this->c + other); };
	Vec3 operator-(F32 other) { return Vec3(this->a - other, this->b - other, this->c - other); };
	Vec3 operator*(F32 other) { return Vec3(this->a * other, this->b * other, this->c * other); };
	Vec3 operator/(F32 other) { return Vec3(this->a / other, this->b / other, this->c / other); };
	
	Vec3 operator+=(F32 other) { this->a += other; this->b += other; this->c += other; return *this; };
	Vec3 operator-=(F32 other) { this->a -= other; this->b -= other; this->c -= other; return *this; };
	Vec3 operator*=(F32 other) { this->a *= other; this->b *= other; this->c *= other; return *this; };
	Vec3 operator/=(F32 other) { this->a /= other; this->b /= other; this->c /= other; return *this; };
};

union Vec4
{
	Vec4(F32 p) : a(p), b(p), c(p), d(p) {};
	Vec4(F32 p1, F32 p2, F32 p3, F32 p4) : a(p1), b(p2), c(p3), d(p4) {};
	
	struct { F32 a, b, c, d; };
	struct { F32 one, two, three, four; };
	struct { F32 w, x, y, z; };
	struct { F32 a, r, g, b; };
	
	Vec4 operator+(Vec4 other) { return Vec4(this->a + other.a, this->b + other.b, this->c + other.c, this->d + other.d); };
	Vec4 operator-(Vec4 other) { return Vec4(this->a - other.a, this->b - other.b, this->c - other.c, this->d - other.d); };
	Vec4 operator*(Vec4 other) { return Vec4(this->a * other.a, this->b * other.b, this->c * other.c, this->d * other.d); };
	Vec4 operator/(Vec4 other) { return Vec4(this->a / other.a, this->b / other.b, this->c / other.c, this->d / other.d); };
	
	Vec4 operator+=(Vec4 other) { this->a += other.a; this->b += other.b; this->c += other.c; this->d += other.d; return *this; };
	Vec4 operator-=(Vec4 other) { this->a -= other.a; this->b -= other.b; this->c -= other.c; this->d -= other.d; return *this; };
	Vec4 operator*=(Vec4 other) { this->a *= other.a; this->b *= other.b; this->c *= other.c; this->d *= other.d; return *this; };
	Vec4 operator/=(Vec4 other) { this->a /= other.a; this->b /= other.b; this->c /= other.c; this->d /= other.d; return *this; };
	
	Vec4 operator+(F32 other) { return Vec4(this->a + other, this->b + other, this->c + other, this->d + other); };
	Vec4 operator-(F32 other) { return Vec4(this->a - other, this->b - other, this->c - other, this->d - other); };
	Vec4 operator*(F32 other) { return Vec4(this->a * other, this->b * other, this->c * other, this->d * other); };
	Vec4 operator/(F32 other) { return Vec4(this->a / other, this->b / other, this->c / other, this->d / other); };
	
	Vec4 operator+=(F32 other) { this->a += other; this->b += other; this->c += other; this->d += other; return *this; };
	Vec4 operator-=(F32 other) { this->a -= other; this->b -= other; this->c -= other; this->d -= other; return *this; };
	Vec4 operator*=(F32 other) { this->a *= other; this->b *= other; this->c *= other; this->d *= other; return *this; };
	Vec4 operator/=(F32 other) { this->a /= other; this->b /= other; this->c /= other; this->d /= other; return *this; };
};

#endif //BASE_MATH_H
