#include <mstest/mstest.hpp>

#include <cstdio>

#include "hal/interrupt/svc.hpp"
#include "hal/time/sleep.hpp"

class SvcShould : public mstest::Test
{
    void setup() override
    {
        hal::interrupt::set_svc_handler([this](uint32_t number, void* argument, void* output){
            number_ = number;
            argument_ = argument;
            output_ = output;
        });
    }
protected:
    int number_;
    void* argument_;
    void* output_;
};

extern "C"
{
    void trigger_syscall(int number, void* argument, void* output)
    {
        asm volatile inline ("svc 0\n"
                  "bx lr\n");
    }
}

MSTEST_F(SvcShould, CallHandlerAndPassArguments)
{
    int value_a = 103;
    double output = 0.0;
    trigger_syscall(10, &value_a, &output);

    mstest::expect_eq(*static_cast<int*>(argument_), 103);
    mstest::expect_eq(output_, &output);
    mstest::expect_eq(number_, 10);
}
