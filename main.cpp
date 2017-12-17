//
//  main.cpp
//  CSVParser
//
//  Created by Кирилл on 13.12.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <sstream>
#include <iostream>

#include "csv_parser.h"

int main(int argc, const char * argv[]) {
  std::istringstream stream("test\ntest\nkirpichik,1,2,ab\nbanyrule,3,4,cd\ndimonchik0036,5,6");
  csv::CSVParser<std::string, int, int, std::string> parser(stream, 2);
  for (std::tuple<std::string, int, int, std::string> line : parser) {
    std::cout << line << std::endl;
  }
  return 0;
}
