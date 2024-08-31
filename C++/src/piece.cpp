#include "../include/piece.hpp"
#include "../include/chessboard.hpp"
#include "../include/globalvar.hpp"
#include <vector>
#include <iostream>

Piece::Piece(){
    /* 
    all the pieces will be initialised with a decimal value which in is similar to initial chess pieces position

    White pawn bitboard                 black pawn bitboard                 black rook bitboard

    8  0 0 0 0 0 0 0 0                  8  0 0 0 0 0 0 0 0                  8  1 0 0 0 0 0 0 1            
    7  0 0 0 0 0 0 0 0                  7  1 1 1 1 1 1 1 1                  7  0 0 0 0 0 0 0 0 
    6  0 0 0 0 0 0 0 0                  6  0 0 0 0 0 0 0 0                  6  0 0 0 0 0 0 0 0 
    5  0 0 0 0 0 0 0 0                  5  0 0 0 0 0 0 0 0                  5  0 0 0 0 0 0 0 0 
    4  0 0 0 0 0 0 0 0                  4  0 0 0 0 0 0 0 0                  4  0 0 0 0 0 0 0 0 
    3  0 0 0 0 0 0 0 0                  3  0 0 0 0 0 0 0 0                  3  0 0 0 0 0 0 0 0
    2  1 1 1 1 1 1 1 1                  2  0 0 0 0 0 0 0 0                  2  0 0 0 0 0 0 0 0
    1  0 0 0 0 0 0 0 0                  1  0 0 0 0 0 0 0 0                  1  0 0 0 0 0 0 0 0

       a b c d e f g h                     a b c d e f g h                     a b c d e f g h
    */

    piece_set[P].set_val(65280ULL);
    piece_set[N].set_val(66ULL);
    piece_set[B].set_val(36ULL);
    piece_set[R].set_val(129ULL);
    piece_set[Q].set_val(16ULL);
    piece_set[K].set_val(8ULL);
    piece_set[p].set_val(71776119061217280ULL);
    piece_set[n].set_val(4755801206503243776ULL);
    piece_set[b].set_val(2594073385365405696ULL);
    piece_set[r].set_val(9295429630892703744ULL);
    piece_set[q].set_val(1152921504606846976ULL);
    piece_set[k].set_val(576460752303423488ULL);

    check[white] = check[black] = false;

    kingPosition[white] = 3;
    kingPosition[black] = 59;

    unsafe_tiles[white] = unsafe_tiles[black] = 0ULL;
}

BitBoard pawn_attack_bitmask_init(int side, int square){
    
    // result attacks bitboard
    BitBoard attacks(0ULL);

    // piece bitboard
    BitBoard bitboard(0ULL);

    //the current position of piece
    bitboard.set_bit(square);

    //black pawns
    if(side){
        if((bitboard.val >> 7) & not_a_file) attacks.val |= (bitboard.val >> 7);
        if((bitboard.val >> 9) & not_h_file) attacks.val |= (bitboard.val >> 9);
    }
    //white pawns
    else{
        if((bitboard.val << 7) & not_h_file) attacks.val |= (bitboard.val << 7);
        if((bitboard.val << 9) & not_a_file) attacks.val |= (bitboard.val << 9);
    }
    // return attack bitboard
    return attacks;
}
BitBoard pawn_push_bitmask_init(int side, int square){
    BitBoard attacks(0ULL);

    // piece bitboard
    BitBoard bitboard(0ULL);

    //the current position of piece
    bitboard.set_bit(square);

    //black pawns
    if(side){
        // if pawn is on initial square then it can move two tiles ahead
        if(square >=48 && square <= 55){
            attacks.val |= (bitboard.val >> 8);
            attacks.val |= (bitboard.val >> 16); 
        }
        else {
            attacks.val |= (bitboard.val >> 8);
        }
    }
    //white pawns
    else{
        if(square >=8 && square <= 15){
            attacks.val |= (bitboard.val << 8);
            attacks.val |= (bitboard.val << 16); 
        }
        else {
            attacks.val |= (bitboard.val << 8);
        }
    }
    // return attack bitboard
    return attacks;
}

