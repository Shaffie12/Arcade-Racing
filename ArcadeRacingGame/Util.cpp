#include "Util.h"


float Racing::Util::Lerp(float a, float b, float t){ return a + (b - a) * t; }
float Racing::Util::clamp(float n, float lower, float upper) 
{ 

	return std::max(lower, std::min(n, upper));

}
float Racing::Util::roundToDP(float val, float prec) 
{ 
	float power = pow(10, prec);
	return round(val * power) / power;
}