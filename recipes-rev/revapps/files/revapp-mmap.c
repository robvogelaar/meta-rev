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

int allocated = 0;
void *alloc;

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s MB\n", argv[0]);
    exit(-1);
  }
  while (1) {
    if (allocated < atoi(argv[1])) {
      alloc = mmap(NULL, 1024 * 1024, PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS
           /* | MAP_POPULATE */
           ,
           -1, 0);
      if (alloc != -1) memset(alloc, 0, 1024 * 1024);
      allocated++;
    }
    usleep(50 * 1000);
  }
}
