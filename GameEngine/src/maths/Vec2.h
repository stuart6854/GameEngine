#pragma once
class Vec2 {

public:
	Vec2(int _x = 0, int _y = 0);

	int x() { return x_; }
	int y() { return y_; }

	void set(const float _arr[]) {
		x_ = _arr[0];
		y_ = _arr[1];
	}

	Vec2 operator+(const Vec2& b);
	Vec2 operator-(const Vec2& b);
	Vec2 operator*(const Vec2& b);
	Vec2 operator/(const Vec2& b);

private:
	int x_, y_;

};

