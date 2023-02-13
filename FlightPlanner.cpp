//
// Created by Alex Shockley on 10/29/2020.
//

#include "FlightPlanner.h"
//input01.txt input02.txt output.txt

// driver function
using namespace std;
void FlightPlanner::run() {

    generateFlightList(); // generates the aList based on input file
    aList.printList(); // prints out the aList for debugging
    generateDesiredFlights(); // generates the desired flights based on the second input file
    printDesiredFlights(); //prints desired flights for debugging
    for(int z = 0; z < desiredFlights.getSize(); z++) { // for loop that runs desirecFLights.size() times
        outputFlights(z); // iterative back tracking to find all possible paths to the end destination
        printFlights(); // prints out the possible flights for debugging

        printCorrectFlights(); // prints out the flghts with formatting
        generatePlans(); // generates the list that contains all the possible paths
        for (int i = 0; i < plans.getSize(); i++) { // calculate the total cost and total time for every path
            plans[i].calculateCost();
            plans[i].calculateTime();
        }
        for (int i = 0; i < plans.getSize(); i++) { // display for debugging
          plans[i].display();
        }
        sortByCost(); // sort the Cost sorted list by cost
        sortByTime(); // sort the Time sorted list by time
        outputToFile(z); // handle formatting and output the best 3 paths
        plans.clear(); // clear out the data in all the lists incase there is a second desired flight
        correctFlights.clear();
        costSort.clear();
        timeSort.clear();
    }
}

void FlightPlanner::outputToFile(int i) { // handles formatting to the output file

        if (desiredFlights[i].getReason() == 'T') { // if user wants time sorted
            fout << "Flight " << i + 1;
            fout << ": " << desiredFlights[i].getPath().first << ", " << desiredFlights[i].getPath().second; // displays the desired flight from the second input file
            fout << " (Time)" << endl;
            for (int j = 0; j < timeSort.getSize() && j < 3; j++) { // for loop that will output up to the 3 best paths based on time
                fout << "Path " << j + 1<< ": ";
                fout << timeSort[j].second; // this is a flightPlan obj which has overloaded << operator that displays the entire path of the plan
                fout << "Time: " << *timeSort[j].second.getTotalTime() << " ";
                fout << "Cost: " << *timeSort[j].second.getTotalCost() << endl;
            }
        } else { // else, they want it sorted by cost handle it the same way, but instead of accessing the list sorted by time, use the list sorted by cost
            fout << "Flight " << i + 1;
            fout << ": " << desiredFlights[i].getPath().first << ", " << desiredFlights[i].getPath().second;
            fout << " (Cost)" << endl;
            for (int j = 0; j < timeSort.getSize() && j < 3; j++) {
                fout << "Path " << j + 1 << ": ";
                fout << timeSort[j].second;
                fout << "Time: " << *timeSort[j].second.getTotalTime() << " ";
                fout << "Cost: " << *timeSort[j].second.getTotalCost() << endl;
            }
        }

}

void FlightPlanner::setInputFile(char *fileName) {
    input.open(fileName);
}

void FlightPlanner::setOutputFile(char *fileName) {
    fout.open(fileName);
}

FlightPlanner::~FlightPlanner() {
    input.close();
    fout.close();
    input2.close();
}

FlightPlanner::FlightPlanner() {
    aList = AList<City>();
    desiredFlights = DSList<DesiredFlight>();
    flights = DSList<Flight>();
}

void FlightPlanner::generateFlightList() { // function that generates the aList
    int numEntries = 0;
    char buffer[50000];
    input.getline(buffer,50000);
    numEntries = atoi(buffer);
    for(int i = 0; i < numEntries; i ++) { // read in x entries
        input.getline(buffer,50000,'|');
        SString endLineTest = SString(buffer);
        City a = City(buffer);
        input.getline(buffer,50000,'|');
        City b = City(buffer);
        input.getline(buffer,50000,'|');
        double price = atof(buffer);
        input.getline(buffer,50000,'|');
        double time = atof(buffer);
        input.getline(buffer,50000);
        SString company = SString(buffer);

        aList.pushMain(a); // note, we must push both a,b and b,a to the list because each city is connected both ways
        aList.pushMain(b);
        aList.pushAdj(a,b);
        aList.pushAdj(b,a);
        Flight flight = Flight(a,b,price,company,time); // same with the flight objects
        Flight reverseFlight = Flight(b,a,price,company,time);
        flights.push_back(flight);
        flights.push_back(reverseFlight);
        //cout << a << ", " << b << ", " << price <<", " << time << ", " <<company.getData() <<endl;

    }
}

void FlightPlanner::setHandleFile(char *fileName) {
    input2.open(fileName);
}

void FlightPlanner::generateDesiredFlights() { // reads in info from second input file
    int numEntries = 0;
    char buffer[50000];
    input2.getline(buffer,50000);
    numEntries = atoi(buffer);
    for(int i = 0; i < numEntries; i ++) {
        input2.getline(buffer,50000,'|');
        City a = City(buffer);
        input2.getline(buffer,50000,'|');
        City b = City(buffer);
        char reason;
        input2.getline(buffer,50000);
        reason = buffer[0];

        pair<City,City> pairToAdd;
        pairToAdd.first = a;
        pairToAdd.second = b;
        DesiredFlight c = DesiredFlight(pairToAdd,reason); // create a desired flight object given names and reason

        desiredFlights.push_back(c);// add it to the list
    }

}

