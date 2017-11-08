//
//  struct.cpp
//  POSD
//
//  Created by 李家豪 on 2017/11/4.
//
#ifndef struct_h
#define struct_h

#include <vector>
#include "term.h"
#include "atom.h"

class Struct : public Term {
private:
    Atom _name;
    std :: vector<Term *>_args;
public:
    Struct(Atom name, std :: vector<Term *>args) : _name(name), _args(args) {}
    Struct(Atom name) : _name(name), _args() {}
    Struct * getStruct() { return this; }
    int arity() { return (int)_args.size(); }
    Term * args(int index) { return _args[index]; }
    Atom name() { return _name; }
    string symbol() {
        if(_args.empty())
            return _name.symbol() + "()";
        string result = _name.symbol() + "(";
        std :: vector<Term *> :: iterator it = _args.begin();
        for(it = _args.begin(); it != _args.end() - 1; it++)
            result += ((*it)->symbol() + ", ");
        return result += ((*(_args.end() - 1))->symbol() + ")");
    }
    string value() {
        if(_args.empty())
            return _name.symbol() + "()";
        string result = _name.symbol() + "(";
        std :: vector<Term *> :: iterator it = _args.begin();
        for(it = _args.begin(); it != _args.end() - 1; it++)
            result += ((*it)->value() + ", ");
        return result += ((*(_args.end() - 1))->value() + ")");
    }
};

#endif
