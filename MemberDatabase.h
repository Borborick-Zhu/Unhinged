//
//  MemberDatabase.h
//  Project 4
//
//  Created by Borborick Zhu on 3/3/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h
#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include <vector>
#include <set>

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<std::vector<std::string>> attributeTree;
    RadixTree<PersonProfile*> profileTree;
    std::set<std::string> comparison;
    std::vector<PersonProfile*> deletionTree;
};
#endif /* MemberDatabase_h */
