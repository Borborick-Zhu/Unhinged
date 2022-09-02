//
//  MatchMaker.cpp
//  Project 4
//
//  Created by Borborick Zhu on 3/3/22.
//

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <algorithm>
#include "MatchMaker.h"
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase &mdb, const AttributeTranslator& at)
{
    memberdb = &mdb;
    att = &at;
}

MatchMaker::~MatchMaker() {
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const {
    vector<EmailCount> returnEmail;
    const PersonProfile *personToMatch = memberdb->GetMemberByEmail(email);
    AttValPair compare;
    map<string, int> mapTing;
    
    for (int i = 0; i < personToMatch->GetNumAttValPairs(); i++) {
        //get each attribute of the email person.
        personToMatch->GetAttVal(i, compare);
        // now get the vector of matching attvalpairs.
        vector<AttValPair> compatiblePairs = att->FindCompatibleAttValPairs(compare);
        // now find all the people who have the compatible pairs.
        for (int i = 0; i < compatiblePairs.size(); i++) {
            vector<string> emailsMatchingMembers = memberdb->FindMatchingMembers(compatiblePairs[i]);
            //cerr << emailsMatchingMembers[2] << endl;
            
            //import all the emails into a map of ints - maps strings to ints.
            for (vector<string>::iterator it = emailsMatchingMembers.begin(); it != emailsMatchingMembers.end(); it++) {
                if (mapTing.find(*it)->first  == *it) {
                    //the string/email is equal to the string/email in the iterator.
                    mapTing.find(*it)->second++;
                } else {
                    mapTing[*it] = 1;
                }
            }
            // this returns a vector of matching emails.
            // now, need to systematically count all the matching people.
        }
    }
    int maxValue = personToMatch->GetNumAttValPairs();
    map<string, int>::iterator it = mapTing.begin();
    while (maxValue >= threshold) {
        EmailCount temp(it->first, it->second);
        if (it->second == maxValue) {
            returnEmail.push_back(temp);
            it = mapTing.erase(it);
            if (it == mapTing.end()) {
                it = mapTing.begin();
                maxValue--;
            }
        } else {
            it++;
            if (it == mapTing.end()) {
                it = mapTing.begin();
                maxValue--;
            }
        }
    }
//    for (map<string, int>::iterator it = mapTing.begin(); maxValue >= threshold;) {
//        EmailCount temp(it->first, it->second);
//        if (it == mapTing.end()) {
//            //reset the iterator.
//            it = mapTing.begin();
//            maxValue--;
//        }
//
//        if (it->second == maxValue) {
//            returnEmail.push_back(temp);
//            it = mapTing.erase(it);
//        } else {
//            it++;
//        }
//    }
    
    return returnEmail;
}
