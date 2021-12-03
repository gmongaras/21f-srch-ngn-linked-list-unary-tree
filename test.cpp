/**
 * Outline: Tests classes within this project to make sure they work correctly
 * Date: 10/10/21
 * Author: Gabriel Mongaras
 * Input: None
 * Output: How many tests cases passed and failed
 */



#include "catch.hpp"
#include <string>
#include "TreeNode.h"
#include <vector>
#include "AVLTree.h"

// Overload the outstrem of the vector for testing
template <class T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& v)
{
    out << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end()-1; ++ii)
    {
        out << ", " << *ii;
    }
    out << v[v.size()];
    out << "]";
    return out;
}




TEST_CASE("TreeNode class", "[TreeNode]") {
    // global variables
    TreeNode<int>* n1 = new TreeNode<int>(1);
    TreeNode<int>* n2 = new TreeNode<int>(n1);
    TreeNode<int>* n3 = new TreeNode<int>(2);
    TreeNode<float>* n4 = new TreeNode<float>(0.009);
    TreeNode<std::string>* n5 = new TreeNode<std::string>(std::string("hello"));
    TreeNode<char>* n6 = new TreeNode<char>('\n');
    TreeNode<std::vector<int>>* n7 = new TreeNode<std::vector<int>>(std::vector<int>{0,1,2,3,4});
    TreeNode<std::vector<int>>* n8 = new TreeNode<std::vector<int>>(std::vector<int>{1,2,3,4,5});


    SECTION("Checking the == operator") {
        REQUIRE(*n1 == *n1);
        REQUIRE(*n1 == *n2);
        REQUIRE(*n1 == 1);
        REQUIRE(*n4 == 0.009);
        REQUIRE(*n5 == std::string("hello"));
        REQUIRE(*n6 == '\n');
        REQUIRE(*n5 == TreeNode<std::string>(std::string("hello")));
        REQUIRE(*n7 == std::vector<int>{0,1,2,3,4});
    }

    SECTION("Checking the != operator") {
        REQUIRE(*n1 != *n3);
        REQUIRE(*n2 != *n3);
        REQUIRE(*n1 != 0);
        REQUIRE(*n4 != 0.0091);
        REQUIRE(*n5 != std::string("hello!"));
        REQUIRE(*n6 != '\t');
        REQUIRE(*n5 != TreeNode<std::string>(std::string("hello!")));
        REQUIRE(*n7 != std::vector<int>{1,2,3,4,5});
        REQUIRE(*n7 != *n8);
    }

    SECTION("Checking the > operator") {
        REQUIRE(*n3 > *n1);
        REQUIRE(*n3 > *n2);
        REQUIRE(*n1 > 0);
        REQUIRE(*n4 > 0.0089);
        REQUIRE(TreeNode<std::string>(std::string("zello")) > *n5);
        REQUIRE(*n6 > '\0');
    }

    SECTION("Checking the < operator") {
        REQUIRE(*n1 < *n3);
        REQUIRE(*n2 < *n3);
        REQUIRE(*n1 < 9);
        REQUIRE(*n4 < 0.0091);
        REQUIRE(*n5 < std::string("zello"));
        REQUIRE(*n5 < TreeNode<std::string>(std::string("zello")));
        REQUIRE(*n6 < '1');
    }

    SECTION("Checking the modifying = operator") {
        REQUIRE((*n1=n3) == n3);
        REQUIRE((*n2=2) == n3);
        REQUIRE((*n1=4) != n3);
        REQUIRE((*n4=0.0091) == 0.0091);
        REQUIRE((*n5=std::string("zello")) == std::string("zello"));
        REQUIRE((*n6='\t') == '\t');
    }

    SECTION("Checking the getData method") {
        int a = 1;
        int b = 2;
        REQUIRE(n1->getData() == a);
        REQUIRE(n2->getData() == a);
        REQUIRE(n3->getData() == b);
        REQUIRE((*n2=2).getData() == b);
        REQUIRE(n4->getData() == 0.009f);
        REQUIRE(n5->getData() == std::string("hello"));
        REQUIRE(n6->getData() == '\n');
    }

    SECTION("Checking the setRight and getRight methods") {
        n1->setRight(n2);
        REQUIRE(*(n1->getRight()) == *(n2));
        n2->setRight(n3);
        REQUIRE(*(n2->getRight()) == *(n3));
        REQUIRE(n1->getRight()->getRight() == n3);
        n7->setRight(n8);
        REQUIRE(n7->getRight() == n8);
        n8->setRight(n8);
        REQUIRE(n7->getRight()->getRight() == n8);
        REQUIRE(n7->getRight()->getRight()->getRight() == n8);
        REQUIRE(n6->getRight() == nullptr);
    }

    SECTION("Checking the setLeft and getLeft methods") {
        n1->setLeft(n2);
        REQUIRE(*(n1->getLeft()) == *(n2));
        n2->setLeft(n3);
        REQUIRE(*(n2->getLeft()) == *(n3));
        REQUIRE(n1->getLeft()->getLeft() == n3);
        n7->setLeft(n8);
        REQUIRE(n7->getLeft() == n8);
        n8->setLeft(n8);
        REQUIRE(n7->getLeft()->getLeft() == n8);
        REQUIRE(n7->getLeft()->getLeft()->getLeft() == n8);
        REQUIRE(n6->getLeft() == nullptr);
    }

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;
    delete n8;
}





