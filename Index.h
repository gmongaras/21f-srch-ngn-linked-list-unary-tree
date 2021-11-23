#ifndef INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H
#define INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H


#include "AVLTree.h"
#include "WordNode.h"




class Index {
private:
    AVLTree<WordNode> words;
    // HashMap<long, PeopleNode> people;
    // HashMap<long, OrgNode> Orgs


public:
    /**
     * addWord Method
     * Adds a word to the words AVL Tree
     * @param word The word to add to the tree
     */
    void addWord(WordNode& word);

    /**
     * getDocs Method
     * Retrieves a WordNode from the words AVLTree
     * @param word The word to search for in the tree
     * @return The WordNode that was searched for
     */
    WordNode& getWord(std::string& word);



    /**
     * addPerson Method
     * Adds a person to the hashmap given a key
     */
    //void addPerson(long key, std::string person);

    /**
     * addPeople Method
     * Adds people to the hashmap given a PersonNode
     */
    //void addPeople(long key, PersonNode& people);

    /**
     * getPeople Method
     * Retrieves a set of people given a key
     */
    //PeopleNode& getPeople(long key);
};




#endif //INC_21F_FINAL_PROJ_TEMPLATE_INDEX_H
