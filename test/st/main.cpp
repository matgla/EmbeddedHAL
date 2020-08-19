#include <board.hpp>

#include <stdio.h>

#include <mstest.hpp>

int main(void)
{
    board::board_init();


    int rc = mstest::run_tests();
    exit(rc);
    while (true)
    {

    }
}
