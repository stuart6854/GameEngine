#include "Math.h"

const double Math::PI = 3.14159265359;

int Math::clamp(int _valToClamp, int _min, int _max) {
	if (_valToClamp < _min) _valToClamp = _min;
	if (_valToClamp > _max) _valToClamp = _max;

	return _valToClamp;
}

double Math::radians(double _degrees) {
	return (_degrees * PI / 180.0);
}

double Math::degrees(double _radians) {
	return (_radians * 180 / PI);
}
