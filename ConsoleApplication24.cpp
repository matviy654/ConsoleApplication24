#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

struct Passenger {
    int arrivalTime;
};

class BusStopSimulation {
public:
    BusStopSimulation(int passengerInterval, int busInterval, int maxPassengers)
        : passengerInterval(passengerInterval), busInterval(busInterval), maxPassengers(maxPassengers) {}

    void runSimulation(int simulationTime) {
        int currentTime = 0;
        int totalWaitTime = 0;
        int passengerCount = 0;

        std::queue<Passenger> queue;

        while (currentTime < simulationTime) {
            if (currentTime % passengerInterval == 0) {
                queue.push({ currentTime });
                std::cout << "Passenger arrived at time " << currentTime << "\n";
            }

            if (currentTime % busInterval == 0 && !queue.empty()) {
                int freeSeats = rand() % 10 + 1;
                std::cout << "Bus arrived at time " << currentTime << " with " << freeSeats << " free seats\n";

                while (freeSeats > 0 && !queue.empty()) {
                    Passenger passenger = queue.front();
                    queue.pop();
                    totalWaitTime += currentTime - passenger.arrivalTime;
                    passengerCount++;
                    freeSeats--;
                }
            }

            if (queue.size() > maxPassengers) {
                std::cout << "Too many passengers at the bus stop! Increase bus frequency.\n";
                break;
            }

            currentTime++;
        }

        if (passengerCount > 0) {
            double averageWaitTime = static_cast<double>(totalWaitTime) / passengerCount;
            std::cout << "Average wait time: " << averageWaitTime << " minutes\n";
        }
        else {
            std::cout << "No passengers served during simulation.\n";
        }
    }

private:
    int passengerInterval;
    int busInterval;
    int maxPassengers;
};

int main() {
    srand(time(0));
    int passengerInterval = 5;
    int busInterval = 10;
    int maxPassengers = 20;
    int simulationTime = 100;
    BusStopSimulation simulation(passengerInterval, busInterval, maxPassengers);
    simulation.runSimulation(simulationTime);
    return 0;
}



#include <iostream>
#include <queue>
#include <string>
#include <ctime>

struct PrintJob {
    std::string user;
    int priority;
    int timestamp;

    bool operator<(const PrintJob& other) const {
        return priority < other.priority;
    }
};

class PrinterQueue {
public:
    void addJob(const std::string& user, int priority) {
        int timestamp = static_cast<int>(time(0));
        jobs.push({ user, priority, timestamp });
        std::cout << "Job added for " << user << " with priority " << priority << "\n";
    }

    void printJobs() {
        while (!jobs.empty()) {
            PrintJob job = jobs.top();
            jobs.pop();
            std::cout << "Printing for " << job.user << " with priority " << job.priority
                << " at time " << job.timestamp << "\n";
        }
    }

private:
    std::priority_queue<PrintJob> jobs;
};

int main() {
    PrinterQueue printerQueue;
    printerQueue.addJob("User1", 2);
    printerQueue.addJob("User2", 5);
    printerQueue.addJob("User3", 1);
    printerQueue.addJob("User4", 3);
    std::cout << "\nStarting print jobs:\n";
    printerQueue.printJobs();
    return 0;
}
