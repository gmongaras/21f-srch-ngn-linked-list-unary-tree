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
    DocumentNode(const std::string& name, int freq);
    DocumentNode(const DocumentNode& node);


    /**
     * Change Value Methods
     */
    void changeName(const std::string& name);
    void changeFrequency(const int freq);


    /**
     * Get Value Methods
     */
    std::string getName() const;
    int getFreq() const;


    /**
     * Equality Operations
     */
    bool operator==(const DocumentNode& node);
    bool operator==(const std::string& name);
    bool operator!=(const DocumentNode& node);
    bool operator!=(const std::string& name);

    /**
     * Comparison Operators
     */
    bool operator<(const DocumentNode& node);
    bool operator<(const std::string& name);
    bool operator>(const DocumentNode& node);
    bool operator>(const std::string& name);


    /**
     * updateFreq Method
     * Adds 1 to the frequency
     * @return The stored value of the frequency
     */
    int updateFreq();


    /**
     * Overloaded Stream Insertion Operator
     */
    friend std::ostream& operator<< (std::ostream&, const DocumentNode&);
};



#endif //INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H
