#ifndef COMMON_HH
#define COMMON_HH

#ifndef __MKB_ALIASES_H
#define __MKB_ALIASES_H

#include <stdint.h>
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;
typedef ptrdiff_t isize;
typedef float f32;
typedef double f64;

#ifdef __cplusplus
    #include <utility>
    //#define let auto
    //#define self (*this)
#endif

#endif // __MKB_ALIASES_H

#include "iocc.hh"
#include <QVector>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

struct ChartData {
    struct Point {
        float t;
        float v;
    };

    QVector<Point> points;
};

enum ColorScheme {
    Light,
    Dark,
    BlueCerulean,
};

#endif // COMMON_HH
