//
//  list.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef list_h
#define list_h

#include "term.h"
#include <vector>

class List : public Term {
private:
    std :: vector<Term *>_elements;
public:
    List() : _elements() {}
    List(std :: vector<Term *>elements) : _elements(elements) {}
    List * getList() { return this; }
    string symbol() {
        if(_elements.empty())
            return "[]";
        string result = "[";
        std :: vector<Term *> :: iterator it;
        for(it = _elements.begin(); it != _elements.end() - 1; it++)
            result += ((*it)->symbol() + ", ");
        return result += ((*(_elements.end() - 1))->symbol() + "]");
    }
    string value() {
        if(_elements.empty())
            return "[]";
        string result = "[";
        std :: vector<Term *> :: iterator it;
        for(it = _elements.begin(); it != _elements.end() - 1; it++)
            result += ((*it)->value() + ", ");
        return result += ((*(_elements.end() - 1))->value() + "]");
    }
    bool match(Term &term) {
        List *pl = term.getList();
        Variable *pv = term.getVariable();
        if(pl) {
            if(_elements.size() != pl->_elements.size())
                return false;
            for(int i = 0; i < _elements.size(); i++)
                if(!_elements[i]->match(*(pl->_elements[i]))) {
                    return false;
                }
            return true;
        }
        if(pv)
            return pv->match(*this);
        return false;
    }
    Term * head() {
        if(_elements.empty())
            throw string("Accessing head in an empty list");
        return _elements[0];
    }
    List * tail() {
        if(_elements.empty())
            throw string("Accessing tail in an empty list");
        std :: vector<Term *>ret(_elements.begin() + 1, _elements.end());
        return new List(ret);
    }
};

#endif /* list_h */