BitBoard Piece::knight_attack_bitmask_init(int square){
    BitBoard attacks(0ULL);

    BitBoard bitboard(0ULL);

    // set piece position
    bitboard.set_bit(square);

    //generate knight attacks
    if((bitboard.val >> 17) & not_h_file) attacks.val |= (bitboard.val >> 17);
    if((bitboard.val >> 15) & not_a_file) attacks.val |= (bitboard.val >> 15);
    if((bitboard.val >> 10) & not_hg_file) attacks.val |= (bitboard.val >> 10);
    if((bitboard.val >> 6) & not_ab_file) attacks.val |= (bitboard.val >> 6);    

    if((bitboard.val << 17) & not_a_file) attacks.val |= (bitboard.val << 17);
    if((bitboard.val << 15) & not_h_file) attacks.val |= (bitboard.val << 15);
    if((bitboard.val << 10) & not_ab_file) attacks.val |= (bitboard.val << 10);
    if((bitboard.val << 6) & not_hg_file) attacks.val |= (bitboard.val << 6); 
    return attacks;
}

BitBoard Piece::king_attack_bitmask_init(int square){
    BitBoard attacks(0ULL);

    BitBoard bitboard(0ULL); 

    bitboard.set_bit(square);

    if(bitboard.val >> 8) attacks.val |= (bitboard.val >> 8);
    if((bitboard.val >> 9) & not_h_file) attacks.val |= (bitboard.val >> 9);
    if((bitboard.val >> 7) & not_a_file) attacks.val |= (bitboard.val >> 7);
    if((bitboard.val >> 1) & not_h_file)attacks.val |= (bitboard.val >> 1);  

    if(bitboard.val << 8) attacks.val |= (bitboard.val << 8);
    if((bitboard.val << 9) & not_a_file) attacks.val |= (bitboard.val << 9);
    if((bitboard.val << 7) & not_h_file) attacks.val |= (bitboard.val << 7);
    if((bitboard.val << 1) & not_a_file)attacks.val |= (bitboard.val << 1);  
    
    return attacks;
}

uint64 Piece::get_bishop_attacks(int square, uint64 block){
    uint64 attacks(0ULL);
    int r, f;
    int tr = square/8;
    int tf = square % 8; 

    for(r = tr +1, f = tf+1; r<=7 && f<=7; r++, f++){
        attacks |= (1ULL << (r*8+f));
        if(block & (1ULL << (r*8+f))) break;
    } 
    for(r = tr -1, f = tf+1; r>=0 && f<=7; r--, f++){
        attacks |= (1ULL << (r*8+f));
        if(block & (1ULL << (r*8+f))) break;
    }
    for(r = tr +1, f = tf-1; r<=7 && f>=0; r++, f--){
        attacks |= (1ULL << (r*8+f));
        if(block & (1ULL << (r*8+f))) break;
    }
    for(r = tr -1, f = tf-1; r>=0 && f>=0; r--, f--){
        attacks |= (1ULL << (r*8+f));
        if(block & (1ULL << (r*8+f))) break;
    } 

    return attacks;
}
uint64 Piece::get_rook_attacks(int square, uint64 block){
    uint64 attacks(0ULL);

    int r,f;
    int tr = square / 8;
    int tf = square % 8;

    for(r = tr+1; r<= 7; r++) {
        attacks |= (1ULL << (r*8 +tf));
        if((1ULL << (r*8 +tf)) & block) break;

    }
    for(r = tr-1; r>= 0; r--) {
        attacks |= (1ULL << (r*8 +tf));
        if((1ULL << (r*8 +tf)) & block) break;
    }
    for(f = tf + 1; f<=7; f++) {
        attacks |= (1ULL << (tr *8 +f));
        if((1ULL << (tr *8 +f)) & block) break;
    }
    for(f = tf - 1; f>=0; f--) {
        attacks |= (1ULL << (tr *8 +f));
        if((1ULL << (tr *8 +f)) & block) break;
    }
    return attacks;
}
uint64 Piece::get_queen_attacks(int square, uint64 block){
    uint64 attacks(0ULL);
    attacks |= get_bishop_attacks(square, block);
    attacks |= get_rook_attacks(square, block);
    return attacks;
}

