#ifndef PRIORITY_H
#define PRIORITY_H

#include <iostream>
#include "process.h"
#include <algorithm> // Required for sort()
using namespace std;

// Structure for a process


// Function declarations
bool compare(Process a, Process b);
void findWaitingTime(Process proc[], int n);
void findTurnaroundTime(Process proc[], int n);
void findAvgTime(Process proc[], int n);

#endif // PRIORITY_NONPREEMPTIVE_H
