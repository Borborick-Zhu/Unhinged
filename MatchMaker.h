//
//  MatchMaker.h
//  Project 4
//
//  Created by Borborick Zhu on 3/3/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* memberdb;
    const AttributeTranslator* att;
};
#endif /* MatchMaker_h */
