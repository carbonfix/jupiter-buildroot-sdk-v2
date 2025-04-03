/*
 * Copyright (C) 2023 Spacemit Limited
 * All Rights Reserved.
 */

// https://ffmpeg.org/doxygen/4.4/cuda__runtime_8h_source.html
// https://github.com/tpn/cuda-samples/blob/master/v8.0/include/vector_types.h

#ifndef _MISSING_DATATYPE_H_
#define _MISSING_DATATYPE_H_


typedef unsigned char uchar;

struct uchar1
{
    unsigned char x;
};
struct uchar2
{
	unsigned char x, y;
};
struct uchar3
{
	unsigned char x, y, z;
};

struct uchar4
{
	unsigned char x, y, z, w;
};

typedef struct int2
{
    int x, y;
} int2;

typedef struct uint3
{
    unsigned int x, y, z;
} uint3;

struct float1
{
    float x;
};
struct float2
{
	float x, y;
};

struct float3
{
	float x, y, z;
};

struct float4
{
	float x, y, z, w;
};

 // Basic initializers (simple macros rather than inline functions)
#define make_int2(a, b) ((int2){.x = a, .y = b})
#define make_uchar2(a, b) ((uchar2){.x = a, .y = b})
#define make_ushort2(a, b) ((ushort2){.x = a, .y = b})
#define make_float2(a, b) ((float2){.x = a, .y = b})
#define make_int4(a, b, c, d) ((int4){.x = a, .y = b, .z = c, .w = d})
#define make_uchar4(a, b, c, d) ((uchar4){.x = a, .y = b, .z = c, .w = d})
#define make_ushort4(a, b, c, d) ((ushort4){.x = a, .y = b, .z = c, .w = d})
#define make_float4(a, b, c, d) ((float4){.x = a, .y = b, .z = c, .w = d})

struct dim3
{
    unsigned int x, y, z;

    dim3(unsigned int vx = 1, unsigned int vy = 1, unsigned int vz = 1) : x(vx), y(vy), z(vz) {};
    // dim3(uint3 v) : x(v.x), y(v.y), z(v.z) {};
    // operator uint3(void) { uint3 t; t.x = x; t.y = y; t.z = z; return t; };
};

typedef struct dim3 dim3;


#endif
