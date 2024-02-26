#include "pch.h"
#include "CSVFileHandlerTest.h"


// Test case for reading from a CSV file
TEST_F(CSVFileHandlerTest, ReadFromFile) {
    // Write some data to a test CSV file
    std::ofstream testFile("test.csv");
    testFile << "1,100\n";
    testFile << "2,200\n";
    testFile.close();

    // Read from the test CSV file
    EXPECT_TRUE(fileHandler.readFromFile("test.csv", database));

    // Verify that the database contains the expected values
    EXPECT_EQ(database.retrieveValue(1), 100);
    EXPECT_EQ(database.retrieveValue(2), 200);
}

// Test case for writing to a CSV file
TEST_F(CSVFileHandlerTest, WriteToFile) {
    // Write the database contents to a test CSV file
    EXPECT_TRUE(fileHandler.writeToFile("test.csv", database));

    // Read from the test CSV file and verify its contents
    std::ifstream testFile("test.csv");
    int key, value;
    testFile >> key;
    char ch;
    testFile >> ch;
    testFile >> value;
    EXPECT_EQ(key, 1);
    EXPECT_EQ(value, 100);
    testFile >> key;
    testFile >> ch;
    testFile >> value;
    EXPECT_EQ(key, 2);
    EXPECT_EQ(value, 200);
}