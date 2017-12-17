//
//  csv_parser_tests.cpp
//  CSVParser
//
//  Created by Кирилл on 17.12.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <sstream>

#include "gtest/gtest.h"

#include "csv_parser.h"

// Выставите значение в 1, чтобы выполнить тесты с проверками ошибок компиляции.
#define _TEST_COMPILE_ERRORS 0

TEST(CSVParser, Right) {
  std::istringstream stream("test\ntest");
  std::ostringstream out;
  csv::CSVParser<std::string> parser1(stream, 0);
  for (auto item : parser1)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "test\ntest\n");
  
  stream = std::istringstream("123\n123");
  out = std::ostringstream();
  csv::CSVParser<int> parser2(stream, 0);
  for (auto item : parser2)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "123\n123\n");
  
  stream = std::istringstream("test,test\n");
  out = std::ostringstream();
  csv::CSVParser<std::string, std::string> parser3(stream, 0);
  for (auto item : parser3)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "test | test\n");
  
  stream = std::istringstream("test,test\ntest,test");
  out = std::ostringstream();
  csv::CSVParser<std::string, std::string> parser4(stream, 0);
  for (auto item : parser4)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "test | test\ntest | test\n");
  
  stream = std::istringstream("test,123,test\ntest,456,test");
  out = std::ostringstream();
  csv::CSVParser<std::string, int, std::string> parser5(stream, 0);
  for (auto item : parser5)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "test | 123 | test\ntest | 456 | test\n");
  
  stream = std::istringstream("\n\n\n123");
  out = std::ostringstream();
  csv::CSVParser<int> parser6(stream, 3);
  for (auto item : parser6)
    out << item << std::endl;
  ASSERT_EQ(out.str(), "123\n");
}

TEST(CSVParser, TooFewColoumns) {
  std::istringstream stream("test,test,test\n,test,test\ntest,test,test");
  csv::CSVParser<std::string, std::string, std::string> parser(stream, 0);
  ASSERT_NO_THROW(parser.begin());
  ASSERT_THROW(++parser.begin(), csv::CSVParseException);
}

TEST(CSVParser, TooMuchColoumns) {
  std::istringstream stream("test,test,test\n,test,test,test,test\ntest,test,test");
  csv::CSVParser<std::string, std::string, std::string> parser(stream, 0);
  ASSERT_NO_THROW(parser.begin());
  ASSERT_THROW(++parser.begin(), csv::CSVParseException);
}

TEST(CSVParser, WrongColoumnType) {
  std::istringstream stream("test,123,test\n,test,test,test\ntest,456,test");
  csv::CSVParser<std::string, int, std::string> parser(stream, 0);
  ASSERT_NO_THROW(parser.begin());
  ASSERT_THROW(++parser.begin(), csv::CSVParseException);
}

#if _TEST_COMPILE_ERRORS > 0

class NoInputOperatorType {
  std::istream& operator>>(std::istream&) = delete;
};

TEST(CSVParser, CompileErrors) {
  std::istringstream stream("test,test");
  std::ostringstream out;
  csv::CSVParser<NoInputOperatorType, NoInputOperatorType> parser(stream, 0);
  for (auto item : parser) {
    out << item;
  }
}
#endif