template <typename T>
void equalityFunction(T& newItem, TreeNode<T>*& curPtr) {
    return;
}

TEST_CASE("AVLTree class", "[AVLTree]") {
    AVLTree<int> AVL1;
    int a = 9; AVL1.insert(a, &equalityFunction<int>);
    int b = 5; AVL1.insert(b, &equalityFunction<int>);
    AVL1.insert(a, &equalityFunction<int>);
    int c = 100; AVL1.insert(c, &equalityFunction<int>);
    int d = 1; AVL1.insert(d, &equalityFunction<int>);
    int e = 0; AVL1.insert(e, &equalityFunction<int>);
    int f = 4; AVL1.insert(f, &equalityFunction<int>);
    int g = 101; AVL1.insert(g, &equalityFunction<int>);
    int h = 11; AVL1.insert(h, &equalityFunction<int>);
    int i = 10; AVL1.insert(i, &equalityFunction<int>);
    int j = 90; AVL1.insert(j, &equalityFunction<int>);
    AVL1.insert(j, &equalityFunction<int>);


    AVLTree<std::string> AVL2;
    std::string a2("hello"); AVL2.insert(a2, &equalityFunction<std::string>);
    std::string b2("sussy"); AVL2.insert(b2, &equalityFunction<std::string>);
    AVL2.insert(b2, &equalityFunction<std::string>);
    std::string c2("Sussy"); AVL2.insert(c2, &equalityFunction<std::string>);
    std::string d2("baka"); AVL2.insert(d2, &equalityFunction<std::string>);
    std::string e2("bob"); AVL2.insert(e2, &equalityFunction<std::string>);
    std::string f2("cob"); AVL2.insert(f2, &equalityFunction<std::string>);
    std::string g2("sob"); AVL2.insert(g2, &equalityFunction<std::string>);
    std::string h2("iii"); AVL2.insert(h2, &equalityFunction<std::string>);
    std::string i2("job"); AVL2.insert(i2, &equalityFunction<std::string>);
    std::string j2("Zaka"); AVL2.insert(j2, &equalityFunction<std::string>);




    SECTION("Checking the insert method with the getInOrderVec method") {
        std::vector<int> v;
        AVL1.getInOrderVec(v);
        REQUIRE(v == std::vector<int>({0,1,4,5,9,10,11,90,100,101}));
        std::vector<std::string> v1;
        AVL2.getInOrderVec(v1);
        REQUIRE(v1 == std::vector<std::string>({std::string("Sussy"), std::string("Zaka"), std::string("baka"), std::string("bob"), std::string("cob"), std::string("hello"), std::string("iii"), std::string("job"), std::string("sob"), std::string("sussy")}));
    }



    SECTION("Checking the hasNode Method") {
        REQUIRE(AVL1.hasNode(c) == true);
        REQUIRE(AVL1.hasNode(g) == true);
        int g1 = 101;
        REQUIRE(AVL1.hasNode(g1) == true);
        int g3 = 102;
        REQUIRE(AVL1.hasNode(g3) == false);
        REQUIRE(AVL2.hasNode(a2) == true);
        REQUIRE(AVL2.hasNode(j2) == true);
        std::string h3("iii");
        REQUIRE(AVL2.hasNode(h3) == true);
        std::string h4("III");
        REQUIRE(AVL2.hasNode(h4) == false);
        std::string h5("iij");
        REQUIRE(AVL2.hasNode(h5) == false);
    }



    SECTION("Checking the getNode Method") {
        REQUIRE(AVL1.getNode(c) == c);
        REQUIRE(AVL1.getNode(g) == g);
        int g1 = 101;
        REQUIRE(AVL1.getNode(g1) == g1);
        int g3 = 102;
        REQUIRE_THROWS(AVL1.getNode(g3));
        REQUIRE(AVL2.getNode(a2) == a2);
        REQUIRE(AVL2.getNode(j2) == j2);
        std::string h3("iii");
        REQUIRE(AVL2.getNode(h3) == h3);
        std::string h4("III");
        REQUIRE_THROWS(AVL2.getNode(h4));
        std::string h5("iij");
        REQUIRE_THROWS(AVL2.getNode(h5));
    }



    SECTION("Checking the clearTree Method") {
        AVL1.clearTree();
        AVL2.clearTree();
        std::vector<int> v;
        AVL1.getInOrderVec(v);
        REQUIRE(v.size() == std::vector<int>().size());
        std::vector<std::string> v1;
        AVL2.getInOrderVec(v1);
        REQUIRE(v1.size() == std::vector<std::string>().size());
    }
}