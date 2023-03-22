#ifndef COMMON_HH
#define COMMON_HH
// #include <MKB/aliases.h>
#ifndef __MKB_ALIASES_H
#define __MKB_ALIASES_H

#include <stdint.h>
#include <stddef.h>

typedef  int8_t   int8 , i8 , s8 , CHAR ;
typedef  int16_t  int16, i16, s16, SHORT;
typedef  int32_t  int32, i32, s32, INT  ;
typedef  int64_t  int64, i64, s64, LONG ;
typedef uint8_t  uint8 , u8 ,      BYTE ;
typedef uint16_t uint16, u16,      WORD ;
typedef uint32_t uint32, u32,      DWORD;
typedef uint64_t uint64, u64,      QWORD;
typedef size_t    usize, usz            ;
typedef ptrdiff_t isize, isz            ;
typedef float            f32            ;
typedef double           f64            ;

#ifdef __cplusplus
    #define fn auto
    #define let auto
    #define self (*this)

    #include <utility>
    using std::move;
#endif

#endif // __MKB_ALIASES_H
#endif // COMMON_HH
