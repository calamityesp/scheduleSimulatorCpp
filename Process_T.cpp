#include <iostream>

class Process_T
{
public:
    int pid = 0;
    int arrivalTime = 0;
    int burst = 0;
    int CPUburst = 0;
    int processes = 0;
    int priority = 0;
    int finish = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int responseTime = 0;
    int NumContext = 0;
    int startTime = 0;
    bool isRunning = false;
    bool firstTimeRunning = true;


    //constructors
    Process_T(){}

    //operator overloads
    void operator=(Process_T process)
    {
        this->pid = process.pid;
        this->arrivalTime = process.arrivalTime;
        this->burst = process.burst;
        this->CPUburst = process.CPUburst;
        this->processes = process.processes;
        this->priority = process.priority;
        this->finish = process.finish;
        this->waitingTime = process.waitingTime;
        this->turnaroundTime = process.turnaroundTime;
        this->responseTime = process.responseTime;
        this->NumContext = process.NumContext;
        this->startTime = process.startTime;
        this->isRunning = process.isRunning;
    }

    bool operator==(Process_T process)
    {
        if (
            this->pid == process.pid &&
            this->arrivalTime == process.arrivalTime &&
            this->burst == process.burst &&
            this->CPUburst == process.CPUburst &&
            this->processes == process.processes &&
            this->priority == process.priority &&
            this->finish == process.finish &&
            this->waitingTime == process.waitingTime &&
            this->turnaroundTime == process.turnaroundTime &&
            this->responseTime == process.responseTime &&
            this->NumContext == process.NumContext &&
            this->startTime == process.startTime &&
            this->isRunning == process.isRunning
            )
            return true;
        else
            return false;
    }

};