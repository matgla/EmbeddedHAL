// This file is part of EmbeddedHAL project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

extern "C"
{
    extern char __StackLimit; /* Set by linker.  */
    
    void *_sbrk(int incr) 
    {
        extern char end; /* Set by linker.  */
        static char *heap_end;
        char *prev_heap_end;

        if (heap_end == 0)
            heap_end = &end;

        prev_heap_end = heap_end;
        char *next_heap_end = heap_end + incr;

        if (__builtin_expect(next_heap_end >= (&__StackLimit), false)) {
    #if PICO_USE_OPTIMISTIC_SBRK
            if (next_heap_end == &__StackLimit) {
    //        errno = ENOMEM;
                return (char *) -1;
            }
            next_heap_end = &__StackLimit;
    #else
            return (char *) -1;
    #endif
        }

        heap_end = next_heap_end;
        return (void *) prev_heap_end;
    }
}

