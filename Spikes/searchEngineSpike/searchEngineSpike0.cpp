#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
#include "wikiEntry.h"
#include <stdio.h>
#include <time.h>

//:)
int main() {
    // Iterate through the terms and set intersect at the same time... Oh god why
    /*
        1) Search through first term 
        2) Store the results in a vector (flushVector). Only using this once, then it becomes a swap 
        3) Search through second term
        4) Temporarily store in another vector (currentVector)
        5) Only store the intersecting values vResults
        6) Move currentVector forwards
        7) Do set_intersection on vResults and currentVector
        8) Store that in flushVector
        9) Clear vResults
        10) Move from flushVector to vResults
        11) Loop to step 5
    */ 

    vector<wikiEntry> entries;
    readInData(entries);
    
    vector<wikiEntry> flushVector, currentVector;
    vector<wikiEntry> resultsVector;
    vector<wikiEntry>::iterator resultIterator;

    clock_t t;

while(1) {
    // Get user input
    vector<string> userInput; 
    getUserInput(userInput);
    vector<string>::iterator userInputIt = userInput.begin();
    
    // Handle only 1 word (do not do the damn loop after 1 word)
    t = clock(); // We liked this code a lot: https://www.tutorialspoint.com/how-to-measure-time-taken-by-a-function-in-c
    searchString(entries, *userInputIt, flushVector);
    ++userInputIt;

    if(userInputIt != userInput.end()) {
    
    // Handle 2 words
    // Search and put results in currentVector
    // Do set intersection, store in resultsVector
    searchString(entries, *userInputIt, currentVector);
    set_intersection(flushVector.begin(), flushVector.end(), currentVector.begin(), currentVector.end(), back_inserter(resultsVector));
    ++userInputIt;
    flushVector.clear();
    currentVector.clear();
    
    // Handle anything more than 2 words (loop)
    for(userInputIt; userInputIt != userInput.end(); ++userInputIt) {
        // Do the search
        // Store in currentVector
        searchString(entries, *userInputIt, currentVector);
        // Set intersect currentVector and resultVector
        // Store the intersected results in flushVector
        set_intersection(currentVector.begin(), currentVector.end(), resultsVector.begin(), resultsVector.end(), back_inserter(flushVector));
        // Clear resultVector
        resultsVector.clear();
        // Move everything from flushVector to resultVector
        resultsVector = flushVector;
        // Clear flushVector
        flushVector.clear();
        currentVector.clear();
    }
    // Print final results
    printEntryVector(resultsVector);
    }
    else
        printEntryVector(flushVector);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    printf("The program took %f seconds to execute\n", time_taken);
    userInput.clear();
    flushVector.clear();
    currentVector.clear();
    resultsVector.clear();

}

    return 0;
}
