#include "AppWrapper.h"
#include <math.h>


zen::AudioInstance ZenInstance;


float gain;
float dtime;
bool buttonState;
int ratio = 2;
float x = 0.0f;
float y = 0.0f;
float a, b, c, d;

float* bufIn;
float* bufOut;

#define MSIZE 2048000
float memory[MSIZE];

	//zen::Wave *wave3;
zen::Wave wave(ZenInstance);
zen::Wave lfo(ZenInstance);
zen::Interpolator sliderInterpolator[SLIDER_NUM_ENUM];
	//zenInterpolate_t phaseInterpolator, fInterpolator, filterInterpolator;
zen::Svf filterTest;

#define NUM_DELAY_CHANNELS 2
zen::Delay<float, 48000, 2> stereoDelay(ZenInstance);

float UIlabels[SLIDER_NUM_ENUM];
float delta;

#define  ZEN_BLOCK_SIZE 64

float slider2_block[ZEN_BLOCK_SIZE];
float slider3_block[ZEN_BLOCK_SIZE];

float sliders_blocks[SLIDER_NUM_ENUM][2048];
float delay_offsets_[NUM_DELAY_CHANNELS][2048] = {0};
float **delay_offsets = new float*[NUM_DELAY_CHANNELS];
float wave_out[2048];

// crazy idea with feedback chains
zen::Compressor<float> feedbackCompressor;
typedef  float (zen::Compressor<float>::*CompressorTick)(float newValue);
CompressorTick fbCompressorTickerPtr = &zen::Compressor<float>::tick;
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
float feedbackChain0(float input)  // Use a typedef for pointer-to-member types
{
	
	float ans = CALL_MEMBER_FN(feedbackCompressor,fbCompressorTickerPtr)(input);
	return ans;
}

float feedbackChain1(float input)  // Use a typedef for pointer-to-member types
{
	
	float ans = CALL_MEMBER_FN(feedbackCompressor,fbCompressorTickerPtr)(input);
	return ans;
}

typedef float (*feedbackChainType) (float input);

feedbackChainType feedbackChains[NUM_DELAY_CHANNELS] = {
	feedbackChain0,
	feedbackChain1
};
// End of crazy idea with feedback chains

void    ZENTest_init            (float sampleRate, int blockSize)
{
	
	for(int i=0; i<NUM_DELAY_CHANNELS; i++)
	{
		delay_offsets[i] = delay_offsets_[i];
	}
	
	slidersConstruct();
	ZenInstance.prepareToPlay(sampleRate, blockSize, &getRandomFloat);
	wave.prepareToPlay(memory, 256, zen::WAVETABLE_SINE);
	lfo.prepareToPlay(memory, 256, zen::WAVETABLE_SINE);
	
	wave.setFreq(440);
	lfo.setFreq(1);
	

	
	filterTest.Init();
	stereoDelay.prepareToPlay();
	feedbackCompressor.prepareToPlay(2.5f, 0.5f);
	for (int ch = 0; ch< NUM_DELAY_CHANNELS; ch++)
	{
		
		stereoDelay.setChannelDelay(500, ch);
		stereoDelay.setChainProcessor(feedbackChains[ch], ch);
	}
	

	
	setSliderValue(SLIDER_DELAY, 100);
	sliderInterpolator[SLIDER_DELAY].prepareToPlay(100, 48000, cSliderRangesMax[SLIDER_DELAY]);
	
	setSliderValue(SLIDER_SPREAD, 0);
	sliderInterpolator[SLIDER_SPREAD].prepareToPlay(0, 48000, cSliderRangesMax[SLIDER_SPREAD]);
	
	setSliderValue(SLIDER_FEEDBACK, 0);
	sliderInterpolator[SLIDER_FEEDBACK].prepareToPlay(0, 48000, cSliderRangesMax[SLIDER_FEEDBACK]);
	
	setSliderValue(SLIDER_LFO_FREQ, 440);
	sliderInterpolator[SLIDER_LFO_FREQ].prepareToPlay(10, 48000, cSliderRangesMax[SLIDER_LFO_FREQ]);
	
	setSliderValue(SLIDER_MODULATION_DEPTH, 0);
	sliderInterpolator[SLIDER_MODULATION_DEPTH].prepareToPlay(0, 48000, cSliderRangesMax[SLIDER_MODULATION_DEPTH]);
	
	setSliderValue(SLIDER_FILTER_CUTOFF, 440);
	sliderInterpolator[SLIDER_FILTER_CUTOFF].prepareToPlay(440, 48000, cSliderRangesMax[SLIDER_FILTER_CUTOFF]);
	
	setSliderValue(SLIDER_FILTER_RESO, 10);
	sliderInterpolator[SLIDER_FILTER_RESO].prepareToPlay(10, 48000, cSliderRangesMax[SLIDER_FILTER_RESO]);
	
	setSliderValue(SLIDER_REVERB_DECAY, 0);
	sliderInterpolator[SLIDER_REVERB_DECAY].prepareToPlay(0, 48000, cSliderRangesMax[SLIDER_REVERB_DECAY]);
	
	setSliderValue(SLIDER_REVERB_SIZE, 0);
	sliderInterpolator[SLIDER_REVERB_SIZE].prepareToPlay(0, 48000, cSliderRangesMax[SLIDER_REVERB_SIZE]);

}


