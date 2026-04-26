/******************************************************************
**
** CS-210 Project Three Submission.
** GroceryTracker.h
**
** Dustin Schroeder
** Southern New Hampshire University
** CS-210-16218-M01 Programming Languages 2026 C-2 (Mar - Apr)
** Kyle Richbourg
** Apr 15, 2026
**
******************************************************************/

//[DRS APR 2026]: Header guard to prevent multiple inclusion
#ifndef CORNER_GROCER_GROCERY_TRACKER_H_
#define CORNER_GROCER_GROCERY_TRACKER_H_

#include <string>
#include <map>

//[DRS APR 2026]: GroceryTracker class handles item frequency tracking and reporting
class GroceryTracker {

public:
    //[DRS APR 2026]: Constructor loads item frequencies from the input file
    GroceryTracker(const std::string& t_inputFile);

    //[DRS APR 2026]: Returns the frequency of a specific item
    int getItemFrequency(const std::string& t_item) const;

    //[DRS APR 2026]: Prints all items with their numeric frequency
    void printAllFrequencies() const;

    //[DRS APR 2026]: Prints a histogram of all items using a special character
    void printHistogram() const;

    //[DRS APR 2026]: Writes all frequencies to a backup data file
    void writeBackupFile(const std::string& t_outputFile) const;

    //[DRS APR 2026]: Main controller - runs the menu loop
    void run();

private:
    //[DRS APR 2026]: Map storing item names and their purchase counts
    std::map<std::string, int> m_itemFrequencies;

    //[DRS APR 2026]: Controls whether ANSI color codes are used in histogram output
    bool m_useColor = true;

    //[DRS APR 2026]: Loads item data from the input file into the map
    void loadInputFile(const std::string& t_inputFile);

    //[DRS APR 2026]: Displays the menu options to the user
    void displayMenu() const;

    //[DRS APR 2026]: Reads and validates a menu choice from the user
    int readMenuChoice() const;
};

#endif // CORNER_GROCER_GROCERY_TRACKER_H_
