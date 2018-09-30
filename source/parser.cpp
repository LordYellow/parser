//
// Created by Raphael Straub on 26.09.18.
//

#include "../header/parser.hpp"
#include <algorithm>
#include <regex>

parser::parser(std::string path) {
    std::ifstream stream;
    stream.open(path,std::ios::in);
    if(!stream.is_open()){
        DEB_ERR("Could not open file")
    }
    this->code = std::string((std::istreambuf_iterator<char>(stream)),
                             std::istreambuf_iterator<char>());
    stream.close();
    //removes one line comments
    std::regex onLineCommand("\\/\\/.*");
    this->code = std::regex_replace(this->code, onLineCommand, "");
    //removes \n
    this->code.erase(std::remove(this->code.begin(), this->code.end(),'\n'), this->code.end());
    //removes multiline comments
    std::regex MultiLineCommand("\\/\\*.+?(?=\\/)\\/");
    this->code = std::regex_replace(this->code, MultiLineCommand, "");
    DEB_MSG_1(this->code)
    std::regex definition("define.+?(?=\\{)");
    auto words_begin =
            std::sregex_iterator(this->code.begin(), this->code.end(), definition);
    auto words_end = std::sregex_iterator();

    DEB_MSG_1("Found " + std::to_string(std::distance(words_begin, words_end)) + " definitions")
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;

        this->functionMap[this->functionName(match.str())] = this->code.find(match.str())+7;

        std::cout << this->functionName(match.str()) << ": " << this->functionMap[this->functionName(match.str())] << std::endl;
    }
}

void parser::doIt() {
    //first cut in in scopes than in commands!
    std::regex command(".+?(?=(;|\\{));");
    auto words_begin =
            std::sregex_iterator(this->code.begin(), this->code.end(), command);
    auto words_end = std::sregex_iterator();

    DEB_MSG_1("Found " + std::to_string(std::distance(words_begin, words_end)) + " commands")
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string s = match.str();
        if(s.find("define") != std::string::npos) continue;
        std::cout << s << std::endl;
    }
}

std::string parser::functionName(std::string s) {
    s.erase(s.begin(), s.begin()+7);
    s = std::regex_replace(s, std::regex(":.*"), "");
    s = std::regex_replace(s, std::regex("(num).+?(?=(,|\\)))"), "num");
    s = std::regex_replace(s, std::regex("(string).+?(?=(,|\\)))"), "string");
    return s;
}
