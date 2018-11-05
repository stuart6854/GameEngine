#pragma once
#include <ostream>
#include "Vec3.h"

class Mat4 {

public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	Mat4();

	void setIdentity();

	Mat4 add(Mat4 _b);
	Mat4 sub(Mat4 _b);

	Mat4 mul(float _scalar);
	Mat4 mul(Mat4 _b);

	void transpose();

	void translate(float _x, float _y, float _z);
	void rotate(float _degrees, Vec3 _axis);
	void scale(float _x, float _y, float _z);

	float* toArray();

	static Mat4 lookAt(Vec3 _eye, Vec3 _lookAt, Vec3 _up);

	static Mat4 orthographic(float _right, float _left, float _top, float _bottom, float _near, float _far);
	static Mat4 perspective(float _fov, float _aspectRatio, float _near, float _far);

	Mat4 operator+(const Mat4& _b);
	Mat4 operator-(const Mat4& _b);
	Mat4 operator*(const Mat4& _b);
	Mat4 operator/(const Mat4& _b);

	friend std::ostream& operator<<(std::ostream& _stream, const Mat4& _m);

};

