#ifndef UTIL_H
#define UTIL_H
#include <assert.h>

#include <stdio.h>
#include <cstdlib>

#define check(val) if(val) { perror("#val: "); exit(EXIT_FAILURE); }
#endif
