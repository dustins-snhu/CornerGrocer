/******************************************************************
**
** CS-210 Project Three Submission.
** main.cpp
**
** Dustin Schroeder
** Southern New Hampshire University
** CS-210-16218-M01 Programming Languages 2026 C-2 (Mar - Apr)
** Kyle Richbourg
** Apr 15, 2026
**
******************************************************************/

#include "GroceryTracker.h"

//[DRS APR 2026]: Main driver - instantiates GroceryTracker and delegates to controller
int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");
    tracker.run();
    return 0;
}
