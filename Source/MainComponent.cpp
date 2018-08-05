#include "MainComponent.h"

namespace
{
    String createUserAgent()
    {
        return "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'";
    }
}

String toString (StoreBrand brand)
{
    switch (brand)
    {
        case StoreBrand::unknown:       return "(Unknown)";
        case StoreBrand::homeDepot:     return "Home Depot";
        case StoreBrand::homeHardware:  return "Home Hardware";
        case StoreBrand::lowes:         return "Lowes";
        case StoreBrand::rona:          return "Rona";

        default:
            jassertfalse;
        break;
    };

    return {};
}

namespace HomeDepot
{
    var getProductInfo (int productId)
    {
        URL url (String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + String (productId));

        String headers;
        headers << createUserAgent() << newLine;

        StringPairArray responseHeaders;
        int statusCode = 0;

        std::unique_ptr<InputStream> stream (url.createInputStream (false, nullptr, nullptr, headers, 10000, &responseHeaders, &statusCode));
        if (stream != nullptr)
        {
            return JSON::parse (stream->readEntireStreamAsString());
        }

        DBG (statusCode);
        jassertfalse;
        return {};
    }

    String getProductName (const var& product)
    {
        return product.getProperty ("name", var()).toString();
    }

    String getProductManufacturer (const var& product)
    {
        return product.getProperty ("manufacturer", var()).toString();
    }

    String getProductPrice (const var& product)
    {
        auto price = product.getProperty ("price", var());
        return price.getProperty ("formattedValue", "0").toString();
    }

    String getProductDisplayDescription (const var& product)
    {
        return getProductName (product) + ", " + getProductManufacturer (product) + ", " + getProductPrice (product);
    }
}

MainComponent::MainComponent()
{
    StringArray items =
    {
        toString (StoreBrand::homeDepot),
        toString (StoreBrand::homeHardware),
        toString (StoreBrand::lowes),
        toString (StoreBrand::rona)
    };
    storeSelector.addItemList (items, 1);
    storeSelector.setSelectedItemIndex (static_cast<int> (brand), dontSendNotification);

    productId.setInputRestrictions (31, "0123456789");
    productId.setMultiLine (false, false);
    productId.setText (String (1000664603));

    resultBox.setMultiLine (true, false);

    productPrice.setText("0", dontSendNotification);

    search.setButtonText ("Search");
    search.addListener (this);

    addAndMakeVisible (storeSelector);
    addAndMakeVisible (productId);
    addAndMakeVisible (resultBox);
    addAndMakeVisible (productPrice);
    addAndMakeVisible (search);
    setSize (600, 400);
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
        const auto productIdToSearch = productId.getText().trim().getIntValue();
        if (productIdToSearch <= 0)
        {
            jassertfalse;
            return;
        }

        auto result = HomeDepot::getProductInfo (productIdToSearch);
        resultBox.setText (JSON::toString (result));
        productPrice.setText (HomeDepot::getProductDisplayDescription (result), dontSendNotification);
    }
}
