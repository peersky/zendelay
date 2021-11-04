/*
 MIT License

 Copyright (c) 2021 Tim Pechersky

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

#ifdef DEBUG
#define USE_DEVLIB_PRINT 1U
#define PRINT_LVL1_ON 1U
#define PRINT_LVL2_ON 1U
#define PRINT_LVL3_ON 1U
#endif

#include "stdint.h"
#include "stdio.h"
#include <io.hpp>
#include <assert.h>
#include "bsp.h"

#ifndef assert_param

#define assert_param(expr) DEVLIB_ASSERT_PARAM(expr)
#endif

#define print(fmt, level, ...)            \
    do                                    \
    {                                     \
        if (level == 1)                   \
            PRINT_LVL1(fmt, __VA_ARGS__); \
        else if (level == 2)              \
            PRINT_LVL2(fmt, __VA_ARGS__); \
        else if (level == 3)              \
            PRINT_LVL3(fmt, __VA_ARGS__); \
        else                              \
            ERROR_HANDLER();              \
    } while (0)

inline void setDebugAnalyser(float *ch1, float *ch2, size_t size)
{
}

inline void send_to_analyser(size_t channel, float *buffer)
{
}

inline void append_to_analyser(size_t channel, float sample)
{
}

namespace debugProvider
{
    class LoadMonitor
    {
    public:
        LoadMonitor()
        {
        }
        ~LoadMonitor()
        {
        }
        inline void startAverageMonitor()
        {
            start_ = DWT->CYCCNT;
            lap_ = 0;
            laps_ = 0;
            total_ = 0;
        }
        inline void Lap()
        {
            lap_ = DWT->CYCCNT;
            total_ += lap_;
            laps_++;
            average_ = total_ / laps_;
        }
        // #else
        //         inline void startAverageMonitor()
        //         {
        //             start_ = std::chrono::high_resolution_clock::now();
        //             lap_ = 0;
        //             laps_ = 0;
        //             total_ = 0;
        //         }
        //         inline void lapStart()
        //         {
        //             start_ = std::chrono::high_resolution_clock::now();
        //         }
        //         inline void lapEnd()
        //         {
        //             lap_ = std::chrono::duration<float, std::milli>(std::chrono::high_resolution_clock::now() - start_).count();
        //             total_ += lap_;
        //             laps_++;
        //             average_ = total_ / laps_;
        //         }
        // #endif

    private:
        int start_;
        int finish_;
        int laps_;
        int average_;
        int lap_;
        int total_;
        // #else
        //         std::chrono::steady_clock::time_point start_;
        //         std::chrono::steady_clock::time_point finish_;
        //         float average_;
        //         float laps_;
        //         float lap_;
        //         float total_;
        // #endif
    };
} //namespace debugProvider
