/*
 ==============================================================================
 
 ECS730P DAFX 2018
 David Foster 160896851
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MultibandDynamicRangeCompressorAudioProcessorEditor::MultibandDynamicRangeCompressorAudioProcessorEditor (MultibandDynamicRangeCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);
    
    // Set up the UI Elements
    
    // Frequence cutoff values
    addAndMakeVisible(&lowFreqSlider_);
    lowFreqSlider_.setSliderStyle(Slider::Rotary);
    lowFreqSlider_.addListener(this);
    lowFreqSlider_.setRange(10.0, 500.0, 1.0);
    lowFreqSlider_.setTextValueSuffix(" Hz");
    lowFreqSlider_.setSkewFactorFromMidPoint(225.0);
    lowFreqSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowFreqSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kFreqLow));
    freqLowValueLabel_.setText("Low/Mid Cutoff", dontSendNotification);
    freqLowValueLabel_.setJustificationType(Justification::centred);
    freqLowValueLabel_.attachToComponent(&lowFreqSlider_, false);
    
    addAndMakeVisible(&highFreqSlider_);
    highFreqSlider_.setSliderStyle(Slider::Rotary);
    highFreqSlider_.addListener(this);
    highFreqSlider_.setRange(501.0, 2000.0, 1.0);
    highFreqSlider_.setTextValueSuffix(" Hz");
    highFreqSlider_.setSkewFactorFromMidPoint(725.0);
    highFreqSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highFreqSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kFreqHigh));
    freqHighValueLabel_.setText("Mid/High Cutoff", dontSendNotification);
    freqHighValueLabel_.setJustificationType(Justification::centred);
    freqHighValueLabel_.attachToComponent(&highFreqSlider_, false);
    
    // Low compressor
    
    addAndMakeVisible(&lowThresholdSlider_);
    lowThresholdSlider_.setSliderStyle(Slider::Rotary);
    lowThresholdSlider_.addListener(this);
    lowThresholdSlider_.setRange(-48.0, 0.0, 0.1);
    lowThresholdSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowThresholdSlider_.setTextValueSuffix(" dB");
    lowThresholdSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kLowThreshold));
    lowThresholdValueLabel_.setText("Thresh.", dontSendNotification);
    lowThresholdValueLabel_.setJustificationType(Justification::centred);
    lowThresholdValueLabel_.attachToComponent(&lowThresholdSlider_, false);
    
    addAndMakeVisible(&lowRatioSlider_);
    lowRatioSlider_.setSliderStyle(Slider::Rotary);
    lowRatioSlider_.addListener(this);
    lowRatioSlider_.setRange(1.0, 10.0, 1.0);
    lowRatioSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowRatioSlider_.setTextValueSuffix(":1");
    lowRatioSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kLowRatio));
    lowRatioValueLabel_.setText("Ratio", dontSendNotification);
    lowRatioValueLabel_.setJustificationType(Justification::centred);
    lowRatioValueLabel_.attachToComponent(&lowRatioSlider_, false);
    
    addAndMakeVisible(&lowAttackSlider_);
    lowAttackSlider_.setSliderStyle(Slider::Rotary);
    lowAttackSlider_.addListener(this);
    lowAttackSlider_.setRange(1.0, 100.0, 1.0);
    lowAttackSlider_.setSkewFactorFromMidPoint(10.0);
    lowAttackSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowAttackSlider_.setTextValueSuffix(" ms");
    lowAttackSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kLowAttack));
    lowAttackValueLabel_.setText("Attack", dontSendNotification);
    lowAttackValueLabel_.setJustificationType(Justification::centred);
    lowAttackValueLabel_.attachToComponent(&lowAttackSlider_, false);
    
    addAndMakeVisible(&lowReleaseSlider_);
    lowReleaseSlider_.setSliderStyle(Slider::Rotary);
    lowReleaseSlider_.addListener(this);
    lowReleaseSlider_.setRange(1.0, 100.0, 1.0);
    lowReleaseSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowReleaseSlider_.setSkewFactorFromMidPoint(30.0);
    lowReleaseSlider_.setTextValueSuffix(" ms");
    lowReleaseSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kLowRelease));
    lowReleaseValueLabel_.setText("Release", dontSendNotification);
    lowReleaseValueLabel_.setJustificationType(Justification::centred);
    lowReleaseValueLabel_.attachToComponent(&lowReleaseSlider_, false);
    
    addAndMakeVisible(&lowGainSlider_);
    lowGainSlider_.setSliderStyle(Slider::Rotary);
    lowGainSlider_.addListener(this);
    lowGainSlider_.setRange(-10.0, 10.0, 0.1);
    lowGainSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    lowGainSlider_.setTextValueSuffix(" dB");
    lowGainSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kLowGain));
    lowGainValueLabel_.setText("Gain", dontSendNotification);
    lowGainValueLabel_.setJustificationType(Justification::centred);
    lowGainValueLabel_.attachToComponent(&lowGainSlider_, false);
    
    // Mid compressor
    
    addAndMakeVisible(&midThresholdSlider_);
    midThresholdSlider_.setSliderStyle(Slider::Rotary);
    midThresholdSlider_.addListener(this);
    midThresholdSlider_.setRange(-48.0, 0.0, 0.1);
    midThresholdSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    midThresholdSlider_.setTextValueSuffix(" dB");
    midThresholdSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kMidThreshold));
    midThresholdValueLabel_.setText("Thresh.", dontSendNotification);
    midThresholdValueLabel_.setJustificationType(Justification::centred);
    midThresholdValueLabel_.attachToComponent(&midThresholdSlider_, false);
    
    addAndMakeVisible(&midRatioSlider_);
    midRatioSlider_.setSliderStyle(Slider::Rotary);
    midRatioSlider_.addListener(this);
    midRatioSlider_.setRange(1.0, 10.0, 1.0);
    midRatioSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    midRatioSlider_.setTextValueSuffix(":1");
    midRatioSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kMidRatio));
    midRatioValueLabel_.setText("Ratio", dontSendNotification);
    midRatioValueLabel_.setJustificationType(Justification::centred);
    midRatioValueLabel_.attachToComponent(&midRatioSlider_, false);
    
    addAndMakeVisible(&midAttackSlider_);
    midAttackSlider_.setSliderStyle(Slider::Rotary);
    midAttackSlider_.addListener(this);
    midAttackSlider_.setRange(1.0, 100.0, 1.0);
    midAttackSlider_.setSkewFactorFromMidPoint(10.0);
    midAttackSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    midAttackSlider_.setTextValueSuffix(" ms");
    midAttackSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kMidAttack));
    midAttackValueLabel_.setText("Attack", dontSendNotification);
    midAttackValueLabel_.setJustificationType(Justification::centred);
    midAttackValueLabel_.attachToComponent(&midAttackSlider_, false);
    
    addAndMakeVisible(&midReleaseSlider_);
    midReleaseSlider_.setSliderStyle(Slider::Rotary);
    midReleaseSlider_.addListener(this);
    midReleaseSlider_.setRange(1.0, 100.0, 1.0);
    midReleaseSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    midReleaseSlider_.setSkewFactorFromMidPoint(30.0);
    midReleaseSlider_.setTextValueSuffix(" ms");
    midReleaseSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kMidRelease));
    midReleaseValueLabel_.setText("Release", dontSendNotification);
    midReleaseValueLabel_.setJustificationType(Justification::centred);
    midReleaseValueLabel_.attachToComponent(&midReleaseSlider_, false);
    
    addAndMakeVisible(&midGainSlider_);
    midGainSlider_.setSliderStyle(Slider::Rotary);
    midGainSlider_.addListener(this);
    midGainSlider_.setRange(-10.0, 10.0, 0.1);
    midGainSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    midGainSlider_.setTextValueSuffix(" dB");
    midGainSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kMidGain));
    midGainValueLabel_.setText("Gain", dontSendNotification);
    midGainValueLabel_.setJustificationType(Justification::centred);
    midGainValueLabel_.attachToComponent(&midGainSlider_, false);
    
    // High compressor
    
    addAndMakeVisible(&highThresholdSlider_);
    highThresholdSlider_.setSliderStyle(Slider::Rotary);
    highThresholdSlider_.addListener(this);
    highThresholdSlider_.setRange(-48.0, 0.0, 0.1);
    highThresholdSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highThresholdSlider_.setTextValueSuffix(" dB");
    highThresholdSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kHighThreshold));
    highThresholdValueLabel_.setText("Thresh.", dontSendNotification);
    highThresholdValueLabel_.setJustificationType(Justification::centred);
    highThresholdValueLabel_.attachToComponent(&highThresholdSlider_, false);
    
    addAndMakeVisible(&highRatioSlider_);
    highRatioSlider_.setSliderStyle(Slider::Rotary);
    highRatioSlider_.addListener(this);
    highRatioSlider_.setRange(1.0, 10.0, 1.0);
    highRatioSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highRatioSlider_.setTextValueSuffix(":1");
    highRatioSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kHighRatio));
    highRatioValueLabel_.setText("Ratio", dontSendNotification);
    highRatioValueLabel_.setJustificationType(Justification::centred);
    highRatioValueLabel_.attachToComponent(&highRatioSlider_, false);
    
    addAndMakeVisible(&highAttackSlider_);
    highAttackSlider_.setSliderStyle(Slider::Rotary);
    highAttackSlider_.addListener(this);
    highAttackSlider_.setRange(1.0, 100.0, 1.0);
    highAttackSlider_.setSkewFactorFromMidPoint(10.0);
    highAttackSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highAttackSlider_.setTextValueSuffix(" ms");
    highAttackSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kHighAttack));
    highAttackValueLabel_.setText("Attack", dontSendNotification);
    highAttackValueLabel_.setJustificationType(Justification::centred);
    highAttackValueLabel_.attachToComponent(&highAttackSlider_, false);
    
    addAndMakeVisible(&highReleaseSlider_);
    highReleaseSlider_.setSliderStyle(Slider::Rotary);
    highReleaseSlider_.addListener(this);
    highReleaseSlider_.setRange(1.0, 100.0, 1.0);
    highReleaseSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highReleaseSlider_.setSkewFactorFromMidPoint(30.0);
    highReleaseSlider_.setTextValueSuffix(" ms");
    highReleaseSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kHighRelease));
    highReleaseValueLabel_.setText("Release", dontSendNotification);
    highReleaseValueLabel_.setJustificationType(Justification::centred);
    highReleaseValueLabel_.attachToComponent(&highReleaseSlider_, false);
    
    addAndMakeVisible(&highGainSlider_);
    highGainSlider_.setSliderStyle(Slider::Rotary);
    highGainSlider_.addListener(this);
    highGainSlider_.setRange(-10.0, 10.0, 0.1);
    highGainSlider_.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    highGainSlider_.setTextValueSuffix(" dB");
    highGainSlider_.setValue(processor.getParameter(MultibandDynamicRangeCompressorAudioProcessor::kHighGain));
    highGainValueLabel_.setText("Gain", dontSendNotification);
    highGainValueLabel_.setJustificationType(Justification::centred);
    highGainValueLabel_.attachToComponent(&highGainSlider_, false);

}

MultibandDynamicRangeCompressorAudioProcessorEditor::~MultibandDynamicRangeCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MultibandDynamicRangeCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (24.0f);
    g.drawFittedText("Low", 75, 10, 50, 30, Justification::centred, 1);
    g.drawFittedText("Mid", 275, 10, 50, 30, Justification::centred, 1);
    g.drawFittedText("High", 475, 10, 50, 30, Justification::centred, 1);
    g.drawLine(200, 0, 200, 50);
    g.drawLine(400, 0, 400, 50);
    g.drawLine(200, 175, 200, 600);
    g.drawLine(400, 175, 400, 600);
}

void MultibandDynamicRangeCompressorAudioProcessorEditor::resized()
{
    lowFreqSlider_.setBounds(100, 75, 200, 100);
    highFreqSlider_.setBounds(300, 75, 200, 100);
    
    lowThresholdSlider_.setBounds(0, 220, 100, 80);
    lowRatioSlider_.setBounds(100, 220, 100, 80);
    lowAttackSlider_.setBounds(0, 350, 100, 80);
    lowReleaseSlider_.setBounds(100, 350, 100, 80);
    lowGainSlider_.setBounds(50, 480, 100, 80);
    
    midThresholdSlider_.setBounds(200, 220, 100, 80);
    midRatioSlider_.setBounds(300, 220, 100, 80);
    midAttackSlider_.setBounds(200, 350, 100, 80);
    midReleaseSlider_.setBounds(300, 350, 100, 80);
    midGainSlider_.setBounds(250, 480, 100, 80);
    
    highThresholdSlider_.setBounds(400, 220, 100, 80);
    highRatioSlider_.setBounds(500, 220, 100, 80);
    highAttackSlider_.setBounds(400, 350, 100, 80);
    highReleaseSlider_.setBounds(500, 350, 100, 80);
    highGainSlider_.setBounds(450, 480, 100, 80);
}

//==============================================================================

// This timer periodically checks whether any of the filter's parameters have changed...
void MultibandDynamicRangeCompressorAudioProcessorEditor::timerCallback()
{
    // DelayAudioAudioProcessor* ourProcessor = getProcessor();
    
    lowFreqSlider_.setValue(processor.freqLow_, dontSendNotification);
    highFreqSlider_.setValue(processor.freqHigh_, dontSendNotification);
    lowThresholdSlider_.setValue(processor.lowThreshold_, dontSendNotification);
    lowRatioSlider_.setValue(processor.lowRatio_, dontSendNotification);
    lowAttackSlider_.setValue(processor.lowAttack_, dontSendNotification);
    lowReleaseSlider_.setValue(processor.lowRelease_, dontSendNotification);
    lowGainSlider_.setValue(processor.lowGain_, dontSendNotification);
    midThresholdSlider_.setValue(processor.midThreshold_, dontSendNotification);
    midRatioSlider_.setValue(processor.midRatio_, dontSendNotification);
    midAttackSlider_.setValue(processor.midAttack_, dontSendNotification);
    midReleaseSlider_.setValue(processor.midRelease_, dontSendNotification);
    midGainSlider_.setValue(processor.midGain_, dontSendNotification);
    highThresholdSlider_.setValue(processor.highThreshold_, dontSendNotification);
    highRatioSlider_.setValue(processor.highRatio_, dontSendNotification);
    highAttackSlider_.setValue(processor.highAttack_, dontSendNotification);
    highReleaseSlider_.setValue(processor.highRelease_, dontSendNotification);
    highGainSlider_.setValue(processor.highGain_, dontSendNotification);

}

// This is our Slider::Listener callback, when the user drags a slider
void MultibandDynamicRangeCompressorAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // It's vital to use setParameterNotifyingHost to change any parameters that are automatable by the host,
    // rather than just modifying them directly, otherwise the host won't know that they've changed.
    
    if (slider == &lowFreqSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kFreqLow, (float)lowFreqSlider_.getValue());
    }
    else if (slider == &highFreqSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kFreqHigh, (float)highFreqSlider_.getValue());
    }
    else if (slider == &lowThresholdSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kLowThreshold, (float)lowThresholdSlider_.getValue());
    }
    else if (slider == &lowRatioSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kLowRatio, (float)lowRatioSlider_.getValue());
    }
    else if (slider == &lowAttackSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kLowAttack, (float)lowAttackSlider_.getValue());
    }
    else if (slider == &lowReleaseSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kLowRelease, (float)lowReleaseSlider_.getValue());
    }
    else if (slider == &lowGainSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kLowGain, (float)lowGainSlider_.getValue());
    }
    else if (slider == &midThresholdSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kMidThreshold, (float)midThresholdSlider_.getValue());
    }
    else if (slider == &midRatioSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kMidRatio, (float)midRatioSlider_.getValue());
    }
    else if (slider == &midAttackSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kMidAttack, (float)midAttackSlider_.getValue());
    }
    else if (slider == &midReleaseSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kMidRelease, (float)midReleaseSlider_.getValue());
    }
    else if (slider == &midGainSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kMidGain, (float)midGainSlider_.getValue());
    }
    else if (slider == &highThresholdSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kHighThreshold, (float)highThresholdSlider_.getValue());
    }
    else if (slider == &highRatioSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kHighRatio, (float)highRatioSlider_.getValue());
    }
    else if (slider == &highAttackSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kHighAttack, (float)highAttackSlider_.getValue());
    }
    else if (slider == &highReleaseSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kHighRelease, (float)highReleaseSlider_.getValue());
    }
    else if (slider == &highGainSlider_)
    {
        processor.setParameterNotifyingHost(MultibandDynamicRangeCompressorAudioProcessor::kHighGain, (float)highGainSlider_.getValue());
    }
}
