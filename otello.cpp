#include<utility>
#include<iostream>
#include<vector>

using namespace std;

class Exception{};

class Player{
public:	
	Player(std::string name):name(name){};	
	std::string name;
};


class Board{
public:
	Board(): board(8, std::vector<std::string>(8, " O ")), empty_cells(64), black_cells(0), white_cells(0){};
	std::string find_winer();
	
private:
	friend class Otello;
	friend class OutputInterface;
	std::vector<std::vector<std::string>> board;
	int empty_cells;
	int black_cells;
	int white_cells;
};

std::string Board::find_winer(){
	if(black_cells > white_cells)
		return "black";
	else if (white_cells > black_cells)
		return "white";
	else
		return "tie";
}

class InputInterface{
public:
	std::pair<int, int> get_move();
};

std::pair<int,int>InputInterface::get_move(){
	std::pair<int,int> move =std::make_pair(-1,-1);
	while(move.first > 7 || move.first < 0 || move.second > 7 || move.second < 0) {	
		std::cin >> move.first >> move.second;
		if(move.first > 7 || move.first < 0 || move.second > 7 || move.second < 0) {	
			std::cout << "Invalid move, choose from the valid moves" << std::endl;
		}
	}
	 
	return move;
};

class OutputInterface{
public:
	void show_board(Board& board);
	void show_available_moves(std::vector<std::pair<int,int>> available_moves, std::string players_name);
};


void OutputInterface::show_board(Board& board){
	std::cout << "         Otello"<<std::endl;
	for(int i=0; i< 8; i++)
		for(int j=0; j<8; j++){
			std::cout << board.board[i][j];
			if(j==7)
				std::cout << std::endl;	
	}
};

void OutputInterface::show_available_moves(std::vector<std::pair<int,int>> available_moves, std::string players_name){
	std::cout<< "Available moves for "<< players_name << ":" << std::endl;
	for (auto move: available_moves)
		std::cout << "("<< move.first <<"," << move.second << " ,";
	std::cout<<std::endl;
}


 
class Otello{
public:	
	Otello():number_of_disks(64){};
	void initialize_board(Board& board);
	void run_game(OutputInterface out,InputInterface in, Board& board, Player &black, Player &white);
private:
	int number_of_disks;
	void flip_disks(std::pair<int,int> move, Board& board){};
	void is_valid_move();
	std::vector<std::pair<int,int>> find_available_moves(Board &board, Player& current_player){};

};

void Otello::initialize_board(Board& board) {
	board.board[3][3] = " W ";
	board.board[3][4] = " B ";
	board.board[4][3] = " B ";
	board.board[4][4] = " W ";
	number_of_disks -= 4;

}


void Otello::run_game(OutputInterface out, InputInterface in, Board& board, Player &black, Player &white){
	initialize_board(board);
	out.show_board(board);
	std::vector<std::pair<int,int>> available_moves;
	Player current_player = black;
	std::cout << "set current player to black" << std::endl;
	std::pair<int,int> current_move;
	while (board.empty_cells){
		//available_moves = find_available_moves(board, current_player);
		out.show_available_moves(available_moves, current_player.name);
		std::cout << board.empty_cells << std::endl;
		//if (!available_moves.empty())
			board.empty_cells --;
		current_move = in.get_move();
		std::cout << current_move.first<< "," << current_move.second << std::endl;
		flip_disks(current_move, board);	
		out.show_board(board);
		if (current_player.name == "Black")
			current_player = white;
		else
			current_player = black;
	}
}

int main(){
	Otello game;
	Board board;
	OutputInterface out;
	InputInterface input;
	Player black("Black");
	Player white("White");
	game.run_game(out, input, board, black, white);

	std::cout << board.find_winer() << std::endl;
	
}
