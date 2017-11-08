#ifndef UTPARSER_H
#define UTPARSER_H

#include "parser.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "term.h"

Scanner scanner;
class ParserTest : public :: testing :: Test {
protected:
    void SetUp() {
        scanner.getSymtable()->clear();
    }
};

TEST_F(ParserTest, createTerm_Var){
    scanner.setInput("X");
    Parser parser(scanner);
    ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Num){
    scanner.setInput("123");
    Parser parser(scanner);
    ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
    scanner.setInput("tom");
    Parser parser(scanner);
    ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createArgs)
{
    scanner.setInput("1, X, tom");
    Parser parser(scanner);
    vector<Term*> terms = parser.getArgs();
    ASSERT_EQ("1", terms[0]->symbol());
    ASSERT_EQ("X", terms[1]->symbol());
    ASSERT_EQ("tom", terms[2]->symbol());
}

TEST_F(ParserTest, createTerms)
{
    scanner.setInput("s(1, X, tom)");
    Parser parser(scanner);
    ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  tom" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "tom".
TEST_F(ParserTest, listOfTermsTwo) {
    scanner.setInput(" 12345, tom");
    Parser parser(scanner);
    vector<Term *>terms = parser.getArgs();
    ASSERT_EQ("12345", terms[0]->symbol());
    ASSERT_EQ("tom", terms[1]->symbol());
}


// Given there is string: "point(1, X, z(1,2,3))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z(1,2,3))".
TEST_F(ParserTest, parseStructOfStruct) {
    scanner.setInput("point(1, X, z(1, 2, 3))");
    Parser parser(scanner);
    ASSERT_EQ("point(1, X, z(1, 2, 3))", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  67" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "67".
TEST_F(ParserTest, listOfTermsTwoNumbers) {
    scanner.setInput(" 12345,  67");
    Parser parser(scanner);
    vector<Term *>terms = parser.getArgs();
    ASSERT_EQ("12345", terms[0]->symbol());
    ASSERT_EQ("67", terms[1]->symbol());
}


// Given there is string: "point(1, X, z)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z)".
TEST_F(ParserTest, parseStructThreeArgs) {
    scanner.setInput("point(1, X, z)");
    Parser parser(scanner);
    ASSERT_EQ("point(1, X, z)", parser.createTerm()->symbol());
}


// Given there is string: "   [   ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[]".
TEST_F(ParserTest, parseListEmpty) {
    scanner.setInput("   [   ]");
    Parser parser(scanner);
    ASSERT_EQ("[]", parser.createTerm()->symbol());
}


// Given there is string: "_date" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Variable.
// And #symbol() of Variable should return "_date".
TEST_F(ParserTest, parseVar) {
    scanner.setInput("_date");
    Parser parser(scanner);
    ASSERT_EQ("_date", parser.createTerm()->symbol());
}


// Given there is not string in scanner.
// When parser parses all terms via scanner.
// Then it should return nothing.
TEST_F(ParserTest, listOfTermsEmpty) {
    scanner.setInput("");
    Parser parser(scanner);
    ASSERT_EQ(nullptr, parser.createTerm());
}


// Given there is string: "s(s(s(s(1))))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "s(s(s(s(1))))".
TEST_F(ParserTest, parseStructOfStructAllTheWay) {
    scanner.setInput("s(s(s(s(1))))");
    Parser parser(scanner);
    ASSERT_EQ("s(s(s(s(1))))", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [] ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], []]".
TEST_F(ParserTest, parseListOfLists) {
    scanner.setInput("   [  [1], [] ]");
    Parser parser(scanner);
    ASSERT_EQ("[[1], []]", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [], s(s(1)) ]   " in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], [], s(s(1))]".
TEST_F(ParserTest, parseListOfListsAndStruct) {
    scanner.setInput("[[1], [], s(s(1))]");
    Parser parser(scanner);
    ASSERT_EQ("[[1], [], s(s(1))]", parser.createTerm()->symbol());
}

// Given there is string: "   [1, 2]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[1, 2]".
TEST_F(ParserTest, parseList) {
    scanner.setInput("   [1, 2]");
    Parser parser(scanner);
    ASSERT_EQ("[1, 2]", parser.createTerm()->symbol());
}

// Given there is string: "[1,2)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a string: "unexpected token" as exception.
TEST_F(ParserTest, illegal1) {
    scanner.setInput("[1,2)");
    Parser parser(scanner);
    try {
        parser.createTerm();
    } catch(string err) {
        ASSERT_EQ("unexpected token", err);
    }
}

// Given there is string: ".(1,[])" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(1, [])".
// And the first term should be number: "1", the second term should be another Strcut: "[]".
TEST_F(ParserTest, ListAsStruct) {
    scanner.setInput(".(1,[])");
    Parser parser(scanner);
    Struct *ps = parser.createTerm()->getStruct();
    ASSERT_EQ(2, ps->arity());
    ASSERT_EQ(".(1, [])", ps->symbol());
    ASSERT_EQ("1", ps->args(0)->symbol());
    ASSERT_EQ("[]", ps->args(1)->symbol());
}


// Given there is string: ".(2,.(1,[]))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(2, .(1, []))"
// And the first term should be number: "2", the second term should be another Strcut: ".(1, [])".
TEST_F(ParserTest, ListAsStruct2) {
    scanner.setInput( ".(2,.(1,[]))");
    Parser parser(scanner);
    Struct *ps = parser.createTerm()->getStruct();
    ASSERT_EQ(2, ps->arity());
    ASSERT_EQ(".(2, .(1, []))", ps->symbol());
    ASSERT_EQ("2", ps->args(0)->symbol());
    ASSERT_EQ(".(1, [])", ps->args(1)->symbol());
}


// Given there is string: "s(s(s(s(1)))), b(1,2,3)" in scanner.
// When parser parses all terms via scanner.
// Then it should return two Struct.
// And #symbol() of the first Strcut should return "s(s(s(s(1))))".
// And #symbol() of the second Strcut should return "b(1, 2, 3)".
TEST_F(ParserTest, parseStructOfStructAllTheWay2) {
    scanner.setInput("s(s(s(s(1)))), b(1,2,3)");
    Parser parser(scanner);
    vector<Term *>terms = parser.getArgs();
    ASSERT_EQ("s(s(s(s(1))))", terms[0]->symbol());
    ASSERT_EQ("b(1, 2, 3)", terms[1]->symbol());
}


// Given there is string: "point()" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point()".
TEST_F(ParserTest, parseStructNoArg) {
    scanner.setInput("point()");
    Parser parser(scanner);
    ASSERT_EQ("point()", parser.createTerm()->symbol());
}
// Given there is string: " 12345,  tom,   Date" in scanner.
// When parser parses all terms via scanner.
// Then it should return three terms: "12345", "tom" and "Date".
TEST_F(ParserTest, listOfTermsThree) {
    scanner.setInput(" 12345,  tom,   Date");
    Parser parser(scanner);
    vector<Term *>terms = parser.getArgs();
    ASSERT_EQ("12345", terms[0]->symbol());
    ASSERT_EQ("tom", terms[1]->symbol());
    ASSERT_EQ("Date", terms[2]->symbol());
}
// Given there is string: "point(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11, 12)".
TEST_F(ParserTest, parseStructTwoArgs) {
    scanner.setInput("point(11,12)");
    Parser parser(scanner);
    ASSERT_EQ("point(11, 12)", parser.createTerm()->symbol());
}
// Given there is string: "...(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "...(11, 12)".
TEST_F(ParserTest, parseStructDOTSTwoArgs) {
    scanner.setInput("...(11,12)");
    Parser parser(scanner);
    ASSERT_EQ("...(11, 12)", parser.createTerm()->symbol());
}


// Given there is string: "point(11)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11)".
TEST_F(ParserTest, parseStructOneArg) {
    scanner.setInput("point(11)");
    Parser parser(scanner);
    ASSERT_EQ("point(11)", parser.createTerm()->symbol());
}

#endif
