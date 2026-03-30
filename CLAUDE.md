# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
# Build (from project root)
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Build with specific options disabled
cmake -B build -DCHESS_LIB_BUILD_EXAMPLE=OFF -DCHESS_LIB_BUILD_UCI=OFF
```

CMake options: `CHESS_LIB_BUILD_EXAMPLE`, `CHESS_LIB_BUILD_UCI`, `CHESS_LIB_BUILD_STATELESS_EXAMPLE` (all ON by default), `WASM_INTERFACE` (OFF by default).

Build produces shared library `chess-lib` and up to three executables: `chess-lib-example`, `chess-lib-uci`, `chess-lib-stateless-example`.

No test framework configured. No linter/formatter configured.

## Architecture Overview

Chess engine library (C++23, `-O3`) with bitboard-based board representation, magic bitboard move generation, alpha-beta AI, and UCI protocol support.

### Layer Structure

```
Public API:  include/chess-lib.hpp (single header, includes all 26 internal headers)
    ├── Board, Move, MoveArray        — core data types
    ├── AI, AlphaAI..DeltaAI          — search engine
    ├── UCI                           — protocol interface
    └── FEN, notations                — serialization
Internal:
    ├── bitboard_operations           — bit manipulation primitives
    ├── magic_numbers                 — sliding piece lookup tables (C code)
    ├── masks/*                       — pre-computed attack/pin masks (11 headers)
    └── zobrist                       — position hashing
```

### Board Representation (`include/headers/board.hpp`)

- `piece_bitboards[2][6]` — 2 colors × 6 piece types (Pawn=0, Rook=1, Knight=2, Bishop=3, Queen=4, King=5)
- `side_bitboards[2]` — combined per-color bitboards
- `all` — all occupied squares
- Colors: `White=0`, `Black=1` (defined in `constants.hpp` as `uint8_t`)
- Castling tracked by 4 separate bools: `w_l_castling`, `w_s_castling`, `b_l_castling`, `b_s_castling`
- `num_of_moves` is `double`, incremented by 0.5 per half-move
- `legal_moves` is a heap-allocated `MoveArray&` (via `*new MoveArray()`)
- `hashes: std::vector<ZobristHash>` — position history for repetition detection
- `move_history: std::vector<std::string>` — moves as algebraic notation strings

Board has three constructors: default (starting position), from bitboard array, from FEN string.

### Move Generation (`src/board/get_legal_moves.cpp`)

Largest file (~400 lines). Algorithm:
1. Compute pin masks (vertical, horizontal, both diagonals) via magic bitboard lookups
2. Detect check status
3. If double check — only king moves
4. If single check — generate moves that block or capture checker
5. For each piece type: generate moves respecting pin restrictions
6. Special handling: castling, en passant, pawn double push

Mask-to-move conversion in `src/mask_to_moves.cpp` and `src/pawn_mask.cpp`. Piece type at target square determined by linear search through 6 bitboards per move.

Pin masks use separate magic number tables (C files in `src/magic_numbers/`), with lookup headers in `include/headers/masks/`.

### Move System (`include/headers/move.hpp`)

`Move` stores: source/dest squares (0-63), piece color/type for both squares, castling flags, en passant flag, pawn double move flag, promotion piece type (`pawn_change_type`). Sentinel value `255` for "no piece".

`MoveArray` — fixed-size array of 218 `Move` objects with `push_back`/`clear`/iterators.

`Board::move(string)` finds matching move by calling `to_string()` on each legal move and comparing strings.

### AI Engine (`src/ai/`)

- `ai.cpp` — `AI::search(Board&)`: root search, iterates legal moves, calls min/max
- `minimax.cpp` — `AI::max()` / `AI::min()`: alpha-beta with Board passed by value (full copy each call)
- `evaluate_position.cpp` — static evaluation: material (2.5×), mobility (0.1×, only for side to move), pawn structure (0.5×), center control (0.2×), bishop pair (+3), check penalties
- `move_sorting.cpp` — sorts by attacker value minus victim value (higher score = attacker more valuable)
- Evaluation always from White's perspective
- `sort_max_depth = 3` — sorting only applied at depths ≥ 3
- Difficulty presets: `AlphaAI`(depth 2), `BetaAI`(3), `GammaAI`(4), `DeltaAI`(5)
- `begin_depth` / `end_depth` fields exist but are unused (iterative deepening not implemented)

### Zobrist Hashing (`src/zobrist.cpp`, `include/headers/zobrist.hpp`)

Pre-computed random constants for each (square, color, piece) triple plus castling/turn. Constructor takes `Board` **by value**. Used for 3-fold repetition detection in `Board::get_num_of_repetitions()`.

### UCI Protocol (`src/uci.cpp`)

Supports: `uci`, `isready`, `position startpos/fen [moves ...]`, `go`, `quit`. Engine name: "ChessLib", author: "Matvey Merzlikin". Logs all input to `logs.txt`.

### Stateless API (`stateless-example/main.cpp`)

Functions that create fresh Board from FEN for each call:
- `getLegalMoves(fen, white_turn)` — returns vector of move strings
- `getAIMove(fen, white_turn, difficulty)` — returns best move string
- `makeMove(fen, move, white_turn)` — returns new FEN after move
- `getResult(fen, white_turn)` — returns game result (0=ongoing, 1=white wins, etc.)

### FEN Support (`src/board/fen.cpp`)

`Board(string fen)` parses full FEN including castling rights and turn. `to_fen()` outputs only piece placement — does NOT include turn, castling, en passant, or move counters.

## Key Constraints and Gotchas

- **C++23 required** — uses `std::popcount`, `std::countr_zero`, compiler-specific constexpr limits raised in CMakeLists.txt
- **No make/unmake** — minimax copies entire Board (including vectors) for each node
- **No quiescence search** — evaluation at depth 0 is purely static
- **No transposition table** — Zobrist hashing exists but not used for search caching
- **Mobility is one-sided** — `evaluate_position` counts legal moves only for side to move
- **Move sorting is inverted** — higher score for moving valuable pieces (opposite of MVV-LVA)
- **`legal_moves` heap-allocated** — `*new MoveArray()` in Board, `delete &legal_moves` in destructor
- **Debug output in hot path** — `Board::move()` prints "KING EATING" to stdout on king capture
- **Magic numbers are C code** — `src/magic_numbers/*.c` compiled separately, wrapped via `extern "C"` in `magic_numbers.hpp`
