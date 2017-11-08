//
//  term.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef term_h
#define term_h

#include <string>
#include <sstream>

using std :: string;

class Variable;
class List;
class Struct;
class Term {
protected:
    string _symbol;
    Term(string symbol) : _symbol(symbol) {}
    Term() : _symbol() {}
    Term(double value) {
        std :: stringstream ss;
        ss << value;
        _symbol = ss.str();
    }
public:
    virtual string symbol() { return _symbol; }
    virtual string value() { return symbol(); }
    virtual Variable * getVariable() { return 0; }
    virtual List * getList() { return 0; }
    virtual Struct * getStruct() { return 0;}
    virtual bool match(Term &term);
};

#endif /* term_h */
