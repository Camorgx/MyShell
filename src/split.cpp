#include "utils.hpp"

#include <string>
#include <vector>

using std::string;

std::vector<string> string_split(const string& source) {
    bool in_quote = false;
    bool after_slash = false;
    string word;
    std::vector<string> tmp;
    for (char ch : source) {
        if (after_slash) {
            word += ch;
            after_slash = false;
        }
        else if (ch == '\"') in_quote = !in_quote;
        else if (ch == ' ') {
            if (in_quote) word += ch;
            else {
                tmp.emplace_back(word);
                word = "";
            }
        }
        else if (ch == '\\') after_slash = true;
        else word += ch;
    }
    tmp.emplace_back(word);
    std::vector<string> res;
    for (auto& str : tmp)
        if (str.length())
            res.emplace_back(str);
    return res;
}
