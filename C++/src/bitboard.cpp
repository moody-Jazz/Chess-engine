#include <./include/bitboard.hpp>
#include <iostream>

using std::cout;
using std::endl;

inline bool BitBoard::get_bit(int square){
    uint64 bitboard = this->bitboard;
    return (bool)((bitboard) & (1ULL <<(square)));
}
inline void BitBoard::set_bit(int square){
    uint64 bitboard = this->bitboard;
    (bitboard) |= (1ULL << (square));
}
inline void BitBoard::pop_bit(int square){
    uint64 bitboard = this->bitboard;
    (bitboard) &= -(1ULL << (square));
}
inline void BitBoard::set_val(uint64 bitboard){
    this->bitboard = bitboard;
}

void BitBoard::print_binary(){
for(int rank = 7 ; rank>=0; rank--){
    cout<<"    ";
    for(int file = 7; file>=0; file--){
        int square = file+rank*8;
        bool x = (get_bit(square))? 1: 0;  
        cout<<x << " ";
    }
    cout<<"\n";
}
    //print bitboard as unsigned decimal number
    cout<<"    bitboard value: "<<bitboard<<"\n";
}
inline int BitBoard::count_bits(){
    int count{};
    uint64 bitboard = this->bitboard;
    // keep reseting least significatn 1st bit until bitboard is 0
    while(bitboard){
        bitboard = bitboard & bitboard -1;
        count++;
    }
    return count;
}
inline int BitBoard::get_lsb_index(){
    // to do 
}

