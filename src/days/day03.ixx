module;
#include "puzzle.hh"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

export module day03;
import utilities;

using std::string, std::vector;

auto to_bitset(const string& s) -> vector<bool> {
    return utl::map(s, [](auto c) { return static_cast<bool>(c - '0'); });
}

auto negate(const vector<bool>& bits) -> vector<bool> {
    return utl::map(bits, [](const auto bit) { return !bit; });
}

auto to_int(const vector<bool>& bits) -> int {
    return std::accumulate(bits.begin(), bits.end(), 0, [](int acc, int bit) { return (acc << 1) + bit; });
}

auto most_common_bits(const vector<vector<bool>>& bitsets) -> vector<bool> {
    auto ones = vector<int>(bitsets[0].size());
    for (const auto& b : bitsets) {
        std::transform(ones.begin(), ones.end(), b.begin(), ones.begin(), std::plus<>());
    }
    return utl::map(ones, [size = bitsets.size()](const auto& b) { return b >= size - b; });
}

auto least_common_bits(const vector<vector<bool>>& bitsets) -> vector<bool> {
    return negate(most_common_bits(bitsets));
}

template <class Predicate>
auto reduce_common_bits(const vector<vector<bool>>& bitsets, Predicate pred) -> vector<bool> {
    auto res = vector<vector<bool>>(bitsets);
    //    for (auto n = 0; res.size() > 1; ++n) {
    //        auto common_bits = pred(res);
    //        auto filtered = res | std::views::filter([n, &common_bits](const auto &bits) { return bits[n] ==
    //        common_bits[n]; }); res = vector<vector<bool>>{filtered.begin(), filtered.end()};
    //    }
    return res[0];
}

export struct Day03 : Puzzle {
    auto part_one(string input) -> string override {
        auto bitsets = utl::map(utl::lines(input), to_bitset);

        auto gamma_rate = most_common_bits(bitsets);
        auto epsilon_rate = negate(gamma_rate);

        return std::to_string(to_int(gamma_rate) * to_int(epsilon_rate));
    }
    auto part_two(string input) -> string override {
        auto bitsets = utl::map(utl::lines(input), to_bitset);

        auto oxygen_rating = reduce_common_bits(bitsets, most_common_bits);
        auto scrubber_rating = reduce_common_bits(bitsets, least_common_bits);

        return std::to_string(to_int(oxygen_rating) * to_int(scrubber_rating));
    }
};