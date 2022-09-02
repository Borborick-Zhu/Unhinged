//
//  RadixTree.h
//  Project 4
//
//  Created by Borborick Zhu on 3/2/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <iostream>
#include <vector>
#include <algorithm>


template <typename ValueType>
class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    struct Node {
        Node (std::string key, bool end) {
            m_key = key;
            endOfKey = end;
        }
        
        
        std::string m_key;
        ValueType v;
        bool endOfKey;
        Node* children[128];
    };
    
    Node* m_root;
    bool nothingAfter(Node *curr) {
        for(int i = 0; i < 128; i++) {
            if (curr->children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }
    void initializeChildrentoNull(Node *&curr) {
        for(int i = 0; i < 128; i++) {
            curr->children[i] = nullptr;
        }
        return;
    }
    
    void insertChild(std::string key, const ValueType& value, Node* &curr);
    ValueType* searchForValue(std::string key, Node* &curr) const;
    
    void deleteNode(Node* &curr) {
        for(int i = 0; i < 128; i++) {
            if (curr->children[i] == nullptr) {
                continue;
            } else {
                deleteNode(curr->children[i]);
            }
        }
        
        delete curr;
    }
};

template <typename ValueType> inline
RadixTree<ValueType>::RadixTree() {
    m_root = nullptr;
}

template <typename ValueType> inline
RadixTree<ValueType>::~RadixTree() {
    deleteNode(m_root);
//    std::cerr << "destructor called" << std::endl;
}

template <typename ValueType> inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
    if (key == "")
        return;
    
    int pos = key[0];
    //std::cerr << "pos: " << pos << std::endl;
    if (m_root == nullptr) {
        //case 1: create a new node.
        Node *rootNode = new Node("", false);
        initializeChildrentoNull(rootNode);
        m_root = rootNode;
    }
    ValueType copyOfValue = value;
    insertChild(key, copyOfValue, m_root->children[pos]);
}

template <typename ValueType> inline
void RadixTree<ValueType>::insertChild(std::string key, const ValueType& value, Node* &curr) {
    //case 1.
    if (curr == nullptr) {
        //create a new node and insert.
        Node *temp = new Node(key, true);
        initializeChildrentoNull(temp);
        curr = temp;
        curr->v = value;
        curr->endOfKey = true;
        return;
    }
    
    //find the matching position.
    int matchPos = 0;
    for (;matchPos < curr->m_key.length(); matchPos++) {
        if (key[matchPos] != curr->m_key[matchPos]) {
            break;
        }
    }
    
    std::string comparisonKey = key.substr(0, matchPos);
    std::string checkKey = key;
    key = key.substr(matchPos, key.length() - matchPos);
    if (checkKey == curr->m_key) { //check
        //match was found and do not insert anything.
        //std::cerr << "return called" << std::endl;
        curr->v = value;
        curr->endOfKey = true;
        return;
    } else if (comparisonKey == curr->m_key && !nothingAfter(curr) && comparisonKey.length() < checkKey.length()) {
        //change the length of the key.
        //std::cerr << "recursing #1" << std::endl;
        int pos = key[0];
        return insertChild(key, value, curr->children[pos]);
    } else if (comparisonKey == curr->m_key && nothingAfter(curr) && comparisonKey.length() < checkKey.length()) {
        // we want to insert one smaller node after. Most of it matches but this is now the end node.
        Node *temp = new Node(key, curr->endOfKey);
        initializeChildrentoNull(temp);
        temp->v = value;
        int pos = key[0];
        curr->children[pos] = temp;
        return;
    } else if (matchPos < curr->m_key.length()){
        //key = the substring key.
        //comparisonKey = the start of the substring key.
        //checkkey = the actual key without doing anything.
        //temp is the new node that is made from curr.
        std::string temp = curr->m_key;
        temp = curr->m_key.substr(matchPos, curr->m_key.length() - matchPos);
        // this takes the c.
        if (temp != "") {
            //inserting in the middle.
            Node *newCurr = new Node (temp, curr->endOfKey);
            initializeChildrentoNull(newCurr);
            if (newCurr->endOfKey) {
                newCurr->v = curr->v;
            }
            
            for (int i = 0; i < 128; i++) {
                newCurr->children[i] =  curr->children[i];
            }
            initializeChildrentoNull(curr);
            
            int pos = temp[0];
            curr->children[pos] = newCurr;
            curr->m_key = comparisonKey;
            if (curr->endOfKey)
                curr->endOfKey = false;
            
            // change the current key.
            if (key == "") {
                curr->v = value;
                curr->endOfKey = true;
            } else {
                // now create the new node that you are trying to insert.
                Node *secondInsert = new Node (key, true);
                initializeChildrentoNull(secondInsert);
                int pos2 = key[0];
                curr->children[pos2] = secondInsert;
                secondInsert->v = value;
                return;
            }
        }
    }
}


template <typename ValueType> inline
ValueType* RadixTree<ValueType>::search(std::string key) const {
    int pos = key[0];
    if (m_root != nullptr) {
        return searchForValue(key, m_root->children[pos]);
    }
    return nullptr;
}

template <typename ValueType> inline
ValueType* RadixTree<ValueType>::searchForValue(std::string key, Node* &curr) const {

    if (curr == nullptr)
        return nullptr;

    int matchPos = 0;
    for (; matchPos < curr->m_key.length(); matchPos++) {
        if (key[matchPos] != curr->m_key[matchPos])
            break;
    }
    key = key.substr(matchPos, key.length() - matchPos);
    if (matchPos == curr->m_key.length() && curr->endOfKey && key == "")
        return &(curr->v);

    
    int pos = key[0];
    return searchForValue(key, curr->children[pos]);
}

#endif /* RadixTree_h */
