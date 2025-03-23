#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <iostream>
struct Process {
    int pid, arrivalTime, burstTime, remainingTime, completionTime, turnaroundTime, waitingTime, priority;
};
void printGanttChart(std::vector<Process> &processes);  

#endif // PROCESS_H
