//
//  AttributeTranslator.h
//  Project 4
//
//  Created by Borborick Zhu on 3/2/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include "provided.h"
#include <vector>
#include "RadixTree.h"

class AttributeTranslator {
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<std::vector<AttValPair>> m_attributeTranslator;
};

#endif /* AttributeTranslator_h */