void FlightPlanner::printDesiredFlights() { // prints desired flights with formatting
    cout <<"==================== DESIRED FLIGHTS================="<<endl;
    for(int i = 0; i < desiredFlights.getSize(); i ++) {
        cout << desiredFlights[i].getPath().first <<" -> ";
        cout << desiredFlights[i].getPath().second;
        cout <<" " <<desiredFlights[i].getReason();
        cout <<endl;
    }

}

void FlightPlanner::outputFlights(int i) { // iterative back tracking to find all possible paths
    Stack<City> stack;
    Stack<DSList<City>::iterator> itrStack;


        stack.push(desiredFlights[i].getPath().first); // add initial city
        City endDest = desiredFlights[i].getPath().second;


        while(!stack.isEmpty()) { // while the stack is not empty
            if(stack.peek() == endDest) { // if the top of the stack is the end destination, save the path and pop
                saveFlightPath(stack);
                stack.pop();

            } else {

                    if(aList.isItrNull(stack.peek())) { // if the iterator is null on the list attached to the city at the top of the stack, the reset that iterator and pop
                        aList.resetItr(stack.peek());
                        stack.pop();


                    }else if(stack.contains(aList.getAdjNodes(stack.peek()).getNext())) { // if the city is already in the list, then just move the iterator and jump to beginning of loop
                        aList.moveItr(stack.peek());
                        continue;

                    } else {
                        auto currCity = stack.peek();
                        stack.push(aList.getAdjNodes(currCity).getNext()); // if none of those cases happen, then we push the city to the stack
                        aList.moveItr(currCity);

                    }

            }

        }



}

void FlightPlanner::printFlights() { // prints flights with formatting
    for(int i = 0; i < flights.getSize(); i++) {
        cout << flights[i].getPath().first << " -> ";
        cout << flights[i].getPath().second << ": ";
        cout << flights[i].getPrice() <<" ";
        cout << flights[i].getTime() <<" ";
        cout << flights[i].getAirline().getData() << endl;
    }
}

void FlightPlanner::saveFlightPath(Stack<City> stack) { // pops the entire list and saves it, in reverse order, to a dsList and adds that to a dsList
    DSList<City> listToAdd;
    while(!stack.isEmpty()) {
        listToAdd.push_back(stack.pop());
    }
    DSList<City> realList;
    for(int i = listToAdd.getSize() - 1; i >= 0; i--) {
        realList.push_back(listToAdd[i]);
    }
    correctFlights.push_back(realList);
}



void FlightPlanner::printCorrectFlights() { // prints out the correctFlights List with formatting for debugging
    cout << "CFLights Size: " << correctFlights.getSize() <<endl;
    for(int i = 0; i < correctFlights.getSize(); i ++) {
        for(int j = 0; j < correctFlights[i].getSize(); j++) {
            cout << correctFlights[i][j].getName() << "-> ";
        }
        cout <<endl;
    }
}


void FlightPlanner::generatePlans() { // generates the plans list
    for(int k = 0; k < correctFlights.getSize(); k++) { //run correctFlights.size times
        FlightPlan a; // create a flight plan
        for (int i = 0; i < correctFlights[k].getSize(); i++) { // create a pair of the city connections based on the correct paths to the destination
            pair<City, City> look;
            if (i + 1 != correctFlights[k].getSize()) {

                look.first = correctFlights[k].at(i);
                look.second = correctFlights[k].at(i+1);
            }

            for (int j = 0; j < flights.getSize(); j++) { // compare those to the pairs of the possible flights to determine the right flight to add (Because the flight object has cost and time and airline)
                pair<City, City> flightPair;
                flightPair = flights[j].getPath();
                if(look == flightPair) {

                    a.addFlight(flights[j]);
                    break;
                }
            }
        }
        plans.push_back(a); // pushback the entire flightPlan to the plans list
    }

}

void FlightPlanner::sortByTime() { // sorts the timeSort list by time

    for(int i = 0; i < plans.getSize(); i ++) { // basically assigning a pair of <Time,TheWholeFlightPlanObj> and sorting those because it sorts by pair.first
        pair<double,FlightPlan> pairToAdd;
        pairToAdd.first = *plans[i].getTotalTime();
        pairToAdd.second = plans[i];
        timeSort.push_back(pairToAdd);
    }
    timeSort.sort();

}


void FlightPlanner::sortByCost() { // same as time, but the pair is <Cost, FlightPlanObj>

    for(int i = 0; i < plans.getSize(); i ++) {
        pair<double,FlightPlan> pairToAdd;
        pairToAdd.first = *plans[i].getTotalCost();
        pairToAdd.second = plans[i];
        costSort.push_back(pairToAdd);
    }
    costSort.sort();
}



