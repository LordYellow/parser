//
// Created by Raphael Straub on 26.09.18.
//

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include "./definitions.hpp"
#include <fstream>
#include <unordered_map>

class parser{
public:
    explicit parser(std::string path);

    void doIt(); //I know the name is great!

private:
    std::string functionName(std::string s);
    std::string code;
    std::unordered_map< std::string, size_t> functionMap;
};

#endif //PARSER_PARSER_HPP
