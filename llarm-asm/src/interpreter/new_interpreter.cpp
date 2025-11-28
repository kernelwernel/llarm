#include "new_interpreter.hpp"

#include "shared/string_view.hpp"

interpreter::tokens_t interpreter::tokenize(const std::string &code) {
    if (code.empty()) {
        llarm::out::error("Empty instruction string for tokenization is invalid");
    }

    std::vector<std::string_view> raw_tokens;
    std::size_t start = 0;

    const std::string instruction = strip(code);

    const std::string_view special_delims = "[]^!-#";
    const std::string_view whitespace_delims = " ,";

    while (start < instruction.size()) {
        const char c = instruction[start];

        if (whitespace_delims.find(c) != std::string_view::npos) {
            ++start;
            continue;
        }

        if (special_delims.find(c) != std::string_view::npos) {
            raw_tokens.emplace_back(&instruction[start], 1);
            ++start;
            continue;
        }

        std::size_t end = start;

        while (
            (end < instruction.size()) &&
            whitespace_delims.find(instruction[end]) == std::string_view::npos &&
            special_delims.find(instruction[end]) == std::string_view::npos
        ) {
            ++end;
        }

        raw_tokens.emplace_back(instruction.substr(start, end - start));
        start = end;
    }

    return raw_tokens;
}