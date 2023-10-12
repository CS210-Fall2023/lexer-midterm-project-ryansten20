//
// Created by Ryan Stenersen on 9/16/23.
//

#ifndef LEXER_LEXEME_H
#define LEXER_LEXEME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void processToken(char *currentToken, FILE *outputFile, char *keywords[], int numKeywords, char  *operators[], int numOperators);

bool isKeyword(const char *token, char *keywords[], int numKeywords);

bool isString(const char *token);

bool isOperator(char *token, char *operators[], int numOperators);

bool isNumLiteral(const char *token);

bool isCharLiteral(const char *token);

bool isIdentifier(const char *token, char *operators[], int numOperators);

bool isOperatorChar(char c, char *operators[], int numOperators);

#endif //LEXER_LEXEME_H