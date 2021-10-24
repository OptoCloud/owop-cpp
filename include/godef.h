#ifndef GOSTR_H
#define GOSTR_H

#include <cstddef> /* for ptrdiff_t below */
#include <string_view>

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

inline _GoString_ MakeGoString(std::string_view s) {
    _GoString_ str;
    str.n = s.size();
    str.p = (char*)malloc(str.n);
    memcpy((char*)str.p, s.data(), str.n);
    return str;
}
inline void FreeGoString(_GoString_ s) {
    free((char*)s.p);
}

#endif // GOSTR_H
