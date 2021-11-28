#ifndef INC_21F_FINAL_PROJ_TEMPLATE_USERINTERFACE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_USERINTERFACE_H

#include "QueryProcessor.h"


class UserInterface {
private:
    QueryProcessor QP;



    /**
     * handleAction
     * Handle a given action from the user
     */
    void handleAction(int action);


public:
    /**
     * Initialize
     * Initialize the UI by displaying a prompt.
     */
    void Initialize();


    /**
     * promptUser
     * Prompts the user for input and requests an action to take
     */
    void promptUser();
};





#endif //INC_21F_FINAL_PROJ_TEMPLATE_USERINTERFACE_H
