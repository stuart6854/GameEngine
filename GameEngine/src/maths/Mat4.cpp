#include "Mat4.h"
#include "Math.h"

Mat4::Mat4() {
	setIdentity();
}

void Mat4::setIdentity() {
	m11 = m12 = m13 = m14 = 0;
	m21 = m22 = m23 = m24 = 0;
	m31 = m32 = m33 = m34 = 0;
	m41 = m42 = m43 = m44 = 0;

	m11 = m22 = m33 = m44 = 1;
}

Mat4 Mat4::add(Mat4 _b) {
	m11 += _b.m11;
	m12 += _b.m12;
	m13 += _b.m13;
	m14 += _b.m14;

	m21 += _b.m21;
	m22 += _b.m22;
	m23 += _b.m23;
	m24 += _b.m24;

	m31 += _b.m31;
	m32 += _b.m32;
	m33 += _b.m33;
	m34 += _b.m34;

	m41 += _b.m41;
	m42 += _b.m42;
	m43 += _b.m43;
	m44 += _b.m44;

	return *this;
}

Mat4 Mat4::sub(Mat4 _b) {
	m11 -= _b.m11;
	m12 -= _b.m12;
	m13 -= _b.m13;
	m14 -= _b.m14;

	m21 -= _b.m21;
	m22 -= _b.m22;
	m23 -= _b.m23;
	m24 -= _b.m24;

	m31 -= _b.m31;
	m32 -= _b.m32;
	m33 -= _b.m33;
	m34 -= _b.m34;

	m41 -= _b.m41;
	m42 -= _b.m42;
	m43 -= _b.m43;
	m44 -= _b.m44;

	return *this;
}

Mat4 Mat4::mul(const float _scalar) {
	m11 *= _scalar;
	m12 *= _scalar;
	m13 *= _scalar;
	m14 *= _scalar;

	m21 *= _scalar;
	m22 *= _scalar;
	m23 *= _scalar;
	m24 *= _scalar;

	m31 *= _scalar;
	m32 *= _scalar;
	m33 *= _scalar;
	m34 *= _scalar;

	m41 *= _scalar;
	m42 *= _scalar;
	m43 *= _scalar;
	m44 *= _scalar;

	return *this;
}

Mat4 Mat4::mul(const Mat4 _b) {
	Mat4 t;
	t.m11 = (m11 * _b.m11) + (m12 * _b.m21) + (m13 * _b.m31) + (m14 * _b.m41);
	t.m12 = (m11 * _b.m12) + (m12 * _b.m22) + (m13 * _b.m32) + (m14 * _b.m42);
	t.m13 = (m11 * _b.m13) + (m12 * _b.m23) + (m13 * _b.m33) + (m14 * _b.m43);
	t.m14 = (m11 * _b.m14) + (m12 * _b.m24) + (m13 * _b.m34) + (m14 * _b.m44);

	t.m21 = (m21 * _b.m11) + (m22 * _b.m21) + (m23 * _b.m31) + (m24 * _b.m41);
	t.m22 = (m21 * _b.m12) + (m22 * _b.m22) + (m23 * _b.m32) + (m24 * _b.m42);
	t.m23 = (m21 * _b.m13) + (m22 * _b.m23) + (m23 * _b.m33) + (m24 * _b.m43);
	t.m24 = (m21 * _b.m14) + (m22 * _b.m24) + (m23 * _b.m34) + (m24 * _b.m44);

	t.m31 = (m31 * _b.m11) + (m32 * _b.m21) + (m33 * _b.m31) + (m34 * _b.m41);
	t.m32 = (m31 * _b.m12) + (m32 * _b.m22) + (m33 * _b.m32) + (m34 * _b.m42);
	t.m33 = (m31 * _b.m13) + (m32 * _b.m23) + (m33 * _b.m33) + (m34 * _b.m43);
	t.m34 = (m31 * _b.m14) + (m32 * _b.m24) + (m33 * _b.m34) + (m34 * _b.m44);

	t.m41 = (m41 * _b.m11) + (m42 * _b.m21) + (m43 * _b.m31) + (m44 * _b.m41);
	t.m42 = (m41 * _b.m12) + (m42 * _b.m22) + (m43 * _b.m32) + (m44 * _b.m42);
	t.m43 = (m41 * _b.m13) + (m42 * _b.m23) + (m43 * _b.m33) + (m44 * _b.m43);
	t.m44 = (m41 * _b.m14) + (m42 * _b.m24) + (m43 * _b.m34) + (m44 * _b.m44);

	*this = t;

	return *this;
}

