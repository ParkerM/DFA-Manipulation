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
    //create and zero array for transition table
    int trans[inputLength + 1][alphabetLength]; 
    for (int i = 0; i <= inputLength; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            trans[i][j] = 0;
        }
    }

    //compute the transition table by finding the
    //longest prefix of the input that is also a suffix
    //of what has been read in each iteration.
    for (int i = 0; i < inputLength; i++) {
        for (int j = 0; j < alphabetLength; j++) {
            string temp;
            string temp2;
            int k = min(inputLength + 1, i + 2);
            do {
                k--;
                temp = input.substr(0, k + 1);
                temp2 = input.substr(0, i) + alphabet.at(j);
            } while (temp.find(temp2) == string::npos && k > 0);
            trans[i][j] = k;
        }
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
