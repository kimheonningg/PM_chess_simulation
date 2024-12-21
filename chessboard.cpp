#include "chessboard.h"

using namespace std;


void ChessBoard::initialize_board()
{
    // TODO: implement initialize_board
    // I used the below overloaded function, initialize_board(char** inputs), instead

}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
    // TODO: implement operator<<

    for(int i = 0; i < board.height; i++) {
        for(int j = 0; j < board.width; j++) {
            if(board.tiles[i][j] == nullptr)
                os << ".";
            else {
                ChessPiece* temp = board.tiles[i][j];
                if(temp->get_color() == "Black") { // black ChessPiece
                    // pawn
                    if(temp->get_type() == "Pawn") { os << 'p'; }
                    // rook
                    if(temp->get_type() == "Rook") { os << 'r'; }
                    // knight
                    if(temp->get_type() == "Knight") { os << 'n'; }
                    // bishop
                    if(temp->get_type() == "Bishop") { os << 'b'; }
                    // queen
                    if(temp->get_type() == "Queen") { os << 'q'; }
                    // king
                    if(temp->get_type() == "King") { os << 'k'; }
                }
                else if(temp->get_color() == "White") { // white ChessPiece
                    // pawn
                    if(temp->get_type() == "Pawn") { os << 'P'; }
                    // rook
                    if(temp->get_type() == "Rook") { os << 'R'; }
                    // knight
                    if(temp->get_type() == "Knight") { os << 'N'; }
                    // bishop
                    if(temp->get_type() == "Bishop") { os << 'B'; }
                    // queen
                    if(temp->get_type() == "Queen") { os << 'Q'; }
                    // king
                    if(temp->get_type() == "King") { os << 'K'; }
                }
            }
        }
        if(i != board.height-1) { os << "\n"; } // do not 'enter' at the last line
    }

    return os;
}

ChessPiece* ChessBoard::operator[](string s)
{
    // TODO: implement operator[]

    // not using

    return nullptr;
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
    // TODO: implement operator=

    return *this;
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
    // TODO: implement copy constructor
}

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

void ChessBoard::initialize_board(char** inputs) {

    // initialize boardInfo
    boardInfo = new char*[height];
    for(int i = 0; i < height; i++) {
        boardInfo[i] = new char[width];
        for(int j = 0; j < width; j++) {
            boardInfo[i][j] = inputs[i][j];
        }
    }

    // set the size of tiles variable

    tiles = new ChessPiece**[height];
    for(int i = 0; i < height; i++) {
        tiles[i] = new ChessPiece*[width];
    }

    // initialize board based on inputs array info
    char temp;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            temp = inputs[i][j];
            tiles[i][j] = nullptr;
            if(isalpha(temp)) {          
                // there is a ChessPiece in the spot
                if(islower(temp)) { // black ChessPiece
                    // pawn 
                    if(temp == 'p') { tiles[i][j] = new Pawn("Black", i, j); }
                    // rook
                    if(temp == 'r') { tiles[i][j] = new Rook("Black", i, j); }
                    // knight
                    if(temp == 'n') { tiles[i][j] = new Knight("Black", i, j); }
                    // bishop
                    if(temp == 'b') { tiles[i][j] = new Bishop("Black", i, j); }
                    // queen
                    if(temp == 'q') { tiles[i][j] = new Queen("Black", i, j); }
                    // king
                    if(temp == 'k') { tiles[i][j] = new King("Black", i, j); blackKing = new King("Black", i, j);}

                    // add ChessPiece into black_pieces set
                    black_pieces.insert(tiles[i][j]);
                }
                else if(isupper(temp)) { // white ChessPiece
                    // pawn 
                    if(temp == 'P') { tiles[i][j] = new Pawn("White", i, j); }
                    // rook
                    if(temp == 'R') { tiles[i][j] = new Rook("White", i, j); }
                    // knight
                    if(temp == 'N') { tiles[i][j] = new Knight("White", i, j); }
                    // bishop
                    if(temp == 'B') { tiles[i][j] = new Bishop("White", i, j); }
                    // queen
                    if(temp == 'Q') { tiles[i][j] = new Queen("White", i, j); }
                    // king
                    if(temp == 'K') { tiles[i][j] = new King("White", i, j); whiteKing = new King("White", i, j);}

                    // add ChessPiece into white_pieces set
                    white_pieces.insert(tiles[i][j]);
                }
            }
            else if (temp == '.') { // empty tile
                // do nothing
            }
        }
    } 
}

