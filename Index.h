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





//    /**
//     * loadTree Helper Method
//     * Loads a tree from a given file
//     * @param filename The file use to lead in
//     * @param delimiter The delimiter used when leading in the tree
//     * @param equalityFunction The function to use when inserting a node and equality is
//     *                         found between two nodes
//     * @param wordsCountsTree A tree to map each unique word to the number of times it's found.
//     */
//    void loadTree(const std::string& filename, char delimiter, std::function<void(WordNode& newItem, TreeNode<WordNode>*& curPtr)> equalityFunction);


public:
    /**
     * clearIndex Method
     * Clears all information from the index
     */
    void clearIndex();

    /**
     * saveFiles
     * Saves the info in index given three file names
     * @param wordsFileName The name of the file to save the words AVL Tree
     * @param peopleFileName The name of the file to save the people Hash Table
     * @param orgsFileName The name of the file to save the organizations Hash Table
     * @param NUMFILES The number of files read in
     */
    void saveFiles(std::string& wordsFileName, std::string& peopleFileName, std::string& orgsFileName, long& NUMFILES);

    /**
     * LoadFiles Method
     * Accepts a few files to parse the indices from
     * @param wordsFileName The name of the file to load the words AVL Tree from
     * @param peopleFileName The name of the file to load the people Hash Table from
     * @param orgsFileName The name of the file to load the organizations Hash Table from
     * @param NUMFILES The number of files read in
     */
    void LoadFiles(std::string& wordsFileName, std::string& peopleFileName, std::string& orgsFileName, long& NUMFILES);








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
     * getNumWords Method
     * @return The number of words read in
     */
    long long getNumWords();

    /**
     * getNumUniqueWords Method
     * @return The number of unique words read in
     */
    int getNumUniqueWords();

    /**
     * getTop50WordCounts Method
     * @return The top 50 word counts in order in a vector
     */
    std::vector<WordNode> getTop50WordCounts();





    /**
     * addPerson Method
     * Adds a person to the hashmap
     * @param person The person to add to the hash map
     * @param node The node to add with the information about the person
     */
    void addPerson(std::string& person, WordNode& node);

    /**
     * getPeople Method
     * @return A WordNode mapping the searched person to document they're found in
     */
    WordNode& getPeopleDocs(std::string& person);

    /**
     * getNumUniquePeople Method
     * @return The number of unique people entered into the map
     */
    int getNumUniquePeople();





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

    /**
     * getNumUniqueOrgs Method
     * @return The number of unique organizations entered into the map
     */
    int getNumUniqueOrgs();




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
