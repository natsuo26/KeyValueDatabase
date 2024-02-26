#include "pch.h"
#include "KeyValueDatabaseTest.h"

TEST_F(KeyValueDatabaseTest, insertTest) {
	ASSERT_EQ(databasePtr->size(), 0);
	ASSERT_TRUE(databasePtr->addValue(1, 1));
	ASSERT_EQ(databasePtr->size(), 1);
	ASSERT_FALSE(databasePtr->addValue(1, 1));
	ASSERT_EQ(databasePtr->size(), 1);
}

TEST_F(KeyValueDatabaseTest, updateTest) {
	databasePtr->addValue(1, 10);
	ASSERT_TRUE(databasePtr->updateEntry(1, 10));
	ASSERT_FALSE(databasePtr->updateEntry(2, 10));
}

TEST_F(KeyValueDatabaseTest, retreivalTest) {
	databasePtr->addValue(20, 30);
	databasePtr->addValue(21, 24);
	databasePtr->addValue(22, 57);
	ASSERT_EQ(databasePtr->retrieveValue(20), 30);
	ASSERT_EQ(databasePtr->retrieveValue(22), 57);
}

TEST_F(KeyValueDatabaseTest, deleteTest) {
	databasePtr->addValue(20, 30);
	databasePtr->addValue(21, 24);
	databasePtr->addValue(22, 57);
	ASSERT_TRUE(databasePtr->deleteEntry(20));
	ASSERT_FALSE(databasePtr->deleteEntry(0));
}