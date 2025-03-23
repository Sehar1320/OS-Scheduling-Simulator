#include <iostream>
#include <vector>
#include <algorithm> // Required for sort()
#include "process.h"
#include "priority.h"

using namespace std;

// Function prototype for Gantt Chart
void printGanttChart(vector<Process> &processes);

// Corrected comparison function for sorting
bool compare(Process a, Process b) {
    if (a.priority == b.priority) {
        return a.arrivalTime < b.arrivalTime; // Sort by arrival time if priorities are the same
    }
    return a.priority < b.priority; // Otherwise, sort by priority (lower number = higher priority)
}

void findWaitingTime(Process proc[], int n) {
    proc[0].waitingTime = 0;
    int completionTime = proc[0].arrivalTime + proc[0].burstTime;

    for (int i = 1; i < n; i++) {
        if (completionTime < proc[i].arrivalTime) {
            completionTime = proc[i].arrivalTime;
        }
        proc[i].waitingTime = completionTime - proc[i].arrivalTime;
        completionTime += proc[i].burstTime;
    }
}

void findTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
    }
}

void findAvgTime(Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    float total_wt = 0, total_tat = 0;
    
    vector<Process> processes(proc, proc + n);  // Convert array to vector for printGanttChart

    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waitingTime;
        total_tat += proc[i].turnaroundTime;
        
        cout << proc[i].pid << "\t\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].priority << "\t\t"
             << proc[i].waitingTime << "\t\t" << proc[i].turnaroundTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (total_wt / n);
    cout << "\nAverage Turnaround Time: " << (total_tat / n) << endl;

    // Print Gantt Chart after calculations
    printGanttChart(processes);
}
