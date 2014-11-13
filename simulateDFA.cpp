/*
 * File: simulateDFA.cpp
 * Author: John Mauney
 * 
 * Accepts a description of a DFA and a series of input strings
 * and tests if the DFA accepts or rejects each string.
 * 
 * Created on September 25, 2014
 * Last modified November 03, 2014
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int numStates;
    vector<int> acceptingStates;
    vector<char> alphabet;
    vector<vector<int> > transitionTable;
    vector<vector<char> > input;
    
   /* 
    * Begin by parsing the dfa description file.
    */
    string dfaString;
    ifstream dfaFile;
    dfaFile.open(argv[1]);

    //get number of states from first line at index 18
    getline(dfaFile, dfaString);
    numStates = atoi(dfaString.substr(18).c_str());
    
    //get accepting states from second line, beginning at index 18
    getline(dfaFile, dfaString);
    dfaString = dfaString.substr(18);
    int pos = 0;
    string tempState;
    while((pos = dfaString.find(" ")) != string::npos) {
        tempState = dfaString.substr(0, pos);
        acceptingStates.push_back(atoi(tempState.c_str()));
        dfaString.erase(0, pos + 1); //delimeter has length 1
    }
    acceptingStates.push_back(atoi(dfaString.c_str())); //get last state from line
    
    //get alphabet from third line, beginning at index 10
    getline(dfaFile, dfaString);
    dfaString = dfaString.substr(10);
    for (int i = 0; i < dfaString.length(); i++) {
        alphabet.push_back(dfaString.at(i));
    }
    
    //finally parse the transition table, starting on line four
    while (getline(dfaFile, dfaString)) {
        vector<int> transRow;
        pos = 0;
        string tempRow;
        while((pos = dfaString.find(" ")) != string::npos) {
            tempRow = dfaString.substr(0, pos);
            transRow.push_back(atoi(tempRow.c_str()));
            dfaString.erase(0, pos + 1); //delimeter has length 1
        }
        transRow.push_back(atoi(dfaString.c_str()));
        transitionTable.push_back(transRow);
    }
    dfaFile.close(); //finished reading dfa file
    
   /*
    * Parse the input file.
    */
    string inputString;
    ifstream inputFile;
    inputFile.open(argv[2]);
    int count = 0;

    while(getline(inputFile, inputString)) {
        vector<char> inputLine;
        for(int i = 0; i < inputString.length(); i++) {
            inputLine.push_back(inputString.at(i));
        }
        input.push_back(inputLine);
    }
    inputFile.close(); //finished reading input file

   /*
    * Now process the DFA
    */
    for (int i = 0; i < input.size(); i++) {
        //alphabetPos == current input char's position in alphabet vector
        int alphabetPos;
        int currentState = 0; //0 is always start state
        bool accept = false;
        //if input is blank, stay at start state
        if (input.at(i).size() != 0) {
            for (int j = 0; j < input.at(i).size(); j++) {
                for (int k = 0; k < alphabet.size(); k++) {
                    if (alphabet.at(k) == input.at(i).at(j)) {
                        alphabetPos = k;
                        break;
                    }
                }
                currentState = transitionTable.at(currentState).at(alphabetPos);
            }
        }
        for (int j = 0; j < acceptingStates.size(); j++) {
            if (currentState == acceptingStates.at(j)) {
                cout << "accept" << endl;
                accept = true;
                break;
            }
        }
        if (!accept) {
            cout << "reject" << endl;
        }
    }
    return 0;
}
