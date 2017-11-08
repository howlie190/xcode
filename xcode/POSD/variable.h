//
//  variable.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef variable_h
#define variable_h

#include "term.h"

class Variable : public Term {
private:
    Term *_ref = nullptr;
public:
    Variable(string symbol) : Term(symbol) {}
    Variable * getVariable() { return this; }
    string value() {
        if(_ref)
            return _ref->value();
        return Term :: value();
    }
    bool match(Term &term) {
        if(this == &term)
            return true;
        if(!_ref) {
            _ref = &term;
            return true;
        }
        return _ref->match(term);
    }
};

#endif /* variable_h */
