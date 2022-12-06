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
    int processes;
    int priority;
    int finish;
    int waitingTime = 0;
    int turnaroundTime;
    int responseTime;
    int NumContext;
    int startTime;
    bool isRunning = false;
} process_t;


//function prototypes
int FCFS( vector<process_t> processList);
int SRTF(vector<process_t> processList);
int RR(vector<process_t> processList);
void printHeader();
void bubbleSort(int array[], int size);

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
        SRTF(processes);
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


int RR(vector<process_t> processList)
{
    Queue<process_t> readyQueue;
    int totalCpuTime = 0;
    int listSize = processList.size();
    int quantium = 0;


     //find total cpu time 
     for (int i = 0; i <  listSize; i++)
    {
        readyQueue.enqueue(processList[i]);
        totalCpuTime += processList[i].CPUburst;
    }

    cout << "Enter Quantium Size: "; 
    cin >> quantium;

    return 0;
}


int SRTF(vector<process_t> processList)
{
    int listSize = processList.size();
    Queue<process_t> arrivalQueue;
    Queue<process_t> finishQueue;
    vector<process_t> readyQueue;
    process_t *process;
    int size = 0;
    int counter = 0;

    //sort the list by the arrival time 
    //let i = time, j = number of elements in the vector 
    for (int i = 0; i <  listSize; i++)
    {
        arrivalQueue.enqueue(processList[i]);        
    }

    //move the first item in queue to readyQueue
    readyQueue.push_back(arrivalQueue.dequeue());
    
    //queue management  
    while (!arrivalQueue.isEmpty() && !readyQueue.empty())
    {
        counter++;

        //check the readyness of the next process
        if(counter == arrivalQueue.peek().arrivalTime)
        {
            process = &arrivalQueue.dequeue();            
            readyQueue.push_back(*process);
        }

        // get the size of the array and sort it by burst time while counting context switching
        size = (int)readyQueue.size();
        process = &readyQueue[0];
        bubbleSortBurst(readyQueue, size);
        if (readyQueue[0].arrivalTime != process->arrivalTime)
        {
            //record context switching
            process->NumContext += 1;
        }

        //using is running to check if this is the first execution
        if (!readyQueue[0].isRunning)
        {
            readyQueue[0].responseTime = counter;
            readyQueue[0].isRunning = true;
        }

        //check burst time of current running process, finish queue if done. 
        readyQueue[0].CPUburst -= 1;
        if (readyQueue[0].CPUburst <= 0)
        {
            process = &readyQueue[0];
            process->turnaroundTime = counter - process->arrivalTime;
            process->finish = counter;

            finishQueue.enqueue(readyQueue[0]);

            //remove first element of vector
            readyQueue.erase(readyQueue.begin());
        }
    }
}



int FCFS( vector<process_t> processList)
{
    Queue<process_t> readyQueue;
    int listSize = processList.size();
    process_t running;
    int totalCpuTime = 0;
    int totalTimeUsed = 0;
    int previousTurnAround= 0;
    int previousStop = 0;
    int previousBurst = 0;
    int previousWait = 0; 

    //sort the list by the arrival time 
    //let i = time, j = number of elements in the vector 
    for (int i = 0; i <  listSize; i++)
    {
        readyQueue.enqueue(processList[i]);
        totalCpuTime += processList[i].CPUburst;
    }


    running = readyQueue.dequeue();
    printHeader();

    for (int i = 0; i < listSize; i++ )
    {
        running.turnaroundTime = (previousTurnAround - running.arrivalTime + running.CPUburst) < 0 ?
                                    (previousTurnAround - running.arrivalTime + running.CPUburst) * -1 :
                                    (previousTurnAround - running.arrivalTime + running.CPUburst) ;
        running.waitingTime =  (previousTurnAround - running.arrivalTime) < 0 ?(previousTurnAround - running.arrivalTime) * -1 : (previousTurnAround - running.arrivalTime) ;
        running.responseTime = previousTurnAround = running.arrivalTime;
        running.finish = running.CPUburst + running.waitingTime + running.arrivalTime;
        running.NumContext = 0; // no context switching with first come first serve. 
        totalTimeUsed += running.CPUburst;


        //write the process out onto the console
        cout << running.pid << setw(14) << right << running.arrivalTime << setw(13);
        cout << running.CPUburst << setw(13) << running.priority << setw(12);
        cout << running.arrivalTime << setw(18) << running.waitingTime << setw(18);
        cout << running.turnaroundTime << setw(19) << running.responseTime << setw(16) << running.NumContext << endl;
        

        previousStop = running.finish;
        previousBurst = running.CPUburst;
        previousTurnAround = running.turnaroundTime;
        previousWait = running.waitingTime;
        running = readyQueue.dequeue();
    }

    return 0;
}

// perform bubble sort
void bubbleSortBurst(vector<process_t> array, int size) {

  // loop to access each array element
  for (int step = 0; step < size; ++step) {
      
    // loop to compare array elements
    for (int i = 0; i < size - step; ++i) {

      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array[i].CPUburst > array[i + 1].CPUburst) {

        // swapping elements if elements
        // are not in the intended order
        process_t temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}