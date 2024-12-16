#ifndef Player_h
#define Player_h

#include "GameLogicHeader.h"
#include "Card.h"
#include "SideBoard.h"

class Joueur{
private:
	std::string name;
	unsigned int coins = 0;
	std::map<Ressources, int> ressource_joueur;
	std::vector<std::vector<Ressources>> ressource_special = {};
	std::vector<std::vector<Ressources>> ressource_choix;
	std::map<Ressources, int> cout_achat;
	unsigned int vic_point = 0;
	unsigned int mil_power = 0;
	std::vector<Symboles_scientifique> sym_scientifique;
	std::vector<Symboles_special> sym_spe;
	std::vector<Jeton*> Jetons;
	unsigned int numJetonsPosseder = 0;
	unsigned int numJetonsAchetables = 0;
	std::vector<Card*> cards_brown;
	std::vector<Card*> cards_grey;
	std::vector<Card*> cards_blue;
	std::vector<Card*> cards_green;
	std::vector<Card*> cards_yellow;
	std::vector<Card*> cards_red;
	std::vector<Card*> cards_purple;
	std::array<Card*, 4> wonders{};
	bool currentPlayerFlag = false;

public:
	Joueur(std::string n) : name(n), coins(7), vic_point(0), mil_power(0) {}
	
	std::string& getName() {return name;}
	unsigned int& getCoins() {return coins;}
	unsigned int& getVicPoint() {return vic_point;}
	unsigned int& getMilPower() {return mil_power;}
	std::map<Ressources, int>& getRessourceJoueur() { return ressource_joueur; }
	std::vector<Symboles_scientifique>& getSsc() { return sym_scientifique; };
	std::vector<Symboles_special>& getSp() { return sym_spe; };
	std::vector<std::vector<Ressources>>& getRessourceChoix() { return ressource_choix; }
	std::vector<Jeton*>& getJetons() { return Jetons; }
	unsigned int& getNumJetonsPosseder() { return numJetonsPosseder; }
	unsigned int& getNumJetonsAchetables() { return numJetonsAchetables; }
	std::map<Ressources, int> getCout() { return cout_achat; }
	std::vector<Card*>& getCards_Brown() {return cards_brown;}
	std::vector<Card*>& getCards_Grey() {return cards_grey;}
	std::vector<Card*>& getCards_Blue() {return cards_blue;}
	std::vector<Card*>& getCards_Green() {return cards_green;}
	std::vector<Card*>& getCards_Yellow() {return cards_yellow;}
	std::vector<Card*>& getCards_Red() {return cards_red;}
	std::vector<Card*>& getCards_Purple() { return cards_purple; }
	std::vector<Card*> getCards();
	std::array<Card*, 4>& getWonders() { return wonders; }
	bool& getCurrentPlayerFlag() { return currentPlayerFlag; }
	void setCurrentPlayerFlag(bool flag) { currentPlayerFlag = flag; }
	void init_achat();

	void incCoins(unsigned int ic) { coins += ic; }

	void ajout_Ressource(std::map<Ressources, int> r);

	void ajout_Ressource_Choix(std::vector<Ressources> r) {
		ressource_choix.push_back(r);
	}

	void modif_CoutAchat(std::map<Ressources, int> r);

	void reduction_ressource(Ressources r) {
		cout_achat[r] = 1;
	}
	
	void incVicPoint(int iv) { vic_point += iv; }
	void incMilPower(unsigned int im) { mil_power += im; }
	void incNumJetonsPosseder() { numJetonsPosseder += 1; }
	void incNumJetonsAchetables() { numJetonsAchetables += 1; }
	void decNumJetonsAchetables() { numJetonsAchetables -= 1; }

	unsigned int decCoins(unsigned int dc);
	
	
	void decVicPoint(unsigned int dv);
	
	void decMilPower(unsigned int dm);
	
	void obtainJetons(Jeton* pt, bool obtainableFlag, bool freeFlag);

	void ajout_SymSp(Symboles_special sp) {
		sym_spe.push_back(sp);
	}

	void ajout_SymSci(Symboles_scientifique sc) {
		sym_scientifique.push_back(sc);
	}

	void obtainCard_Brown(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_brown.push_back(card);
	}
	void obtainCard_Grey(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_grey.push_back(card);
	}
	void obtainCard_Blue(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_blue.push_back(card);
	}
	void obtainCard_Green(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_green.push_back(card);
	}
	void obtainCard_Yellow(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_yellow.push_back(card);
	}
	void obtainCard_Red(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_red.push_back(card);
	}
	void obtainCard_Purple(Card* card, bool confirmFlag)
	{
		if (!confirmFlag) { return; }
		cards_purple.push_back(card);
	}


	//A reverifier tout ce qui est en dessous
	void obtainWonder(Card* wdr, bool confirmFlag);
	
	void distributeWonders(std::array<Card*, 4> wdrs) { wonders = wdrs; }
	void constructWonder(unsigned int wonderID, bool constructibleFlag)
	{
		if (!constructibleFlag) { return; }
		for (auto it = wonders.begin(); it != wonders.end(); ++it)
		{
			if ((*it)->getID() == wonderID) { (*it)->setConstructedFlag(true); }
		}
	}

};

#endif // !Player_h