#include <errno.h>
#include <string.h>
#include <cstdint>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include "hal/memory/heap.hpp"

extern "C"
{
    int _gettimeofday(struct timeval* tv, void* tzvp);
    void _init();
    void _exit(int code);
    int _kill(int pid, int sig);
    int _getpid(int n);
    caddr_t _sbrk(int incr);
    int _write(int file, const char* ptr, int len);
    int _read(int file, char* ptr, int len);
    int _isatty(int file);
    int _lseek(int file, int ptr, int dir);
    int _close(int file);
    int _fstat(int file, struct stat* st);
}

int _gettimeofday(struct timeval* tv, void* tzvp)
{
    return 0;
}

void _init()
{
}
void _exit(int code)
{
}
int _kill(int pid, int sig)
{
    return 0;
}
int _getpid(int n)
{
    return 0;
}

extern char __heap_start;
extern char __heap_end;

static char* current_heap_end = &__heap_start;

caddr_t _sbrk(int incr)
{

    if (current_heap_end + incr > (&__heap_end))
    {
        errno = ENOMEM;
        return NULL;
    }

    char* previous_heap_end = current_heap_end;
    current_heap_end += incr;
    return static_cast<caddr_t>(previous_heap_end);
}

namespace hal
{
namespace memory
{

std::size_t get_heap_size()
{
    return (&__heap_end) - (&__heap_start);
}

std::size_t get_heap_usage()
{
    return current_heap_end - (&__heap_start);
}

} // namespace memory
} // namespace hal

int _write(int file, const char* ptr, int len)
{
    return 0;
}

int _read(int file, char* ptr, int len)
{
    return 0;
}

int _isatty(int file)
{
    return 0;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _close(int file)
{
    return 0;
}

int _fstat(int file, struct stat* st)
{
    return 0;
}