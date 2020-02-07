#ifndef MarkovChain_h
#define MarkovChain_h

#include "Arduino.h"
#define n 3
#define m 5


class MarkovChain
{
  public:
    double* predict(char element, char* elements, int numOfElements, char sequences[n][m], int numSequences);
  private:
    int countElementsInSequence(char * sequence);
    int** createTransitionMatrix(char elements [], int numOfElements, char sequences[n][m], int numSequences);
    int counterTransitionsInSequence(char expectedFrom, char expectedTo, char sequence [], int numOfElements);
    double** MarkovChain::createTransitionProbabilityMatrix(int* rowsTotals, int** transitionMatrix, int numOfElements);
    int* MarkovChain::countRowsTotals(int** transitionMatrix, int numOfElements);
};

#endif
