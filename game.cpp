#include "game.h"

using namespace std;


void Game::read_file(string filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
    
    ifs >> problem_id;

    if(problem_id == 0){
        problem_specification = "";
    }
    else{
        ifs >> problem_specification;
    }

    cout << "problem_id: [" << problem_id << "]" << endl;
    cout << "problem_specification: [" << problem_specification << "]" << endl;

    // TODO: CREATE CHESSBOARD

    // initialize chessboard with width and height from input.txt
    int chessBoardWidth, chessBoardHeight;
    ifs >> chessBoardHeight;
    ifs >> chessBoardWidth;
    
    // create dynamic array to store board info from input.txt
    char** inputChars = new char*[chessBoardHeight];
    for(int i = 0; i < chessBoardHeight; i++) {
        inputChars[i] = new char[chessBoardWidth];
    }

    // store board info from input.txt to inputChars array
    for(int i = 0; i < chessBoardHeight; i++) {
        for(int j = 0; j < chessBoardWidth; j++) {
            ifs >> inputChars[i][j];
        }
    }

    ifs.close();

    // pass the board info to ChessBoard::initialize_board()
    board = new ChessBoard(chessBoardWidth, chessBoardHeight, inputChars);
}

void Game::open_output_file(string filename)
{
    ofs.open(filename);
    if (!ofs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
}

void Game::solve()
{
    switch (problem_id)
    {
    case 0:
        solve_print_board();
        break;
    case 1:
        solve_print_possible_moves();
        break;
    case 2:
        solve_check();
        break;
    case 3:
        solve_checkmate();
        break;
    case 4:
        solve_checkmate_in_one_move();
        break;
    default:
        cout << "Invalid problem_id" << endl;
        break;
    }
    return;
}

void Game::solve_print_board()
{
    ofs << *board;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// IN MY CODE, x AND y FOLLOWS THE MATRIX NOTATION
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void Game::solve_print_possible_moves()
{
    // TODO

    // interpret problem specification
    // problem_specification length can be 3 or 4
    char current_piece; // current target piece
    char loc_alpha_horizontal; // target piece horizontal location in alphabet
    int loc_num_horizontal; // target piece horizontal location in int, using loc_alpha_horizontal
    // loc_num_horizontal stores the location starting from the left column, starting with 0. So 0, 1, 2, ...
    int loc_num_vertical_bottom; // target piece vertical location, starting from 0 from the bottom
    // because in problem specification, vertical location starts from the bottom row
    int loc_num_vertical; // target piece vertical location in int 
    // loc_num_vertical stores the location starting from the top row, starting with 0. So, 0, 1, 2, ...

    // initialize target piece infos
    current_piece = problem_specification[0];
    loc_alpha_horizontal = problem_specification[1];
    loc_num_horizontal = loc_alpha_horizontal - 'a';

    if(problem_specification.length() == 3) {
        loc_num_vertical_bottom = problem_specification[2] - '0'; 
    }
    else if(problem_specification.length() == 4) {
        loc_num_vertical_bottom = 10 * (problem_specification[2] - '0') + (problem_specification[3] - '0');
    }
    loc_num_vertical = board->getHeight() - loc_num_vertical_bottom;

    string current_piece_color = "";
    if(islower(current_piece)) { // target piece is black 
        current_piece_color = "Black";
    }
    else if(isupper(current_piece)){ // target piece is white
        current_piece_color = "White";
    }

    // make targetPiece object
    ChessPiece* targetPiece = board->getPiece(loc_num_vertical, loc_num_horizontal);
    
    vector<tuple<MoveType, Direction, int, int>> possible_moves = board->getPossibleMovesVector(targetPiece);

    board->printProb1Board(ofs, possible_moves, loc_num_vertical, loc_num_horizontal, current_piece);

}

int Game::solve_check()
{
    // TODO
    // EXAMPLE: "Black king is in check"
    //          "White king is not in check"

    // interpret problem_specification
    string current_color = ""; // stores the given color
    string opponent_color = ""; // stores the non-given color
    if(problem_specification == "w") { current_color = "White"; opponent_color = "Black"; }
    else if (problem_specification == "b") { current_color = "Black"; opponent_color = "White"; }
    
    // if current color king is in check
    bool isCheck = board->ifIsInCheck(current_color, opponent_color);
    
    ofs << current_color << " king is" << (isCheck ? " " : " not ") << "in check" << endl;

    return 0;
}

int Game::solve_checkmate()
{
    // TODO 
    // EXAMPLE: "Black king is checkmated"
    //          "White king is not checkmated"

    // interpret problem_specification
    string current_color = ""; // stores the given color
    string opponent_color = ""; // stores the non-given color
    if(problem_specification == "w") { current_color = "White"; opponent_color = "Black"; }
    else if (problem_specification == "b") { current_color = "Black"; opponent_color = "White"; }

    bool isCheckmate = board->ifIsInCheckMate(current_color, opponent_color);

    ofs << current_color << " king is" <<  (isCheckmate ? "" : " not") << " checkmated";

    return 0;
}

int Game::solve_checkmate_in_one_move()
{
    // TODO
    // EXAMPLE: "Black king is checkmated in one move"
    //          "White king is not checkmated in one move"

    // interpret problem_specification
    string current_color = ""; // stores the given color -check if current_color is checkmated
    string opponent_color = ""; // stores the non-given color -move the opponent_color pieces
    if(problem_specification == "w") { current_color = "White"; opponent_color = "Black"; }
    else if (problem_specification == "b") { current_color = "Black"; opponent_color = "White"; }

    bool solveCheckmateInOneMove = board->ifCanCheckmateInOneMove(current_color, opponent_color);

    ofs << current_color << " king is" <<  (solveCheckmateInOneMove ? "" : " not") << " checkmated in one move";

    return 0;
}

