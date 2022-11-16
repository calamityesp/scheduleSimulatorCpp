#include <iostream>
#include <fstream>
#include <string>
#include "queue.cpp"

using namespace std;

typedef struct pcb
{
    int pid;
    int priority;
    int arrivalTime;
    int CPUburst;
    int IOburst;
    int CPUremainingTime;
    int IOremainingTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
} process_t;


//function prototypes


int main(int argc, char *argv[])
{
    process_t processList[100];     
    ifstream inFile("input10.txt");
    int algorithmSelection;
    int counter = 0;



    cout << "Reading from file..." << endl;
    while  (!inFile.eof())
    {
        process_t process;
        inFile >> process.pid >> process.arrivalTime >> process.CPUburst >> process.priority;
        processList[counter] = process;
        cout << "Print PID: " << processList[counter].pid << endl;
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
        /* code */
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
