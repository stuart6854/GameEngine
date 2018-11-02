#pragma once
#include <ostream>

class Mat4 {

public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	Mat4();

	void setIdentity();
	void scale(float _s);
	void mul(Mat4 _b);

	friend std::ostream& operator<<(std::ostream& stream, const Mat4& m);

};

