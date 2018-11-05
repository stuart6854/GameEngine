#pragma once

class Math {

public:
	static const double PI;

	static int clamp(int _valToClamp, int _min, int _max);

	static double radians(double _degrees);
	static double degrees(double _radians);

};
