#include "tokens.hpp"

#include <llarm/shared/string_view.hpp>
#include <llarm/shared/out.hpp>

raw_tokens_t tokens::tokenize(sv instruction) {
    if (instruction.empty()) {
        llarm::out::error("Empty instruction string for tokenization is invalid");
    }

    std::vector<sv> raw_tokens;
    std::size_t start = 0;

    // this is really ugly, might remake this in the future
    while (!instruction.empty() && std::isspace(static_cast<unsigned char>(instruction.front()))) {
        instruction.remove_prefix(1);
    }

    while (!instruction.empty() && std::isspace(static_cast<unsigned char>(instruction.back()))) {
        instruction.remove_suffix(1);
    }


    // delims = deliminators

    const sv special_delims = "[]^!-+#<>";
    const sv whitespace_delims = " ,";

    while (start < instruction.size()) {
        const char c = instruction.at(start);

        if (whitespace_delims.find(c) != sv::npos) {
            ++start;
            continue;
        }

        if (special_delims.find(c) != sv::npos) {
            raw_tokens.emplace_back(&instruction.at(start), 1);
            ++start;
            continue;
        }

        std::size_t end = start;

        while (
            (end < instruction.size()) &&
            whitespace_delims.find(instruction.at(end)) == sv::npos &&
            special_delims.find(instruction.at(end)) == sv::npos
        ) {
            ++end;
        }

        raw_tokens.emplace_back(instruction.substr(start, end - start));
        start = end;
    }

    return raw_tokens;
}