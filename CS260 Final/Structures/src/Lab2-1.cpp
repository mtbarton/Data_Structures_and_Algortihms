//============================================================================
// Name        : Lab2-2.cpp
// Author      : Mitchel Barton
// Version     : 1.0
// Copyright   : Copyright � 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include "CSVparser.hpp" //references the CSVParser header file


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    std::cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    std::cout << "Enter title: ";
    std::cin.ignore();
    std::getline(std::cin, bid.title);

    std::cout << "Enter fund: ";
    std::cin >> bid.fund;

    std::cout << "Enter amount: ";
    std::cin.ignore();
    string strAmount;
    std::getline(std::cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	//Defined a vector data structure bidVals to hold a collection of bids.

    vector<Bid> bidVals;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

	// loop to read rows of a CSV file
	for (unsigned int i = 0; i < file.rowCount(); i++) {
        // Set instance of Bid data structure to hold data from each row and add to vector bidVals
        Bid bid;
        bid.title = file[i][0];
        bid.fund = file[i][8];
        bid.amount = strToDouble(file[i][4], '$');
        bidVals.push_back(bid);
    }
    return bidVals;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    //vector to hold all the bids
    vector<Bid> allBids;

    //timer variable for "load bids" method
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            cout << "Not currently implemented." << endl;
        }
            break;

        case 2:
        {
            // Initialize a timer variable before loading bids
            ticks = clock();
            // Method call to load the bids into main vector
            allBids = loadBids(csvPath);

            // Calculate elapsed time to load bids into vector and display result
            ticks = clock() - ticks;
            cout << "Time: " << ticks << " milliseconds" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
        }
            break;
        case 3:
        {
            // For loop to read all bids in the csv file and display them
            for (unsigned int i = 0; i < allBids.size(); ++i) {
                displayBid(allBids[i]);
            }
            cout << endl;
        }
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
