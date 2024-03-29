#include <stdio.h>

// Bitboard data type
#define U64 unsigned long long

// Bitboard macros
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

enum { white, black };

// Print bitboard for debugging
void printBitboard(U64 bitboard) {
    printf("\n");
    for (int rank = 0; rank < 8; ++rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            if (!file)
                printf(" %d  ", 8 - rank); // Print ranks
            // Print bit state (either 1 or 0)
            printf("%d ", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n\n"); // Print files
    printf("    Bitboard: %llud\n", bitboard);
}

// Not file constants
const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_hg_file = 4557430888798830399ULL;

// Pawn attacks table [side][square]
U64 pawn_attacks[2][64];

// Generate pawn attacks
U64 maskPawnAttacks(int side, int square) {
    // Result / Attacks bitboard
    U64 attacks = 0ULL;
    // Piece bitboard
    U64 bitboard = 0ULL;
    // Set piece on board
    set_bit(bitboard, square);

    if (!side) {
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    } else {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    
    }
    return attacks;
}

// Fill pawn_attacks array
void initLeaperAttacks() {
    for (int square = 0; square < 64; ++square) {
        pawn_attacks[white][square] = maskPawnAttacks(white, square);
        pawn_attacks[black][square] = maskPawnAttacks(black, square);
    }
}

int main() {
    printf("RUNNING: mcb-bitboard\n");
    // Init leaper pieces attacks
    initLeaperAttacks();
    for (int square = 0; square < 64; ++square) {
        printBitboard(pawn_attacks[black][square]);
    }
    return 0;
}