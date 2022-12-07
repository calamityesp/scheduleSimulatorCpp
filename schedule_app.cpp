#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include "queue.cpp"
#include "Process_T.cpp"
#include "stack.cpp"

#define MAXTIME 25

using namespace std;

typedef struct pcb
{
    int pid =0;
    int arrivalTime=0;
    int burst = 0;
    int CPUburst=0;
    int processes=0;
    int priority=0;
    int finish=0;
    int waitingTime = 0;
    int turnaroundTime=0;
    int responseTime=0;
    int NumContext=0;
    int startTime=0;
    bool isRunning = false;
    bool firstTimeRunning = true;
    bool ctxSwitch = false;

} process_t;


//function prototypes
int FCFS( vector<process_t> processList);
void SRTF(vector<process_t> processList);
int RR(vector<process_t> processList);
void printHeader();

int main(int argc, char *argv[])
{

    //note: there was no rules in using vectors to transport the data, just can't manage readyQueue

    vector<process_t> processes;   
    ifstream inFile("input10.txt");
    int algorithmSelection;
    int counter = 0;

    cout << "Reading from file..." << endl;
    while  (!inFile.eof())
    {
        process_t process;
        inFile >> process.pid >> process.arrivalTime >> process.CPUburst >> process.priority;
        process.burst = process.CPUburst;   
        processes.push_back(process);        
        counter++;        
    }
    
    //reset counter 
    counter = 0;
    inFile.close();

    cout << "Select the algorithm you wish to simulate: " << endl;
    cout << "1) FIFO" << endl;
    cout << "2) SRTF" << endl;
    cout << "3) RR" << endl;
    cout << "Selection: ";
    cin >> algorithmSelection;

    switch (algorithmSelection)
    {
    case 1:
        FCFS(processes);
        break;
    case 2:
        SRTF(processes);
        break;
    case 3:
        RR(processes);
        break;
    default:
        break;
    }

    return 0;
}

void printHeader()
{    
    cout <<"PID " << setw(13) << right << "| Arrival " << setw(12);
    cout <<"| Burst " << setw(13) << "| Priority " << setw(12);
    cout <<"| Finish " << setw(17) << "| Waiting Time" << setw(17);
    cout <<"| Turn Around " << setw(18) << "| Response Time " << setw(18) << "| N0. of Context" << endl;
}


int RR(vector<process_t> processList)
{
    Queue<process_t> arrivalQueue;
    Queue<process_t> readyQueue;
    Queue<process_t> readyQueue2;
    Queue<process_t> finishQueue;
    process_t *process;
    process_t store;
    int timeQuantum = 0;
    bool sw = false;
    int counter = 0;

    cout << "Enter your time quantium for round robin: ";
    cin >> timeQuantum;

    for (int x = 0; x < processList.size(); x++)
    {        
        arrivalQueue.enqueue(processList[x]);   
    }

    while (!arrivalQueue.isEmpty() || !readyQueue.isEmpty() || !readyQueue2.isEmpty())
    {         
        //check if the arrival queue is not empty before moving to readyQueue
        if (!arrivalQueue.isEmpty())
        {
            if(arrivalQueue.peek().arrivalTime == counter)
                readyQueue.enqueue(arrivalQueue.dequeue());            
        }
        
        //check for whcih readyQueue is empty and switch
        if (readyQueue.size() == 0)
            sw = true;
        else if (readyQueue2.size() == 0)
            sw = false;

        if (sw == false)
        {
            //process the front of the readyQueue
            process = &readyQueue.accessFront();
            process->burst -= 1;
            if(process->firstTimeRunning == true)
            {
                process->startTime = counter;
                process->firstTimeRunning = false;
                process->responseTime = counter - process->arrivalTime;
            }
        }
        else
        {
            //process the front of the readyQueue
            process = &readyQueue2.accessFront();
            process->burst -= 1;
            if(process->firstTimeRunning == true)
            {
                process->startTime = counter;
                process->firstTimeRunning = false;
                process->responseTime = counter - process->arrivalTime;
            }
        }
        

        if (process->burst == 0 && sw == false)
        {
            process->finish = counter;
            process->turnaroundTime = counter - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burst;
            process->NumContext=0;
            finishQueue.enqueue(readyQueue.dequeue());
        }
        else
        {
            process->finish = counter;
            process->turnaroundTime = counter - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burst;
            process->NumContext=0;
            finishQueue.enqueue(readyQueue2.dequeue());
        }
        

        //check timeQuantium for contextSwitching
        if (counter % timeQuantum == 0)
        {
            if(false == sw)
            {
                process = &readyQueue.accessFront();
                process->NumContext += 1;
                readyQueue2.enqueue(readyQueue.dequeue());

            }
            else
            {
                process = &readyQueue2.accessFront();
                process->NumContext += 1;
                readyQueue.enqueue(readyQueue2.dequeue());

            }
            
        }
        counter++;
    }


    return 0;
}


// An optimized version of Bubble Sort
void bubbleSortBurst(Queue<process_t> *queue, int size, int time)
{    
    process_t array[size];    

    //dequeue the queue into an array
    for (int x = 0; x < size; x++)
    {
        array[x] = queue->dequeue();        
    }

    //sort the array, then reinsert it into the queue
    int i, j;
    bool swapped;
    for (i = 0; i < size-1; i++)
    {
        swapped = false;
        for (j = 0; j < size-i-1; j++)
        {
            if (array[j].burst > array[j+1].burst)
            {
                if (array[j].isRunning == true)
                {
                    array[j].NumContext += 1;
                    
                    array[j].isRunning = false;                
                }                
                swap(array[j], array[j+1]);
                swapped = true;
            }
        }

        //break if no swaps in the inner loop 
        if (swapped == false)
            break;
    }
    
    //make sure the first element of the array is running 
    if (array[0].isRunning == false)
        array[0].isRunning = true;
         
    for (int x = 0; x < size; x++)
    {        
        queue->enqueue(array[x]);
    }    
}

