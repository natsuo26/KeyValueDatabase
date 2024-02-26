#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include <unordered_map>
#include "SystemError.h"
#include "KeyNotFoundError.h"
#include "DuplicateKeyError.h"

template<typename KeyType, typename ValueType>
class KeyValueDatabase final {
public:

    using MapType = std::unordered_map<KeyType, ValueType>;
    KeyValueDatabase() {
        try {
            auto temp = std::make_unique<MapType>();
            if (temp) {
                database = std::move(temp);
            }
            else {
                throw SystemError(GetErrorMessageInContextWithErrorNumber());
            }
        }
        catch (SystemError& error) {
            std::wcerr << L"SystemError encountered: " << error.get_message();
        }
        catch (std::exception& error) {
            std::wcerr << error.what() << std::endl;
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

    inline bool addValue(const KeyType& _key, const ValueType& _value) {
        try {
            if (database->find(_key) != database->end()) {
                throw DuplicateKeyError();
            }
            else if((database->insert(std::make_pair(_key, _value))).second==false)
            { 
                throw SystemError(GetErrorMessageInContextWithErrorNumber());
            }
            return true;
        }
        catch (DuplicateKeyError& error){
            std::wcerr<< error.wwhat();
            return false;
        }
        catch (SystemError& error) {
            std::wcerr << L"Exception encountered: "<<error.get_message();
            return false;
        }
        catch (std::exception& error) {
            std::cerr << error.what() << std::endl;
        }
        return false;
    }

    inline const ValueType retrieveValue(const KeyType& _key) const {
        try {
            auto iter = database->find(_key);
            if (iter == database->end()) {
                throw KeyNotFoundError();
            }
            return iter->second;
        }
        catch (KeyNotFoundError& error) {
            std::wcerr << error.wwhat();
            return ValueType{};
        }
        catch (std::exception& error) {
            std::cerr << error.what() << std::endl;
            return ValueType{};
        }
    }

    inline long long size() {
        return database->size();
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
        catch (KeyNotFoundError& error) {
            std::wcerr << error.wwhat();
        }
        catch (std::exception& error) {
            std::cerr << error.what() << std::endl;
        }
        return false;
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
        catch (KeyNotFoundError& error) {
            std::wcerr<<error.wwhat();
            return false;
        }
        catch (std::exception& error) {
            std::cerr << error.what();
        }
        return false;
    }
 
    typename MapType::iterator begin() {
        return database->begin();
    }

    typename MapType::iterator begin() const {
        return database->begin();
    }

    typename MapType::iterator end() {
        return database->end();
    }
    typename MapType::iterator end() const{
        return database->end();
    }
    virtual ~KeyValueDatabase() = default;
private:
    std::unique_ptr<MapType> database;
};