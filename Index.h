#ifndef INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H
#define INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H


#include "AVLTree.h"
#include "WordNode.h"
#include "HashMap.h"




class Index {
private:
    AVLTree<WordNode> words;
    HashMap<std::string, WordNode> people; //HashMap<long, PeopleNode> people;
    HashMap<std::string, WordNode> orgs; //HashMap<long, OrgNode> Orgs


public:
    /**
     * clearIndex Method
     * Clears all information from the index
     */
    void clearIndex();








    /**
     * addWord Method
     * Adds a word to the words AVL Tree
     * @param word The word to add to the tree
     */
    void addWord(WordNode& word);

    /**
     * getWord Method
     * Retrieves a WordNode from the words AVLTree
     * @param word The word to search for in the tree
     * @return The WordNode that was searched for
     */
    WordNode& getWord(std::string& word);



    /**
     * addPerson Method
     * Adds a person to the hashmap
     * @param person The person to add to the hash map
     * @param node The node to add with the information about the person
     */
    //void addPerson(long key, std::string person);
    void addPerson(std::string& person, WordNode& node);

    /**
     * addPeople Method
     * Adds people to the hashmap given a PersonNode
     */
    //void addPeople(long key, PersonNode& people);

    /**
     * getPeople Method
     * @return A WordNode mapping the searched person to document they're found in
     */
    WordNode& getPeopleDocs(std::string& person);
    //PeopleNode& getPeople(long key);





    /**
     * addOrg Method
     * Adds a org to the hashmap
     * @param org The organization to add to the hash map
     * @param node The node to add with the information about the organization
     */
    void addOrg(std::string& org, WordNode& node);

    /**
     * getOrg Method
     * @return A WordNode mapping the searched organization to document they're found in
     */
    WordNode& getOrgDocs(std::string& org);




//
//    /**
//     * addOrg Method
//     * Adds an organization to the hashmap
//     * @param organization The organization to add to the hash map
//     * @param node The node to add with the information about the organization
//     */
//    void addOrg(std::string& person, WordNode& node);
};




#endif //INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H
