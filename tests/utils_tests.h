#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "config.h"

#ifdef HAVE_C99_VARARGS_MACROS
#define PRINT_ERR(...)               fprintf(stderr, "AUBIO ERROR: " __VA_ARGS__)
#define PRINT_MSG(...)               fprintf(stdout, __VA_ARGS__)
#define PRINT_DBG(...)               fprintf(stderr, __VA_ARGS__)
#define PRINT_WRN(...)               fprintf(stderr, "AUBIO WARNING: " __VA_ARGS__)
#else
#define PRINT_ERR(format, args...)   fprintf(stderr, "AUBIO ERROR: " format , ##args)
#define PRINT_ERR(format, args...)   fprintf(stdout, format , ##args)
#define PRINT_ERR(format, args...)   fprintf(stderr, format , ##args)
#define PRINT_ERR(format, args...)   fprintf(stderr, "AUBIO WARNING: " format, ##args)
#endif

#ifdef HAVE_WIN_HACKS
// http://en.wikipedia.org/wiki/Linear_congruential_generator
// no srandom/random on win32

uint_t srandom_seed = 1029;

void srandom(uint_t new_seed) {
    srandom_seed = new_seed;
}

uint_t random(void) {
    srandom_seed = 1664525 * srandom_seed + 1013904223;
    return srandom_seed;
}
#endif

void utils_init_random (void);

void utils_init_random (void) {
  time_t now = time(0);
  struct tm *tm_struct = localtime(&now);
  int seed = tm_struct->tm_sec;
  //PRINT_WRN("current seed: %d\n", seed);
  srandom (seed);
}
