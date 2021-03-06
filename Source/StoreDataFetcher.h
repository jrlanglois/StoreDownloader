#ifndef STORE_DATA_FETCHER_H
#define STORE_DATA_FETCHER_H

#include "Region.h"

class StoreDataFetcher
{
public:
    StoreDataFetcher();
    virtual ~StoreDataFetcher();

    virtual String getCompanyName() const = 0;

    var fetch (const String& productId) const;

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
    virtual String generateHeader() const;
    virtual URL generateProductUrl (const String& productId) const = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoreDataFetcher)
};

//==============================================================================
class CanadianTireStoreFetcher : public StoreDataFetcher
{
public:
    CanadianTireStoreFetcher() {}
    ~CanadianTireStoreFetcher() {}

    String getCompanyName() const override
    {
        return "CanadianTire";
    }

    String generateHeader() const override;

    URL generateProductUrl (const String& productId) const override
    {
        return String ("http://www.canadiantire.ca/ESB/PriceAvailability?Product=")
             + productId
             + String ("P&Store=0144&Banner=CTR&isKiosk=FALSE&Language=E");
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CanadianTireStoreFetcher)
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

    URL generateProductUrl (const String& productId) const override
    {
        return String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + productId;
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
class HomeHardwareStoreFetcher : public StoreDataFetcher
{
public:
    HomeHardwareStoreFetcher() {}
    ~HomeHardwareStoreFetcher() {}

    String getCompanyName() const override
    {
        return "HomeHardware";
    }

    URL generateProductUrl (const String& productId) const override
    {
        return String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + productId;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeHardwareStoreFetcher)
};

//==============================================================================
class LowesStoreFetcher : public StoreDataFetcher
{
public:
    LowesStoreFetcher() {}
    ~LowesStoreFetcher() {}

    String getCompanyName() const override
    {
        return "Lowes";
    }

    URL generateProductUrl (const String& productId) const override
    {
        return String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + productId;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowesStoreFetcher)
};

//==============================================================================
class RonaStoreFetcher : public StoreDataFetcher
{
public:
    RonaStoreFetcher() {}
    ~RonaStoreFetcher() {}

    String getCompanyName() const override
    {
        return "Rona";
    }

    URL generateProductUrl (const String& productId) const override
    {
        return String ("https://www.homedepot.ca/homedepotcacommercewebservices/v2/homedepotca/products/") + productId;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RonaStoreFetcher)
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
