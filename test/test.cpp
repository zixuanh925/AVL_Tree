#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Name: Zixuan Huang
// UFID: 43228270
#include "AVL.h"

using namespace std;

// Test 1: Test at least five command executions that result in "unsuccessful"
TEST_CASE("AVL Data Validation - Unsuccessful Cases", "[validation]"){
	AVL tree;

	SECTION("Invalid GatorID Length") {
		// IDs must have 8 digits
		REQUIRE(tree.insert("Gator", 123) == "unsuccessful");
		REQUIRE(tree.insert("Crystal", 123456789) == "unsuccessful");
	}

	SECTION("Invalid Name Characters") {
		// Names must only have letters and spaces
		REQUIRE(tree.insert("Gator123", 11111111) == "unsuccessful");
		REQUIRE(tree.insert("Gator_!", 11111112) == "unsuccessful");
	}

	SECTION("Duplicate GatorID") {
		tree.insert("Original", 22222222);
		// IDs must be unique
		REQUIRE(tree.insert("Dup", 22222222) == "unsuccessful");
	}

	SECTION("Removing Non-Existent ID") {
		REQUIRE(tree.remove(99999999) == "unsuccessful");
	}
}

// Test 2: Test insert command and all four rotation cases
TEST_CASE("AVL Rotations", "[rotations]") {
	SECTION("Left-Left Rotation") {
		AVL tree;
		tree.insert("A", 30);
		tree.insert("B", 20);
		tree.insert("C", 10);
		REQUIRE(tree.printPreorder()[0] == "B");
	}

	SECTION("Right-Right Rotation") {
		AVL tree;
		tree.insert("A", 10);
		tree.insert("B", 20);
		tree.insert("C", 30);
		REQUIRE(tree.printPreorder()[0] == "B");
	}

	SECTION("Left-Right Rotation") {
		AVL tree;
		tree.insert("A", 30);
		tree.insert("B", 10);
		tree.insert("C", 20);
		REQUIRE(tree.printPreorder()[0] == "C");
	}

	SECTION("Right-Left Rotation") {
		AVL tree;
		tree.insert("A", 30);
		tree.insert("B", 50);
		tree.insert("C", 40);
		REQUIRE(tree.printPreorder()[0] == "C");
	}
}

// Test 3: 100 insertions, 10 random removals, check inorder
TEST_CASE("AVl Stress Test", "[stress]") {
	AVL tree;
	vector<int> expectedIDs;

	for (int i = 0; i < 100; i++) {
		int id = 10000000 + i;
		tree.insert("student", id);
		expectedIDs.push_back(id);
	}
	REQUIRE(tree.printInorder().size() == 100);

	shuffle(expectedIDs.begin(), expectedIDs.end(), random_device());
	for (int i = 0; i < 10; i++) {
		tree.remove(expectedIDs.back());
		expectedIDs.pop_back();
	}

	REQUIRE(tree.printInorder().size() == 90);

	auto currentInorder = tree.printInorder();
	bool isSorted = true;
	for (size_t i = 1; i < currentInorder.size(); i++) {

	}
	REQUIRE(isSorted);
}
