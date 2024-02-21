#include<iostream>
#include<vector>
#include"keyValueDatabase.h"
#include"IOHandler.h"

int main() {
    KeyValueDatabase<int,int> d1;
    KeyValueDatabase<std::string, int> si1;
    si1.addValue("abhay", 3469);
    si1.addValue("abhay2", 3454);

    std::wcout << si1.retrieveValue("abhay") << std::endl;;

    si1.deleteEntry("abhay");
    
    std::wcout << si1.retrieveValue("abhay") << std::endl;



    return 0;
}