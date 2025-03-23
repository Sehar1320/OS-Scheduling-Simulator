#include <iostream>
#include <vector>
#include <algorithm>
#include "fcfs.h"
#include "process.h"

using namespace std;

// Sorting function for processes based on arrival time
bool compareArrival(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void fcfsScheduling(vector<Process>& processes) {
    int n = processes.size();
    
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);
    
    processes[0].waitingTime = 0; // First process has no waiting time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    
    for (int i = 1; i < n; i++) {
        if (processes[i - 1].completionTime < processes[i].arrivalTime) {
            // CPU idle, jump to next process
            processes[i].completionTime = processes[i].arrivalTime + processes[i].burstTime;
        } else {
            processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        }

        processes[i].waitingTime = processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
    }

    // Print results
    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";
    float totalWT = 0, totalTAT = 0;
    for (const auto& p : processes) {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
    cout << "\nAverage Waiting Time: " << (totalWT / n);
    cout << "\nAverage Turnaround Time: " << (totalTAT / n) << "\n";

    printGanttChart(processes);

}
