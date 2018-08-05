#ifndef STORE_DATA_FETCHER_H
#define STORE_DATA_FETCHER_H

#include "JuceHeader.h"

#if JUCE_CLANG
    #pragma clang diagnostic warning "-Wall"
    #pragma clang diagnostic warning "-Wconstant-conversion"
    #pragma clang diagnostic warning "-Wconversion"
    #pragma clang diagnostic warning "-Wextra-semi"
    #pragma clang diagnostic warning "-Wint-conversion"
    #pragma clang diagnostic warning "-Wnewline-eof"
    #pragma clang diagnostic warning "-Wnon-virtual-dtor"
    #pragma clang diagnostic warning "-Woverloaded-virtual"
    #pragma clang diagnostic warning "-Wreorder"
    #pragma clang diagnostic warning "-Wshadow"
    #pragma clang diagnostic warning "-Wshorten-64-to-32"
    #pragma clang diagnostic warning "-Wsign-compare"
    #pragma clang diagnostic warning "-Wsign-conversion"
    #pragma clang diagnostic warning "-Wstrict-aliasing"
    #pragma clang diagnostic warning "-Wuninitialized"
    #pragma clang diagnostic warning "-Wunused-parameter"
#elif JUCE_MSVC
    #pragma warning (default: 4242)
    #pragma warning (default: 4254)
    #pragma warning (default: 4264)
    #pragma warning (default: 4265)
    #pragma warning (default: 4287)
    #pragma warning (default: 4296)
    #pragma warning (default: 4302)
    #pragma warning (default: 4342)
    #pragma warning (default: 4350)
    #pragma warning (default: 4355)
#endif

enum class StoreBrand
{
    unknown = -1,
    homeDepot,
    homeHardware,
    lowes,
    rona
};

String toString (StoreBrand brand);

class StoreDataFetcher
{
public:
    StoreDataFetcher();
    virtual ~StoreDataFetcher();

    virtual String getCompanyName() const = 0;

    virtual URL generateProductUrl (int productId) const = 0;
    
    virtual String getProductName (const var&) const = 0;
    virtual String getProductManufacturer (const var&) const = 0;
    virtual double getProductPrice (const var&) const = 0;
    
    /** @returns a pre-formatted product price, as given by the source website.
        If this is unsupported, it will simply call getProductPrice.
        
        @see getProductPrice
    */
    virtual double getFormattedProductPrice (const var&) const;
    
    /** @returns a default way to display a description for the given product. */
    virtual String getProductDisplayDescription (const var& product);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoreDataFetcher)
};

#endif //STORE_DATA_FETCHER_H