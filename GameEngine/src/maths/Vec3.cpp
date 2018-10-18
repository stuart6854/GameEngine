#include "Vec3.h"

Vec3::Vec3() {
	x_ = 0;
	y_ = 0;
	z_ = 0;
}

Vec3::Vec3(const int _x, const int _y, const int _z) {
	x_ = _x;
	y_ = _y;
	z_ = _z;
}

Vec3 Vec3::operator+(const Vec3& b) {
	return {this->x_ + b.x_, this->y_ + b.y_, this->z_ + b.z_};
}

Vec3 Vec3::operator-(const Vec3& b) {
	return { this->x_ - b.x_, this->y_ - b.y_, this->z_ - b.z_ };
}

Vec3 Vec3::operator*(const Vec3& b) {
	return { this->x_ * b.x_, this->y_ * b.y_, this->z_ * b.z_ };
}

Vec3 Vec3::operator/(const Vec3& b) {
	return { this->x_ / b.x_, this->y_ / b.y_, this->z_ / b.z_ };
}
