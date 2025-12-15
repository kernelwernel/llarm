#include "tokens.hpp"

#include <algorithm>

#include "shared/string_view.hpp"
#include "shared/out.hpp"

tokens_t tokens::tokenize(const std::string &code) {
    if (code.empty()) {
        llarm::out::error("Empty instruction string for tokenization is invalid");
    }

    std::vector<llarm::string_view> raw_tokens;
    std::size_t start = 0;

    const std::string instruction = strip(code);

    // delims = deliminators

    const llarm::string_view special_delims = "[]^!-#<>";
    const llarm::string_view whitespace_delims = " ,";

    while (start < instruction.size()) {
        const char c = instruction[start];

        if (whitespace_delims.find(c) != llarm::string_view::npos) {
            ++start;
            continue;
        }

        if (special_delims.find(c) != llarm::string_view::npos) {
            raw_tokens.emplace_back(&instruction[start], 1);
            ++start;
            continue;
        }

        std::size_t end = start;

        while (
            (end < instruction.size()) &&
            whitespace_delims.find(instruction[end]) == llarm::string_view::npos &&
            special_delims.find(instruction[end]) == llarm::string_view::npos
        ) {
            ++end;
        }

        raw_tokens.emplace_back(instruction.substr(start, end - start));
        start = end;
    }

    return raw_tokens;
}


// remake this, this is super inefficient
std::string tokens::strip(std::string str) {
    // erase leading
    str.erase(
        str.begin(), 
        std::find_if(str.begin(), str.end(), [](unsigned char ch) { 
            return !std::isspace(ch); 
        })
    );

    // erase trailing
    str.erase(
        std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { 
            return !std::isspace(ch); 
        }).base(), str.end()
    );

    // remove all instances of '+', redundant to showcase positive integers
    str.erase(std::remove(str.begin(), str.end(), '+'), str.end());

    return str;
}