#pragma once
#include<fstream>

template<typename KeyType, typename ValueType>
class IOHandler {
public:
    static bool readFromFile(const std::string& filename, KeyValueDatabase<KeyType, ValueType>& db) {
        try {
            std::ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                std::cerr << L"Error opening file: " << filename << std::endl;
                return false;
            }

            //KeyType key;
            //ValueType value;
            //while (true)
            //{
            //    string key, value;
            //    //try to read key, if there is none, break
            //    if (!getline(openFile, key, ',')) break;
            //    //read value
            //    getline(openFile, value, '\n');
            //    mymap[key] = value;
            //    cout << key << ":" << value << endl;
            //}
            //while (inputFile >> key >> value) {
            //    db.insert({ key, value });
            //}
            //correct implementation is yet to be implemented.


            inputFile.close();
            return true;
        }
        catch (const std::exception& e) {
            std::wcerr << L"Exception encountered while reading from file: " << e.what() << std::endl;
            return false;
        }
    }

    // Write data from the KeyValueDatabase to a file
    static bool writeToFile(const std::string& filename, const KeyValueDatabase<KeyType, ValueType>& db) {
        try {
            std::ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                std::cerr << L"Error opening file: " << filename << std::endl;
                return false;
            }

            for (const auto& pair : db) {
                outputFile << pair.first << "," << pair.second << std::endl;
            }

            outputFile.close();
            return true;
        }
        catch (const std::exception& e) {
            std::wcerr << L"Exception encountered while writing to file: " << e.what() << std::endl;
            return false;
        }
    }
    //typedef std::ostream& operator<<(std::ostream& os, const ValueType::iterator& it) {
    //    for (auto& x : it) {
    //        os << x;
    //    }
    //    return os;
    //}
};
