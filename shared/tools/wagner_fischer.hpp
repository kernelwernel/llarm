// try to make a "did you mean x?" kind of 
// algorithm here. for example, if the input 
// is "hlep", it'll suggest if they meant "help"

#pragma once

#include <string>
#include <vector>
#include <map>

#include "../out.hpp"
#include "../types.hpp"

struct shared {
private:
    static u8 wagner_fischer(
        sv a, 
        sv b
    ) {
        u8 a_length = static_cast<u8>(a.length());
        u8 b_length = static_cast<u8>(b.length());

        if (a_length > b_length) {
            std::swap(a, b);
            std::swap(a_length, b_length);
        }

        std::vector<u8> curr_row(a_length + 1);
        std::vector<u8> prev_row(a_length + 1);

        curr_row.resize(std::max(a_length, b_length));
        prev_row.resize(std::max(a_length, b_length));

        for (u8 j = 0; j <= a_length; ++j) {
            prev_row[j] = j;
        }

        for (u8 i = 1; i <= b_length; ++i) {
            curr_row[0] = i;

            for (u8 j = 1; j <= a_length; ++j) {
                u8 add = prev_row[j] + 1;
                u8 del = curr_row[j - 1] + 1;
                u8 change = prev_row[j - 1];

                if (a[j - 1] != b[i - 1]) {
                    change += 1;
                }

                curr_row[j] = std::min({add, del, change});
            }

            std::swap(prev_row, curr_row);
        }

        return prev_row[a_length];
    }


public:
    template <std::size_t N>
    static std::vector<std::string> spell_check(
        const sv misspelled_word, 
        const std::array<std::string, N> &dictionary
    ) {
        std::multimap<u8, std::string, std::greater<>> pool;

        for (const auto &word : dictionary) {
            u8 distance = wagner_fischer(word, misspelled_word);
            if (distance <= 3) {
                pool.insert({word, distance});
            }
        }

        std::vector<std::string> suggestions = {};

        for (const auto& [distance, word] : pool) {
            suggestions.push_back(word);
        }

        return suggestions;
    }


    static void manage_output(const std::vector<std::string> &tmp) {

    }
    
}