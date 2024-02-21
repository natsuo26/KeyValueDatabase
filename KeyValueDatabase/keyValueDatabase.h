#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include <unordered_map>
#include "SystemError.h"
#include "KeyNotFoundError.h"
#include "DuplicateKeyError.h"

template<typename KeyType, typename ValueType>
class KeyValueDatabase {
public:

    KeyValueDatabase() {
        try {
            auto temp = std::make_unique<std::unordered_map<KeyType, ValueType>>();
            if (temp) {
                database = std::move(temp);
            }
            else {
                throw SystemError(GetErrorMessageInContextWithErrorNumber());
            }
        }
        catch (SystemError& error) {
            std::wcerr << "Exception encountered: " << error.get_message();
        }
    }
    
    KeyValueDatabase(std::initializer_list<std::pair<KeyType, ValueType>> initList):KeyValueDatabase()
    {
        try {
            for (const auto& pair : initList) {
                if ((database->insert(pair)).second == false) {
                    throw SystemError(GetErrorMessageInContextWithErrorNumber());
                }
            }
        }
        catch (SystemError& error) {
            std::wcerr << "Exception encountered: " << error.get_message();
        }
    }

    inline void addValue(const KeyType& _key, const ValueType& _value) {
        try {
            if (database->find(_key) != database->end()) {
                throw DuplicateKeyError();
            }
            else if((database->insert(std::make_pair(_key, _value))).second==false)
            { 
                throw SystemError(GetErrorMessageInContextWithErrorNumber());
            }
        }
        catch (DuplicateKeyError& e) {
            std::wcerr<<e.wwhat();
        }
        catch (SystemError& error) {
            std::wcerr << "Exception encountered: "<<error.get_message();
        }
    }

    inline const ValueType retrieveValue(const KeyType& _key) const {
        try {
            auto iter = database->find(_key);
            if (iter == database->end()) {
                throw KeyNotFoundError();
            }
            return iter->second;
        }
        catch (KeyNotFoundError& e) {
            std::wcerr<<e.wwhat();
            return ValueType{};
        }
    }

    //update entry, returning success:true, fail:false.
    inline bool updateEntry(const KeyType& _key, const ValueType& _value) {
        try {
            auto iter = database->find(_key);
            if (iter == database->end()) {
                throw KeyNotFoundError();
            }
            iter->second = _value;
            return true;
        }
        catch (KeyNotFoundError& e) {
            std::wcerr<<e.wwhat();
        }
 
    }

     //deleting entry, returning success:true, fail:false.
    bool deleteEntry(const KeyType& _key) {
        try {
            auto iter = database->find(_key);
            if (iter == database->end()) {
                throw KeyNotFoundError();
            }
            database->erase(_key);
            return true;
        }
        catch (KeyNotFoundError& e) {
            std::wcerr<<e.wwhat();
            return false;
        }
    }

    typename std::unordered_map<KeyType, ValueType>::iterator begin() {
        if (database) {
            return database->begin();
        }
        throw SystemError(GetErrorMessageInContextWithErrorNumber());
    }

    typename std::unordered_map<KeyType, ValueType>::iterator begin() const {
        if (database) {
            return database->begin();
        }
        throw SystemError(GetErrorMessageInContextWithErrorNumber());
    }

    typename std::unordered_map<KeyType, ValueType>::iterator end() {
        if (database) {
            return database->end();
        }
        throw SystemError(GetErrorMessageInContextWithErrorNumber());
    }
    typename std::unordered_map<KeyType, ValueType>::iterator end() const{
        if (database) {
            return database->end();
        }
        throw SystemError(GetErrorMessageInContextWithErrorNumber());
    }

private:
    std::unique_ptr<std::unordered_map<KeyType, ValueType>> database;
};

