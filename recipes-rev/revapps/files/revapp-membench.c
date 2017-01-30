#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

extern void tditrace(const char* format, ...) __attribute__((weak));

int main(void) {
#define TIMES 100

#define LARGE 512 * 1024
#define SMALL 64 * 1024

  int large = LARGE;
  int small = SMALL;

  void* allocated_mmap[TIMES];
  void* allocated_malloc_small[TIMES];
  void* allocated_malloc_large[TIMES];

  memset(allocated_mmap, 0, sizeof allocated_mmap);
  memset(allocated_malloc_small, 0, sizeof allocated_malloc_small);
  memset(allocated_malloc_large, 0, sizeof allocated_malloc_large);

  size_t count = 0;
  size_t i = 0;

  while (1) {
    for (i = 0; i < TIMES; i++) {

      if (tditrace != NULL) tditrace("@S+mmap");

      allocated_mmap[i] =
          mmap(NULL, large, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS
               /* | MAP_POPULATE */
               ,
               -1, 0);
      if (allocated_mmap[i] != -1) memset(allocated_mmap[i], 0, large);

      if (tditrace != NULL) tditrace("@S+malloc");

      allocated_malloc_large[i] = malloc(large);
      if (allocated_malloc_large[i]) memset(allocated_malloc_large[i], 0, large);

      allocated_malloc_small[i] = malloc(small);
      if (allocated_malloc_small[i]) memset(allocated_malloc_small[i], 0, small);

      usleep(50 * 1000);
    }

    for (i = 0; i < TIMES; i++) {
      if (allocated_mmap[i]) {
        munmap(allocated_mmap[i], large);
        free(allocated_malloc_large[i]);
        free(allocated_malloc_small[i]);
        usleep(50 * 1000);
      }
    }
  
    large += 50 * 1024;
    small += 10 * 1024;
  }
}