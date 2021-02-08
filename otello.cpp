#include<iostream>
#include<vector>

using namespace std;

class Exception{};

class Player{
public:	
	
	Player(std::string name):name(name), number_of_disks(30){};	
	std::string name;
	void borrow_disk(Player &opponent);
	int get_number_of_disks() {return number_of_disks;};
	
private:
	bool my_turn;
	std::string color;
	int number_of_disks;
};

void Player::borrow_disk(Player &opponent){
	if (number_of_disks > 0 || !my_turn)
		throw Exception();
	if (opponent.number_of_disks){ 
		opponent.number_of_disks--;
		number_of_disks++;
	}
}



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
	void get_player_name();
};

class OutputInterface{
public:
	void show_board(Board& board);
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



 
class Otello{
public:	
	void initialize_board(Board& board);
	void run_game(OutputInterface out, Board& board);
private:
	void flip_disks();
	void is_valid_move();
	void find_valid_moves();
	void change_turn();
};

void Otello::initialize_board(Board& board) {
	board.board[3][3] = " W ";
	board.board[3][4] = " B ";
	board.board[4][3] = " B ";
	board.board[4][4] = " W ";
}

void Otello::run_game(OutputInterface out, Board& board){
	initialize_board(board);
	out.show_board(board);
	while (board.empty_cells){
		std::cout << board.empty_cells << std::endl;
		board.empty_cells --;
	
	}
}

int main(){
	Otello game;
	Board board;
	OutputInterface out;
	InputInterface input;
	game.run_game(out, board);

	std::cout << board.find_winer() << std::endl;
	
	std::string black_name;
	std::cout << "Enter name of black player:" << endl;
	std::cin >> black_name;
	Player black(black_name);
	std::cout << black.name << " has " << black.get_number_of_disks() << " disks." << std::endl;
}
