//
//  parser.h
//  gtest
//
//  Created by 李家豪 on 2017/11/5.
//

#ifndef parser_h
#define parser_h

#include "scanner.h"
#include "variable.h"

class Parser {
private:
    Scanner _scanner;
    Symtable _table;
public:
    Parser(Scanner scanner) : _scanner(scanner) {}
    Term * createTerm() {
        int token = _scanner.nextToken();
        std :: vector<std :: pair<std :: string, int>>symtable = *_scanner.getSymtable();
        if(token == _table.VAR())
            return new Variable(symtable[_scanner.tokenValue()].first);
        else if(token == _table.NUMBER())
            return new Number(_scanner.tokenValue());
        else if(token == _table.ATOM() || token == _table.ATOMSC()) {
            Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
            if(_scanner.nextToken() == '(') {
                vector<Term*> terms = getArgs();
                if(_scanner.nextToken() == ')')
                    return new Struct(*atom, terms);
            } else {
                _scanner.backPosition();
                return atom;
            }
        } else if(token == '[') {
            if(_scanner.nextToken() == ']')
                return new List;
            _scanner.backPosition();
            vector<Term *>terms = getArgs();
            if(_scanner.nextToken() == ']')
                return new List(terms);
            throw string("unexpected token");
        }
        return nullptr;
    }
    vector<Term*> getArgs() {
        Term* term = createTerm();
        vector<Term*> args;
        if(term)
            args.push_back(term);
        while((_scanner.nextToken()) == ',')
            args.push_back(createTerm());
        _scanner.backPosition();
        return args;
    }
};

#endif /* parser_h */
