#pragma once
#include <ostream>

class Vec3 {

private:
	int x_, y_, z_;

public:
	static const Vec3 zero;
	static const Vec3 one;
	static const Vec3 right;
	static const Vec3 up;
	static const Vec3 forward;

	Vec3();
	Vec3(int _x, int _y, int _z);

	int x() { return x_; }
	int y() { return y_; }
	int z() { return z_; }

	void set(const float _arr[]) {
		x_ = _arr[0];
		y_ = _arr[1];
		z_ = _arr[2];
	}

	void negate();

	float length();
	void normalize();
	Vec3 normalized();

	Vec3 operator+(const Vec3& _b);
	Vec3 operator-(const Vec3& _b);
	Vec3 operator*(const Vec3& _b);
	Vec3 operator/(const Vec3& _b);

	static Vec3 normalize(Vec3 _vec);
	static float dot(const Vec3 _a, const Vec3 _b);
	static Vec3 cross(const Vec3 _a, const Vec3 _b);

	friend std::ostream& operator<<(std::ostream& _output, const Vec3& _v);

};

