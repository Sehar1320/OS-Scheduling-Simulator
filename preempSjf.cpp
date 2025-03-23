#include <iostream>
#include "process.h"
#include <vector>
#include <algorithm>
#include <climits>
#include "preempSjf.h"


using namespace std;

// Structure for a process


// Function to compare based on arrival time
bool compareArrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

// Function to implement Non-Preemptive SJF
void sjfNonPreemptive(vector<Process> &processes) {
    int n = processes.size();
    vector<bool> completed(n, false);
    int currentTime = 0, completedCount = 0;

    while (completedCount < n) {
        int shortestJobIndex = -1;
        int minBurstTime = INT_MAX;

        // Find the shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
        } else {
            Process &p = processes[shortestJobIndex];
            p.completionTime = currentTime + p.burstTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            completed[shortestJobIndex] = true;
            completedCount++;
            currentTime = p.completionTime;
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
