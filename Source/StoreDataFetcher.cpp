#include "StoreDataFetcher.h"

namespace
{
    String createDefaultUserAgent()
    {
        return String ("User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'")
               + newLine;
    }
}

StoreDataFetcher::StoreDataFetcher() {}
StoreDataFetcher::~StoreDataFetcher() {}

String StoreDataFetcher::generateHeader() const
{
    return createDefaultUserAgent();
}

var StoreDataFetcher::fetch (const String& productId) const
{
    auto url = generateProductUrl (productId);

    StringPairArray responseHeaders;
    int statusCode = 0;

    std::unique_ptr<InputStream> stream (url.createInputStream (false, nullptr, nullptr, generateHeader(), 10000, &responseHeaders, &statusCode));

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
String CanadianTireStoreFetcher::generateHeader() const
{
    auto header = createDefaultUserAgent();
    header
    << "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8" << newLine
    << "Accept-Encoding: gzip, deflate" << newLine
    << "Accept-Language: en-US,en;q=0.9" << newLine
    << "Host: www.canadiantire.ca" << newLine
    << "Cache-Control: max-age=31556926" << newLine
    << "Connection: keep-alive" << newLine
    << "DNT: 1" << newLine
    << "Upgrade-Insecure-Requests: 1";
    
    return header;
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
    knownFetchers.add (new HomeHardwareStoreFetcher());
    knownFetchers.add (new LowesStoreFetcher());
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
