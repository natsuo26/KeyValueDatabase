#include<iostream>
#include <ostream>
#include<vector>
#include<random>
#include"keyValueDatabase.h"
#include"CSVFileHandler.h"
#include"IFileHandler.h"

int main()
{
	KeyValueDatabase<int, int> db1{ {1,2},{3,4},{5,6} };
	KeyValueDatabase<int, std::string>db2{ {1,"ram"},{2,"sham"} };
	CSVFileHandler<int, int> fileHandler;
	std::cout<<db1.size();
	std::cout << "hello\n";
	return 0;
}