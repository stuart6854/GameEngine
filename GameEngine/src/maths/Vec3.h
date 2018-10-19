#pragma once
class Vec3 {

public:
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

	Vec3 operator+(const Vec3& b);
	Vec3 operator-(const Vec3& b);
	Vec3 operator*(const Vec3& b);
	Vec3 operator/(const Vec3& b);

private:
	int x_, y_, z_;

};

