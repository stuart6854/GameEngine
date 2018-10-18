#pragma once
class Vec3 {

public:
	Vec3();
	Vec3(int _x, int _y, int _z);

	int x() { return x_; }
	int y() { return y_; }
	int z() { return z_; }

	Vec3 operator+(const Vec3& b);
	Vec3 operator-(const Vec3& b);
	Vec3 operator*(const Vec3& b);
	Vec3 operator/(const Vec3& b);

private:
	int x_, y_, z_;

};

