#include "election.h"

#include <stdio.h>
#include <stdlib.h>
//include any other headers you need here...
//numbers cant have more than 100 digits.
#define MAX_DIGITS_IN_POPULATION 100
#define MAX_DIGITS_IN_VOTES 100

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t thisState;
  int i = 0;  //this is a loop variable
  while (line[i] != ':' && i < (MAX_STATE_NAME_LENGTH - 1)) {
    //loop over string and append each char to the name of the state
    thisState.name[i] = line[i];
    i++;
  }
  thisState.name[i] = '\0';  //add a \0 at the end of the state's name
  if (line[i] != ':') {  //make sure you stopped at a ":". Otherwise, state's name is long
    printf("This state's name is too long");
    exit(EXIT_FAILURE);
  }
  i++;  //now, line[i] should be the first digit of the population
  char stringPopulation[MAX_DIGITS_IN_POPULATION + 1] = "";  //start
  //a string to store the population
  int j = 0;  //another loop variable to check size of population
  while (line[i] != ':' && j < MAX_DIGITS_IN_POPULATION) {
    if (line[i] >= 48 && line[i] <= 57) {  //check if char is a digit
      stringPopulation[j] = line[i];
      i++;
      j++;
    }
    else {
      printf("your population value contain characters that are not decimal digits\n");
      exit(EXIT_FAILURE);
    }
  }
  stringPopulation[j] = '\0';
  if (line[i] != ':') {  //make sure you stopped the while loop at a ":".
    //Otherwise your state's population is too long
    printf("This state's population is too long");
    exit(EXIT_FAILURE);
  }
  char foo = 'a';  //just initializing a char ** to serve as arg to strtoul
  char * foo2 = &foo;
  char ** endptr = &foo2;
  thisState.population =
      strtoull(stringPopulation, endptr, 10);  //this function gets large numbers
  i++;  //now, line[i] should be the first digit of the number of electoral votes
  char stringVotes[MAX_DIGITS_IN_VOTES + 1] =
      "";  //start a string to store the number of electoral votes
  j = 0;   //reset j
  while (line[i] != '\0' && j < MAX_DIGITS_IN_VOTES) {
    if (line[i] >= 48 && line[i] <= 57) {  //check if char is a digit
      stringVotes[j] = line[i];
      i++;
      j++;
    }
    else {
      printf("your electoral votes value contain characters that are not decimal "
             "digits\n");
      exit(EXIT_FAILURE);
    }
  }
  stringVotes[j] = '\0';
  if (line[i] != '\0') {  //make sure you stopped the while loop at a "\0".
    //Otherwise your state's votes is too long
    printf("This state's number of electoral votes is too long");
    exit(EXIT_FAILURE);
  }
  thisState.electoralVotes =
      strtoull(stringVotes, endptr, 10);  //this function gets large numbers

  return thisState;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  unsigned int totalElectoralVotes = 0;   //start counting votes
  for (size_t i = 0; i < nStates; i++) {  //loop over states
    if (voteCounts[i] > stateData[i].population / 2 &&
        voteCounts[i] <= stateData[i].population) {
      //if candidate has more than half the votes give him the electoral votes of that state
      //we have to check if the number of votes is smaller than population, otherwise, the date
      //is definitely wrong.
      totalElectoralVotes += stateData[i].electoralVotes;
    }
    if (voteCounts[i] > stateData[i].population) {
      printf(
          "Your data has problems, the number of votes is larger than the population\n");
      exit(EXIT_FAILURE);
    }
  }

  return totalElectoralVotes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double percentage = 0;  //percentage of votes of candidate A on each state
  for (size_t i = 0; i < nStates; i++) {                           //loop over states.
    percentage = voteCounts[i] / (double)stateData[i].population;  //cast the
    //population to guarantee a double division instead of int division
    if (percentage >= 0.495 && percentage <= 0.505) {
      //check if percentage is in recount range
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100);
    }
    if (voteCounts[i] > stateData[i].population) {
      printf(
          "Your data has problems, the number of votes is larger than the population\n");
      exit(EXIT_FAILURE);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double percentage = 0;     //percentage of votes of candidate A on each state
  double maxpercentage = 0;  //max percentage of votes of candidate A among all states
  size_t index = 0;          //index of the state with max percentage of votes
  for (size_t i = 0; i < nStates; i++) {                           //loop over states.
    percentage = voteCounts[i] / (double)stateData[i].population;  //cast the
    //population to guarantee a double division instead of int division
    if (percentage > maxpercentage) {
      //check if current state has a larger percentage than current maxpercentage
      //if so, update maxpercentage and index
      maxpercentage = percentage;
      index = i;
    }
    if (voteCounts[i] > stateData[i].population) {
      printf(
          "Your data has problems, the number of votes is larger than the population\n");
      exit(EXIT_FAILURE);
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n",
         stateData[index].name,
         maxpercentage * 100);
}
