#pragma once
/*
 * board.h
 */
#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cctype>

#include "utils.h"
#include "chesspiece.h"

using namespace std;


class ChessBoard
{
public:
    void initialize_board();
    
    ChessBoard(int width, int height): width(width), height(height) { initialize_board(); }

    ChessBoard& operator=(const ChessBoard& other);
    
    friend ostream& operator<<(ostream& os, const ChessBoard& board);
    ChessPiece* operator[](string s);

    ChessBoard(const ChessBoard& other);

    // NOTE: YOU CAN ADD MORE MEMBER FUNCTIONS HERE
    void initialize_board(char** inputs);
    ChessBoard(int width, int height, char** inputs): width(width), height(height) { initialize_board(inputs); }
    ChessBoard() {}

    int getWidth() {return width;}
    int getHeight() {return height;}
    char** getBoardInfo() {return boardInfo;}
    ChessPiece* getPiece(int x, int y) {return tiles[x][y];}
    vector<tuple<MoveType, Direction, int, int>> getPossibleMovesVector(ChessPiece* currentPiece);
    
    // for problem 1
    void printProb1Board(ofstream& ofs, const vector<tuple<MoveType, Direction, int, int>>& possible_moves, int current_x, int current_y, char current_piece);
    
    // for problem 2
    bool canCurrentPieceCheck(ChessPiece* currentPiece); // true if currentPiece can check opponent King
    bool ifIsInCheck(string current_color, string opponent_color); // true if current_color King can be checked by opponent_color

    // for problem 3
    bool ifIsInCheckMate(string current_color, string opponent_color); // true if current_color King can be checkmated

    // for problem 4
    bool ifCanCheckmateInOneMove(string current_color, string opponent_color); // true if current_color King can be checkmated by one move of opponent_color

private: 
    int width, height;
    ChessPiece*** tiles;
    set<ChessPiece*> white_pieces;
    set<ChessPiece*> black_pieces;

    // NOTE: YOU CAN ADD MORE MEMBER VARIABLES HERE
    ChessPiece* blackKing;
    ChessPiece* whiteKing;
    char** boardInfo; // chessboard info in 2d char array
};

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

#endif /* CHESSBOARD_H_ */