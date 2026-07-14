#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);
    setAudioChannels(2, 2);
    addAndMakeVisible(&thresholdSlider);
    thresholdSlider.setRange(0.0, 1.0);
    thresholdSlider.setValue(0.1);

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
    // We will leave this empty for now
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    int numChan = bufferToFill.buffer->getNumChannels();
    int numSamples = bufferToFill.numSamples;

    //for each channel...
    for (int channel = 0; channel < numChan; ++channel) {
        //Microphone input var
        const float* readPointer  = bufferToFill.buffer->getReadPointer (channel, bufferToFill.startSample);
        //Audio output var
        float* writePointer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
        //for each audio sample...
        for (int sample = 0; sample < numSamples; ++sample) {
            //simply play the same input audio to speakers
            if (readPointer[sample] > 0.1) {
                writePointer[sample] = 0.1;
            } else if (readPointer[sample] < -0.1) {
                writePointer[sample] = -0.1;
            } else {
                writePointer[sample] = readPointer[sample];               
            }
        }
    }
}