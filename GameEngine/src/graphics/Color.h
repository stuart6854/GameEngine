#pragma once
class Color {

private:
	float r_, g_, b_, a_;

public:
	Color();
	Color(float _red, float _green, float _blue, float _alpha);
	Color(int _red, int _green, int _blue, float _alpha);

	float r() { return r_; }
	float g() { return g_; }
	float b() { return b_; }
	float a() { return a_; }

	void set(float _red, float _green, float _blue, float _alpha);
	void set(int _red, int _green, int _blue, float _alpha);

};

inline Color::Color() {
	r_ = 1.f;
	g_ = 1.f;
	b_ = 1.f;
	a_ = 1.f;
}

inline Color::Color(float _red, float _green, float _blue, float _alpha) {
	r_ = _red;
	g_ = _green;
	b_ = _blue;
	a_ = _alpha;
}

inline Color::Color(int _red, int _green, int _blue, float _alpha) {
	r_ = _red / 255.f;
	g_ = _green / 255.f;
	b_ = _blue / 255.f;
	a_ = _alpha;
}

inline void Color::set(float _red, float _green, float _blue, float _alpha) {
	r_ = _red;
	g_ = _green;
	b_ = _blue;
	a_ = _alpha;
}

inline void Color::set(int _red, int _green, int _blue, float _alpha) {
	r_ = _red / 255.f;
	g_ = _green / 255.f;
	b_ = _blue / 255.f;
	a_ = _alpha;
}
