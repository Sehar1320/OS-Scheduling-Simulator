#include <iostream>
#include "process.h"
#include <vector>
#include <climits>
#include "sjf.h" 

using namespace std;

// Structure for a process


// Function to implement Preemptive SJF (SRTF)
void sjfPreemptive(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0, shortestProcess = -1;
    int minRemainingTime;

    // Initialize remaining time for each process
    for (auto &p : processes) {
        p.remainingTime = p.burstTime;
    }

    while (completed < n) {
        shortestProcess = -1;
        minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                shortestProcess = i;
            }
        }

        if (shortestProcess == -1) {
            currentTime++;  // No process available, so increase time
        } else {
            processes[shortestProcess].remainingTime--;
            currentTime++;

            if (processes[shortestProcess].remainingTime == 0) {
                completed++;
                processes[shortestProcess].completionTime = currentTime;
                processes[shortestProcess].turnaroundTime = processes[shortestProcess].completionTime - processes[shortestProcess].arrivalTime;
                processes[shortestProcess].waitingTime = processes[shortestProcess].turnaroundTime - processes[shortestProcess].burstTime;
            }
        }
    }

    // Output results
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    float totalTAT = 0, totalWT = 0;
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t" << p.turnaroundTime << "\t" << p.waitingTime << "\n";
        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    printGanttChart(processes);

}

