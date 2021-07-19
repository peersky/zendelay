	//
	//  ZENLink.h
	//  ZenPlugin - All
	//
	//  Created by Tim on 27/04/2021.
	//  Copyright © 2021 Teknologic. All rights reserved.
	//

#ifndef ZENLink_h
#define ZENLink_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../source/zen.h"
#include "stdlib.h"

enum SlidersEnum
{
	SLIDER_DELAY=0,
	SLIDER_SPREAD,
	SLIDER_FEEDBACK,
	SLIDER_LFO_FREQ,
	SLIDER_MODULATION_DEPTH,
	SLIDER_FILTER_CUTOFF,
	SLIDER_FILTER_RESO,
	SLIDER_REVERB_DECAY,
	SLIDER_REVERB_SIZE,
	SLIDER_NUM_ENUM
};

extern std::vector<juce::String> cSliderNames;

extern std::vector<juce::String> cButtonNames;

extern std::vector<juce::String> cComboBoxNames;

extern std::vector<juce::String> cWaveformTypes;

extern std::vector<float> cSliderValues;

extern std::vector<float> cSliderModelValues;

extern std::vector<bool> cButtonStates;

extern std::vector<int> cComboBoxStates;

extern std::vector<float> cSliderSteps;
extern std::vector<float> cSliderRangesMin;
extern std::vector<float> cSliderRangesMax;
extern std::vector<float> cSliderSkew;
extern std::vector<juce::String> cSliderSuffix;
extern std::vector<float> cLabelValues;
extern std::vector<juce::String> cLabelNames;

extern Array<AudioBuffer<float>> loadedAudio;

void printSliderValues(void);
bool getButtonState(String name);
void setButtonState(String name, bool on);
int getComboBoxState(String name);
void setComboBoxState(String name, int idx);
void setSliderModelValue(String name, float val);
void setSliderValue(String name, float val);
	//float getSliderValue(String name);
float getRandomFloat(void);
	//void setLabelValue_f(float **pVal);

template<typename T>
inline void setLabelValue(T *pVal)
{
	for (int i = 0; i<4; i++)
	{
		cLabelValues[i] = (float)pVal[i];
	}
	
	
}

	//template <String &name>
inline float getSliderValue(SlidersEnum i)
{
	float value = 0.0f;
	value = cSliderValues[i];
		//	for (int i = 0; i < cSliderNames.size(); i++)
		//	{
		//		if (name == cSliderNames[i])
		//		{
		//			value = cSliderValues[i];
		//			break;
		//		}
		//	}
	
	return value;
}
	//template <String &name>
inline void setSlider(SlidersEnum slider, String name, float min, float max, float step, float skew, String suffix)
{
	cSliderNames[slider]=name;
	cSliderRangesMax[slider]=max;
	cSliderRangesMin[slider]=min;
	cSliderSteps[slider]=max*step;
	cSliderSkew[slider]=skew;
	cSliderSuffix[slider]=suffix;
}

inline void slidersConstruct()
{
	
	float step12b = 1.0f/4096.0f;
	setSlider(SLIDER_DELAY, "Delay", 0, 500, step12b, 0.5f, "ms");
	setSlider(SLIDER_SPREAD, "Spread", 0, 50, step12b, 0.5f, "ms");
	setSlider(SLIDER_FEEDBACK, "Feedback", 0, 1.3, step12b, 0.5f, "%");
	setSlider(SLIDER_LFO_FREQ,"LFO", 0,  1000, step12b, 0.5f, "Hz");
	setSlider(SLIDER_FILTER_RESO, "Q", 0, 1000, step12b, 0.5f, "");
	setSlider(SLIDER_REVERB_SIZE, "Size", 0, 1, step12b, 0.5f, "");
	setSlider(SLIDER_REVERB_DECAY, "Decay", 0, 1, step12b, 0.5f, "");
	setSlider(SLIDER_FILTER_CUTOFF, "Fc", 0, 10000, step12b, 0.5f, "Hz");
	setSlider(SLIDER_MODULATION_DEPTH, "M Depth", 0, 1, step12b, 1, "%");
	
}

inline void setSliderValue(SlidersEnum slider, float val)
{
	cSliderValues[slider] = val;
}

#endif /* ZENLink_h */
