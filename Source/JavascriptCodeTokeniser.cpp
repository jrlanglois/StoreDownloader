#include "JavascriptCodeTokeniser.h"

namespace JsTokeniserFunctions
{
    bool isIdentifierStart (juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetter (c) || c == '_' || c == '$';
    }

    bool isIdentifierBody (juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetterOrDigit (c) || c == '_' || c == '$';
    }

    bool isReservedKeyword (String::CharPointerType token, const int tokenLength) noexcept
    {
        static const char* const keywords2Char[] =
        { "if", "do", "in", nullptr };
        
        static const char* const keywords3Char[] =
        { "for", "int", "new", "try", "var", nullptr };
        
        static const char* const keywords4Char[] =
        { "else", "null", "long", "goto", "eval", "true", "byte", "case", "char", "void", "with", "this", nullptr };
        
        static const char* const keywords5Char[] =
        { "break", "catch", "const", "final", "false", "short", "while", "yield", "throw", "float", nullptr };
        
        static const char* const keywords6Char[] =
        { "delete", "double", "native", "public", "return", "static", "switch", "throws", "typeof", nullptr };
        
        static const char* const keywords7Char[] =
        { "package", "private", "boolean", "default", "finally", nullptr };  
        
        static const char* const keywordsOther[] =
        { "volatile", "continue", "abstract", "debugger", "function", "protected", "arguments", "interface", "transient", "implements", "instanceof", "synchronized", nullptr };

        const char* const* k;

        switch (tokenLength)
        {
            case 2: k = keywords2Char; break;
            case 3: k = keywords3Char; break;
            case 4: k = keywords4Char; break;
            case 5: k = keywords5Char; break;
            case 6: k = keywords6Char; break;
            case 7: k = keywords7Char; break;

            default:
                if (tokenLength < 2 || tokenLength > 16)
                    return false;

                k = keywordsOther;
                break;
        }

        for (int i = 0; k[i] != nullptr; ++i)
            if (token.compare (CharPointer_ASCII (k[i])) == 0)
                return true;

        return false;
    }

    template<typename Iterator>
    int parseIdentifier (Iterator& source) noexcept
    {
        int tokenLength = 0;
        String::CharPointerType::CharType possibleIdentifier[100];
        String::CharPointerType possible (possibleIdentifier);

        while (isIdentifierBody (source.peekNextChar()))
        {
            const auto c = source.nextChar();

            if (tokenLength < 20)
                possible.write (c);

            ++tokenLength;
        }

        if (tokenLength > 1 && tokenLength <= 16)
        {
            possible.writeNull();

            if (isReservedKeyword (String::CharPointerType (possibleIdentifier), tokenLength))
                return JavascriptCodeTokeniser::tokenType_keyword;
        }

        return JavascriptCodeTokeniser::tokenType_ientifier;
    }
}

//==============================================================================
CodeEditorComponent::ColourScheme JavascriptCodeTokeniser::getDefaultEditorColourScheme()
{
    static const CodeEditorComponent::ColourScheme::TokenType types[] =
    {
        { "Error",          Colour (Colours::red) },
        { "Comment",        Colour (Colours::grey) },
        { "Keyword",        Colour (Colours::skyblue) },
        { "Operator",       Colour (Colours::white) },
        { "Identifier",     Colour (Colours::white) },
        { "Integer",        Colour (Colours::lightseagreen) },
        { "Float",          Colour (Colours::lightseagreen) },
        { "String",         Colour (Colours::orange) },
        { "Bracket",        Colour (Colours::white) },
        { "Punctuation",    Colour (Colours::white) }
    };

    CodeEditorComponent::ColourScheme cs;

    for (const auto& type : types)
        cs.set (type.name, type.colour);

    return cs;
}

CodeEditorComponent::ColourScheme JavascriptCodeTokeniser::getDefaultColourScheme()
{
    return getDefaultEditorColourScheme();
}

int JavascriptCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    source.skipWhitespace();

    const auto firstChar = source.peekNextChar();

    switch (firstChar)
    {
        case 0:
        break;

        case '0':   case '1':   case '2':   case '3':   case '4':
        case '5':   case '6':   case '7':   case '8':   case'9':
        case '.':
        {
            int result = CppTokeniserFunctions::parseNumber (source);

            if (result == tokenType_error)
            {
                source.skip();

                if (firstChar ==  '.')
                    return tokenType_punctuation;
            }

            return result;
        }

        case ',':   case ';':   case ':':
            source.skip();
            return tokenType_punctuation;

        case '(':   case ')':
        case '{':   case '}':
        case '[':   case ']':
            source.skip();
            return tokenType_bracket;

        case '"':
        case '\'':
            CppTokeniserFunctions::skipQuotedString (source);
            return tokenType_string;

        case '+':
            source.skip();
            CppTokeniserFunctions::skipIfNextCharMatches (source, '+', '=');
            return tokenType_operator;

        case '-':
        {
            source.skip();
            int result = CppTokeniserFunctions::parseNumber (source);

            if (result == tokenType_error)
            {
                CppTokeniserFunctions::skipIfNextCharMatches (source, '-', '=');
                return tokenType_operator;
            }

            return result;
        }

        case '*':   case '%':
        case '=':   case '!':
            source.skip();
            CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
            CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
            return tokenType_operator;

        case '/':
        {
            source.skip();

            if (source.peekNextChar() == '/')
            {
                source.skipToEndOfLine();
                return tokenType_comment;
            }

            if (source.peekNextChar() == '*')
            {
                source.skip();
                CppTokeniserFunctions::skipComment (source);
                return tokenType_comment;
            }

            if (source.peekNextChar() == '=')
                source.skip();

            return tokenType_operator;
        }

        case '>':   case '<':
            source.skip();
            CppTokeniserFunctions::skipIfNextCharMatches (source, firstChar);
            CppTokeniserFunctions::skipIfNextCharMatches (source, firstChar);
            CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
            return tokenType_operator;

        case '|':   case '&':   case '^':
            source.skip();
            CppTokeniserFunctions::skipIfNextCharMatches (source, firstChar);
            CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
            return tokenType_operator;

        case '~':   case '?':
            source.skip();
            return tokenType_operator;

        default:
            if (JsTokeniserFunctions::isIdentifierStart (firstChar))
                return JsTokeniserFunctions::parseIdentifier (source);

            source.skip();
        break;
    }

    return tokenType_error;
}
