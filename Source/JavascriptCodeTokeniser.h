#ifndef JAVASCRIPT_TOKENISER_H
#define JAVASCRIPT_TOKENISER_H

#include "JuceHeader.h"

class JavascriptCodeTokeniser : public CodeTokeniser
{
public:
    JavascriptCodeTokeniser() {}
    ~JavascriptCodeTokeniser() {}

    static CodeEditorComponent::ColourScheme getDefaultEditorColourScheme();
    CodeEditorComponent::ColourScheme getDefaultColourScheme() override;

    int readNextToken (CodeDocument::Iterator& source) override;

    enum TokenType
    {
        tokenType_error = 0,
        tokenType_comment,
        tokenType_keyword,
        tokenType_operator,
        tokenType_ientifier,
        tokenType_integer,
        tokenType_float,
        tokenType_string,
        tokenType_bracket,
        tokenType_punctuation
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JavascriptCodeTokeniser)
};

#endif //JAVASCRIPT_TOKENISER_H