vector<tuple<MoveType, Direction, int, int>> ChessBoard::getPossibleMovesVector(ChessPiece* currentPiece) {
    
    vector<tuple<MoveType, Direction, int, int>> possible_moves = {};
    string type = currentPiece->get_type();
    string color = currentPiece->get_color();
    string opponent_color = (color == "Black") ? "White" : "Black";
    int x = currentPiece->get_x();
    int y = currentPiece->get_y();

    if(type == "Pawn") {

        bool isAtStart = false;
        if(color == "Black" && x == 1) { isAtStart = true; }
        else if(color == "White" && x == height-2) { isAtStart = true; }
        else { isAtStart = false; }

        if(color == "White") {
            if(isAtStart) {
                if(tiles[x-2][y] == nullptr) {
                    // pawn can go UP 2 tiles
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x-2, y));
                }
            }
            if(x != 0 && tiles[x-1][y] == nullptr) {
                possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x-1, y));
            }
            if(x != 0 && y != 0 && tiles[x-1][y-1] != nullptr && tiles[x-1][y-1]->get_color() == opponent_color){
                possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, x-1, y-1));
            }
            if(x != 0 && y != width-1 && tiles[x-1][y+1] != nullptr && tiles[x-1][y+1]->get_color() == opponent_color) {
                possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, x-1, y+1));
            }
        }
        else if(color == "Black") {
            if(isAtStart) {
                if(tiles[x+2][y] == nullptr) {
                    // pawn can go UP 2 tiles
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x+2, y));
                }
            }
            if(x != height-1 && tiles[x+1][y] == nullptr) {
                possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x+1, y));
            }
            if(x != height-1 && y != width-1 && tiles[x+1][y+1] != nullptr && tiles[x+1][y+1]->get_color() == opponent_color ) {
                possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, x+1, y+1));
            }
            if(x != height-1 && y != 0 && tiles[x+1][y-1] != nullptr && tiles[x+1][y-1]->get_color() == opponent_color ) {
                possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, x+1, y-1));
            }
        }
    }

    else if(type == "Knight") {
        if(color == "White") {
            if(x >= 2 && y >= 1) {
                if(tiles[x-2][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_UP_LEFT, x-2, y-1)); 
                }
                else if(tiles[x-2][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_UP_LEFT, x-2, y-1)); 
                }
            }
            if(x >= 2 && y < width-1) {
                if(tiles[x-2][y+1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_UP_RIGHT, x-2, y+1));  
                }
                else if(tiles[x-2][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_UP_RIGHT, x-2, y+1));  
                }
               
            }
            if(x >= 1 && y >= 2) {
                if(tiles[x-1][y-2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT_LEFT_UP, x-1, y-2)); 
                }
                else if(tiles[x-1][y-2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT_LEFT_UP, x-1, y-2)); 
                }
            }
            if(x < height-1 && y >= 2) {
                if(tiles[x+1][y-2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT_LEFT_DOWN, x+1, y-2)); 
                }
                else if(tiles[x+1][y-2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT_LEFT_DOWN, x+1, y-2)); 
                }
            }
            if(x >= 1 && y < width-2) {
                if(tiles[x-1][y+2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT_RIGHT_UP, x-1, y+2)); 
                }
                else if(tiles[x-1][y+2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT_RIGHT_UP, x-1, y+2));  
                }
            }
            if(x < height-1 && y < width-2) {
                if(tiles[x+1][y+2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT_RIGHT_DOWN, x+1, y+2)); 
                }
                else if(tiles[x+1][y+2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT_RIGHT_DOWN, x+1, y+2));
                }
            }
            if(x < height-2 && y >= 1) {
                if(tiles[x+2][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_DOWN_LEFT, x+2, y-1)); 
                }
                else if(tiles[x+2][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_DOWN_LEFT, x+2, y-1)); 
                }
            }
            if(x < width-2 && y < height-1) {
                if(tiles[x+2][y+1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_DOWN_RIGHT, x+2, y+1)); 
                }
                else if(tiles[x+2][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_DOWN_RIGHT, x+2, y+1)); 
                }
            }
        }
        else if(color == "Black") {
            if(x >= 2 && y >= 1) {
                if(tiles[x-2][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_DOWN_RIGHT, x-2, y-1)); 
                }
                else if(tiles[x-2][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_DOWN_RIGHT, x-2, y-1)); 
                }
            }
            if(x >= 2 && y < width-1) {
                if(tiles[x-2][y+1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_DOWN_LEFT, x-2, y+1));  
                }
                else if(tiles[x-2][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_DOWN_LEFT, x-2, y+1));  
                }
               
            }
            if(x >= 1 && y >= 2) {
                if(tiles[x-1][y-2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT_RIGHT_DOWN, x-1, y-2)); 
                }
                else if(tiles[x-1][y-2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT_RIGHT_DOWN, x-1, y-2)); 
                }
            }
            if(x < height-1 && y >= 2) {
                if(tiles[x+1][y-2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT_RIGHT_UP, x+1, y-2)); 
                }
                else if(tiles[x+1][y-2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT_RIGHT_UP, x+1, y-2)); 
                }
            }
            if(x >= 1 && y < width-2) {
                if(tiles[x-1][y+2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT_LEFT_DOWN, x-1, y+2)); 
                }
                else if(tiles[x-1][y+2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT_LEFT_DOWN, x-1, y+2));  
                }
            }
            if(x < height-1 && y < width-2) {
                if(tiles[x+1][y+2] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT_LEFT_UP, x+1, y+2)); 
                }
                else if(tiles[x+1][y+2]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT_LEFT_UP, x+1, y+2));
                }
            }
            if(x < height-2 && y >= 1) {
                if(tiles[x+2][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_UP_RIGHT, x+2, y-1)); 
                }
                else if(tiles[x+2][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_UP_RIGHT, x+2, y-1)); 
                }
            }
            if(x < width-2 && y < height-1) {
                if(tiles[x+2][y+1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_UP_LEFT, x+2, y+1)); 
                }
                else if(tiles[x+2][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_UP_LEFT, x+2, y+1)); 
                }
            }
        }
    }

    else if(type == "Bishop") {
        int temp_x, temp_y;
        if(color == "White") {

            // moving up left
            temp_x = x;
            temp_y = y;
            while(temp_x > 0 && temp_y > 0) {
                --temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up right 
            temp_x = x;
            temp_y = y;
            while (temp_x > 0 && temp_y < width-1) {
                --temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down left
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y > 0) {
                ++temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down right
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y < width-1) {
                ++temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }
        }
        else if(color == "Black") {
            // moving down right
            temp_x = x;
            temp_y = y;
            while(temp_x > 0 && temp_y > 0) {
                --temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down left
            temp_x = x;
            temp_y = y;
            while (temp_x > 0 && temp_y < width-1) {
                --temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up right
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y > 0) {
                ++temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up left
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y < width-1) {
                ++temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }
        }
    }

    else if(type == "Rook") {
        if(color == "White") {
            // moving up
            if(x != 0) {
                for(int i = x-1; i >= 0; i--) { 
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, i, y)); 
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, i, y)); 
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving left
            if(y != 0) {
                for(int j = y-1; j >= 0; j--) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving right
            if(y != width-1) {
                for(int j = y+1; j < width; j++) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving down
            if(x != height-1) {
                for(int i = x+1; i < height; i++) {
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, i, y));
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, i, y));
                        break;
                    }
                    else { break; } // my team
                }
            }
        }
        else if(color == "Black") {
            // moving down
            if(x != 0) {
                for(int i = x-1; i >= 0; i--) { 
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, i, y)); 
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, i, y)); 
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving right
            if(y != 0) {
                for(int j = y-1; j >= 0; j--) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving left
            if(y != width-1) {
                for(int j=y+1; j<width; j++) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving up
            if(x != height-1) {
                for(int i=x+1; i<height; i++) {
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, i, y));
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, i, y));
                        break;
                    }
                    else { break; } // my team
                }
            }
        }
    }

    else if(type == "Queen") {
        int temp_x, temp_y;
        if(color == "White") {
            // moving up
            if(x != 0) {
                for(int i = x-1; i >= 0; i--) { 
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, i, y)); 
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, i, y)); 
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving left
            if(y != 0) {
                for(int j = y-1; j >= 0; j--) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving right
            if(y != width-1) {
                for(int j=y+1; j<width; j++) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving down
            if(x != height-1) {
                for(int i=x+1; i<height; i++) {
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, i, y));
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, i, y));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving up left
            temp_x = x;
            temp_y = y;
            while(temp_x > 0 && temp_y > 0) {
                --temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up right 
            temp_x = x;
            temp_y = y;
            while (temp_x > 0 && temp_y < width-1) {
                --temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down left
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y > 0) {
                ++temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down right
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y < width-1) {
                ++temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }
        }
        else if(color == "Black") {
            // moving down
            if(x != 0) {
                for(int i = x-1; i >= 0; i--) { 
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, i, y)); 
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, i, y)); 
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving right
            if(y != 0) {
                for(int j = y-1; j >= 0; j--) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving left
            if(y != width-1) {
                for(int j=y+1; j<width; j++) {
                    if(tiles[x][j] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, j));
                    }
                    else if(tiles[x][j]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, j));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving up
            if(x != height-1) {
                for(int i=x+1; i<height; i++) {
                    if(tiles[i][y] == nullptr) {
                        possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, i, y));
                    }
                    else if(tiles[i][y]->get_color() == opponent_color) {
                        possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, i, y));
                        break;
                    }
                    else { break; } // my team
                }
            }

            // moving down right
            temp_x = x;
            temp_y = y;
            while(temp_x > 0 && temp_y > 0) {
                --temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving down left
            temp_x = x;
            temp_y = y;
            while (temp_x > 0 && temp_y < width-1) {
                --temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up right
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y > 0) {
                ++temp_x; --temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }

            // moving up left
            temp_x = x;
            temp_y = y;
            while(temp_x < height-1 && temp_y < width-1) {
                ++temp_x; ++temp_y;
                if(tiles[temp_x][temp_y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, temp_x, temp_y));
                }
                else if(tiles[temp_x][temp_y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, temp_x, temp_y));
                    break;
                }
                else { break; } // my team
            }
        }
    }

    else if(type == "King") {
        if(color == "White") {
            if(x != 0) {
                if(tiles[x-1][y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x-1, y));
                }
                else if(tiles[x-1][y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, x-1, y));
                }
            }
            if(x != 0 && y != 0) {
                if(tiles[x-1][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, x-1, y-1));
                }
                else if(tiles[x-1][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, x-1, y-1));
                }
            }
            if(x != 0 && y != width-1) {
                if(tiles[x-1][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, x-1, y+1));
                }
                else if(tiles[x-1][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, x-1, y+1));
                }
            }
            if(y != 0) {
                if(tiles[x][y-1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, y-1));
                }
                else if(tiles[x][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, y-1));
                }
            }
            if(y != width-1) {
                if(tiles[x][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, y+1));
                }
                else if(tiles[x][y+1]->get_color() == opponent_color) {
                     possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, y+1));
                }
            }
            if(x != height-1) {
                if(tiles[x+1][y] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, x+1, y));
                }
                else if(tiles[x+1][y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, x+1, y));
                }
            }
            if(x != height-1 && y != 0) {
                if(tiles[x+1][y-1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, x+1, y-1)); 
                }
                else if(tiles[x+1][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, x+1, y-1)); 
                }
            }
            if(x != height-1 && y != width-1) {
                if(tiles[x+1][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, x+1, y+1));
                }
                else if(tiles[x+1][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, x+1, y+1));
                }
            }
        }
        else if(color == "Black") {
            if(x != 0) {
                if(tiles[x-1][y] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN, x-1, y));
                }
                else if(tiles[x-1][y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN, x-1, y));
                }
            }
            if(x != 0 && y != 0) {
                if(tiles[x-1][y-1] == nullptr) {
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_RIGHT, x-1, y-1));
                }
                else if(tiles[x-1][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_RIGHT, x-1, y-1));
                }
            }
            if(x != 0 && y != width-1) {
                if(tiles[x-1][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::DOWN_LEFT, x-1, y+1));
                }
                else if(tiles[x-1][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::DOWN_LEFT, x-1, y+1));
                }
            }
            if(y != 0) {
                if(tiles[x][y-1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::RIGHT, x, y-1));
                }
                else if(tiles[x][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::RIGHT, x, y-1));
                }
            }
            if(y != width-1) {
                if(tiles[x][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::LEFT, x, y+1));
                }
                else if(tiles[x][y+1]->get_color() == opponent_color) {
                     possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::LEFT, x, y+1));
                }
            }
            if(x != height-1) {
                if(tiles[x+1][y] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP, x+1, y));
                }
                else if(tiles[x+1][y]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP, x+1, y));
                }
            }
            if(x != height-1 && y != 0) {
                if(tiles[x+1][y-1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_RIGHT, x+1, y-1)); 
                }
                else if(tiles[x+1][y-1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_RIGHT, x+1, y-1)); 
                }
            }
            if(x != height-1 && y != width-1) {
                if(tiles[x+1][y+1] == nullptr){
                    possible_moves.push_back(make_tuple(MoveType::MOVE, Direction::UP_LEFT, x+1, y+1));
                }
                else if(tiles[x+1][y+1]->get_color() == opponent_color) {
                    possible_moves.push_back(make_tuple(MoveType::ATTACK, Direction::UP_LEFT, x+1, y+1));
                }
            }
        }
    }

    return possible_moves;
}

