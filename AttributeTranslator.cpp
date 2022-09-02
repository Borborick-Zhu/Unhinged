//
//  AttributeTranslator.cpp
//  Project 4
//
//  Created by Borborick Zhu on 3/2/22.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "AttributeTranslator.h"
using namespace std;

AttributeTranslator::AttributeTranslator() {}

AttributeTranslator::~AttributeTranslator() {
}

bool AttributeTranslator::Load(string filename) {
    ifstream inFile(filename);
    if(inFile.is_open()) {
        string line;
        while(getline(inFile, line)) {
            if (line == "") {
                getline(inFile, line);
            }
            stringstream ss(line);
            string baseAttr, baseVal, compAttr, compVal;
            //import into the new variables that were made.
            getline(ss, baseAttr, ',');
            getline(ss, baseVal, ',');
            getline(ss, compAttr, ',');
            getline(ss, compVal, ',');
            
            string source = baseAttr + "," + baseVal;
    
            AttValPair temp(compAttr, compVal);
            
            if (m_attributeTranslator.search(source) == nullptr) {
                vector<AttValPair> curr;
                curr.push_back(temp);
                m_attributeTranslator.insert(source, curr);
            } else
                m_attributeTranslator.search(source)->push_back(temp);
        }
        inFile.close();
        return true;
    } else {
        return false;
    }
        
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair &source) const {
    string search = source.attribute + ',' + source.value;
    vector<AttValPair> temp;
    temp = *m_attributeTranslator.search(search);
    return temp;
}

