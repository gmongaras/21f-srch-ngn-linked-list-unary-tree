#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTNODE_H



#include <string>



class DocumentNode {
private:
    std::string fileName; // The file name of this document (the path of the document)
    int frequency; // The number of times a word shows up in this document
    std::string documentID; // The ID of the document
    int docLength; // The length of the document
    std::string title; // The title of the document
    std::string author; // The author of the article
    std::string date; // The date the document was published



public:
    /**
     * Constructors
     */
    DocumentNode();
    DocumentNode(const std::string& name, int freq, std::string ID, int length, std::string& Title, std::string& Author, std::string& Date);
    DocumentNode(const DocumentNode& node);


    /**
     * Change Value Methods
     */
    void changeName(const std::string& name);
    void changeFrequency(const int freq);
    void changeID(const std::string& ID);
    void changeLength(const int length);
    void changeTitle(const std::string& Title);
    void changeAuthor(const std::string& Author);
    void changeDate(const std::string& Date);


    /**
     * Get Value Methods
     */
    std::string getName() const;
    int getFreq() const;
    std::string getID() const;
    int getLength() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getDate() const;


    /**
     * getRelevancyRanking Method
     * Returns the relevancy ranking for this document and the word it's
     * a part of
     * @return The relevancy ranking of this document with respect to the
     *         word it belongs to
     */
    float getRelevancyRanking() const;


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
