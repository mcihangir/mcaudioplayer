#pragma once

#include <iostream>
#include <cstdio>

#define MC_DEBUG

#ifdef MC_DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        do { \
            fprintf(stdout, fmt, ##__VA_ARGS__); \
        } while (0)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

//fprintf(stdout, fmt "\n", ##__VA_ARGS__); \