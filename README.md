DFA-Manipulation
================

Simulate a deterministic finite automata with given inputs, and construct a text searcher DFA

DFA Simulator
================

Takes a DFA description and a list of strings as input, and prints ```accept``` or ```reject``` to stdout for each string.
DFA descriptions should be formatted like so:
```
Number of states: 5
Accepting states: 1 4
Alphabet: 01
0 1
2 3
4 0
1 2
3 4
```
This describes the following DFA: 

![DFA image](http://i.imgur.com/pY1ipug.png)

Note that 0 is always the start state.

Input descriptions should be formatted like so:
```
0000
0001
0010
0011
0100
0101
```
Running the simulator on this DFA and string file will look like this:
```
./simulateDFA <dfa file> <string file>
reject
accept
reject
reject
accept
reject
```
A more complex example DFA and strings file is provided in the repo.

Text Searcher
================

Takes a string as input and prints to stdout a DFA that will accept strings containing the input string as a substring. The DFA will be formatted as previously described. The string input file should contain a single line and belong to the alphabet a-z (all lowercase letters).

To run:
```
./textsearch <string file>
```
The simulator can be used to confirm that the resulting DFA is correct.
```
./texsearch <string file> > outdfa
./simulateDFA outdfa <string file>
accept
```

An example text search string file is provided in the repo.
