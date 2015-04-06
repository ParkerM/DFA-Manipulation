/*
 * File: textsearch.cpp
 * Author: John Mauney
 * 
 * Reads a string from a text file and writes
 * to stdout a description of a DFA that accepts
 * strings containing the input as a substring.
 * 
 * Created on November 06, 2014
 * Last modified April 6, 2015
 */
 
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;
 
int main(int argc, char** argv) {
    int numStates = 0;
    string input;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetLength = alphabet.length();
    int inputLength;
    int acceptingState;
    int offset = 97; //char to int offset for lowercase letters
     
   /*
    * read input from text file
    */
    ifstream textFile;
    textFile.open(argv[1]);
    getline(textFile, input);
    inputLength = input.length();
    acceptingState = inputLength;
    numStates = inputLength + 1;
 
   /*
    * Construct a DFA that accepts the input string
    */
    //create array for transition table
    int trans[numStates][alphabetLength]; 

    //Compute transition table via Knuth-Morris-Pratt construction.
    //Process state 1 on its own so we can fill the rest of it with 0's.
    trans[0][input.at(0) - offset] = 1;
    for (int i = 0; i < alphabetLength; i++) {
        if (i != input.at(0) - offset)
            trans[0][i] = 0;
    }

    //First copy the mismatch case to account for loops within the 
    //substring. Then set the match case to account for finding the
    //pure string without looping. Finally save the restart state
    //for the mismatch case.
    int s = 0; //restart state for mismatch case
    for (int i = 1; i < inputLength; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            if (j != input.at(i) - offset)
                trans[i][j] = trans[s][j]; //mismatch case
        }
        trans[i][input.at(i) - offset] = i + 1; //match case
        s = trans[s][input.at(i) - offset]; //set restart state
    }

    //the last state will only transition to itself
    for (int i = 0; i < alphabetLength; i++) {
        trans[numStates - 1][i] = numStates - 1;
    }
 
   /*
    * Reconstruct the DFA to a readable format and
    * print to stdout.
    */
    cout << "Number of states: " << numStates << endl;
    cout << "Accepting states: " << acceptingState << endl;
    cout << "Alphabet: " << alphabet << endl;
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < alphabetLength - 1; j++) {
            cout << trans[i][j] << " ";
        }
        cout << trans[i][alphabetLength - 1] << endl;
    }
    return 0;
}
