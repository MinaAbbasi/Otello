#include<iostream>
using namespace std;

class Exception{};

class Player{
public:	
	
	Player(std::string name):name(name), number_of_disks(32){};	
	std::string name;
	void borrow_disk(Player &opponent);
	int get_number_of_disks() {return number_of_disks;};
	
private:
	std::string color;
	int number_of_disks;
};

void Player::borrow_disk(Player &opponent){
	if (number_of_disks > 0)
		throw Exception();
	if (opponent.number_of_disks){ 
		opponent.number_of_disks--;
		number_of_disks++;
	}
}



class Board{
public:
	void show_board();
private:
};

class InputInterface{};

class OutputInterface{};
 
class Otello{};


int main(){
	std::string black_name;
	std::cout << "Enter name of black player:" << endl;
	std::cin >> black_name;
	Player black(black_name);
	std::cout << black.name << " has " << black.get_number_of_disks() << " disks." << std::endl;
}
