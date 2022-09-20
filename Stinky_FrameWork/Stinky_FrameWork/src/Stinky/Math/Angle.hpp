#pragma once 

namespace Stinky
{
	//	declared PI
	constexpr float PI = 3.14159265f;

	constexpr float HALF_PI = PI / 2.f;
	constexpr float QUARTER_PI = PI / 4.f;

	constexpr float TWO_PI = PI * 2.f;
	
	//	translate between radians and degrees
	constexpr float to_radians(float angle_in_degrees) noexcept { return angle_in_degrees * PI / 180.f; }
	constexpr float to_degrees(float angle_in_radians) noexcept { return angle_in_radians * 180.f / PI; }

}