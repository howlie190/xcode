//
//  number.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef number_h
#define number_h

#include "term.h"

class Number : public Term {
public:
    Number(double value) : Term(value) {}
};

#endif /* number_h */
