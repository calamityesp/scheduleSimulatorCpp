#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "queue.cpp"

#define MAXTIME 25

using namespace std;

typedef struct pcb
{
    int pid;
    int arrivalTime;
    int CPUburst;
    int priority;
    int finish;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    int NumContext;
    bool isRunning = false;
} process_t;


//function prototypes
int FCFS( vector<process_t> processList);
void printHeader();


int main(int argc, char *argv[])
{
    vector<process_t> processes;   
    ifstream inFile("input10.txt");
    int algorithmSelection;
    int counter = 0;



    cout << "Reading from file..." << endl;
    while  (!inFile.eof())
    {
        process_t process;
        inFile >> process.pid >> process.arrivalTime >> process.CPUburst >> process.priority;
        processes.push_back(process);
        cout << processes[counter].arrivalTime << endl;   
        counter++;
    }
    //reset counter 
    counter = 0;
    inFile.close();

    cout << "Select the algorithm you wish to simulate: " << endl;
    cout << "1) FIFO" << endl;
    cout << "2) SRTF" << endl;
    cout << "3) RR" << endl;
    cin >> algorithmSelection;

    switch (algorithmSelection)
    {
    case 1:
        FCFS(processes);
        break;
    case 2:
        break;
    case 3:
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


int FCFS( vector<process_t> processList)
{
    Queue<process_t> readyQueue;
    int listSize = processList.size();
    process_t running;
    int totalCpuTime;
    int previousStop = 0;

    cout << "List size: " << listSize << endl;

    //sort the list by the arrival time 
    //let i = time, j = number of elements in the vector 
    for (int i = 0; i <  listSize; i++)
    {
        readyQueue.enqueue(processList[i]);
        totalCpuTime += processList[i].CPUburst;
        /*loop through the remaining list to sort the values 
        for (int j = 0 ; j < listSize; j++)
        {
            if (processList[j].arrivalTime == i)
            {
                readyQueue.enqueue(processList[j]);                
                break;
            }
        }*/
    }


    running = readyQueue.dequeue();
    printHeader();

    for (int i = 0; i < listSize; i++ )
    {
        running.waitingTime = running.arrivalTime/1;
        running.turnaroundTime = running.CPUburst;
        running.finish = running.arrivalTime + running.CPUburst;
        running.responseTime = running.arrivalTime + previousStop;
        cout << running.pid << setw(13) << right << running.arrivalTime << setw(12);
        cout <<running.CPUburst << setw(13) << running.priority << setw(12);
        cout << running.arrivalTime << setw(17) << "| Waiting Time" << setw(17);
        cout <<"| Turn Around " << setw(18) << "| Response Time " << setw(18) << "| N0. of Context" << endl;
        

        previousStop = running.finish;
    }

    return 0;
}