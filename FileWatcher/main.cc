#include <QCoreApplication>
#include <cmath>
#include "common.hh"

fn main (i32 argc, char ** argv) -> i32 {
    printf ("hello!!!\n");
    ret QCoreApplication {argc, argv} .exec();
}