void Mat4::transpose() {
	Mat4 m;

	m.m11 = m11;
	m.m12 = m21;
	m.m13 = m31;
	m.m14 = m41;

	m.m21 = m12;
	m.m22 = m22;
	m.m23 = m32;
	m.m24 = m42;

	m.m31 = m13;
	m.m32 = m23;
	m.m33 = m33;
	m.m34 = m43;

	m.m41 = m14;
	m.m42 = m24;
	m.m43 = m34;
	m.m44 = m44;

	*this = m;
}

void Mat4::translate(const float _x, const float _y, const float _z) {
	m14 += _x;
	m24 += _y;
	m34 += _z;
}

void Mat4::rotate(float _degrees, Vec3 _axis) {
	const double rads = Math::radians(_degrees);

	Mat4 xRotM;
	Mat4 yRotM;
	Mat4 zRotM;
	if(_axis.x() != 0) {
		xRotM.m22 = cos(rads);
		xRotM.m23 = -sin(rads);
		xRotM.m32 = sin(rads);
		xRotM.m33 = cos(rads);
	}
	if(_axis.y() != 0) {
		yRotM.m11 = cos(rads);
		yRotM.m13 = sin(rads);
		yRotM.m31 = -sin(rads);
		yRotM.m33 = cos(rads);
	}
	if(_axis.z() != 0) {
		zRotM.m11 = cos(rads);
		zRotM.m12 = -sin(rads);
		zRotM.m21 = sin(rads);
		zRotM.m22 = cos(rads);
	}
	Mat4 rotMatrix = xRotM;
	rotMatrix.mul(yRotM);
	rotMatrix.mul(zRotM);

	this->mul(rotMatrix);
}

void Mat4::scale(float _x, float _y, float _z) {
	Mat4 scaleMatrix;
	scaleMatrix.m11 = _x;
	scaleMatrix.m22 = _y;
	scaleMatrix.m33 = _z;

	this->mul(scaleMatrix);
}

Mat4 Mat4::lookAt(Vec3 _eye, Vec3 _lookAt, Vec3 _up = Vec3::up) {
	Vec3 forward = Vec3::normalize(_eye - _lookAt);
	Vec3 right = Vec3::cross(_up, forward);
	Vec3 up = Vec3::cross(forward, right);

	Mat4 lookAt;

	lookAt.m11 = right.x();
	lookAt.m12 = right.y();
	lookAt.m13 = right.z();
	lookAt.m21 = up.x();
	lookAt.m22 = up.y();
	lookAt.m23 = up.z();
	lookAt.m31 = forward.x();
	lookAt.m32 = forward.y();
	lookAt.m33 = forward.z();
	lookAt.m14 = -_eye.x();
	lookAt.m24 = -_eye.y();
	lookAt.m34 = -_eye.z();

	return lookAt;
}

Mat4 Mat4::orthographic(float _right, float _left, float _top, float _bottom, float _near, float _far) {
	Mat4 ortho;

	ortho.m11 = (2) / (_right - _left);
	ortho.m22 = (2) / (_top - _bottom);
	ortho.m33 = -((2) / (_far - _near));
	ortho.m14 = -((_right + _left) / (_right - _left));
	ortho.m24 = -((_top + _bottom) / (_top - _bottom));
	ortho.m34 = -((_far + _near) / (_far - _near));

	return ortho;
}

Mat4 Mat4::perspective(float _fov, float _aspectRatio, float _near, float _far) {
	const float top = _near * tan(Math::radians(_fov / 2));
	const float bottom = -top;
	const float right = top * _aspectRatio;
	const float left = -right;
	
	Mat4 persp;

	persp.m11 = (2 * _near) / (right - left);
	persp.m22 = (2 * _near) / (top - bottom);
	persp.m13 = (right + left) / (right - left);
	persp.m23 = (top + bottom) / (top - bottom);
	persp.m33 = -(_far + _near) / (_far - _near);
	persp.m34 = -(2 * _far * _near) / (_far - _near);
	persp.m43 = -1;

	return persp;
}

Mat4 Mat4::operator*(const Mat4& _b) {
	return this->mul(_b);
}

std::ostream& operator<<(std::ostream& _stream, const Mat4& _m) {
	_stream << "|" << _m.m11 << ", " << _m.m12 << ", " << _m.m13 << ", " << _m.m14 << "|\n";
	_stream << "|" << _m.m21 << ", " << _m.m22 << ", " << _m.m23 << ", " << _m.m24 << "|\n";
	_stream << "|" << _m.m31 << ", " << _m.m32 << ", " << _m.m33 << ", " << _m.m34 << "|\n";
	_stream << "|" << _m.m41 << ", " << _m.m42 << ", " << _m.m43 << ", " << _m.m44 << "|\n";


	return _stream;
}
