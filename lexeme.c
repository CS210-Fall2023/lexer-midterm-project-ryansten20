//
// Created by Ryan Stenersen on 9/16/23.
//

#include "lexeme.h"


// Function to check if a token is a keyword
bool isKeyword(const char *token, char *keywords[], int numKeywords) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return true; //token is a keyword
        }
    }
    return false; //token is not a keyword
}

// Function to check if a token is a string
bool isString(const char *token) {
    for (int i = 0; i < strlen(token); i++) {
        if (token[i] == '"') {
            return true; //token is a string
        }
    }
    return false; //not a string
}

// Function to check if a token is a numeric literal
bool isNumLiteral(const char *token) {
    // Check if the token consists of valid characters (0-9, '.', '#')
    for (int i = 0; i < strlen(token); i++) {
        if (isdigit(token[i]) || token[i] == '.' || token[i] == '#') {
            continue; //every character is either one of the above
        } else {
            return false; //found something that doesn't meet the cases
        }
    }
    return true; // num literal
}

// Function to check if a token is a character literal
bool isCharLiteral(const char *token)
{
    // Check if the token starts and ends with single quotes and contains exactly one character in between
    return (strlen(token) == 3 && token[0] == '\'' && token[2] == '\'');
}

// Function to check if a token is an identifier
bool isIdentifier(const char *token, char *operators[], int numOperators) {
    if (!isalpha(token[0]) && token[0] != '_')
    {
        return false; // Identifiers must start with a letter or underscore
    }

    for (int i = 1; i < strlen(token); i++)
    {
        if (!isalnum(token[i]) && token[i] != '_')
        {
            return false; // Identifiers can only contain letters, numbers, and underscores
        }
    }

    return true; // It's an identifier
}

//check if char passed matches an operator or the first
bool isOperatorChar(char c, char *operators[], int numOperators)
{
    for(int i = 0; i < numOperators; i++)
    {
        if(strchr(operators[i], c) != 0)
        {
            return true; //operator character found, in 1st or 2nd postion
        }
    }
    return false; //no operator character found
}

//processToken, check for each condition with the token passed through
void processToken(char *currentToken, FILE *outputFile, char *keywords[], int numKeywords, char  *operators[], int numOperators)
{
    if (isKeyword(currentToken, keywords, numKeywords))
    {
    fprintf(outputFile, "%s (keyword)\n", currentToken);
    }
    else if (isNumLiteral(currentToken))
    {
    fprintf(outputFile, "%s (numeric literal)\n", currentToken);
    }
    else if (isString(currentToken))
    {
    fprintf(outputFile, "%s (string)\n", currentToken);
    }
    else if (isCharLiteral(currentToken))
    {
    fprintf(outputFile, "%s (character literal)\n", currentToken);
    }
    else if (isIdentifier(currentToken, operators, numOperators))
    {
    fprintf(outputFile, "%s (identifier)\n", currentToken);
    }
    else
    {
    fprintf(outputFile, "%s (unknown)\n", currentToken);
    }
}
