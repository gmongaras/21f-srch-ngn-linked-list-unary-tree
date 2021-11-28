#include <iostream>


#include "UserInterface.h"
#include "catch_setup.h"




int main(int argc, char** argv) {
    // If there are no command line arguments, run the catch tests
//    if(argc == 1) {
//        runCatchTests();
//        return 0;
//    }


    // Create a User Interface object to handle all actions
    // the user gives
    UserInterface UI;

    // Initialize the UI
    UI.Initialize();


    // Prompt the user for input and handle it
    UI.promptUser();




    return 0;
}
