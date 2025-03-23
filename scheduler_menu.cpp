#include <iostream>
#include <vector>
#include "process.h"         
#include "fcfs.h"           
#include "rr.h"    
#include "sjf.h"  
#include "preempSjf.h"  
#include "preempPriority.h" 
#include "priority.h"  

using namespace std;

void displayMenu() {
    cout << "\nCPU Scheduling Algorithms:\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF) - Non-Preemptive\n";
    cout << "3. Shortest Job First (SJF) - Preemptive\n";
    cout << "4. Round Robin (RR)\n";
    cout << "5. Priority Scheduling - Non-Preemptive\n";
    cout << "6. Priority Scheduling - Preemptive\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void printGanttChart(vector<Process> &processes) {
    cout << "\n**Gantt Chart:**\n";
    
    // Upper border
    cout << " ";
    for (Process &p : processes) {
        for (int i = 0; i < p.burstTime; i++) cout << "--";
        cout << " ";
    }
    cout << "\n|";

    // Process ID in middle
    for (Process &p : processes) {
        for (int i = 0; i < p.burstTime - 1; i++) cout << " ";
        cout << "P" << p.pid;
        for (int i = 0; i < p.burstTime - 1; i++) cout << " ";
        cout << "|";
    }

    // Lower border
    cout << "\n ";
    for (Process &p : processes) {
        for (int i = 0; i < p.burstTime; i++) cout << "--";
        cout << " ";
    }

    // Time labels
    cout << "\n0";
    int currentTime = 0;
    for (Process &p : processes) {
        for (int i = 0; i < p.burstTime; i++) cout << "  ";
        currentTime += p.burstTime;
        printf("%2d", currentTime);
    }
    cout << "\n";
}

int main() {
    int choice, n, timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        processes[i].pid = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime; // Initialize for preemptive algorithms
    }

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                findAvgTime(processes.data(), n); // FCFS function takes an array
                break;

            case 2:
                sjfNonPreemptive(processes);
                break;

            case 3:
                sjfPreemptive(processes);
                break;

            case 4:
                cout << "Enter Time Quantum for Round Robin: ";
                cin >> timeQuantum;
                roundRobin(processes, timeQuantum);
                break;

            case 5:
                cout << "Enter Priority for each process:\n";
                for (int i = 0; i < n; i++) {
                    cout << "Process " << processes[i].pid << " Priority: ";
                    cin >> processes[i].priority;
                }
                findAvgTime(processes.data(), n); // Since findAvgTime expects an array

                break;

            case 6:
                cout << "Enter Priority for each process:\n";
                for (int i = 0; i < n; i++) {
                    cout << "Process " << processes[i].pid << " Priority: ";
                    cin >> processes[i].priority;
                }
                preemptivePriorityScheduling(processes);
                break;

            case 7:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }

    } while (choice != 7);

    return 0;
}
