#include "StoreDataFetcher.h"

namespace
{
    String createUserAgent()
    {
        return "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'";
    }
}

StoreDataFetcher::StoreDataFetcher() {}
StoreDataFetcher::~StoreDataFetcher() {}

var StoreDataFetcher::fetch (const String& productId) const
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

//==============================================================================
StoreDataFetcherManager::StoreDataFetcherManager()
{
}

StoreDataFetcherManager::~StoreDataFetcherManager()
{
}

void StoreDataFetcherManager::registerFetcher (StoreDataFetcher* const newFetcher)
{
    jassert (newFetcher != nullptr);

    if (newFetcher != nullptr)
        knownFetchers.addIfNotAlreadyThere (newFetcher);
}

void StoreDataFetcherManager::registerBasicFetchers()
{
    knownFetchers.add (new CanadianTireStoreFetcher());
    knownFetchers.add (new HomeDepotStoreFetcher());
    knownFetchers.add (new RonaStoreFetcher());
}

void StoreDataFetcherManager::clearFetchers()
{
    knownFetchers.clear();
}

StringArray StoreDataFetcherManager::getKnownFetcherNames() const
{
    StringArray results;

    for (auto* fetcher : knownFetchers)
        results.add (fetcher->getCompanyName());

    return results;
}
