#include "UserInterface.h"




int main(int argc, char** argv) {
    // Create a User Interface object to handle all actions
    // the user gives
    UserInterface UI;

    // Initialize the UI
    UI.Initialize();


    // Prompt the user for input and handle it
    UI.promptUser();




    return 0;
}
