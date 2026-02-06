#pragma once

#include <random>

#include <llarm/shared/types.hpp>

#include <llarm-asm/llarm-asm.hpp>


struct random {
private:
    static std::mt19937& engine() {
        static std::mt19937 gen{ std::random_device{}() };
        return gen;
    }

public:
    template <typename T>
    static T generate(u8 begin, u8 end) {
        std::uniform_int_distribution<T> dist(begin, end);
        return dist(engine());
    }

    static bool generate_bit() {
        return engine()() & 1;
    }
};