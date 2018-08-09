#ifndef REGION_H
#define REGION_H

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
class Currency
{
public:
    /** Constructor. */
    Currency() {}

    /** Destructor. */
    ~Currency() {}

    /** @returns */
    const String& getCode() const noexcept { return code; }

    /** @returns */
    int getNumericCode() const noexcept { return numericCode; }

    /** @returns */
    int getMinorUnit() const noexcept { return minorUnit; }

private:
    String code;
    int numericCode = 0, minorUnit = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Currency)
};

//==============================================================================
class Script
{
public:
    /** Constructor. */
    Script() {}

    /** Destructor. */
    ~Script() {}

private:
};

//==============================================================================
class Language
{
public:
    /** Constructor. */
    Language() {}

    /** Destructor. */
    ~Language() {}

private:
};

//==============================================================================
class Country
{
public:
    /** Constructor. */
    Country() {}

    /** Destructor. */
    ~Country() {}

    /** @returns */
    String getName() const { return TRANS (name); }

    /** @returns */
    String getLocalShortName() const { return TRANS (localShortName); }

    /** @returns */
    const String& getAlpha2ISOCode() const noexcept { return alpha2; }

    /** @returns */
    const String& getAlpha3ISOCode() const noexcept { return alpha3; }

    /** @returns */
    int getNumericCode() const noexcept { return numeric; }

    /** @returns */
    bool isIndependant() const noexcept { return independant; }

    /** @returns */
    const Currency& getCurrency() const noexcept { return currency; }

private:
    String name, localShortName, alpha2, alpha3;
    Currency currency;
    int numeric = 0;
    bool independant = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Country)
};

#endif //REGION_H
