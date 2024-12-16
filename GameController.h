#ifndef GameController_h
#define GameController_h

#include "Deck.h"
//#include "SideBoard.h"
#include "Player.h"
//#include "QtHeader.h"


class GameController{
private:
	GameController() { init_Game(); }
	~GameController()
	{
		delete deck;
		delete player1;
		delete player2;
		delete sideBoard;
	}
	GameController(const GameController&) = delete;
	GameController& operator=(const GameController&) = delete;

	Deck* deck = nullptr;
	Joueur* player1 = nullptr;
	Joueur* player2 = nullptr;
	Joueur* winner = nullptr;
	SideBoard* sideBoard = nullptr;
	unsigned int numCardTaken = 0;
	unsigned int numWonderBuilt = 0;
	bool rejouerFlag = false;			// indique si le joueur actuel peut rejouer
	bool hasPlayedFlag = false;			// indique si le joueur actuel a fini son tour

	bool verifyChainSymbol(Joueur* player, Card* card);

	bool verifyItems(Joueur* player, Card* card, std::map<Ressources, int>& nums_LackItems);

	//std::vector<Ressources> chooseResources(Joueur* player, std::vector<std::vector<Ressources>>& rsc, std::map<Ressources, int>& nums_LackItems);

	Ressources chooseReduction(Joueur* player, std::vector<Ressources>& rsc, std::map<Ressources, int>& nums_LackItems);

	bool verifyCoins(Joueur* player, Card* card, std::map<Ressources, int>& nums_LackItems, unsigned int& extraCost);

	bool verifySciSymbols(Joueur* player);

	bool verifyMilitarySupremacy();

	bool verifyScientificSupremacy(Joueur* player);
	
	bool verifyCivilianVictory();

	void handleCardObtained_Brown(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);
	
	void handleCardObtained_Grey(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleCardObtained_Blue(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleCardObtained_Green(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleCardObtained_Yellow(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleCardObtained_Red(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleCardObtained_Purple(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag);

	void handleWonderObtained(Joueur* player, Card* building, Card* wonder, unsigned int extraCost, bool confirmFlag);

public:
	static GameController& getInstance();

	Deck* getDeck() { return deck; }
	Joueur* getPlayer1() { return player1; }
	Joueur* getPlayer2() { return player2; }
	Joueur* getCurrentPlayer()
	{
		return player1->getCurrentPlayerFlag() ? player1 : player2;
	}
	Joueur* getWinner() { return winner; }
	SideBoard* getSideBoard() { return sideBoard; }
	bool& getRejouer() { return rejouerFlag; }
	bool& getHasPlayed() { return hasPlayedFlag; }
	void setRejouer(bool flag) { rejouerFlag = flag; }
	void setHasPlayed(bool flag) { hasPlayedFlag = flag; }
	unsigned int& getNumCardTaken() { return numCardTaken; }
	unsigned int& getNumWonderBuilt() { return numWonderBuilt; }

	void init_Game();

	char constructBuilding(Joueur* player, Card* card);
	
	void discardBuilding(Joueur* player, Card* card);
	
	char constructWonder(Joueur* player, Card* building, Card* wonder);
	
	void checkLootingToken();

	int updateSideBoard();
	
	char takeJeton(Joueur* player, Jeton* jeton);

	bool checkVictoryConditions();

	void destructBuilding(Joueur* player, Card* card); //permet de détruire un batiment déjà construit
};

#endif // !GameController_h