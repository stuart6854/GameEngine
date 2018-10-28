#include "Vec2.h"

Vec2::Vec2(const int _x, const int _y) {
	x_ = _x;
	y_ = _y;
}

Vec2 Vec2::operator+(const Vec2& b) {
	return {this->x_ + b.x_, this->y_ + b.y_};
}

Vec2 Vec2::operator-(const Vec2& b) {
	return {this->x_ - b.x_, this->y_ - b.y_};
}

Vec2 Vec2::operator*(const Vec2& b) {
	return {this->x_ * b.x_, this->y_ * b.y_};
}

Vec2 Vec2::operator/(const Vec2& b) {
	return {this->x_ / b.x_, this->y_ / b.y_};
}
