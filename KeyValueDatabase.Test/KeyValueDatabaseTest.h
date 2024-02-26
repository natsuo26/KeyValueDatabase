#pragma once
#include "stdafx.h"

class KeyValueDatabaseTest :public ::testing::Test
{
protected:
	void KeyValueDatabaseTest::SetUp() override {
		// Initialize the KeyValueDatabase
		databasePtr = std::make_unique<KeyValueDatabase<int, int>>();
	}
	void KeyValueDatabaseTest::TearDown() override {
		// Clean up
		databasePtr.reset();
	}
	std::unique_ptr<KeyValueDatabase<int, int>> databasePtr;
};

