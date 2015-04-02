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
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    int numStates = 0;
    string input;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int inputLength;
    int alphabetLength = alphabet.length();
    int acceptingState;
    int count = 0; //count # of filled spaces
    int totalTrans;

   /*
    * read input from text file
    */
    ifstream textFile;
    textFile.open(argv[1]);
    getline(textFile, input);
    inputLength = input.length();
    acceptingState = inputLength;
    numStates = inputLength;

   /*
    * Construct a DFA that accepts the input string
    */
    //count the number of unique chars in the input string
    int charsPresent = alphabetLength;
    vector<char> charAssoc;
    for (int i = 0; i < alphabetLength; i++) {
        if (input.find(alphabet.at(i)) == string::npos) {
            charsPresent--;
        } else charAssoc.push_back(alphabet.at(i));
    }
    totalTrans = numStates * charsPresent;
    cout << "trans required: " << totalTrans << endl;

    //create transition table
    int trans[numStates + 1][charsPresent]; 

    //compute transition table via Knuth-Morris-Pratt construction
    //this section accounts for finding a pure substring without looping
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < charsPresent; j++) {
            if (charAssoc.at(j) == input.at(i)) {
                trans[i][j] = i + 1;
                count++;
                cout << count << endl;
                if (i == 0) { //fill the rest of state 0 with 0s
                    for (int k = 0; k < charsPresent; k++) {
                        if (trans[i][k] != i+1) {
                            trans[i][k] = 0;
                            count++;
                        }
                    }
                }
            }
        }
    }

    //now we account for loops within the substring
    int s = 0;
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < charsPresent; j++) {
            if (charAssoc.at(j) != input.at(i)) {
                trans[i][j] = trans[s][j];
                count++;
                cout << count << endl;
                if (count == totalTrans) {
                    goto done;
                }
            }
        }

        for (int j = 0; j < charsPresent; j++) {
            if (input.at(s) == charAssoc.at(j)) {
                s = trans[s][j];
                cout << "changing s to " << s << endl;
                break;
            }
        }
        cout << "out of loop" << endl;
    }
    // for (int i = s; i < numStates; i++) {
    //     for (int j = 0; j < charsPresent; j++) {
    //         if (charAssoc.at(j) == input.at(i)) {
    //             s = trans[s][j];
    //             cout << "changing s to " << s << endl;
    //             exitLoop = true;
    //             break;
    //         }
    //     }
    //     cout << "still in loop " << i << endl;
    // }
    done:


    //now loop final state to itself in every case
    for (int i = 0; i < charsPresent; i++) {
        trans[numStates][i] = acceptingState;
    }

   /*
    * Reconstruct the DFA to a readable format and
    * print to stdout.
    */
    cout << "Number of states: " << numStates + 1 << endl;
    cout << "Accepting states: " << acceptingState << endl;
    cout << "Alphabet: abcdefghijklmnopqrstuvwxyz" << endl;
    for (int i = 0; i <= numStates; i++) {
        for (int j = 0; j < charsPresent - 1; j++) {
            cout << trans[i][j] << " ";
        }
        cout << trans[i][charsPresent - 1] << endl;
    }
    return 0;
}
