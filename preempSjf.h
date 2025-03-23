#ifndef PREEMPSJF_H
#define PREEMPSJF_H

#include <iostream>
#include "process.h"
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure for a process


// Function declarations
bool compareArrival(Process p1, Process p2);
void sjfNonPreemptive(vector<Process> &processes);

#endif // SJF_H
