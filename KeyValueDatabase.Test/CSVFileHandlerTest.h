#pragma once
#include"stdafx.h"

class CSVFileHandlerTest : public ::testing::Test
{
protected:
    void CSVFileHandlerTest::SetUp() override {
        // Initialize the KeyValueDatabase
        database.addValue(1, 100);
        database.addValue(2, 200);

    }
    void CSVFileHandlerTest::TearDown() override {
        std::remove("test.csv");
    }

    KeyValueDatabase<int, int> database;
    CSVFileHandler<int, int> fileHandler;
};
