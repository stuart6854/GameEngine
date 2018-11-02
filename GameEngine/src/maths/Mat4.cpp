#include "Mat4.h"

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

void Mat4::scale(const float _s) {
	m11 *= _s;
	m12 *= _s;
	m13 *= _s;
	m14 *= _s;

	m21 *= _s;
	m22 *= _s;
	m23 *= _s;
	m24 *= _s;

	m31 *= _s;
	m32 *= _s;
	m33 *= _s;
	m34 *= _s;

	m41 *= _s;
	m42 *= _s;
	m43 *= _s;
	m44 *= _s;
}

void Mat4::mul(const Mat4 _b) {
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
}

std::ostream& operator<<(std::ostream& stream, const Mat4& m) {
	stream << "|" << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.m14 << "|\n";
	stream << "|" << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.m24 << "|\n";
	stream << "|" << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.m34 << "|\n";
	stream << "|" << m.m41 << ", " << m.m42 << ", " << m.m43 << ", " << m.m44 << "|\n";


	return stream;
}
