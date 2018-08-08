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

//==============================================================================
class StoreDataFetcher
{
public:
    StoreDataFetcher();
    virtual ~StoreDataFetcher();

    virtual String getCompanyName() const = 0;

    var fetch (int productId) const;

    virtual String getProductName (const var& product) const = 0;
    virtual String getProductManufacturer (const var& product) const = 0;
    virtual double getProductPrice (const var& product) const = 0;

    /** @returns a pre-formatted product price, as given by the source website.
        If this is unsupported, it will simply return the result from
        getProductPrice as a string.

        @see getProductPrice
    */
    virtual String getFormattedProductPrice (const var& product) const;

    /** @returns a default way to display a description for the given product. */
    virtual String getProductDisplayDescription (const var& product) const;

protected:
    virtual URL generateProductUrl (int productId) const = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoreDataFetcher)
};

//==============================================================================
class HomeDepotStoreFetcher : public StoreDataFetcher
{
public:
    HomeDepotStoreFetcher() {}
    ~HomeDepotStoreFetcher() {}

    String getCompanyName() const override
    {
        return "HomeDepot";
    }

    URL generateProductUrl (int productId) const override
    {
        return String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + String (productId);
    }

    String getProductName (const var& product) const override
    {
        return product.getProperty ("name", var()).toString();
    }

    String getProductManufacturer (const var& product) const override
    {
        return product.getProperty ("manufacturer", var()).toString();
    }

    double getProductPrice (const var& product) const override
    {
        auto price = product.getProperty ("price", var());
        return static_cast<double> (price.getProperty ("value", 0.0));
    }

    String getFormattedProductPrice (const var& product) const override
    {
        auto price = product.getProperty ("price", var());
        return price.getProperty ("formattedValue", "0").toString();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeDepotStoreFetcher)
};

//==============================================================================
/**

*/
class StoreDataFetcherManager
{
public:
    /** Constructor. */
    StoreDataFetcherManager();

    /** Destructor. */
    ~StoreDataFetcherManager();

    //==============================================================================
    /** Adds a fetcher to the manager's list of available file types.

        The object passed-in will be deleted by this object, so don't keep a pointer to it!
    */
    void registerFetcher (StoreDataFetcher* newFetcher);

    /** Handy method to make it easy to register known fetchers. */
    void registerBasicFetchers();

    /** Clears the list of known fetchers. */
    void clearFetchers();

    /** Returns the number of currently registered fetchers. */
    int getNumKnownFetchers() const noexcept                      { return knownFetchers.size(); }

    /** Returns one of the registered fetchers. */
    StoreDataFetcher* getKnownFetcher (int index) const           { return knownFetchers[index]; }

    /** Returns one of the registered fetchers without checking the provided index. */
    StoreDataFetcher* getKnownFetcherUnchecked (int index) const  { return knownFetchers.getUnchecked (index); }

    /** Iterator access to the list of known fetchers. */
    StoreDataFetcher** begin() const noexcept                     { return knownFetchers.begin(); }

    /** Iterator access to the list of known fetchers. */
    StoreDataFetcher** end() const noexcept                       { return knownFetchers.end(); }

    /** @returns a StringArray containing all of the known fetchers' names. */
    StringArray getKnownFetcherNames() const;

private:
    //==============================================================================
    OwnedArray<StoreDataFetcher> knownFetchers;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoreDataFetcherManager)
};

#endif //STORE_DATA_FETCHER_H
