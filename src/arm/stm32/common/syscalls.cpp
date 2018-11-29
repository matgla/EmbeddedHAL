#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

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

caddr_t _sbrk(int incr)
{
    return 0;
}

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