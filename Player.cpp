#include "Player.h"

unsigned int Joueur::decCoins(unsigned int dc){
	if (coins >= dc)
	{
		coins -= dc;
		return dc;
	}
	else
	{
		int tmpVal = coins;
		coins = 0;
		return tmpVal;
	}
}

void Joueur::decVicPoint(unsigned int dv){
	if (vic_point >= dv) { vic_point -= dv; }
	else { vic_point = 0; }
}

void Joueur::decMilPower(unsigned int dm){
	if (mil_power >= dm) { mil_power -= dm; }
	else { mil_power = 0; }
}

void Joueur::ajout_Ressource(std::map<Ressources, int> r) {
	std::map<Ressources, int>::iterator it;
	for (it = r.begin(); it != r.end(); ++it) {
		if (it->first == Ressources::piece) {

			coins += it->second;
		}
		else if (it->first == Ressources::point_victoire) {
			vic_point += it->second;
		}
		else if (it->first == Ressources::puissance_millitaire) {
			mil_power += it->second;
		}
		else {
			ressource_joueur[it->first] += it->second;
		}
	}
}

void Joueur::obtainWonder(Card* wdr, bool confirmFlag){
	if (!confirmFlag) { return; }
	
}

std::vector<Card*> Joueur::getCards(){
	std::vector<Card*> tmpCards;
	tmpCards.insert(tmpCards.end(), cards_brown.begin(), cards_brown.end());
	tmpCards.insert(tmpCards.end(), cards_grey.begin(), cards_grey.end());
	tmpCards.insert(tmpCards.end(), cards_blue.begin(), cards_blue.end());
	tmpCards.insert(tmpCards.end(), cards_green.begin(), cards_green.end());
	tmpCards.insert(tmpCards.end(), cards_yellow.begin(), cards_yellow.end());
	tmpCards.insert(tmpCards.end(), cards_red.begin(), cards_red.end());
	tmpCards.insert(tmpCards.end(), cards_purple.begin(), cards_purple.end());
	return tmpCards;
}

void Joueur::modif_CoutAchat(std::map<Ressources, int> r) {
	std::map<Ressources, int>::iterator it;
	for (it = r.begin(); it != r.end(); ++it) {
		if (it->first != Ressources::point_victoire && it->first != Ressources::puissance_millitaire && it->first != Ressources::piece) {
			if (cout_achat[it->first] != 1)
				cout_achat[it->first] += it->second;
		}
	}
}

void Joueur::init_achat() {
	cout_achat[Ressources::bois] = 2;
	cout_achat[Ressources::brique] = 2;
	cout_achat[Ressources::papier] = 2;
	cout_achat[Ressources::pierre] = 2;
	cout_achat[Ressources::verre] = 2;
	ressource_joueur[Ressources::bois] = 0;
	ressource_joueur[Ressources::brique] = 0;
	ressource_joueur[Ressources::papier] = 0;
	ressource_joueur[Ressources::pierre] = 0;
	ressource_joueur[Ressources::verre] = 0;
}

void Joueur::obtainJetons(Jeton* pt, bool obtainableFlag, bool freeFlag){
	if (!obtainableFlag) { return; }
	if (!freeFlag) { decNumJetonsAchetables(); }
	if (pt->getName() == "Agriculture"){
		incCoins(6);
		incVicPoint(4);
	}
	else if (pt->getName() == "Loi"){
		ajout_SymSci(Symboles_scientifique::balance);
	}
	else if (pt->getName() == "Urbanisme"){
		incCoins(6);
	}
	else if (pt->getName() == "Philosophie"){
		incVicPoint(7);
	}
	Jetons.push_back(pt);
}