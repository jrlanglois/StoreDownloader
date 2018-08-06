#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include "JavascriptCodeTokeniser.h"
#include "StoreDataFetcher.h"

class MainComponent : public Component,
                      public Button::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void resized() override;
    void buttonClicked (Button*) override;

private:
    CodeDocument codeDocument;
    JavascriptCodeTokeniser tokeniser;

    StoreBrand brand = StoreBrand::homeDepot;

    ComboBox storeSelector;
    TextEditor productId;
    CodeEditorComponent resultBox;
    Label productPrice;
    TextButton search;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif //MAIN_COMPONENT_H
