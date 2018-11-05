#include "Vec3.h"
#include <cmath>

const Vec3 Vec3::zero = Vec3(0, 0, 0);
const Vec3 Vec3::one = Vec3(1, 1, 1);
const Vec3 Vec3::right = Vec3(1, 0, 0);
const Vec3 Vec3::up = Vec3(0, 1, 0);
const Vec3 Vec3::forward = Vec3(0, 0, 1);

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

void Vec3::negate() {
	x_ *= -1;
	y_ *= -1;
	z_ *= -1;
}

float Vec3::length() {
	const float x = x_ ^ 2;
	const float y = y_ ^ 2;
	const float z = z_ ^ 2;
	return sqrt(x + y + z);
}

void Vec3::normalize() {
	const float l = length();
	x_ = x_ / l;
	y_ = y_ / l;
	z_ = z_ / l;
}

Vec3 Vec3::normalized() {
	Vec3 normalized(*this);
	normalized.normalize();
	return normalized;
}

Vec3 Vec3::operator+(const Vec3& _b) {
	return {this->x_ + _b.x_, this->y_ + _b.y_, this->z_ + _b.z_};
}

Vec3 Vec3::operator-(const Vec3& _b) {
	return { this->x_ - _b.x_, this->y_ - _b.y_, this->z_ - _b.z_ };
}

Vec3 Vec3::operator*(const Vec3& _b) {
	return { this->x_ * _b.x_, this->y_ * _b.y_, this->z_ * _b.z_ };
}

Vec3 Vec3::operator/(const Vec3& _b) {
	return { this->x_ / _b.x_, this->y_ / _b.y_, this->z_ / _b.z_ };
}

Vec3 Vec3::normalize(Vec3 _vec) {
	return _vec.normalized();
}

float Vec3::dot(const Vec3 _a, const Vec3 _b) {
	return (_a.x_ * _b.x_) + (_a.y_ + _a.y_) + (_a.z_ + _b.z_);
}

Vec3 Vec3::cross(const Vec3 _a, const Vec3 _b) {
	Vec3 cross;

	cross.x_ = (_a.y_ * _b.z_) - (_a.z_ * _b.y_);
	cross.y_ = (_a.z_ * _b.x_) - (_a.x_ * _b.z_);
	cross.z_ = (_a.x_ * _b.y_) - (_a.y_ * _b.x_);

	return cross;
}

std::ostream& operator<<(std::ostream& _output, const Vec3& _v) {
	_output << "[" << _v.x_;
	_output << ", " << _v.y_;
	_output << ", " << _v.z_;
	_output << "]";
	return _output;
}
