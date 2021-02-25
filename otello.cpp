#include<utility>
#include<iostream>
#include<vector>

using namespace std;

typedef  std::pair<std::pair<int,int>,std::pair<int,int>> path;

class Exception{};

class Player{
public:	
	Player(std::string name);
	std::string name;
	std::string label;
};


Player::Player(std::string name):name(name){ 
	label = name.at(0);
	label.insert(0, " ");
	label.append(" "); 
} ;


class Board{
public:
	Board(): board(8, std::vector<std::string>(8, " O ")), empty_cells(64), black_cells(0), white_cells(0){};
	std::string find_winer();
	void place_disk(std::pair<int,int> disk_location, Player player);	
	void flip_disks(std::pair<int,int> disk_location, Player player);
private:
	friend class Otello;
	friend class OutputInterface;
	std::vector<std::vector<std::string>> board;
	int empty_cells;
	int black_cells;
	int white_cells;
	std::vector<path> find_all_paths(std::pair<int,int> disk_location, std::string disk_color);	
};

void Board::place_disk(std::pair<int,int> disk_location, Player player){
	board[disk_location.first][disk_location.second] = player.label;
	if (player.name == "Black")
		black_cells++;
	else
		white_cells++;
}

std::vector<path> Board::find_all_paths(std::pair<int,int> disk_location, std::string disk_color){
	std::vector<path> all_paths;
	all_paths.push_back(std::make_pair(std::make_pair(2,3), std::make_pair(4,3)));
	return all_paths;
}

void Board::flip_disks(std::pair<int,int> disk_location, Player player){
	std::vector<path> all_paths;
	all_paths = find_all_paths(disk_location, player.label);
	std::string opponent_label;
	if (player.label == " W ")
		opponent_label = " B ";
	else
		opponent_label = " W ";
	std::cout<<"player_lable:" << player.label<<",opponent_label:"<<opponent_label<<std::endl;

	for (auto path_iter = all_paths.begin(); path_iter< all_paths.end(); path_iter++){
		std::pair<int,int> start, end;
		start = path_iter->first;
		end = path_iter->second;
		if (start.first == end.first)
			std::replace(&board[start.first][start.second+1], &board[end.first][end.second], opponent_label, player.label);
		else if (start.second == end.second)
			for(int i= start.first+1; i<end.first; i++)
				if(board[i][start.second] == opponent_label)
					board[i][start.second] = player.label;
				else
					std::cout<<"1"<<std::endl;
					//throw Exception();
		else if (start.first<end.first && start.second<end.second)
			for (int i=start.first, j=start.second; i<end.first && j<end.second; i++, j++)
				if (board[i][j] == opponent_label)
					board[i][j] = player.label;
				else	
					std::cout<<"2"<<std::endl;
					//throw Exception();
		else if (start.first>end.first && start.second<end.second)
			for (int i=start.first, j=start.second; i>end.first && j<end.second; i--, j++)
				if (board[i][j] == opponent_label)	
					board[i][j] = player.label;
				else	
					std::cout<<"3"<<std::endl;
					//throw Exception();
		else
			std::cout<<"4"<<std::endl;
			//throw Exception();
		
	}
}


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
		std::cout << "("<< move.first <<"," << move.second << ") ";
	std::cout<<std::endl;
}


 
class Otello{
public:	
	Otello():number_of_disks(64){};
	void initialize_board(Board& board);
	void run_game(OutputInterface out,InputInterface in, Board& board, Player &black, Player &white);
private:
	int number_of_disks;
	void is_valid_move();
	//std::vector<std::pair<int,int>> find_available_moves(Board &board, Player& current_player){};
	void find_available_moves(Board &board, Player& current_player){};

};

void Otello::initialize_board(Board& board) {
	board.board[3][3] = " W ";
	board.board[3][4] = " B ";
	board.board[4][3] = " B ";
	board.board[4][4] = " W ";
	number_of_disks -= 4;
	board.empty_cells -=4;
	board.black_cells = 2;
	board.white_cells = 2;


}


void Otello::run_game(OutputInterface out, InputInterface in, Board& board, Player &black, Player &white){
	initialize_board(board);
	out.show_board(board);
	std::vector<std::pair<int,int>> available_moves = {std::make_pair(2,3)};
	Player current_player = black;
	std::cout << "set current player to black" << std::endl;
	std::pair<int,int> current_move;
	while (board.empty_cells){
		std::cout << "-----------------------------" << std::endl;
		//available_moves = find_available_moves(board, current_player);
		//out.show_available_moves(available_moves, current_player.name);	
		current_move = in.get_move();	
		std::cout << current_move.first<< "," << current_move.second << std::endl;
		std::cout << board.empty_cells << std::endl;
		board.place_disk(current_move, current_player);
		out.show_board(board);
		if (!available_moves.empty())
			board.empty_cells --;

		board.flip_disks(current_move, current_player);	
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
