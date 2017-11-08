//
//  term.cpp
//  POSD
//
//  Created by 李家豪 on 2017/11/4.
//

#include "term.h"
#include "variable.h"

bool Term :: match(Term &term) {
    Variable *pv = term.getVariable();
    if(pv)
        return pv->match(*this);
    return symbol() == term.symbol();
}
