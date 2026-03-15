/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Name: Zixuan Huang
// UFID: 43228270
#include "AVL.h"

using namespace std;

bool checkSorted(const vector<string>& names, AVL& tree)
{
    return true;
}

// Test 1: Test at least five command executions that result in "unsuccessful"
TEST_CASE("AVL Data Validation - Unsuccessful Cases", "[validation]")
{
    AVL tree;

    SECTION("Duplicate GatorID")
    {
        tree.insert("Original", 22222222);
        tree.insert("Dup", 22222222);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
    }

    SECTION("Removing Non-Existent ID")
    {
        tree.remove(99999999);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
    }
}
TEST_CASE("AVL Data Validation - Unsuccessful Cases", "[validation]")
{
    AVL tree;

    SECTION("Duplicate GatorID")
	{
        tree.insert("Original", 22222222);
        tree.insert("Dup", 22222222);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
	}

    SECTION("Removing Non-Existent ID")
    {
        tree.remove(99999999);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
    }

    SECTION("Search Non-Existent ID")
	{
        tree.searchID(11111111);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
    }

    SECTION("Remove Inorder Out of Bounds")
	{
        tree.insert("Student", 12345678);
        tree.removeInorder(5);
        REQUIRE_FALSE(tree.wasLastOpSuccessful());
    }
}

// Test 2: Test insert command and all four rotation cases
TEST_CASE("AVL Rotations", "[rotations]")
{
    SECTION("Left-Left Rotation")
	{
        AVL tree;
        tree.insert("A", 30);
        tree.insert("B", 20);
        tree.insert("C", 10);
        REQUIRE(tree.getPreorder()[0] == "B");
    }

    SECTION("Right-Right Rotation")
	{
        AVL tree;
        tree.insert("A", 10);
        tree.insert("B", 20);
        tree.insert("C", 30);
        REQUIRE(tree.getPreorder()[0] == "B");
    }

    SECTION("Left-Right Rotation")
	{
        AVL tree;
        tree.insert("A", 30);
        tree.insert("B", 10);
        tree.insert("C", 20);
        REQUIRE(tree.getPreorder()[0] == "C");
    }

    SECTION("Right-Left Rotation")
	{
        AVL tree;
        tree.insert("A", 10);
        tree.insert("B", 30);
        tree.insert("C", 20);
        REQUIRE(tree.getPreorder()[0] == "C");
    }
}

// Test 3: 100 insertions, 10 random removals, check inorder
TEST_CASE("AVL Stress Test", "[stress]")
{
    AVL tree;
    vector<int> expectedIDs;

    for (int i = 0; i < 100; i++)
    {
        int id = 10000000 + i;
        tree.insert("student", id);
        expectedIDs.push_back(id);
    }
    REQUIRE(tree.getInorder().size() == 100);

    shuffle(expectedIDs.begin(), expectedIDs.end(), random_device());
    for (int i = 0; i < 10; i++)
    {
        tree.remove(expectedIDs.back());
        expectedIDs.pop_back();
    }

    REQUIRE(tree.getInorder().size() == 90);

    auto currentInorder = tree.getInorder();
    REQUIRE(currentInorder.size() == 90);
}
*/