BitBoard Piece::get_legal_move(Board board, char type, int square){

    char piece = toupper(type);
    int turn = (type < 'Z')?0:1;
    BitBoard res(0ULL);
    
    switch (piece)
    {
        case 'P': {
           // find legal attack moves
            uint64 pawn_attack = pawn_attack_bitmask[turn][square] & board.bitboards[!turn].val;

            // find legal push moves
            uint64 pawn_push = pawn_push_bitmask[turn][square] & ~(board.bitboards[both].val);

            /*
            check if there is a piece directly infront of pawn if so then return zero legal push moves
            this if condition is necessary because on thier initial squares pawn can move two tiles 
            if the condition below doen't exist then the pawn will have one legal move which is 
            behind the blocker piece even when a piece is directly in front of it 

            legal moves if the below if() condition is not there

                5   - - - - - - - -
                4   1 - R - 1 - - 1
                3   1 - 1 - B - - r
                2   P - P - P - - P
                1   - - - - - - - -
            */ 
            if((!turn && 1ULL<<(square+8) & board.bitboards[both].val) ||
                (turn && 1ULL<<(square-8) & board.bitboards[both].val)) {
                    pawn_push = 0ULL; 
            }
            res.val = pawn_attack | pawn_push;
            break;
        }
        case 'N': {
            res.val = knight_attack_bitmask[square] & ~(board.bitboards[turn].val);
            break;
        }
        case 'K': {
            res.val = king_attack_bitmask[square] & ~(board.bitboards[turn].val);
            res.val &= ~unsafe_tiles[turn].val;

            if(!turn && (board.castle[wk] || board.castle[wq])){ //for white castle
                uint64 castle_bitmask = 118ULL;
                castle_bitmask &= ~unsafe_tiles[turn].val & ~board.bitboards[both].val;

                if((castle_bitmask & 6ULL) == 6ULL && board.castle[wk]) 
                    res.val |= 6ULL;
                if((castle_bitmask & 112ULL) == 112ULL && board.castle[wq])
                    res.val |= 48ULL;
            }
            else if(turn && (board.castle[bk] || board.castle[bq])){ // for black castle
                uint64 castle_bitmask = 8502796096475496448ULL;
                castle_bitmask &= ~unsafe_tiles[turn].val & ~board.bitboards[both].val;

                if((castle_bitmask & 432345564227567616ULL) == 432345564227567616ULL && board.castle[bk])
                    res.val |= 432345564227567616ULL;
                if((castle_bitmask & 8070450532247928832ULL) == 8070450532247928832ULL && board.castle[bq]) 
                    res.val |= 3458764513820540928ULL;
            }
            break;
        }
        case 'R': {
            res.val = get_rook_attacks(square, board.bitboards[both].val) &
                        ~(board.bitboards[turn].val);
            break;
        }
        case 'B': {
            res.val = get_bishop_attacks(square, board.bitboards[both].val) &
                        ~(board.bitboards[turn].val);
            break;
        }
        case 'Q': {
            res.val = get_queen_attacks(square, board.bitboards[both].val) &
                        ~(board.bitboards[turn].val);
            break;
        }
    default:{
        break;
    }
    }
    return res;
}

void Piece::update_unsafe_tiles(Board board){
    BitBoard black_attacks(0ULL), white_attacks(0ULL);

    for(int i{}; i<totalPiece; i++){
        PieceUI *curr = &pieceTextures[i];
        int square = 63 - (curr->row*8 + curr->col);

        if(curr->type == 'p' || curr->type == 'P'){    // if current piece is pawn then only take its attacking squares
            if(curr->type == 'p') black_attacks.val |= pawn_attack_bitmask[black][square];
            else white_attacks.val |= pawn_attack_bitmask[white][square];
        }

        else if(curr->type > 'a') black_attacks.val |= get_legal_move(board, curr->type, square).val;

        else white_attacks.val |= get_legal_move(board, curr->type, square).val;
    }
    unsafe_tiles[white] = black_attacks.val;
    unsafe_tiles[black] = white_attacks.val;
}

bool Piece::is_king_safe(Board board, bool white){
    std::vector<int> attacks = unsafe_tiles[board.turn].get_set_bit_index();
    for(auto& x:attacks)
        if(kingPosition[white] == x) return false;
    return true;
}