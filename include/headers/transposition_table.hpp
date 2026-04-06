#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace chess::engine {

    enum class TTFlag : uint8_t { EXACT, LOWER_BOUND, UPPER_BOUND };

    struct TTEntry {
        uint64_t key = 0;
        int score = 0;
        uint32_t best_move = 0;
        int8_t depth = 0;
        TTFlag flag = TTFlag::EXACT;
    };

    class TranspositionTable {
        std::vector<TTEntry> table;
        uint64_t mask = 0;

    public:
        explicit TranspositionTable(const size_t size_mb = 64) { resize(size_mb); }

        void resize(const size_t size_mb) {
            const size_t num_entries = size_mb * 1024 * 1024 / sizeof(TTEntry);
            size_t size = 1;
            while (size * 2 <= num_entries)
                size *= 2;
            table.assign(size, TTEntry{});
            mask = size - 1;
        }

        void clear() { std::ranges::fill(table, TTEntry{}); }

        TTEntry* probe(const uint64_t hash) {
            TTEntry& entry = table[hash & mask];
            if (entry.key == hash)
                return &entry;
            return nullptr;
        }

        void store(const uint64_t hash, const int score, const int8_t depth, const TTFlag flag, const uint32_t best_move) {
            TTEntry& entry = table[hash & mask];
            if (entry.key == 0 || entry.key == hash || depth >= entry.depth) {
                entry.key = hash;
                entry.score = score;
                entry.depth = depth;
                entry.flag = flag;
                entry.best_move = best_move;
            }
        }
    };

}  // namespace chess::engine
