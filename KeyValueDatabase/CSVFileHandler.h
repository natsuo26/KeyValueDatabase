#pragma once
#include<string>
#include<sstream>
#include "IFileHandler.h"
#include "FileIOError.h"

template<typename KeyType, typename ValueType>
class CSVFileHandler : public IFileHandler<KeyType,ValueType> {
public:
    bool readFromFile(const std::string& filename, KeyValueDatabase<KeyType, ValueType>& db) override {
        try {
            std::ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                throw FileIOError();
            }
            std::string line;
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                std::string key, value;
                if (std::getline(iss, key, ',') && std::getline(iss, value)) {
                    KeyType k = convertToKeyType(key); // Convert string to KeyType
                    ValueType v = convertToValueType(value); // Convert string to ValueType
                    db.addValue(k,v);
                }
            }
            inputFile.close();
            return true;
        }
        catch (const FileIOError& e) {
            std::cerr<<e.what()<< "Error opening file: " << filename << std::endl;
            return false;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception encountered while reading from file: " << e.what() << std::endl;
            return false;
        }
    }
    bool writeToFile(const std::string& filename, const KeyValueDatabase<KeyType, ValueType>& db) override {
        try {
            std::ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                throw FileIOError();
            }

            for (const auto& pair : db) {
                outputFile << pair.first << "," << pair.second << std::endl;
            }

            outputFile.close();
            return true;
        }
        catch (const FileIOError& e) {
            std::cerr << e.what() << "Error opening file: " << filename << std::endl;
            return false;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception encountered while writing to file: " << e.what() << std::endl;
            return false;
        }
    }

private:
    KeyType convertToKeyType(const std::string& key) {
        std::istringstream iss(key);
        KeyType result;
        iss >> result;
        return result;
    }
    ValueType convertToValueType(const std::string& value) {
        std::istringstream iss(value);
        ValueType result;
        iss >> result;
        return result;
    }
};