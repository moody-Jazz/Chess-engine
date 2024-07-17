#include<iostream>
using namespace std;



//defines an unsigned long long as u64********************************************************************
#define u64 unsigned long long 


// define macros***********************************************************************************
#define get_bit(bitboard, square) (bitboard & (1ULL <<square))
#define set_bit(bitboard,square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square)? bitboard^=(1ULL<< square):0)

// enum definitions ***********************************************************************************************
enum{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

enum{white, black};

//print the bit board***********************************************************************
void print_bb(u64 bitboard){
    for(int rank{} ; rank<8; rank++){
        for(int file{}; file<8; file++){
            int square = file+rank*8;
            if(!file)
                cout<< 8-rank<<"  ";
            bool x = (get_bit(bitboard,square))? 1: 0;  
            cout<< x << " ";
        }
        cout<<endl;
    }
    cout<<endl<<"   a b c d e f g h"<<endl<<endl;

    //print bitboard as unsigned decimal number
    cout<<"bitboard value: "<<bitboard<<endl;
   
}

// attack tables**********************************************************************************

/*  
not file a :
    8  0 1 1 1 1 1 1 1
    7  0 1 1 1 1 1 1 1
    6  0 1 1 1 1 1 1 1
    5  0 1 1 1 1 1 1 1
    4  0 1 1 1 1 1 1 1
    3  0 1 1 1 1 1 1 1
    2  0 1 1 1 1 1 1 1
    1  0 1 1 1 1 1 1 1
       a b c d e f g h
*/const u64 not_a_file = 18374403900871474942ULL;
/*  
not_h_file: 
    8  1 1 1 1 1 1 1 0
    7  1 1 1 1 1 1 1 0
    6  1 1 1 1 1 1 1 0
    5  1 1 1 1 1 1 1 0
    4  1 1 1 1 1 1 1 0
    3  1 1 1 1 1 1 1 0
    2  1 1 1 1 1 1 1 0
    1  1 1 1 1 1 1 1 0
       a b c d e f g h
*/const u64 not_h_file = 9187201950435737471ULL;
/*  
not_hg_file:
    8  1 1 1 1 1 1 0 0
    7  1 1 1 1 1 1 0 0
    6  1 1 1 1 1 1 0 0
    5  1 1 1 1 1 1 0 0
    4  1 1 1 1 1 1 0 0 
    3  1 1 1 1 1 1 0 0
    2  1 1 1 1 1 1 0 0
    1  1 1 1 1 1 1 0 0
       a b c d e f g h
*/const u64 not_hg_file = 4557430888798830399ULL;
/*  
not_ab_file:
    8  0 0 1 1 1 1 1 1
    7  0 0 1 1 1 1 1 1
    6  0 0 1 1 1 1 1 1
    5  0 0 1 1 1 1 1 1
    4  0 0 1 1 1 1 1 1
    3  0 0 1 1 1 1 1 1
    2  0 0 1 1 1 1 1 1
    1  0 0 1 1 1 1 1 1
       a b c d e f g h
*/const u64 not_ab_file = 18229723555195321596ULL;

//*******************************************************************************************************
