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
        REQUIRE(n1->getData() == 1);
        REQUIRE(n2->getData() == 1);
        REQUIRE(n3->getData() == 2);
        REQUIRE((*n2=2).getData() == 2);
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