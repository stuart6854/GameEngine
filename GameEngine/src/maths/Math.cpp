#include "Math.h"

int Math::clamp(int _valToClamp, int _min, int _max) {
	if (_valToClamp < _min) _valToClamp = _min;
	if (_valToClamp > _max) _valToClamp = _max;

	return _valToClamp;
}
