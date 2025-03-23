#include <iostream>
#include "process.h"
#include <vector>
#include <queue>
#include <algorithm>
#include "preempPriority.h"
using namespace std;



// Custom comparator for priority queue (Min-Heap based on Priority)
struct Compare {
    bool operator()(const Process* a, const Process* b) {
        if (a->priority == b->priority)
            return a->arrivalTime > b->arrivalTime; // If same priority, pick earlier arrival
        return a->priority > b->priority; // Lower number = Higher priority
    }
};

void preemptivePriorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });
    
    priority_queue<Process*, vector<Process*>, Compare> pq;
    int time = 0, completed = 0;
    vector<bool> isInQueue(n, false);

    while (completed < n) {
        // Push all available processes at current time into priority queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && !isInQueue[i]) {
                pq.push(&processes[i]);
                isInQueue[i] = true;
            }
        }

        if (!pq.empty()) {
            Process* current = pq.top();
            pq.pop();
            current->remainingTime--;
            time++;

            // If process is completed
            if (current->remainingTime == 0) {
                current->completionTime = time;
                current->turnaroundTime = current->completionTime - current->arrivalTime;
                current->waitingTime = current->turnaroundTime - current->burstTime;
                completed++;
            } else {
                pq.push(current); // Put the process back in queue if not finished
            }
        } else {
            time++; // If no process is available, increment time
        }
    }
    printGanttChart(processes);

}

void printProcesses(const vector<Process>& processes) {
    cout << "\nPID\tAT\tBT\tPriority\tWT\tTAT\n";
    float totalWT = 0, totalTAT = 0;
    for (const auto& p : processes) {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.priority << "\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
    cout << "\nAverage Waiting Time: " << (totalWT / processes.size());
    cout << "\nAverage Turnaround Time: " << (totalTAT / processes.size()) << "\n";
}


