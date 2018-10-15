/*
 ==============================================================================
 Dave Foster
 Swing City Music Ltd
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class MultibandDynamicRangeCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MultibandDynamicRangeCompressorAudioProcessor();
    ~MultibandDynamicRangeCompressorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    int getNumParameters() override;
    
    float getParameter(int index) override;
    void setParameter(int index, float newValue) override;
    
    const String getParameterName(int index) override;
    
    enum Parameters
    {
        kFreqLow = 0,
        kFreqHigh,
        kLowThreshold,
        kMidThreshold,
        kHighThreshold,
        kLowRatio,
        kMidRatio,
        kHighRatio,
        kLowAttack,
        kMidAttack,
        kHighAttack,
        kLowRelease,
        kMidRelease,
        kHighRelease,
        kLowGain,
        kMidGain,
        kHighGain,
        kNumParameters
    };
    
    enum Filters
    {
        kLowFilter = 0,
        kMidFilter,
        kHighFilter,
        kNumFilters
    };
    
    // Adjustable parameters:
    float freqLow_; // The freq of the low/mid boundary
    float freqHigh_; // The freq of the mid/high boundary
    float lowThreshold_;// The amplitude of the low thresh
    float lowRatio_; // The ratio of the low compressor
    float lowAttack_; // The attack speed of the low compressor
    float lowRelease_; // The release speed of the low compressor
    float lowGain_; // The make up gain of the low compressor
    float midThreshold_;// The amplitude of the mid thresh
    float midRatio_; // The ratio value of the mid compressor
    float midAttack_; // The attack speed of the mid compressor
    float midRelease_; // The release speed of the mid compressor
    float midGain_; // The make up gain of the low compressor
    float highThreshold_;// The amplitude of the mid thresh
    float highRatio_; // The ratio value of the mid compressor
    float highAttack_; // The attack speed of the mid compressor
    float highRelease_; // The release speed of the mid compressor
    float highGain_; // The make up gain of the low compressor
    
    
private:
    //==============================================================================
    
    // IIR Filters and helper functions
    
    IIRFilter *lowFilterL_, *midFilterL_, *highFilterL_, *lowFilterR_, *midFilterR_, *highFilterR_;
    
    void updateFilter(int filterNumber);
    
    // Temporary buffers for processing data before combining
    
    AudioSampleBuffer lowBuffer_, midBuffer_, highBuffer_, inputBuffer_;
    
    // Compression function
    float yLprevLow_, yLprevMid_, yLprevHigh_;
    HeapBlock <float> xg_, xl_, yg_, yl_, c_;
    void applyCompression(int filterNumber, int numSamples);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandDynamicRangeCompressorAudioProcessor)
};
