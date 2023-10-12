//
// Created by Ryan Stenersen on 9/16/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexeme.h"

int main(int argc, char *argv[]) {

    char *keywords[] = {
            "accessor", "and", "array", "begin", "bool", "case",
            "character", "constant", "else", "elsif", "end",
            "exit", "function", "if", "in", "integer", "interface", "is", "loop", "module", "mutator",
            "natural", "null", "of", "or", "other", "out",
            "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"
    };

    char *operators[] = {
            ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":",
            "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"
    };

    /*
     * Read in file and check for errors
     */
    FILE *file = fopen(argv[1], "r"); // Open input file
    FILE *outputFile = fopen(argv[2], "w"); // Open output file

    // Check for error
    if (file == NULL || outputFile == NULL) {
        perror("Opening file");
        exit(1);
    }

    //variables to for outputting
    int currentChar;
    char currentToken[1096] = "";
    int tokenIndex = 0;
    //variables to keep track of strings
    bool inString = false;
    int stringCount = 0;
    bool inComment = false;

    /*
     * read through file
     * main loop
     */
    while ((currentChar = fgetc(file)) != EOF) {

        /*
         * First, start with special cases that have to be seperated by char
         * such as strings, comments, and operators
         */

        /* CASE 1
         * if we are in the comment and we get to a *, check if the following character is a /
        * this means we reached the end of our token
        *we then put them in our token and null terminate it
        * make in comment false
        */
        if (inComment && currentChar == '*') {
            char nextChar = fgetc(file);
            if (nextChar == '/') {
                inComment = false; //break out of comment

                currentToken[tokenIndex++] = currentChar;
                currentToken[tokenIndex++] = nextChar;
                currentToken[tokenIndex] = '\0'; // end the token when reaching that last */

                fprintf(outputFile, "%s (comment)\n", currentToken);

                //reset token
                tokenIndex = 0;
                currentToken[0] = '\0';

            } else {
                //continue to add current character to the token
                currentToken[tokenIndex++] = currentChar;
                ungetc(nextChar, file);

            }
            continue; //restart the loop
        }

        //if we are not in a comment and reach a /, this might be a comment if the next character is *
        if (currentChar == '/' && !inComment) {
            char nextChar = fgetc(file);
            if (nextChar == '*') {
                //yes, we are in a comment
                inComment = true;
                //put back the next character to add to the token
                ungetc(nextChar, file);
            } else {
                //not in a comment, put back char and continue
                ungetc(nextChar, file);
            }
        }

        /*
         * CASE 2
         * strings
         */

        //check for beginning of a string and make sure the string is not in a comment
        if (currentChar == '"' && !inComment) {
            inString = true;
            stringCount++;
            //stringCount = 2 when encountering the second " of the string or end of it
            if (stringCount == 2) {
                inString = false; //we have reached the end of our string
                stringCount = 0;
            }
        }

        /*
         * CASE 3
         * OPERATORS
         */
        if (isOperatorChar(currentChar, operators, sizeof(operators) / sizeof(operators[0])) && !inComment &&
            !inString) {

            //if there is a token being made already, end it
            if (tokenIndex != 0) {
                currentToken[tokenIndex] = '\0'; // End the token
                processToken(currentToken, outputFile, keywords, sizeof(keywords) / sizeof(keywords[0]), operators,
                             sizeof(operators) / sizeof(operators[0])); //process it
                tokenIndex = 0;
                currentToken[0] = '\0';  // Reset the token
            }

            char nextChar = fgetc(file); //get the next character

            // If the next character is the 2nd of an operator, add it to the token
            if (nextChar == '=' || nextChar == '.' || nextChar == '<' || nextChar == '>' || nextChar == '*') {
                //create out token for double operator
                currentToken[tokenIndex] = currentChar;
                currentToken[tokenIndex + 1] = nextChar;
                currentToken[tokenIndex + 2] = '\0'; // End the token

                fprintf(outputFile, "%s (operator)\n", currentToken);

                // Reset token
                tokenIndex = 0;
                currentToken[0] = '\0';
            } else {
                // the token is a single operator
                ungetc(nextChar, file); //put the next char back

                //create a new token with a single operator
                currentToken[tokenIndex] = currentChar;
                currentToken[tokenIndex + 1] = '\0'; // End the token

                fprintf(outputFile, "%s (operator)\n", currentToken);

                // Reset token
                tokenIndex = 0;
                currentToken[0] = '\0';
            }
        }

        /*
         * CASE 4
         * MAKE TOKENS
         */

        /*
         * 1. current char is not a space and not an operator character
         * 2. or we are in a string
         * 3. or we are in a comment
         */
        if (!isspace(currentChar) &&
            !isOperatorChar(currentChar, operators, sizeof(operators) / sizeof(operators[0])) || inString ||
            inComment) {
            //check for space and add to token
            if (tokenIndex < sizeof(currentToken) - 1) {
                currentToken[tokenIndex++] = currentChar;
                //keep adding to token until a condition is not met
            }
        }

            //else we have our complete token
        else {
            //if token is not empty
            if (tokenIndex != 0) {
                currentToken[tokenIndex] = '\0'; // End the token


                //pass token through to check for keyword, num literal, char literal, string or identifier
                processToken(currentToken, outputFile, keywords, sizeof(keywords) / sizeof(keywords[0]), operators,
                             sizeof(operators) / sizeof(operators[0]));

                // Reset token variables to start a new token
                tokenIndex = 0;
                currentToken[0] = '\0';

            }
        }
    }

    // Close the files
    fclose(file);
    fclose(outputFile);

    //exit
    return 0;
}

