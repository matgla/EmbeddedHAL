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

    void teardown() override
    {
        hal::interrupt::set_svc_handler([this](uint32_t number, void* argument, void* output){
        });
    }
protected:
    int number_;
    void* argument_;
    void* output_;
};

extern "C"
{
    void trigger_syscall(int number, const void* argument, void* output);
}

MSTEST_F(SvcShould, CallHandlerAndPassArguments)
{
    const int value_a = 103;
    double output = 0.0;
    trigger_syscall(10, &value_a, &output);

    mstest::expect_eq(*static_cast<int*>(argument_), 103);
    mstest::expect_eq(output_, &output);
    mstest::expect_eq(number_, 10);

    const int value_b = 123111;
    int output_b = 0;
    trigger_syscall(123, &value_b, &output_b);

    mstest::expect_eq(*static_cast<int*>(argument_), 123111);
    mstest::expect_eq(output_, &output_b);
    mstest::expect_eq(number_, 123);
}
