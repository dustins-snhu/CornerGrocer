/******************************************************************
**
** CS-210 Project Three Submission.
** GroceryTracker.cpp
**
** Dustin Schroeder
** Southern New Hampshire University
** CS-210-16218-M01 Programming Languages 2026 C-2 (Mar - Apr)
** Kyle Richbourg
** Apr 15, 2026
**
******************************************************************/

#include "GroceryTracker.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

//[DRS APR 2026]: Constructor loads frequencies from input file on creation
GroceryTracker::GroceryTracker(const string& t_inputFile) {
    loadInputFile(t_inputFile);
}

//[DRS APR 2026]: Reads the input file and counts occurrences of each item
void GroceryTracker::loadInputFile(const string& t_inputFile) {
    ifstream inputFile(t_inputFile);

    //[DRS APR 2026]: Validate that the input file opened successfully
    if (!inputFile.is_open()) {
        throw runtime_error("Could not open input file: " + t_inputFile);
    }

    string item;
    //[DRS APR 2026]: Read each line and increment the count in the map
    while (getline(inputFile, item)) {
        //[DRS APR 2026]: Strip trailing carriage return from Windows-style line endings
        if (!item.empty() && item.back() == '\r') {
            item.pop_back();
        }
        if (!item.empty()) {
            m_itemFrequencies[item]++;
        }
    }

    inputFile.close();
}

//[DRS APR 2026]: Returns frequency count for a specific item, 0 if not found
int GroceryTracker::getItemFrequency(const string& t_item) const {
    auto it = m_itemFrequencies.find(t_item);
    if (it != m_itemFrequencies.end()) {
        return it->second;
    }
    return 0;
}

//[DRS APR 2026]: Prints each item and its numeric frequency
void GroceryTracker::printAllFrequencies() const {
    for (const auto& pair : m_itemFrequencies) {
        cout << pair.first << " " << pair.second << endl;
    }
}

//[DRS APR 2026]: Prints each item followed by asterisks representing its frequency
void GroceryTracker::printHistogram() const {
    //[DRS APR 2026]: Copy items into a vector so we can sort by frequency descending
    vector<pair<string, int>> sorted(m_itemFrequencies.begin(), m_itemFrequencies.end());
    sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    //[DRS APR 2026]: Find the longest item name to align all asterisks to the same column
    size_t maxLength = 0;
    for (const auto& item : sorted) {
        if (item.first.length() > maxLength) {
            maxLength = item.first.length();
        }
    }

    //[DRS APR 2026]: Define gradient colors from red (top) through yellow/green to blue (bottom)
    //[DRS APR 2026]: Each entry is {R, G, B} using ANSI 24-bit color codes
    vector<vector<int>> gradient = {
        {255, 0, 0},       // red
        {255, 64, 0},      // red-orange
        {255, 128, 0},     // orange
        {255, 200, 0},     // yellow-orange
        {255, 255, 0},     // yellow
        {200, 255, 0},     // yellow-green
        {100, 255, 0},     // green
        {0, 200, 100},     // green-teal
        {0, 150, 200},     // teal-blue
        {0, 100, 255}      // blue
    };

    int totalItems = static_cast<int>(sorted.size());

    //[DRS APR 2026]: Find the max frequency to set bracket width for all rows
    int maxFrequency = sorted.empty() ? 0 : sorted[0].second;

    for (int i = 0; i < totalItems; i++) {
        //[DRS APR 2026]: Map row index to a position in the gradient
        int colorIndex = 0;
        if (totalItems > 1) {
            colorIndex = i * (static_cast<int>(gradient.size()) - 1) / (totalItems - 1);
        }

        int r = gradient[colorIndex][0];
        int g = gradient[colorIndex][1];
        int b = gradient[colorIndex][2];

        //[DRS APR 2026]: Print item name, then bracketed bar with asterisks and padding
        //[DRS APR 2026]: Only emit ANSI color codes when m_useColor is enabled
        int padding = maxFrequency - sorted[i].second;
        cout << sorted[i].first
             << string(maxLength - sorted[i].first.length() + 1, ' ')
             << "[";
        if (m_useColor) {
            cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
        }
        cout << string(sorted[i].second, '*');
        if (m_useColor) {
            cout << "\033[0m";
        }
        cout << string(padding, ' ')
             << "]" << endl;
    }
}

//[DRS APR 2026]: Writes all item frequencies to a backup data file
void GroceryTracker::writeBackupFile(const string& t_outputFile) const {
    ofstream outputFile(t_outputFile);

    //[DRS APR 2026]: Validate that the output file opened successfully
    if (!outputFile.is_open()) {
        throw runtime_error("Could not open output file: " + t_outputFile);
    }

    //[DRS APR 2026]: Write each item and its count to the file
    for (const auto& pair : m_itemFrequencies) {
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close();
}

//[DRS APR 2026]: Displays the menu options to the user
void GroceryTracker::displayMenu() const {
    cout << endl;
    cout << "**********************************" << endl;
    cout << "****** Corner Grocer Menu ********" << endl;
    cout << "**********************************" << endl;
    cout << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print item histogram" << endl;
    //[DRS APR 2026]: Option 4 - Toggle colored output for terminal compatibility
    cout << "4. Toggle colored output (currently " << (m_useColor ? "ON" : "OFF") << ")" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

//[DRS APR 2026]: Reads a menu choice with input validation
int GroceryTracker::readMenuChoice() const {
    int choice;
    while (true) {
        cin >> choice;
        //[DRS APR 2026]: Check for non-numeric input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-5): ";
            continue;
        }
        //[DRS APR 2026]: Check for valid range
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter a number (1-5): ";
            continue;
        }
        return choice;
    }
}

//[DRS APR 2026]: Main controller - runs the menu loop until user exits
void GroceryTracker::run() {
    //[DRS APR 2026]: Create backup file at program start without user intervention
    try {
        writeBackupFile("frequency.dat");
    }
    catch (const exception& e) {
        cout << "Warning: " << e.what() << endl;
    }

    bool running = true;

    //[DRS APR 2026]: Main menu loop
    while (running) {
        displayMenu();
        int choice = readMenuChoice();

        switch (choice) {
            case 1: {
                //[DRS APR 2026]: Option 1 - Search for a specific item frequency
                cout << "Enter the item to search for: ";
                string item;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, item);

                int frequency = getItemFrequency(item);
                if (frequency > 0) {
                    cout << item << " " << frequency << endl;
                }
                else {
                    cout << item << " was not found in the records." << endl;
                }
                break;
            }
            case 2:
                //[DRS APR 2026]: Option 2 - Print all items with numeric frequencies
                cout << endl;
                printAllFrequencies();
                break;
            case 3:
                //[DRS APR 2026]: Option 3 - Print histogram of all items
                cout << endl;
                printHistogram();
                break;
            case 4:
                //[DRS APR 2026]: Option 4 - Toggle colored histogram output
                m_useColor = !m_useColor;
                cout << "Colored output " << (m_useColor ? "enabled" : "disabled") << "." << endl;
                break;
            case 5:
                //[DRS APR 2026]: Option 5 - Exit the program
                cout << "Thank you for using Corner Grocer Tracker!" << endl;
                running = false;
                break;
        }
    }
}
