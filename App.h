/*
  ==============================================================================

    MyTest.h
    Created: 23 Jan 2017 9:39:38am
    Author:  Michael R Mulshine

  ==============================================================================
*/

#pragma once

#define ZEN_USE_DYNAMIC_ALLOCATION 0


#include "AppWrapper.h"
#include "../zenlib/zen.h"


//namespace zen {
//class ZenProcessor
//{
//public:
//	ZenProcessor(float sampleRate, int blockSize): Instance (sampleRate, (size_t)blockSize, &getRandomFloat)
//	{
//
//	}
//	~ZenProcessor()
//	{
//
//	}
//private:
//
//};
//} //namespace zen


	// ZENTest API
float   ZENTest_tick            (float input);
void 	ZENTest_processBlock(const float **in, float **out, int chan_num, size_t size);
void    ZENTest_init            (float sampleRate, int blocksize);
void    ZENTest_block           (void);
void    ZENTest_end             (void);
void    ZENTest_noteOn          (int midiNoteNumber, float velocity);
void    ZENTest_noteOff         (int midiNoteNumber);