void update_UI()
{
	UIlabels[0] = (float)stereoDelay.getChannelDelay_ms(0);
	UIlabels[1] = sliderInterpolator[SLIDER_DELAY].a_;
	setLabelValue(UIlabels);
}

void interpolatedBlockFromSample(float endValue, float* output, size_t size, zen::Interpolator &interpolator, float gain)
{
	endValue = ceil(4096*endValue);
	endValue = endValue/4096;
	float startValue = output[size-1]/gain;
//	float startValue = (output[size-1]>0 && output[size-1]<abs(gain)) ? output[size-1]/gain : 0.0f;
	for (int i = 0; i< size; i++ )
	{
		float lerpStep = lerp(startValue, endValue, (float) i/size);
		float out =  gain* interpolator.tick(lerpStep);
		output[i] = out;
	}
	
}



size_t getZenBlockNum (size_t JUCE_BlockSize)
{
	size_t blocksNum = JUCE_BlockSize > ZEN_BLOCK_SIZE ? JUCE_BlockSize/ZEN_BLOCK_SIZE : 1;
	return JUCE_BlockSize%ZEN_BLOCK_SIZE==0 ? blocksNum : blocksNum+1;
}


void ZENTest_processBlock(const float **in, float **out, int chan_num, size_t size)
{
	update_UI();
		

	
	for(int slider_num = 0; slider_num< SLIDER_NUM_ENUM; slider_num++)
	{
		sliderInterpolator[slider_num].processBlock(getSliderValue((SlidersEnum)slider_num), sliders_blocks[slider_num], size, 1);
	}
	
//	for(int ch = 0; ch < NUM_DELAY_CHANNELS; ch++)
	{
		memcpy(delay_offsets[1],sliders_blocks[SLIDER_SPREAD], 4*size);
		
	}
	
	
	
	
	float waveFreq = 440;
	wave.setFreq(waveFreq);
	
	
	float LFOVals[size];
	
	lfo.processBlock(LFOVals, sliders_blocks[SLIDER_LFO_FREQ], size);
//	wave.processBlock(out[0], sliders_blocks[SLIDER_LFO_FREQ], size);
//	memcpy(out[1], out[0], 4*size);
	
//	const float *delayInputChPointer[2] = {out[0], out[0]};
	
	stereoDelay.processBlock((const float **)in,out, sliders_blocks[SLIDER_DELAY], (float**)delay_offsets, size, sliders_blocks[SLIDER_FEEDBACK], 0.1f);
	
//	delay[0].processBlock(out[0], out[0], sliders_blocks[SLIDER_DELAY], size, sliders_blocks[SLIDER_FEEDBACK]);
//	delay[1].processBlock(out[0], out[1], sliders_blocks[SLIDER_DELAY], sliders_blocks[SLIDER_SPREAD], size, sliders_blocks[SLIDER_FEEDBACK]);
	
}


int firstFrame = 1;
bool lastState = false, lastPlayState = false;
void    ZENTest_block           (void)
{
	
	
}



int lastNote;
void    ZENTest_noteOn          (int note, float velocity)
{
}


void    ZENTest_noteOff         (int note)
{
}



void    ZENTest_end             (void)
{
	
}

