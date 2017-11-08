//
//  scanner.h
//  gtest
//
//  Created by 李家豪 on 2017/11/5.
//

#ifndef scanner_h
#define scanner_h

#include "symtable.h"
#include <string>

class Scanner {
private:
    Symtable _table;
    string _buffer;
    int _position;
    int _tokenValue;
    template<int TokenType>
    void processToken(string const &s) {
        int val = -1;
        if(_table.symbolExist(s, val)) {
            _tokenValue = val;
        } else {
            _table.getSymtable()->push_back(std :: pair<std :: string, int>(s, TokenType));
            _tokenValue = (int)(_table.getSymtable()->size() - 1);
        }
    }
public:
    Scanner(std :: string in = "") : _buffer(in), _position(0), _tokenValue(_table.NONE()) {}
    void setInput(std :: string in) { _buffer = in; }
    int tokenValue() const { return _tokenValue; }
    int position() { return _position; }
    char currentChar() { return _buffer[_position]; }
    int nextToken() {
        if(skipLeadingWhiteSpace() >= _buffer.length())
            return _table.EOS();
        else if(isdigit(currentChar())) {
            _tokenValue = extractNumber();
            return _table.NUMBER();
        } else if(islower(currentChar())) {
            std :: string s = extractAtom();
            processToken<257>(s);
            return _table.ATOM();
        } else if(_table.isSpecialCh(currentChar())) {
            std :: string s = extractAtomSC();
            processToken<258>(s);
            return _table.ATOMSC();
        } else if(isupper(currentChar()) || currentChar() == '_') {
            std :: string s = extractVar();
            processToken<259>(s);
            return _table.VAR();
        } else {
            _tokenValue = _table.NONE();
            return extractChar();
        }
    }
    int skipLeadingWhiteSpace() {
        for(; (_buffer[_position] == ' ' || _buffer[_position] == '\t') && _position < _buffer.length(); ++_position);
        return position();
    }
    int extractNumber() {
        int posBegin = position();
        for(; isdigit(_buffer[_position]); ++_position);
        return stoi(_buffer.substr(posBegin, _position - posBegin));
    }
    std :: string extractAtom() {
        int posBegin = position();
        for(; isalnum(_buffer[_position]); ++_position);
        return _buffer.substr(posBegin, _position - posBegin);
    }
    std :: string extractAtomSC() {
        int posBegin = position();
        for(; _table.isSpecialCh(_buffer[_position]); ++_position);
        return _buffer.substr(posBegin, _position - posBegin);
    }
    std :: string extractVar() {
        int posBegin = position();
        for(; isalnum(_buffer[_position]) || _buffer[_position] == '_'; ++_position);
        return _buffer.substr(posBegin, _position - posBegin);
    }
    char extractChar() { return _buffer[_position++]; }
    std :: vector<std :: pair<std :: string, int>> * getSymtable() { return _table.getSymtable(); }
    void backPosition() { _position--; }
};

#endif /* scanner_h */