void ChessBoard::printProb1Board(ofstream& ofs, const vector<tuple<MoveType, Direction, int, int>>& possible_moves, int current_x, int current_y, char current_piece) {    

    char** printCharArr = new char*[height];
    for(int i = 0; i< height; i++) {
        printCharArr[i] = new char[width];
    }

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            printCharArr[i][j] = '.';
        }
    }

    for(auto itr = possible_moves.begin(); itr != possible_moves.end(); itr++) {
        if(get<0>(*itr) == MoveType::ATTACK) { 
            printCharArr[get<2>(*itr)][get<3>(*itr)] = 'x';
        }
        else if(get<0>(*itr) == MoveType::MOVE) {
            printCharArr[get<2>(*itr)][get<3>(*itr)] = 'o';
        }
    }

    printCharArr[current_x][current_y] = current_piece;

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            ofs << printCharArr[i][j];
        }
        ofs << endl;
    }

    ofs.close();
}

bool ChessBoard::canCurrentPieceCheck(ChessPiece* currentPiece) {

    string type = currentPiece->get_type();
    string color = currentPiece->get_color();
    string opponent_color = (color == "Black") ? "White" : "Black";
    int x = currentPiece->get_x();
    int y = currentPiece->get_y();

    if(type == "Pawn") {
        if(color == "White") {
            if(x != 0 && y != 0 && tiles[x-1][y-1] != nullptr && tiles[x-1][y-1]->get_type() == "King" && tiles[x-1][y-1]->get_color() == opponent_color){
                // opponent King
                return true;
            }
            if(x != 0 && y != width-1 && tiles[x-1][y+1] != nullptr && tiles[x-1][y+1]->get_type() == "King" && tiles[x-1][y+1]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
            return false;
        }
        else if(color == "Black") {
            if(x != height-1 && y != width-1 && tiles[x+1][y+1] != nullptr && tiles[x+1][y+1]->get_type() == "King" && tiles[x+1][y+1]->get_color() == opponent_color ) {
                // opponent King
                return true;
            }
            if(x != height-1 && y != 0 && tiles[x+1][y-1] != nullptr && tiles[x+1][y-1]->get_type() == "King" && tiles[x+1][y-1]->get_color() == opponent_color ) {
                // opponent King
                return true;
            }
            return false;
        }
    }

    else if(type == "Knight") {
        // irrelevant with color
        if(x >= 2 && y >= 1) {
            if(tiles[x-2][y-1] != nullptr && tiles[x-2][y-1]->get_type() == "King" && tiles[x-2][y-1]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x >= 2 && y < width-1) {
            if(tiles[x-2][y+1] != nullptr && tiles[x-2][y+1]->get_type() == "King" && tiles[x-2][y+1]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x >= 1 && y >= 2) {
            if(tiles[x-1][y-2] != nullptr && tiles[x-1][y-2]->get_type() == "King" && tiles[x-1][y-2]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x < height-1 && y >= 2) {
            if(tiles[x+1][y-2] != nullptr && tiles[x+1][y-2]->get_type() == "King" && tiles[x+1][y-2]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x >= 1 && y < width-2) {
            if(tiles[x-1][y+2] != nullptr && tiles[x-1][y+2]->get_type() == "King" && tiles[x-1][y+2]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x < height-1 && y < width-2) {
            if(tiles[x+1][y+2] != nullptr && tiles[x+1][y+2]->get_type() == "King" && tiles[x+1][y+2]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x < height-2 && y >= 1) {
            if(tiles[x+2][y-1] != nullptr && tiles[x+2][y-1]->get_type() == "King" && tiles[x+2][y-1]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        if(x < width-2 && y < height-1) {
            if(tiles[x+2][y+1] != nullptr && tiles[x+2][y+1]->get_type() == "King" && tiles[x+2][y+1]->get_color() == opponent_color) {
                // opponent King
                return true;
            }
        }
        return false;
    }

    else if(type == "Bishop") {
        // irrelevant with color
        int temp_x, temp_y;
        
        // moving up left (white's view) or down right (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x > 0 && temp_y > 0) {
            --temp_x; --temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        // moving up right (white's view) or down left (black's view)
        temp_x = x;
        temp_y = y;
        while (temp_x > 0 && temp_y < width-1) {
            --temp_x; ++temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        // moving down left (white's view) or up right (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x < height-1 && temp_y > 0) {
            ++temp_x; --temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }
        
        // moving down right (white's view) or up left (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x < height-1 && temp_y < width-1) {
            ++temp_x; ++temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        return false;
    }

    else if(type == "Rook") {
        // irrelevant with color
       
        // moving up (white's view) or down (black's view)
        if(x != 0) {
            for(int i = x-1; i >= 0; i--) { 
                if(tiles[i][y] != nullptr) {
                    // blocked by a piece
                    if(tiles[i][y]->get_type() != "King" || tiles[i][y]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving left (white's view) or right (black's view)
        if(y != 0) {
            for(int j = y-1; j >= 0; j--) {
                if(tiles[x][j] != nullptr) {
                    // blocked by a piece
                    if(tiles[x][j]->get_type() != "King" || tiles[x][j]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving right (white's view) or left (black's view)
        if(y != width-1) {
            for(int j = y+1; j < width; j++) {
                if(tiles[x][j] != nullptr) {
                    // blocked by a piece
                    if(tiles[x][j]->get_type() != "King" || tiles[x][j]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving down (white's view) or up (black's view)
        if(x != height-1) {
            for(int i = x+1; i < height; i++) {
                if(tiles[i][y] != nullptr) {
                    // blocked by a piece
                    if(tiles[i][y]->get_type() != "King" || tiles[i][y]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

    else if(type == "Queen") {
        // irrelevant with color
        int temp_x, temp_y;
       
        // moving up (white's view) or down (black's view)
        if(x != 0) {
            for(int i = x-1; i >= 0; i--) { 
                if(tiles[i][y] != nullptr) {
                    // blocked by a piece
                    if(tiles[i][y]->get_type() != "King" || tiles[i][y]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving left (white's view) or right (black's view)
        if(y != 0) {
            for(int j = y-1; j >= 0; j--) {
                if(tiles[x][j] != nullptr) {
                    // blocked by a piece
                    if(tiles[x][j]->get_type() != "King" || tiles[x][j]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving right (white's view) or left (black's view)
        if(y != width-1) {
            for(int j = y+1; j < width; j++) {
                if(tiles[x][j] != nullptr) {
                    // blocked by a piece
                    if(tiles[x][j]->get_type() != "King" || tiles[x][j]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving down (white's view) or up (black's view)
        if(x != height-1) {
            for(int i = x+1; i < height; i++) {
                if(tiles[i][y] != nullptr) {
                    // blocked by a piece
                    if(tiles[i][y]->get_type() != "King" || tiles[i][y]->get_color() != opponent_color) {
                        // not the opponent King- blocked by other
                        break;
                    }
                    else {
                        // opponent King
                        return true;
                    }
                }
            }
        }

        // moving up left (white's view) or down right (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x > 0 && temp_y > 0) {
            --temp_x; --temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        // moving up right (white's view) or down left (black's view)
        temp_x = x;
        temp_y = y;
        while (temp_x > 0 && temp_y < width-1) {
            --temp_x; ++temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        // moving down left (white's view) or up right (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x < height-1 && temp_y > 0) {
            ++temp_x; --temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }
        
        // moving down right (white's view) or up left (black's view)
        temp_x = x;
        temp_y = y;
        while(temp_x < height-1 && temp_y < width-1) {
            ++temp_x; ++temp_y;
            if(tiles[temp_x][temp_y] != nullptr) {
                // blocked by a piece
                if(tiles[temp_x][temp_y]->get_type() != "King" || tiles[temp_x][temp_y]->get_color() != opponent_color) {
                    // not the opponent King- blocked by other
                    break;
                }
                else {
                    // opponent King
                    return true;
                }
            }
        }

        return false;
    }

    else { // type == "King" 
        
        // irrelevant with color
    
        if(x != 0) {
            if(tiles[x-1][y] != nullptr && tiles[x-1][y]->get_type() == "King" && tiles[x-1][y]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(x != 0 && y != 0) {
            if(tiles[x-1][y-1] != nullptr && tiles[x-1][y-1]->get_type() == "King" && tiles[x-1][y-1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(x != 0 && y != width-1) {
            if(tiles[x-1][y+1] != nullptr && tiles[x-1][y+1]->get_type() == "King" && tiles[x-1][y+1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(y != 0) {
            if(tiles[x][y-1] != nullptr && tiles[x][y-1]->get_type() == "King" && tiles[x][y-1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(y != width-1) {
            if(tiles[x][y+1] != nullptr && tiles[x][y+1]->get_type() == "King" && tiles[x][y+1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(x != height-1) {
            if(tiles[x+1][y] != nullptr && tiles[x+1][y]->get_type() == "King" && tiles[x+1][y]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(x != height-1 && y != 0) {
            if(tiles[x+1][y-1] != nullptr && tiles[x+1][y-1]->get_type() == "King" && tiles[x+1][y-1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        if(x != height-1 && y != width-1) {
            if(tiles[x+1][y+1] != nullptr && tiles[x+1][y+1]->get_type() == "King" && tiles[x+1][y+1]->get_color() == opponent_color) {
                //opponent King
                return true;
            }
        }
        return false;
    }

    return false;
}

bool ChessBoard::ifIsInCheck(string current_color, string opponent_color) {
    // true if current_color King can be checked by opponent_color pieces

    // get every opponent pieces
    set<ChessPiece*> opponent_pieces;
    if(opponent_color == "White") { opponent_pieces = white_pieces; }
    else { opponent_pieces = black_pieces;}

    for(ChessPiece* opponent_piece : opponent_pieces) {
        bool canBeChecked = canCurrentPieceCheck(opponent_piece);
        if(canBeChecked) { return true; }
    }

    return false;
}

bool ChessBoard::ifIsInCheckMate(string current_color, string opponent_color) { 
    // true if current_color King can be checkmated

    // first check if current_color King is checked
    // if current_color King is not in check, return false
    if(!ifIsInCheck(current_color, opponent_color)) { return false; }

    // current_color King is in check
    // move King to its every possible move, and see if King is checked when located in every possible moves

    ChessPiece* currentKing;
    set<ChessPiece*> currentPieces;
    if(current_color == "White") {currentKing = whiteKing; currentPieces = white_pieces;}
    else {currentKing = blackKing; currentPieces = black_pieces;}

    int king_from_x = currentKing->get_x(), king_from_y = currentKing->get_y();

    vector<tuple<MoveType, Direction, int, int>> current_king_every_possible_moves = getPossibleMovesVector(currentKing);

    if(current_king_every_possible_moves.size() == 0) { return true; } // cannot move

    for(auto current_king_every_possible_move : current_king_every_possible_moves) {
        // move king to that location, by making new board
        int king_to_x = get<2>(current_king_every_possible_move), king_to_y = get<3>(current_king_every_possible_move);

        // initialize tempBoardInfo 
        char** tempBoardInfo = new char*[height];
        for(int i = 0; i < height; i++) {
            tempBoardInfo[i] = new char[width];
            for (int j = 0; j < width; j++) {
                if(i == king_from_x && j == king_from_y) { tempBoardInfo[i][j] = '.'; }
                else if(i == king_to_x && j == king_to_y) { tempBoardInfo[i][j] = (current_color=="White" ? 'K' : 'k'); }
                else { tempBoardInfo[i][j] = boardInfo[i][j]; }
            }
        }

        // make tempBoard
        ChessBoard* tempBoard = new ChessBoard(width, height, tempBoardInfo);

        // check if King is not check in tempBoard
        if(!tempBoard->ifIsInCheck(current_color, opponent_color)) {
            // not checkmate
            
            // delete
            for(int i = 0; i < height; i++)
                delete[] tempBoardInfo[i];
            delete[] tempBoardInfo;
            delete tempBoard;

            return false;
        }
        
        for(int i = 0; i < height; i++)
            delete[] tempBoardInfo[i];
        delete[] tempBoardInfo;
        delete tempBoard;

    }

    // move other current_color pieces to every possible moves, and see if King is checked when located in every possible moves
    for(ChessPiece* current_piece : currentPieces) {

        if(current_piece->get_type() == "King") {continue;}

        vector<tuple<MoveType, Direction, int, int>> current_piece_possible_moves = getPossibleMovesVector(current_piece);

        char current_piece_char = piece_to_char[current_piece->get_type()];
        if(current_color == "Black") { current_piece_char = tolower(current_piece_char);}
        else { current_piece_char = toupper(current_piece_char); }

        int piece_from_x = current_piece->get_x(), piece_from_y = current_piece->get_y();

        for(auto current_piece_possible_move : current_piece_possible_moves) {
            // move piece to that place
            int piece_to_x = get<2>(current_piece_possible_move), piece_to_y = get<3>(current_piece_possible_move);

            // initialize tempBoardInfo 
            char** tempBoardInfo = new char*[height];
            for(int i = 0; i < height; i++) {
                tempBoardInfo[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    if(i == piece_from_x && j == piece_from_y) { tempBoardInfo[i][j] = '.'; }
                    else if(i == piece_to_x && j == piece_to_y) { tempBoardInfo[i][j] = current_piece_char; }
                    else { tempBoardInfo[i][j] = boardInfo[i][j]; }
                }
            }

            // make tempBoard
            ChessBoard* tempBoard = new ChessBoard(width, height, tempBoardInfo);

            // check if King is not check in tempBoard
            if(!tempBoard->ifIsInCheck(current_color, opponent_color)) {
                // not checkmate
                
                // delete
                for(int i = 0; i < height; i++)
                    delete[] tempBoardInfo[i];
                delete[] tempBoardInfo;
                delete tempBoard;

                return false;
            }
            
            for(int i = 0; i < height; i++)
                delete[] tempBoardInfo[i];
            delete[] tempBoardInfo;
            delete tempBoard;
        }
    }

    return true;
}

bool ChessBoard::ifCanCheckmateInOneMove(string current_color, string opponent_color) { 
    // true if current_color King can be checkmated by one move of opponent_color

    // for every possible moves of every opponent_color pieces, check if King is checkmated there
    set<ChessPiece*> opponentPieces;
    if(opponent_color == "White") {opponentPieces = white_pieces;}
    else {opponentPieces = black_pieces;}

    for(ChessPiece* opponentPiece : opponentPieces) {
        // get every possible moves of opponentPiece
        vector<tuple<MoveType, Direction, int, int>> opponent_piece_possible_moves = getPossibleMovesVector(opponentPiece);
        
        int opponent_piece_from_x = opponentPiece->get_x(), opponent_piece_from_y = opponentPiece->get_y();
        
        char opponent_piece_char = piece_to_char[opponentPiece->get_type()];
        if (opponent_color == "White") {opponent_piece_char = toupper(opponent_piece_char);}
        else {opponent_piece_char = tolower(opponent_piece_char);}

        // make tempBoard for every possible moves
        for(auto opponent_piece_possible_move : opponent_piece_possible_moves) {

            int opponent_piece_to_x = get<2>(opponent_piece_possible_move);
            int opponent_piece_to_y = get<3>(opponent_piece_possible_move);

            // initialize tempBoardInfo 
            char** tempBoardInfo = new char*[height];
            for(int i = 0; i < height; i++) {
                tempBoardInfo[i] = new char[width];
                for (int j = 0; j < width; j++) {
                    if(i == opponent_piece_from_x && j == opponent_piece_from_y) { tempBoardInfo[i][j] = '.'; }
                    else if(i == opponent_piece_to_x && j == opponent_piece_to_y) { tempBoardInfo[i][j] = opponent_piece_char; }
                    else { tempBoardInfo[i][j] = boardInfo[i][j]; }
                }
            }

            // make tempBoard
            ChessBoard* tempBoard = new ChessBoard(width, height, tempBoardInfo);

            // check if King is checkmated in tempBoard
            if(tempBoard->ifIsInCheckMate(current_color, opponent_color)) {
                // can be checkmated
                
                // delete
                for(int i = 0; i < height; i++)
                    delete[] tempBoardInfo[i];
                delete[] tempBoardInfo;
                delete tempBoard;

                return true;
            }

            for(int i = 0; i < height; i++)
                delete[] tempBoardInfo[i];
            delete[] tempBoardInfo;
            delete tempBoard;
        }
    }
    return false;
}