void SRTF(vector<process_t> processList)
{
    process_t *process;
    process_t store;
    Queue<process_t> arrivalQueue;
    Queue<process_t> readyQueue;
    Queue<process_t> finishQueue;
    int counter = 0;
    int size;

    for (int x = 0; x < processList.size(); x++)
    {        
        arrivalQueue.enqueue(processList[x]);
    }


    while (!arrivalQueue.isEmpty() || !readyQueue.isEmpty())
    {        
        //check if the arrival queue is not empty before moving to readyQueue
        if (!arrivalQueue.isEmpty())
            if(arrivalQueue.peek().arrivalTime == counter)
                readyQueue.enqueue(arrivalQueue.dequeue());
        
        //process the front of the readyQueue
        process = &readyQueue.accessFront();
        process->burst -= 1;
        if(process->firstTimeRunning == true)
        {
            process->startTime = counter;
            process->firstTimeRunning = false;
            process->responseTime = counter - process->arrivalTime;
        }

        if (process->burst == 0)
        {
            process->finish = counter;
            process->turnaroundTime = counter - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burst;
            finishQueue.enqueue(readyQueue.dequeue());
        }

        //sort the readyQueue before next iteration
        bubbleSortBurst(&readyQueue, readyQueue.size(), counter);
        counter++;        
    }

    printHeader();
    size = finishQueue.size();
    double totalBurstTime=0;
    double totalTurnAroundTime=0;
    double totalContextSwitching=0;
    double totalWaitingTime=0;
    double totalResponseTIme=0;

    for (int x = 0; x < size; x++)
    {
        store = finishQueue.dequeue();
        cout << store.pid << setw(14) << right << store.arrivalTime << setw(13);
        cout << store.CPUburst << setw(13) << store.priority << setw(12);
        cout << store.arrivalTime << setw(18) << store.waitingTime << setw(16);
        cout << store.turnaroundTime << setw(14) << store.responseTime << setw(13) << store.NumContext << endl;

        totalBurstTime += store.CPUburst;
        totalContextSwitching += store.NumContext;
        totalWaitingTime += store.waitingTime;
        totalResponseTIme += store.responseTime;
        totalTurnAroundTime += store.turnaroundTime;
    }

    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Average CPU Burst: " << totalBurstTime / size << endl;
    cout << "Average TurnAroundTime: " << totalTurnAroundTime / size << endl;
    cout << "Average Waiting Time: " << totalWaitingTime / size << endl;
    cout << "Average Response Time: " << totalResponseTIme / size << endl;
    cout << "Total No. of Context Switching: " << totalContextSwitching << endl; 
}



int FCFS( vector<process_t> processList)
{
    Queue<process_t> arrivalQueue;
    Queue<process_t> readyQueue;
    Queue<process_t> finishQueue;
    process_t *process;
    process_t store;
    int counter = 0;
    int size = 0;
    
    for (int x = 0; x < processList.size(); x++)
    {        
        arrivalQueue.enqueue(processList[x]);      
    }

    while (!arrivalQueue.isEmpty() || !readyQueue.isEmpty())
    { 
        //check if the arrival queue is not empty before moving to readyQueue
        if (!arrivalQueue.isEmpty())
        {
            if(arrivalQueue.peek().arrivalTime == counter)
                readyQueue.enqueue(arrivalQueue.dequeue());            
        }
        
        //process the front of the readyQueue
        process = &readyQueue.accessFront();
        process->burst -= 1;
        if(process->firstTimeRunning == true)
        {
            process->startTime = counter;
            process->firstTimeRunning = false;
            process->responseTime = counter - process->arrivalTime;
        }

        if (process->burst == 0)
        {
            process->finish = counter;
            process->turnaroundTime = counter - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burst;
            process->NumContext=0;
            finishQueue.enqueue(readyQueue.dequeue());
        }
        counter++;
    }

    cout << "FinishQueueSize: " << finishQueue.size() << endl;
    printHeader();
    size = finishQueue.size();
    double totalBurstTime=0.0;
    double totalTurnAroundTime=0.0;
    int totalContextSwitching=0;
    double totalWaitingTime=0.0;
    double totalResponseTIme=0.0;

    for (int x = 0; x < size; x++)
    {
        store = finishQueue.dequeue();
        cout << store.pid << setw(14) << right << store.arrivalTime << setw(13);
        cout << store.CPUburst << setw(13) << store.priority << setw(12);
        cout << store.finish << setw(18) << store.waitingTime << setw(16);
        cout << store.turnaroundTime << setw(14) << store.responseTime << setw(13) << store.NumContext << endl;

        totalBurstTime += store.CPUburst;
        totalContextSwitching += store.NumContext;
        totalWaitingTime += store.waitingTime;
        totalResponseTIme += store.responseTime;
        totalTurnAroundTime += store.turnaroundTime;
    }

    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "Average CPU Burst: " << totalBurstTime / size << endl;
    cout << "Average TurnAroundTime: " << totalTurnAroundTime / size << endl;
    cout << "Average Waiting Time: " << totalWaitingTime / size << endl;
    cout << "Average Response Time: " << totalResponseTIme / size << endl;
    cout << "Total No. of Context Switching: " << totalContextSwitching << endl; 
    return 0;
};

