#pragma once
#include <JuceHeader.h>

//child class inherits from a juce class
class MainComponent : public juce::AudioAppComponent{

public:
    //Constructor for window
    MainComponent();

    //Deconstructor
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    void releaseResources() override;

    void paint (juce::Graphics& g) override;

    void resized() override;
    
private:
    juce::Slider thresholdSlider;
    float threshold = 0.1f; // Our shared variable, initialized to 0.1
};