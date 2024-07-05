#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(c) if (!c) { (*(volatile int *)0 = 0);  } while(0)

#define LOG(...) fprintf(stdout, ##__VA_ARGS__)
#define LOG_ERROR(...) fprintf(stderr, ##__VA_ARGS__)
#define LOG_ASSERT(c, ...) if (!c) { LOG(##__VA_ARGS__); ASSERT(c); } while(0)

#define STRADD(a, b) a ## b