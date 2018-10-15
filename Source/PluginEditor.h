/*
 ==============================================================================
 
 ECS730P DAFX 2018
 David Foster 160896851
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MultibandDynamicRangeCompressorAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer
{
public:
    MultibandDynamicRangeCompressorAudioProcessorEditor (MultibandDynamicRangeCompressorAudioProcessor&);
    ~MultibandDynamicRangeCompressorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    
    // UI functions
    void sliderValueChanged (Slider*) override;
    void timerCallback() override;

private:
    
    // UI Elements
    Label freqLowValueLabel_, freqHighValueLabel_, lowThresholdValueLabel_, lowAttackValueLabel_, lowRatioValueLabel_, lowReleaseValueLabel_, lowGainValueLabel_, midThresholdValueLabel_, midAttackValueLabel_, midRatioValueLabel_, midReleaseValueLabel_, midGainValueLabel_, highThresholdValueLabel_, highAttackValueLabel_, highRatioValueLabel_, highReleaseValueLabel_, highGainValueLabel_;
    Slider lowFreqSlider_, highFreqSlider_, lowThresholdSlider_, lowAttackSlider_, lowRatioSlider_, lowReleaseSlider_, lowGainSlider_, midThresholdSlider_, midAttackSlider_, midRatioSlider_, midReleaseSlider_, midGainSlider_, highThresholdSlider_, highAttackSlider_, highRatioSlider_, highReleaseSlider_, highGainSlider_;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultibandDynamicRangeCompressorAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandDynamicRangeCompressorAudioProcessorEditor)
};
