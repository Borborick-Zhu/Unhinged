//
//  MemberDatabase.cpp
//  Project 4
//
//  Created by Borborick Zhu on 3/3/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "MemberDatabase.h"
using namespace std;

MemberDatabase::MemberDatabase() {
    
}

MemberDatabase::~MemberDatabase() {
    for(int i = 0; i < deletionTree.size(); i++) {
        if (deletionTree[i] != nullptr) {
            delete deletionTree[i];
        }
    }
}

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream inFile(filename);
    if (!inFile) {
        return false;
    }
    string line;
    while(inFile.peek() != EOF) {
        string name, email, attributeNumber;
        getline(inFile, name);
        if (name == "") {
            continue;
        }  else {
            getline(inFile, email);
            getline(inFile, attributeNumber);
            
            PersonProfile* temp = new PersonProfile(name, email);
            for (int i = 0 ; i < stoi(attributeNumber); i++) {
                string attribute, value;
                string attValPair;
                getline(inFile, attValPair);
                attribute = attValPair.substr(0, attValPair.find(','));
                value = attValPair.substr(attValPair.find(',') + 1);
                temp->AddAttValPair(AttValPair(attribute, value));
                
                //insertion for the attributeTree
                string avpInput = attribute + "," + value;
                // if the attribute value pair does not exist.
                if (attributeTree.search(avpInput) == nullptr) {
                    //create a new list of strings and add that.
                    vector<string> temp;
                    temp.push_back(email);
                    attributeTree.insert(avpInput, temp);
                    comparison.insert(email);
                } else {
                    //insert only if its unique
                    long size = comparison.size();
                    comparison.insert(email);
                    if (comparison.size() == size) {
                        attributeTree.search(avpInput)->push_back(email);
                    }
                }
            }
            profileTree.insert(email, temp);
            deletionTree.push_back(temp);
        }
        
    }
    inFile.close();
    return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    string srcInput = input.attribute + "," + input.value;
    vector<string> temp;
    if (attributeTree.search(srcInput) == nullptr) {
        return temp;
    } else {
        return *(attributeTree.search(srcInput));
    }
    
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {
    if (profileTree.search(email) == nullptr) {
        return nullptr;
    } else {
        return *(profileTree.search(email));
    }
    
}
