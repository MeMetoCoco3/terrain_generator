
#ifndef VSTD
#define VSTD
#include <cstdio>
#include <string>
#include <stdint.h>

typedef uint32_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t   u8;

typedef int32_t b32;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t   i8;

typedef float f32;
typedef double f64;

struct vec2
{
    f32 x;
    f32 y;
	vec2() = default;
	vec2(f32 a, f32 b) : x(a), y(b) {}
	std::string to_string(void) const
	{
		char buffer[64];
		std::snprintf(buffer, sizeof(buffer), "%.2f, %.2f\n", x, y);
		return buffer;
	}
};

struct vec3
{
    f32 x;
    f32 y;
    f32 z;

	vec3() = default;
	vec3(f32 a, f32 b, f32 c) : x(a), y(b), z(c) {}

	std::string to_string(void) const
	{
		char buffer[64];
		std::snprintf(buffer, sizeof(buffer), "%.2f, %.2f, %.2f\n", x, y, z);
		return buffer;
	}

};


#endif
