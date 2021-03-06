#include "MainComponent.h"

MainComponent::MainComponent() :
    resultBox (codeDocument, &tokeniser)
{
    fetchers.registerBasicFetchers();

    storeSelector.addItemList (fetchers.getKnownFetcherNames(), 1);
    storeSelector.setSelectedItemIndex (0, dontSendNotification);

    productId.setInputRestrictions (31, "0123456789");
    productId.setMultiLine (false, false);
    productId.setTabKeyUsedAsCharacter (false);
    productId.setText (String (1000664603));
    productId.onReturnKey = [&]()
    {
        buttonClicked (&search);
    };

    resultBox.setTabSize (4, true);
    resultBox.setReadOnly (true);

    productPrice.setText ("0", dontSendNotification);

    search.setButtonText ("Search");
    search.addListener (this);

    addAndMakeVisible (storeSelector);
    addAndMakeVisible (productId);
    addAndMakeVisible (resultBox);
    addAndMakeVisible (productPrice);
    addAndMakeVisible (search);
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    search.removeListener (this);
}

//==============================================================================
void MainComponent::resized()
{
    auto b = getBounds().reduced (16);
    storeSelector.setBounds (b.removeFromTop (32));
    b.removeFromTop (16);
    productId.setBounds (b.removeFromTop (32));
    b.removeFromTop (16);
    search.setBounds (b.removeFromBottom (32));
    b.removeFromBottom (16);
    productPrice.setBounds (b.removeFromBottom (32));
    b.removeFromBottom (16);
    resultBox.setBounds (b);
}

void MainComponent::buttonClicked (Button* button)
{
    if (button == &search)
    {
        const auto productIdToSearch = productId.getText().trim();
        if (productIdToSearch.isEmpty())
        {
            jassertfalse;
            return;
        }

        auto index = storeSelector.getSelectedItemIndex();
        auto fetcher = fetchers.getKnownFetcher (index);
        if (fetcher == nullptr)
        {
            jassertfalse;
            return;
        }

        auto result = fetcher->fetch (productIdToSearch);

        if (result.isVoid() || result.isUndefined())
        {
            jassertfalse;
        }

        codeDocument.replaceAllContent (JSON::toString (result));
        productPrice.setText (fetcher->getProductDisplayDescription (result), dontSendNotification);
    }
}
