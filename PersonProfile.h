//
//  PersonsProfile.h
//  Project 4
//
//  Created by Borborick Zhu on 3/2/22.
//

#ifndef PersonsProfile_h
#define PersonsProfile_h
#include "provided.h"
#include "RadixTree.h"
#include <vector>
#include <set>
class PersonProfile {
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    int counter;
    
    std::vector<AttValPair> m_vecAttr;
    RadixTree<std::string> m_attributes;
};

#endif /* PersonsProfile_h */

