#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H



#include <string>



class DocumentNode {
private:
    std::string documentName; // The name of this document
    int frequency; // The number of times a word shows up in this document



public:
    /**
     * Constructors
     */
    DocumentNode();
    DocumentNode(const std::string& name, const int freq);
    DocumentNode(const DocumentNode& node);


    /**
     * Change Value Methods
     */
    void changeName(const std::string& name);
    void changeFrequency(const int freq);


    /**
     * Get Value Methods
     */
    std::string& getName();
    int getFreq();


    /**
     * updateFreq Method
     * Adds 1 to the frequency
     * @return The stored value of the frequency
     */
    int updateFreq();
};



#endif //INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H
