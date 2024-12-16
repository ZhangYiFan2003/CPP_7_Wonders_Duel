#ifndef SideBoard_h
#define SideBoard_h

#include "GameLogicHeader.h"

class Jeton{
private:
	unsigned int id;
	std::string name;
	bool discardedFlag = false;
	bool takenFlag = false;

public:
	Jeton(int i, std::string n) : id(i), name(n), takenFlag(false) {}
	unsigned int& getID() { return id; }
	std::string& getName() { return name; }
	bool& getDiscardedFlag() { return discardedFlag; }
	bool& getTakenFlag() { return takenFlag; }
	void setDiscardedFlag(bool flag) { discardedFlag = flag; }
	void setTakenFlag(bool flag) { takenFlag = flag; }
};

class SideBoard{
private:
	std::array<Jeton*, 10> Jetons;
	std::array<Jeton*, 5> JetonsDeck; //la liste des jetons qui sera sur le plateau
	std::array<Jeton*, 3> JetonsNonPris; //la liste des jetons qui sera utiliser pour la pioche de jetons hors plateau
	int conflictPawnPosition = 0;

	bool left_2Coins_taken = false;
	bool left_5Coins_taken = false;

	bool right_2Coins_taken = false;
	bool right_5Coins_taken = false;

public:
	SideBoard();
	
	~SideBoard(){
		for (size_t i = 0; i < 10; i += 1) { delete Jetons.at(i); }
	}

	std::array<Jeton*, 5>& getJetonsDeck() { return JetonsDeck; }
	std::array<Jeton*, 3>& getJetonsNonPris() { return JetonsNonPris; }
	unsigned int getNumJetonsRestants();
	int& getConflictPawnPosition() { return conflictPawnPosition; }
	bool& getLeft2CoinsTaken() { return left_2Coins_taken; }
	bool& getLeft5CoinsTaken() { return left_5Coins_taken; }
	bool& getRight2CoinsTaken() { return right_2Coins_taken; }
	bool& getRight5CoinsTaken() { return right_5Coins_taken; }
	std::array<bool, 4> getLootingFlags(){
		std::array<bool, 4> lootingFlags;
		lootingFlags[0] = left_5Coins_taken;
		lootingFlags[1] = left_2Coins_taken;
		lootingFlags[2] = right_2Coins_taken;
		lootingFlags[3] = right_5Coins_taken;
		return lootingFlags;
	}

	void setConflictPawnPosition(int pos) { conflictPawnPosition = pos; }
	void setLeft2CoinsTaken(bool flag) { left_2Coins_taken = flag; }
	void setLeft5CoinsTaken(bool flag) { left_5Coins_taken = flag; }
	void setRight2CoinsTaken(bool flag) { right_2Coins_taken = flag; }
	void setRight5CoinsTaken(bool flag) { right_5Coins_taken = flag; }
};

#endif // !SideBoard_h