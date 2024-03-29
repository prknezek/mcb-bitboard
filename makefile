all:
	gcc -oFast mcb-bitboard.c -o bb

debug:
	gcc mcb-bitboard.c -o bb