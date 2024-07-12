#include "include/raylib.h"
#include <string>
#include <iostream>
const unsigned int tileSize = 100;

typedef struct Piece
{
    char type;
    Texture2D texture;
    int row;
    int col;
} Piece;

Piece piece[32];

void InitializePiece(Piece *piece, char type, Texture2D texture, int row, int col)
{
    piece->type = type;
    piece->texture = texture;
    piece->row = row;
    piece->col = col;
}
// Function to initialize all pieces
void InitializePieces(Texture2D texture[])
{
    // pieceTexture[12] contains the texture of pieces in this order: [br, bk, bb, bq, bking, bpawn, wpawn, wr, wk, wb, wq, wking]
    // Initialize black pieces
    InitializePiece(&piece[0], 'r', texture[0], 0,0); // Rook
    InitializePiece(&piece[1], 'n', texture[1], 0,1); // Knight
    InitializePiece(&piece[2], 'b', texture[2], 0,2); // Bishop
    InitializePiece(&piece[3], 'q', texture[3], 0,3); // Queen
    InitializePiece(&piece[4], 'k', texture[4], 0,4); // King
    InitializePiece(&piece[5], 'b', texture[2], 0,5); // Bishop
    InitializePiece(&piece[6], 'n', texture[1], 0,6); // Knight
    InitializePiece(&piece[7], 'r', texture[0], 0,7); // Rook
    for (int i = 0; i < 8; i++)
        InitializePiece(&piece[8 + i], 'p', texture[5], 1,i); // Pawns

    // Initialize white pieces
    InitializePiece(&piece[16], 'R', texture[7], 7,0);  // Rook
    InitializePiece(&piece[17], 'N', texture[8], 7,1);  // Knight
    InitializePiece(&piece[18], 'B', texture[9], 7,2);  // Bishop
    InitializePiece(&piece[19], 'Q', texture[10], 7,3); // Queen
    InitializePiece(&piece[20], 'K', texture[11], 7,4); // King
    InitializePiece(&piece[21], 'B', texture[9], 7,5);  // Bishop
    InitializePiece(&piece[22], 'N', texture[8], 7,6);  // Knight
    InitializePiece(&piece[23], 'R', texture[7], 7,7);  // Rook
    for (int i = 0; i < 8; i++)
        InitializePiece(&piece[24 + i], 'P', texture[6], 6,i); // Pawns
}

void loadTextures()
{
    std::string pieceDir[] = {"../Assets/blackRook.png", "../Assets/blackKnight.png", "../Assets/blackBishop.png", "../Assets/blackQueen.png", "../Assets/blackKing.png", "../Assets/blackPawn.png",
                              "../Assets/whitePawn.png", "../Assets/whiteRook.png", "../Assets/whiteKnight.png", "../Assets/whiteBishop.png", "../Assets/whiteQueen.png", "../Assets/whiteKing.png"};
    Texture2D pieceTexture[12]; //[br, bk, bb, bq, bking, bpawn, wpawn, wr, wk, wb, wq, wking]

    for (int i{}; i < 12; i++)
    {
        Image image = LoadImage(pieceDir[i].c_str());
        ImageResize(&image, tileSize, tileSize);
        pieceTexture[i] = LoadTextureFromImage(image); // Load texture in graphics VRAM
        UnloadImage(image);                            // unload image from RAM
    }
    InitializePieces(pieceTexture);
}
void updateBoard()
{
    Color light{218, 217, 233, 255},
        dark{161, 123, 185, 255},
        tileColor;
    // coloring the board
    for (int row{}; row < 8; row++)
    {
        for (int col{}; col < 8; col++)
        {
            tileColor = ((row + col) % 2 == 0) ? light : dark; // white tiles will always be on (row + col == even) position
            DrawRectangle(tileSize * col, tileSize * row, tileSize, tileSize, tileColor);
        }
    }
    for (int i{}; i < 32; i++)
    {
        DrawTexture(piece[i].texture, piece[i].col * tileSize, piece[i].row * tileSize, WHITE);
    }
} 

int clickedOnRow = -1, clickedOnCol = -1;
int releasedOnTileRow = -1, releasedOnTileCol = -1;
bool pieceSelected = false;
Piece* currPiece = nullptr;
void mouseDragHandler()
{
    // if a piece is bieng clicked copy it into the currPiece and change the cursor  
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        clickedOnRow = (int)GetMousePosition().y/tileSize; // this will give the row of the tile clicked
        clickedOnCol = (int)GetMousePosition().x/tileSize; // this will give the column of the tile clicked
        // std::cout<<pressedMousePosX<<" "<<pressedMousePosY<<std::endl;
        for (int i{}; i < 32; i++)
        {
            if ((piece[i].row == clickedOnRow) && (piece[i].col == clickedOnCol))
            {   std::cout<<"true"<<std::endl; 
                currPiece = &piece[i];
                pieceSelected = true;
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                // draw an outline and highlight the square bieng clicked
                Color temp = {255, 150, 84, 100};
                DrawRectangle(clickedOnCol * tileSize, clickedOnRow * tileSize, tileSize, tileSize, temp);
                std::cout<<currPiece->type<<std::endl;
                break;
            }
        }
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && pieceSelected)
    {
        clickedOnRow = GetMousePosition().y/tileSize;
        clickedOnCol = GetMousePosition().x/tileSize;
        Rectangle rec = {clickedOnCol * tileSize, clickedOnRow * tileSize, tileSize, tileSize};
        DrawRectangleLinesEx(rec, 4, WHITE);
        std::cout <<currPiece->type<<" "<< clickedOnRow << " " << clickedOnCol << std::endl;
        // if piece is dragged redraw its textures
        DrawTexture(currPiece->texture, GetMousePosition().x - 45, GetMousePosition().y - 45, WHITE);

    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        bool isMouseInsideVertically = GetMousePosition().y >= 0 && GetMousePosition().y < GetScreenWidth(),
             isMouseInsideHorizontally = GetMousePosition().x >= 0 && GetMousePosition().x < GetScreenHeight();
        // if mouse is holding a piece and released inside the board update the position of the piece 
        if(isMouseInsideHorizontally && isMouseInsideVertically && pieceSelected){
            releasedOnTileCol = GetMousePosition().x/tileSize;
            releasedOnTileRow = GetMousePosition().y/tileSize;
            currPiece->row = releasedOnTileRow;
            currPiece->col = releasedOnTileCol;
        }     
        currPiece = nullptr;
        pieceSelected = false;
    }
}

int main()
{
    InitWindow(tileSize * 8, tileSize * 8, "Chess");
    SetTargetFPS(30);
    loadTextures();
    //print the intial position of every piece
    // for (int i{}; i < 32; i++) 
    // {
    //     std::cout << piece[i].type << " " << piece[i].row << " " << piece[i].col << std::endl;
    // }
    while (!WindowShouldClose())
    {
        BeginDrawing();
        updateBoard();
        mouseDragHandler();
        EndDrawing();
    }
    CloseWindow();
}