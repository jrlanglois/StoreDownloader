#include "StoreDataFetcher.h"

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

namespace
{
    String createUserAgent()
    {
        return "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'";
    }
}

StoreDataFetcher::StoreDataFetcher() {}
StoreDataFetcher::~StoreDataFetcher() {}

var StoreDataFetcher::fetch (int productId) const
{
    auto url = generateProductUrl (productId);

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

String StoreDataFetcher::getFormattedProductPrice (const var& product) const
{
    return String (getProductPrice (product), 2);
}

String StoreDataFetcher::getProductDisplayDescription (const var& product) const
{
    return getProductName (product) + ", " + getProductManufacturer (product) + ", " + getFormattedProductPrice (product);
}
