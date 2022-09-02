//
//  PersonsProfile.cpp
//  Project 4
//
//  Created by Borborick Zhu on 3/2/22.
//

#include <iostream>
#include "PersonProfile.h"
using namespace std;

PersonProfile::PersonProfile(string name, string email) {
    m_name = name;
    m_email = email;
    counter = 0;
}

PersonProfile::~PersonProfile() {
}

string PersonProfile::GetName() const {
    return m_name;
}

string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    
    string *temp = m_attributes.search(attval.attribute);
    
    if(temp != nullptr && *temp == attval.value)
        return;
    else {
        m_attributes.insert(attval.attribute, attval.value);
        m_vecAttr.push_back(attval);
        counter++;
    }
}

int PersonProfile::GetNumAttValPairs() const {
    return counter;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair &attval) const {
    //index starts from 0.
    if (attribute_num >= counter || attribute_num < 0) {
        return false;
    }
    attval = m_vecAttr[attribute_num];
    return true;
}
