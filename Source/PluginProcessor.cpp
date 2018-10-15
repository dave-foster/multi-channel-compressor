/*
  ==============================================================================

        ECS730P DAFX 2018
        David Foster 160896851
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MultibandDynamicRangeCompressorAudioProcessor::MultibandDynamicRangeCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Set default values
    freqLow_ = 225.0;
    freqHigh_ = 725.0;
    lowThreshold_ = -24.0;
    lowRatio_ = 2.0;
    lowAttack_ = 10.0;
    lowRelease_ = 30.0;
    lowGain_ = 0.0;
    midThreshold_ = -24.0;
    midRatio_ = 2.0;
    midAttack_ = 10.0;
    midRelease_ = 30.0;
    midGain_ = 0.0;
    highThreshold_ = -24.0;
    highRatio_ = 2.0;
    highAttack_ = 10.0;
    highRelease_ = 30.0;
    highGain_ = 0.0;
    
    // Initialise FFR Filters
    lowFilterL_ = new IIRFilter;
    lowFilterR_ = new IIRFilter;
    //updateFilter(kLowFilter);
    midFilterL_ = new IIRFilter;
    midFilterR_ = new IIRFilter;
    //updateFilter(kMidFilter);
    highFilterL_ = new IIRFilter;
    highFilterR_ = new IIRFilter;
    //updateFilter(kHighFilter);
    
}

MultibandDynamicRangeCompressorAudioProcessor::~MultibandDynamicRangeCompressorAudioProcessor()
{
}

// Filter helper function

void MultibandDynamicRangeCompressorAudioProcessor::updateFilter(int filterNumber)
{
    double Q, centreFreq, bandwidth;
    double sampleRate = getSampleRate();
    
    if (sampleRate == 0.0)
        return;
    switch(filterNumber)
    {
        case kLowFilter:
            lowFilterL_->setCoefficients(IIRCoefficients::makeLowPass(sampleRate, freqLow_));
            lowFilterR_->setCoefficients(IIRCoefficients::makeLowPass(sampleRate, freqLow_));
            break;
        case kMidFilter:
            bandwidth = freqHigh_ - freqLow_;
            centreFreq = (bandwidth / 2.0) + freqLow_;
            Q = centreFreq / bandwidth;
            midFilterL_->setCoefficients(IIRCoefficients::makeBandPass(sampleRate, centreFreq, Q));
            midFilterR_->setCoefficients(IIRCoefficients::makeBandPass(sampleRate, centreFreq, Q));
            break;
        case kHighFilter:
            highFilterL_->setCoefficients(IIRCoefficients::makeHighPass(sampleRate, freqHigh_));
            highFilterR_->setCoefficients(IIRCoefficients::makeHighPass(sampleRate, freqHigh_));
            break;
        default:
            return;
    }
}

//==============================================================================
const String MultibandDynamicRangeCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultibandDynamicRangeCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultibandDynamicRangeCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultibandDynamicRangeCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultibandDynamicRangeCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultibandDynamicRangeCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultibandDynamicRangeCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultibandDynamicRangeCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String MultibandDynamicRangeCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandDynamicRangeCompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

// Getting and setting parameter values

int MultibandDynamicRangeCompressorAudioProcessor::getNumParameters()
{
    return kNumParameters;
}

float MultibandDynamicRangeCompressorAudioProcessor::getParameter(int index)
{
    // This method will be called by the host, probably on the audio thread, so it's absolutely time-critical. Don't use critical sections or anything UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case kFreqLow:          return freqLow_;
        case kFreqHigh:         return freqHigh_;
        case kLowThreshold:     return lowThreshold_;
        case kLowRatio:         return lowRatio_;
        case kLowAttack:        return lowAttack_;
        case kLowRelease:       return lowRelease_;
        case kLowGain:          return lowGain_;
        case kMidThreshold:     return midThreshold_;
        case kMidRatio:         return midRatio_;
        case kMidAttack:        return midAttack_;
        case kMidRelease:       return midRelease_;
        case kMidGain:          return midGain_;
        case kHighThreshold:    return highThreshold_;
        case kHighRatio:        return highRatio_;
        case kHighAttack:       return highAttack_;
        case kHighRelease:      return highRelease_;
        case kHighGain:         return highGain_;
        default:                return 0.0f;
    }
}

const String MultibandDynamicRangeCompressorAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
        case kFreqLow:          return "Low/Mid Cutoff Freq";
        case kFreqHigh:         return "Mid/High Cutoff Freq";
        case kLowThreshold:     return "Low Threshold";
        case kLowRatio:         return "Low Ratio";
        case kLowAttack:        return "Low Attack";
        case kLowRelease:       return "Low Release";
        case kLowGain:          return "Low Gain";
        case kMidThreshold:     return "Mid Threshold";
        case kMidRatio:         return "Mid Ratio";
        case kMidAttack:        return "Mid Attack";
        case kMidRelease:       return "Mid Release";
        case kMidGain:          return "Mid Gain";
        case kHighThreshold:    return "High Threshold";
        case kHighRatio:        return "High Ratio";
        case kHighAttack:       return "High Attack";
        case kHighRelease:      return "High Release";
        case kHighGain:         return "High Gain";
        default:                break;
    }
    return String::empty;
}

void MultibandDynamicRangeCompressorAudioProcessor::setParameter(int index, float newValue)
{
    switch (index)
    {
        case kFreqLow:
        {
            freqLow_ = newValue;
            // Update filter coefficients whenever slider adjusted
            updateFilter(kLowFilter);
            updateFilter(kMidFilter);
            break;
        }
        case kFreqHigh:
        {
            freqHigh_ = newValue;
            updateFilter(kMidFilter);
            updateFilter(kHighFilter);
            break;
        }
        case kLowThreshold:
        {
            lowThreshold_ = newValue;
            break;
        }
        case kLowRatio:
        {
            lowRatio_ = newValue;
            break;
        }
        case kLowAttack:
        {
            lowAttack_ = newValue;
            break;
        }
        case kLowRelease:
        {
            lowRelease_ = newValue;
            break;
        }
        case kLowGain:
        {
            lowGain_ = newValue;
            break;
        }
        case kMidThreshold:
        {
            midThreshold_ = newValue;
            break;
        }
        case kMidRatio:
        {
            midRatio_ = newValue;
            break;
        }
        case kMidAttack:
        {
            midAttack_ = newValue;
            break;
        }
        case kMidRelease:
        {
            midRelease_ = newValue;
            break;
        }
        case kMidGain:
        {
            midGain_ = newValue;
            break;
        }
        case kHighThreshold:
        {
            highThreshold_ = newValue;
            break;
        }
        case kHighRatio:
        {
            highRatio_ = newValue;
            break;
        }
        case kHighAttack:
        {
            highAttack_ = newValue;
            break;
        }
        case kHighRelease:
        {
            highRelease_ = newValue;
            break;
        }
        case kHighGain:
        {
            highGain_ = newValue;
            break;
        }
        default:
            break;
    }
}

//==============================================================================
void MultibandDynamicRangeCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Set the size of the helper buffers
    lowBuffer_.setSize(getTotalNumInputChannels(), samplesPerBlock);
    midBuffer_.setSize(getTotalNumInputChannels(), samplesPerBlock);
    highBuffer_.setSize(getTotalNumInputChannels(), samplesPerBlock);
    inputBuffer_.setSize(getTotalNumInputChannels(), samplesPerBlock);
    
    // Set the size of the helper arrays
    xg_.allocate(samplesPerBlock, true);
    xl_.allocate(samplesPerBlock, true);
    yg_.allocate(samplesPerBlock, true);
    yl_.allocate(samplesPerBlock, true);
    c_.allocate(samplesPerBlock, true);
    
    yLprevLow_ = 0.0;
    yLprevMid_ = 0.0;
    yLprevHigh_ = 0.0;
    
    updateFilter(kLowFilter);
    updateFilter(kMidFilter);
    updateFilter(kHighFilter);
}

void MultibandDynamicRangeCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandDynamicRangeCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultibandDynamicRangeCompressorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Copy into temp buffers, so the original values are not altered when applying the filters
    lowBuffer_.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
    midBuffer_.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
    highBuffer_.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
    
    // Filter the signal into the 3 desired bands
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* lowChannelData = lowBuffer_.getWritePointer (channel);
        auto* midChannelData = midBuffer_.getWritePointer (channel);
        auto* highChannelData = highBuffer_.getWritePointer (channel);

        switch (channel)
        {
            case 0:
                lowFilterL_->processSamples(lowChannelData, numSamples);
                midFilterL_->processSamples(midChannelData, numSamples);
                highFilterL_->processSamples(highChannelData, numSamples);
                break;
            case 1:
                lowFilterR_->processSamples(lowChannelData, numSamples);
                midFilterR_->processSamples(midChannelData, numSamples);
                highFilterR_->processSamples(highChannelData, numSamples);
                break;
            default:
                break;
        }
    }
    String message;
    message << "SCM  makeUpGain = " << lowGain_ << newLine;
    message << "SCM  lowThreshold_ = " << lowThreshold_;
    //Logger::getCurrentLogger()->writeToLog (message);
    
    // Apply compression to each band in turn
    applyCompression(kLowFilter, numSamples);
    applyCompression(kMidFilter, numSamples);
    applyCompression(kHighFilter, numSamples);
    
    // Sum the results together to form the output
    for (auto i = 0; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
        buffer.addFrom(i, 0, lowBuffer_, i, 0, numSamples);
        buffer.addFrom(i, 0, midBuffer_, i, 0, numSamples);
        buffer.addFrom(i, 0, highBuffer_, i, 0, numSamples);
    }
    
}

// Compression function

void MultibandDynamicRangeCompressorAudioProcessor::applyCompression(int filterNumber, int numSamples)
{
    // Using code from DAFX lecture slides used here
    float yLprev, threshold, ratio, tauAttack, tauRelease, makeUpGain;
    float sampleRate = getSampleRate();
    
    // Clear the input buffer and all the helper arrays
    inputBuffer_.clear(0, 0, numSamples);
    for (int i = 0; i < numSamples; ++i)
    {
        xg_[i] = 0; yg_[i] = 0;
        xl_[i] = 0; yl_[i] = 0;
        c_[i] = 0;
    }
    
    // Assign the values from the appropriate band and mix down left-right to anayse the input
    switch(filterNumber)
    {
        case kLowFilter:
            yLprev = yLprevLow_;
            threshold = lowThreshold_;
            ratio = lowRatio_;
            tauAttack = lowAttack_;
            tauRelease = lowRelease_;
            makeUpGain = lowGain_;
            inputBuffer_.addFrom(0,0,lowBuffer_,0,0,numSamples,0.5);
            inputBuffer_.addFrom(0,0,lowBuffer_,1,0,numSamples,0.5);
            break;
        case kMidFilter:
            yLprev = yLprevMid_;
            threshold = midThreshold_;
            ratio = midRatio_;
            tauAttack = midAttack_;
            tauRelease = midRelease_;
            makeUpGain = midGain_;
            inputBuffer_.addFrom(0,0,midBuffer_,0,0,numSamples,0.5);
            inputBuffer_.addFrom(0,0,midBuffer_,1,0,numSamples,0.5);
            break;
        case kHighFilter:
            yLprev = yLprevHigh_;
            threshold = highThreshold_;
            ratio = highRatio_;
            tauAttack = highAttack_;
            tauRelease = highRelease_;
            makeUpGain = highGain_;
            inputBuffer_.addFrom(0,0,highBuffer_,0,0,numSamples,0.5);
            inputBuffer_.addFrom(0,0,highBuffer_,1,0,numSamples,0.5);
            break;
        default:
            return;
    }
    
    if (threshold == 0.0)
        return;
    
    // Compression : calculates the control voltage
    float alphaAttack = exp(-1/(0.001 * sampleRate * tauAttack));
    float alphaRelease = exp(-1/(0.001 * sampleRate * tauRelease));
    
    String message;
    message << "SCM Comp makeUpGain = " << makeUpGain << newLine;
    message << "SCM Comp threshold = " << threshold << newLine;
    message << "SCM Comp ratio = " << ratio << newLine;
    message << "SCM Comp alphaAttack = " << alphaAttack << newLine;
    message << "SCM Comp alphaRelease = " << alphaRelease << newLine;
    //Logger::getCurrentLogger()->writeToLog (message);
    
    for (int i = 0 ; i < numSamples ; ++i)
    {
        // Level detection- estimate level using peak detector
        if (fabs(inputBuffer_.getWritePointer(0)[i]) <0.000001)
            xg_[i] = -120;
        else
        {
            xg_[i] = 20*log10(fabs(inputBuffer_.getWritePointer(0)[i]));
        }
        // Gain computer - static apply input/output curve
        if (xg_[i] >= threshold)
        {
            yg_[i] = threshold + (xg_[i] - threshold) / ratio;
        }
        else
            yg_[i] = xg_[i];
        xl_[i] = xg_[i] - yg_[i];
        // Ballistics - smoothing of the gain
        if (xl_[0] > yLprev)
            yl_[i] = alphaAttack * yLprev + (1 - alphaAttack) * xl_[i];
        else
            yl_[i] = alphaRelease * yLprev + (1 - alphaRelease) * xl_[i];
        // find control
        c_[i] = pow(10,(makeUpGain - yl_[i])/20);
        yLprev = yl_[i];
    }
    
    
    
    // Apply control voltage to the appropriate band, update previous sample
    switch(filterNumber)
    {
        case kLowFilter:
            for (int i = 0 ; i < numSamples ; ++i)
            {
                lowBuffer_.applyGain(0, i, 1, c_[i]);
                lowBuffer_.applyGain(1, i, 1, c_[i]);
            }
            yLprevLow_ = yLprev;
            break;
        case kMidFilter:
            for (int i = 0 ; i < numSamples ; ++i)
            {
                midBuffer_.applyGain(0, i, 1, c_[i]);
                midBuffer_.applyGain(1, i, 1, c_[i]);
            }
            yLprevMid_ = yLprev;
            break;
        case kHighFilter:
            for (int i = 0 ; i < numSamples ; ++i)
            {
                highBuffer_.applyGain(0, i, 1, c_[i]);
                highBuffer_.applyGain(1, i, 1, c_[i]);
            }
            yLprevHigh_ = yLprev;
            break;
        default:
            return;
    }
}

//==============================================================================
bool MultibandDynamicRangeCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultibandDynamicRangeCompressorAudioProcessor::createEditor()
{
    return new MultibandDynamicRangeCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MultibandDynamicRangeCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Save the settings
    // Using code from Reiss/McPherson Parametric EQ
    
    XmlElement xml("DAFXPLUGINSETTINGS");
    xml.setAttribute("freqLow_", freqLow_);
    xml.setAttribute("freqHigh_", freqHigh_);
    xml.setAttribute("lowThreshold_", lowThreshold_);
    xml.setAttribute("lowRatio_", lowRatio_);
    xml.setAttribute("lowAttack_", lowAttack_);
    xml.setAttribute("lowRelease_", lowRelease_);
    xml.setAttribute("lowGain_", lowGain_);
    xml.setAttribute("midThreshold_", midThreshold_);
    xml.setAttribute("midRatio_", midRatio_);
    xml.setAttribute("midAttack_", midAttack_);
    xml.setAttribute("midRelease_", midRelease_);
    xml.setAttribute("midGain_", midGain_);
    xml.setAttribute("highThreshold_", highThreshold_);
    xml.setAttribute("highRatio_", highRatio_);
    xml.setAttribute("highAttack_", highAttack_);
    xml.setAttribute("highRelease_", highRelease_);
    xml.setAttribute("highGain_", highGain_);
    
    copyXmlToBinary(xml, destData);
}

void MultibandDynamicRangeCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall the settings
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if(xmlState != 0)
    {
        if(xmlState->hasTagName("DAFXPLUGINSETTINGS"))
        {
            freqLow_  = (float)xmlState->getDoubleAttribute("freqLow_", freqLow_);
            freqHigh_  = (float)xmlState->getDoubleAttribute("freqHigh_", freqHigh_);
            
            lowThreshold_  = (float)xmlState->getDoubleAttribute("lowThreshold_", lowThreshold_);
            lowRatio_  = (float)xmlState->getDoubleAttribute("lowRatio_", lowRatio_);
            lowAttack_  = (float)xmlState->getDoubleAttribute("lowAttack_", lowAttack_);
            lowRelease_  = (float)xmlState->getDoubleAttribute("lowRelease_", lowRelease_);
            lowGain_  = (float)xmlState->getDoubleAttribute("lowGain_", lowGain_);
            midThreshold_  = (float)xmlState->getDoubleAttribute("midThreshold_", midThreshold_);
            midRatio_  = (float)xmlState->getDoubleAttribute("midRatio_", midRatio_);
            midAttack_  = (float)xmlState->getDoubleAttribute("midAttack_", midAttack_);
            midRelease_  = (float)xmlState->getDoubleAttribute("midRelease_", midRelease_);
            midGain_  = (float)xmlState->getDoubleAttribute("midGain_", midGain_);
            highThreshold_  = (float)xmlState->getDoubleAttribute("highThreshold_", highThreshold_);
            highRatio_  = (float)xmlState->getDoubleAttribute("highRatio_", highRatio_);
            highAttack_  = (float)xmlState->getDoubleAttribute("highAttack_", highAttack_);
            highRelease_  = (float)xmlState->getDoubleAttribute("highRelease_", highRelease_);
            highGain_  = (float)xmlState->getDoubleAttribute("highGain_", highGain_);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandDynamicRangeCompressorAudioProcessor();
}

/*
 // To report filter coefficients:
 
 IIRCoefficients lowFilterCoefs = lowFilterL_->getCoefficients();
 IIRCoefficients midFilterCoefs = midFilterL_->getCoefficients();
 IIRCoefficients highFilterCoefs = highFilterL_->getCoefficients();
 
 String message;
 //message << "SCM Preparing to play audio..." << newLine;
 //message << "SCM  samplesPerBlock = " << samplesPerBlock << newLine;
 //message << "SCM  sampleRate = " << sampleRate;
 message << "SCM Low Filter b0 = " << lowFilterCoefs.coefficients[0] << newLine;
 message << "SCM Low Filter b1 = " << lowFilterCoefs.coefficients[1] << newLine;
 message << "SCM Low Filter b2 = " << lowFilterCoefs.coefficients[2] << newLine;
 message << "SCM Low Filter a0 = " << lowFilterCoefs.coefficients[3] << newLine;
 message << "SCM Low Filter a1 = " << lowFilterCoefs.coefficients[4] << newLine;
 message << "SCM Low Filter a2 = " << lowFilterCoefs.coefficients[5] << newLine;
 message << "SCM Mid Filter b0 = " << midFilterCoefs.coefficients[0] << newLine;
 message << "SCM Mid Filter b1 = " << midFilterCoefs.coefficients[1] << newLine;
 message << "SCM Mid Filter b2 = " << midFilterCoefs.coefficients[2] << newLine;
 message << "SCM Mid Filter a0 = " << midFilterCoefs.coefficients[3] << newLine;
 message << "SCM Mid Filter a1 = " << midFilterCoefs.coefficients[4] << newLine;
 message << "SCM Mid Filter a2 = " << midFilterCoefs.coefficients[5] << newLine;
 message << "SCM High Filter b0 = " << highFilterCoefs.coefficients[0] << newLine;
 message << "SCM High Filter b1 = " << highFilterCoefs.coefficients[1] << newLine;
 message << "SCM High Filter b2 = " << highFilterCoefs.coefficients[2] << newLine;
 message << "SCM High Filter a0 = " << highFilterCoefs.coefficients[3] << newLine;
 message << "SCM High Filter a1 = " << highFilterCoefs.coefficients[4] << newLine;
 message << "SCM High Filter a2 = " << highFilterCoefs.coefficients[5] << newLine;
 Logger::getCurrentLogger()->writeToLog (message);
 */
