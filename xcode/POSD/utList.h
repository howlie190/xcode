#ifndef utList_h
#define utList_h

#include "variable.h"
#include "term.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include <iostream>
using std :: vector;
// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    List list;
    ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
    Number num(8128);
    vector<Term *>v = {&num};
    List list(v);
    ASSERT_EQ("[8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom atom1("terence_tao"), atom2("alan_mathison_turing");
    vector<Term *>v = {&atom1, &atom2};
    List list(v);
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X"), Y("Y");
    vector<Term *>v = {&X, &Y};
    List list(v);
    ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Variable X("X");
    Atom tom("tom"), terence_tao("terence_tao");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number num(496), num8128(8128);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_FALSE(num8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number num(496);
    vector<Term *>t = {&X};
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    Struct s(Atom("s"), t);
    ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Variable X("X"), Y("Y");
    Atom terence_tao("terence_tao");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_TRUE(Y.match(list));
    ASSERT_TRUE(Y.match(list));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Variable X("X"), Y("Y");
    Atom terence_tao("terence_tao");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    vector<Term *>t = {&num, &Y, &terence_tao};
    List list(v), list2(t);
    ASSERT_TRUE(list.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number num(496), num2(8128);
    vector<Term *>v = {&num, &X, &terence_tao};
    vector<Term *>t = {&num, &num2, &terence_tao};
    List list(v), list2(t);
    ASSERT_TRUE(list.match(list2));
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Variable X("X"), Y("Y");
    Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
    Number num(496);
    vector<Term *>v = {&num, &X, &terence_tao};
    List list(v);
    ASSERT_TRUE(Y.match(list));
    ASSERT_TRUE(X.match(alan_mathison_turing));
    ASSERT_TRUE(Y.match(list));
    ASSERT_TRUE(X.match(alan_mathison_turing));
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    EXPECT_EQ("first", l.head()->value());
    EXPECT_EQ("[second, third]", l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f};
    List l(args);
    vector<Term *> args2 = {&l, &s, &t};
    List l2(args2);
    EXPECT_EQ("[first]", l2.head()->value());
    EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    EXPECT_EQ("third", l.tail()->tail()->head()->value());
    EXPECT_EQ("[]", l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    List list;
    try {
        list.head();
    }
    catch(string err) {
        EXPECT_EQ("Accessing head in an empty list", err);
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    List list;
    try {
        list.tail();
    }
    catch(string err) {
        EXPECT_EQ("Accessing tail in an empty list", err);
    }
}
TEST (List,  test) {
    Variable X("X");
	Atom tom("tom");
	Number number(1);
    vector<Term *>v = {&X, &tom, &number};
    vector<Term *>v2 = {&X, &tom, &number};
    vector<Term *>v3 = {&X, &tom, &number};
	List l1(v);
	List l2(v2);
	List l3(v);
    List l4(v);
    List l5(v2);
    List l6(v3);
    List l7(v2);
    List l8(v2);
    List l9(v3);
    List l10(v2);
    List l11(v2);
    List l12(v3);
    List l13(v2);
    ASSERT_TRUE(l1.match(l2));
	ASSERT_TRUE(l1.match(l2));
	ASSERT_TRUE(l2.match(l3));
	ASSERT_TRUE(l3.match(l3));
	ASSERT_TRUE(l2.match(l5));
	ASSERT_TRUE(l5.match(l4));
	ASSERT_TRUE(l2.match(l4));
    ASSERT_TRUE(l4.match(l4));
    ASSERT_TRUE(l1.match(l2));
	ASSERT_TRUE(l1.match(l2));
	ASSERT_TRUE(l2.match(l3));
	ASSERT_TRUE(l3.match(l3));
	ASSERT_TRUE(l6.match(l5));
	ASSERT_TRUE(l7.match(l10));
	ASSERT_TRUE(l10.match(l9));
    ASSERT_TRUE(l3.match(l13));
}
// TEST(Test, test) {
//     Variable X("X"), Y("Y"), W("W"), Z("Z"), U("U"), T("T"), V("V");
//     X.match(Y);
//     W.match(Z);
//     X.match(W);
//     U.match(T);
//     V.match(T);
//     T.match(X);
//     Atom tom("tom"), jerry("jerry");
//     Z.match(tom);
//     ASSERT_EQ("tom", X.value());
//     ASSERT_EQ("tom", Y.value());
//     ASSERT_EQ("tom", W.value());
//     ASSERT_EQ("tom", Z.value());
//     ASSERT_EQ("tom", U.value());
//     ASSERT_EQ("tom", T.value());
//     ASSERT_EQ("tom", V.value());

// }
// TEST(Test, test2) {
//     Variable X("X"), Y("Y"), Z("Z"), W("W"), A("A"), B("B"), N("N"), M("M");
//     Number num(1);
//     Z.match(num);
//     X.match(Y);
//     Z.match(W);
//     A.match(B);
//     N.match(M);
//     X.match(W);
//     X.match(A);
//     X.match(N);
//     ASSERT_EQ("1", X.value());
//     ASSERT_EQ("1", Y.value());
//     ASSERT_EQ("1", W.value());
//     ASSERT_EQ("1", Z.value());
//     ASSERT_EQ("1", A.value());
//     ASSERT_EQ("1", B.value());
//     ASSERT_EQ("1", N.value());
//     ASSERT_EQ("1", M.value());
// }
#endif
