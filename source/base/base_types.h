/* date = April 5th 2024 7:31 pm */

#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <stdint.h>

typedef int8_t  I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float  F32;
typedef double F64;

typedef I8 B8;
typedef I16 B16;
typedef I32 B32;
typedef I64 B64;

// Compatability NOTE
typedef void U0;
typedef U64 size_t;

#define	function	static
#define local		static

#endif //BASE_TYPES_H
