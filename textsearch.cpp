/*
 * File: textsearch.cpp
 * Author: John Mauney
 * 
 * Reads a string from a text file and writes
 * to stdout a description of a DFA that accepts
 * strings containing the input as a substring.
 * 
 * Created on November 06, 2014
 * Last modified November 11, 2014
 */
 
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;
 
int main(int argc, char** argv) {
    int numStates = 0;
    string input;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int inputLength;
    int alphabetLength = alphabet.length();
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
    // for (int i = 0; i < numStates; i++) {
    //     for (int j = 0; j < alphabetLength; j++) {
    //         trans[i][j] = 0;
    //     }
    // }

    //compute transition table via Knuth-Morris-Pratt construction
    //this section accounts for finding a pure substring without looping
    for (int i = 0; i < inputLength; i++) {
        trans[i][input.at(i) - offset] = i + 1;
        //fill the rest of state 1 with 0's
        if (i == 0) {
            for (int j = 0; j < alphabetLength; j++) {
                if (j != input.at(i) - offset)
                    trans[i][j] = 0;
            }
        }
    }

    //now we account for loops within the substring
    int s = 0;
    for (int i = 0; i < inputLength; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            if (j != input.at(i) - offset)
                trans[i][j] = trans[s][j];
        }
        s = trans[s][input.at(i) - offset];
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
    cout << "Alphabet: abcdefghijklmnopqrstuvwxyz" << endl;
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < alphabetLength - 1; j++) {
            cout << trans[i][j] << " ";
        }
        cout << trans[i][alphabetLength - 1] << endl;
    }
    return 0;
}
