#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);
    setAudioChannels(2, 2);
    addAndMakeVisible (&thresholdLabel);
    addAndMakeVisible (&thresholdSlider);

    thresholdLabel.setText ("Distortion Threshold", juce::dontSendNotification);
    thresholdLabel.setJustificationType (juce::Justification::centred);    thresholdSlider.setRange(0.01, 1.0);
    thresholdSlider.setValue(0.1);
    thresholdSlider.onValueChange = [this] { threshold = thresholdSlider.getValue(); };
    // Updates threshold everytime it changes
    thresholdSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    // Change the active track/thumb color of the knob to a cool purple
    thresholdSlider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::darkviolet);
    thresholdSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
}

MainComponent::~MainComponent()
{
    shutdownAudio();    
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // We will leave this empty for now
}

void MainComponent::releaseResources()
{
    // We will leave this empty for now
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black); // Fills the background with black
}

void MainComponent::resized()
{
// Position the label at the top center
    thresholdLabel.setBounds (300, 180, 200, 30);

    // Position the knob directly below the label
    thresholdSlider.setBounds (300, 220, 200, 200);}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    int numChan = bufferToFill.buffer->getNumChannels();
    int numSamples = bufferToFill.numSamples;

    //Makeup gain to increase amplitude
    float makeupGain = 1.0f / threshold;

    //for each channel...
    for (int channel = 0; channel < numChan; ++channel) {
        //Microphone input var
        const float* readPointer  = bufferToFill.buffer->getReadPointer (channel, bufferToFill.startSample);
        //Audio output var
        float* writePointer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
        //for each audio sample...
        for (int sample = 0; sample < numSamples; ++sample) {
            //simply play the same input audio to speakers
            float inputSample = readPointer[sample];
            
            if (inputSample > threshold) {
                inputSample = threshold;
            } else if (inputSample < -threshold) {
                inputSample = -threshold;
            }

            writePointer[sample] = inputSample * makeupGain;
            
        }
    }
}