#!/bin/bash

echo "==EXECUTE TESTS=="
echo "1) UT"
mkdir -p build/x86_64/ut
cd build/x86_64/ut
cmake ../../.. -DBUILD_UT=ON -DCMAKE_BUILD_TYPE=release -GNinja
ninja run_hal_ut
cd ../..
mkdir -p arm
cd arm
mkdir -p stm32-black-pill-st
cd stm32-black-pill-st
cmake ../../.. -DBUILD_ST=ON -DCMAKE_BUILD_TYPE=release -DBOARD=Stm32_Black_Pill
