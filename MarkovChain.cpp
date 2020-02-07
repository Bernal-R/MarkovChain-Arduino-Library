#include "Arduino.h"
#include "MarkovChain.h"


//-----------------------------------------------------------------------------------
//                    Principal function - Predict
//-----------------------------------------------------------------------------------
double* MarkovChain::predict(char element, char* elements, int numOfElements, char sequences[n][m], int numSequences) {
  double* probabilities = (double *)malloc(numOfElements * sizeof(double));
  int row = -1;
  for (int i = 0; i < numOfElements; i++) {
    if (elements[i] == element && row == -1) {
      row = i;
    }
  }

  if (row == -1) {
    return NULL;
  }

  int ** transitionMatrix = createTransitionMatrix(elements, numOfElements, sequences, numSequences);;
  int * rowsTotals = countRowsTotals(transitionMatrix, numOfElements);

  double ** transitionProbabilityMatrix = createTransitionProbabilityMatrix(rowsTotals, transitionMatrix, numOfElements);


  for (int i = 0; i < numOfElements; i++) {
    double prob = transitionProbabilityMatrix[row][i];
    probabilities[i] = prob;
  }
  for (int i = 0; i < numOfElements; i++)
    free(transitionMatrix[i]);
  free(transitionMatrix);

  free(rowsTotals);

  for (int i = 0; i < numOfElements; i++)
    free(transitionProbabilityMatrix[i]);
  free(transitionProbabilityMatrix);

  return probabilities;
}


// Create Transition matrix
int** MarkovChain::createTransitionMatrix(char elements [], int numOfElements, char sequences[n][m], int numSequences) {
  int** matrix;
  matrix = (int **) malloc(numOfElements * sizeof(int *));
  for (int i = 0; i < numOfElements; i++)
    matrix[i] = (int *) malloc(numOfElements * sizeof(int));

  int row = 0;
  int col = 0;
  int count = 0;
  for (int iFrom = 0; iFrom < numOfElements; iFrom++) {
    for (int iTo = 0; iTo < numOfElements; iTo++) {
      for (int iSequences = 0; iSequences < numSequences; iSequences++) {
        char from = elements[iFrom];
        char to = elements[iTo];
        char* sequence  = sequences[iSequences];
        int num = countElementsInSequence(sequence);
        count = count + counterTransitionsInSequence(from, to, sequence, num);
      }
      matrix[row][col] =  count;
      count = 0;
      col++;
    }
    row++;
    col = 0;
  }
  return matrix;
}

//Compute number of elements
int MarkovChain::countElementsInSequence(char * sequence) {
  int count = -1;
  char current = '1';
  while (current != '\0') {
    count++;
    current = sequence[count];
  }
  return count;
}


//Compute probabilities in transicion matrix 
double** MarkovChain::createTransitionProbabilityMatrix(int* rowsTotals, int** transitionMatrix, int numOfElements) {
  double** probMatrix;
  probMatrix = (double **) malloc(numOfElements * sizeof(double *));
  for (int i = 0; i < numOfElements; i++)
    probMatrix[i] = (double *) malloc(numOfElements * sizeof(double));

  for (int i = 0; i < numOfElements; i++) {
    for (int j = 0; j < numOfElements; j++) {
      probMatrix[i][j] = (double)transitionMatrix[i][j] / (double)rowsTotals[i];
    }
  }

  return probMatrix;
}


//Compute transition in sequence
int MarkovChain::counterTransitionsInSequence(char expectedFrom, char expectedTo, char sequence [], int numOfElements) {
  int count = 0;
  for (int i = 0; i < numOfElements; i++) {
    char actualFrom = sequence[i];
    char actualTo = sequence[i + 1];
    if ((actualFrom == expectedFrom) && (actualTo == expectedTo))
      count++;
  }
  return count;
}


//Get number of rows
int* MarkovChain::countRowsTotals(int** transitionMatrix, int numOfElements) {
  int* totals = (int *)malloc(numOfElements * sizeof(int));
  for (int i = 0; i < numOfElements; ++i) {
    totals[i] = 0;
  }

  for (int i = 0; i < numOfElements; ++i) {
    for (int j = 0; j < numOfElements; ++j) {
      totals[i] = totals[i] + transitionMatrix[i][j];
    }
  }
  return totals;
}
