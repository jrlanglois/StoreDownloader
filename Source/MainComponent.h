#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include "JuceHeader.h"

enum class StoreBrand
{
    unknown = -1,
    homeDepot,
    homeHardware,
    lowes,
    rona
};

String toString (StoreBrand brand);

class MainComponent : public Component,
                      public Button::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void resized() override;
    void buttonClicked (Button*) override;

private:
    StoreBrand brand = StoreBrand::homeDepot;

    ComboBox storeSelector;
    TextEditor productId, resultBox;
    Label productPrice;
    TextButton search;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //MAIN_COMPONENT_H
