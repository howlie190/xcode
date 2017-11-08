//
//  utTest.h
//  gtest
//
//  Created by 李家豪 on 2017/11/4.
//

#ifndef utTest_h
#define utTest_h

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "parser.h"
#include "scanner.h"
Scanner scanner;
class parserTest : public :: testing :: Test {
protected:
    void SetUp() {
        scanner.getSymtable()->clear();
    }
};

TEST(Atom, atomTesting) {
    Atom tom("tom"), jerry("jerry");
    ASSERT_EQ("tom", tom.symbol());
    ASSERT_FALSE(tom.match(jerry));
}
TEST(Number, numberTesting) {
    Number num1(3.14), num2(2);
    Atom tom("tom");
    ASSERT_EQ("3.14", num1.symbol());
    ASSERT_FALSE(num1.match(num2));
    ASSERT_FALSE(num2.match(num1));
}
TEST(Variable, variableTesting) {
    Atom tom("tom");
    Variable X("X"), Y("Y"), Z("Z"), W("W");
    X.match(Y);
    Z.match(W);
    X.match(W);
    Z.match(tom);
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
}
TEST(Struct, variableTesting) {
    Atom tom("tom"), justin("justin");
    Number num(3.14);
    Variable X("X"), Y("Y");
    X.match(justin);
    std :: vector<Term *>v = {&tom, &num, &X};
    Struct s(Atom("s"), v);
    X.match(justin);
    s.match(Y);
    ASSERT_EQ("s(tom, 3.14, X)", s.symbol());
    ASSERT_EQ("s(tom, 3.14, justin)", s.value());
    ASSERT_EQ("Y", Y.symbol());
    ASSERT_EQ("s(tom, 3.14, justin)", Y.value());
}

#endif /* utTest_h */
