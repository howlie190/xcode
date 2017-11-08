#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "term.h"
#include "atom.h"
#include "number.h"
#include "struct.h"
#include <vector>
TEST(Variable, constructor){
    Variable X("X");
    ASSERT_EQ("X", X.symbol());
}
TEST(Variable , matching){
    Atom tom("tom");
    Variable X("X");
    X.match(tom);
    ASSERT_EQ( "tom", X.value());
}
TEST (Variable , haveValue){
    Atom tom ("tom");
    Atom jerry ("jerry");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(jerry));
}
// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
    Variable X("X");
    Number num(2.7182);
    EXPECT_TRUE(num.match(X));
    EXPECT_EQ("2.7182", X.value());
}
// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
    Variable X("X"), Y("Y");
    Number num(1);
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(X.match(num));
    EXPECT_TRUE(Y.match(num));
}
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
    Variable X("X"), Y("Y");
    Number num(1);
    EXPECT_TRUE(Y.match(num));
    EXPECT_TRUE(X.match(num));
}
// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
    Variable X("X");
    Number num(1);
    EXPECT_TRUE(X.match(X));
    EXPECT_TRUE(X.match(num));
    EXPECT_EQ("1", X.value());
}
// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
    Variable X("X"), Y("Y");
    Number num(1);
    EXPECT_TRUE(Y.match(num));
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(X.match(num));
}
// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
    Variable X("X"), Y("Y"), Z("Z");
    Number num(1);
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_TRUE(Z.match(num));
    EXPECT_EQ("1", X.value());
    EXPECT_EQ("1", Y.value());
    EXPECT_EQ("1", Z.value());
}
// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable X("X"), Y("Y"), Z("Z");
    Number num(1);
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(X.match(Z));
    EXPECT_TRUE(Z.match(num));
    EXPECT_EQ("1", X.value());
    EXPECT_EQ("1", Y.value());
    EXPECT_EQ("1", Z.value());
}
// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
    Variable X("X"), Y("Y");
    std :: vector<Term *>v = {&X};
    Struct s(Atom("s"), v);
    EXPECT_TRUE(Y.match(s));
    EXPECT_EQ("Y", Y.symbol());
    EXPECT_EQ("s(X)", Y.value());
}
// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
    Variable X("X"), Y("Y");
    Atom teddy("teddy");
    std :: vector<Term *>v = {&X};
    Struct s(Atom("s"), v);
    EXPECT_TRUE(s.match(Y));
    EXPECT_TRUE(X.match(teddy));
    EXPECT_EQ("Y", Y.symbol());
    EXPECT_EQ("s(teddy)", Y.value());
}
TEST (Test, test) {
    Variable X("X"), Y("Y"), W("W"), Z("Z");
    X.match(Y);
    W.match(Z);
    X.match(W);
    Atom tom("tom");
    Z.match(tom);
    ASSERT_EQ("tom", X.value());
    ASSERT_EQ("tom", Y.value());
    ASSERT_EQ("tom", W.value());
    ASSERT_EQ("tom", Z.value());

}
#endif
