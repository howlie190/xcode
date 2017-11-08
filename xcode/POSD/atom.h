//
//  atom.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef atom_h
#define atom_h

#include "term.h"

class Atom : public Term {
public:
    Atom(string symbol) : Term(symbol) {}
};

#endif /* atom_h */
