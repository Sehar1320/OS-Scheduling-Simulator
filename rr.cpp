#include <iostream>
#include "process.h"
#include <vector>
#include <queue>
#include "rr.h" 

using namespace std;

// Structure to store process details


// Function to implement Round Robin Scheduling
void roundRobin(vector<Process> &processes, int timeQuantum) {
    int n = processes.size();
    queue<int> readyQueue;
    int currentTime = 0, completed = 0;
    
    // Initialize remaining times
    for (auto &p : processes) {
        p.remainingTime = p.burstTime;
    }

    // Mark first process in queue
    vector<bool> inQueue(n, false);
    readyQueue.push(0);
    inQueue[0] = true;

    while (completed < n) {
        int i = readyQueue.front();
        readyQueue.pop();

        if (processes[i].remainingTime > timeQuantum) {
            currentTime += timeQuantum;
            processes[i].remainingTime -= timeQuantum;
        } else {
            currentTime += processes[i].remainingTime;
            processes[i].remainingTime = 0;
            completed++;
            processes[i].completionTime = currentTime;
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        }

        // Add new processes that arrived during execution
        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0) {
                readyQueue.push(j);
                inQueue[j] = true;
            }
        }

        // Re-add current process if it's not finished
        if (processes[i].remainingTime > 0) {
            readyQueue.push(i);
        }
    }

    // Display results
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


