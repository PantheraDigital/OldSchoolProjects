#include "Vec3.h"

int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	float d = 4.0f;

	Vec3<int> vec(a,b,c);
	Vec3<int> vec2(c,b,a);

	vec.GetLengthSqrt();

	vec + vec2;
	//vec = vec2;
	vec - vec2;
	vec * vec2;

	vec += vec2;
	vec == vec2;
	vec -= vec2;

	vec *= d;
	vec /= d;
	

	std::cout << "\n" << vec2 << "\n" << vec;

	getchar();
	return 0;
}