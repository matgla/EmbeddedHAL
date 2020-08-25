#include <board.hpp>

#include <stdio.h>

#include <mstest/mstest.hpp>

int main(void)
{
    board::board_init();


    int rc = mstest::run_tests();
    printf("Exit with code: %d\n", rc);
    exit(rc);
    printf("Exited: %d\n", rc);

    while (true)
    {

    }
}
