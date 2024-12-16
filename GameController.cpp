#include "GameController.h"
#include <QDebug>

GameController& GameController::getInstance() {
	static GameController instance;
	return instance;
}

bool GameController::verifyChainSymbol(Joueur* player, Card* card){
	// Get the ID of the chain symbol required by the card
	Symboles_special card_CS_id1 = card->getSymbolespe1();
	Symboles_special card_CS_id2 = card->getSymbolespe2();

	if (card_CS_id1 != Symboles_special::aucun) {
		for (int i = 0; i < player->getSp().size(); i++) {
			if (card_CS_id1 == player->getSp()[i]) {
				for (int i = 0; i < player->getJetons().size(); i++){
					Jeton* jeton = player->getJetons()[i];
					if (jeton->getName() == "Urbanisme")
						player->incCoins(4);
				}
				return true;
			}
		}

	}
	//on v�rifie aussi il n'y a pas de 2eme symbole
	else if (card_CS_id2 != Symboles_special::aucun) {
		for (int i = 0; i < player->getSp().size(); i++) {
			if (card_CS_id2 == player->getSp()[i]) {
				for (int i = 0; i < player->getJetons().size(); i++) {
					Jeton* jeton = player->getJetons()[i];
					if (jeton->getName() == "Urbanisme")
						player->incCoins(4);
				}
				return true;
			}
		}

	}

	// If not, return false
	return false;
}

bool GameController::verifyItems(Joueur* player, Card* card, std::map<Ressources, int>& nums_LackItems){
	// Reset the array of numbers representing lacking items to all zeros
	nums_LackItems = {};

	// Get the array of items needed to construct the card
	std::map<Ressources, int> itemsNeeded(card->getCoutAchat());

	// Get the array of items possessed by the player
	std::map<Ressources, int> playersItems(player->getRessourceJoueur());

	// Get the array of items choices possessed by the player
	std::vector<std::vector<Ressources>> ressource_choix(player->getRessourceChoix());
	

	// Reduce the cost by the items possessed by the player
	std::vector<Ressources> rsc = { Ressources::brique, Ressources::bois , Ressources::pierre, Ressources::verre, Ressources::papier };
	for (int i = 0; i < rsc.size(); i++) {
		// If the player has fewer items than needed
		if (playersItems[rsc[i]] < itemsNeeded[rsc[i]]) {
			nums_LackItems[rsc[i]] = itemsNeeded[rsc[i]] - playersItems[rsc[i]];
		}
		else {
			nums_LackItems[rsc[i]] = 0;
		}
	}

	// Reduce the cost by the items choices possessed by the player
	if (!ressource_choix.empty()) {
		for (size_t i = 0; i < ressource_choix.size(); i++) {
			if (!ressource_choix[i].empty()) {
				Ressources ressource = chooseReduction(player, ressource_choix[i], nums_LackItems);
				if (nums_LackItems[ressource] > 0) {
					nums_LackItems[ressource]--;
				}
			}
		}
	}

	// Reduce the cost if the player has Maconnerie or Architecture tokens and the card type matches
	bool reductionFromToken = false;
	for (int i = 0; i < player->getJetons().size(); i++) {
		Jeton* jeton = player->getJetons()[i];
		if (jeton->getName() == "Maconnerie") {
			if (card->getTypes() == Types::civils) {
				reductionFromToken = true;
			}
		}
		if (jeton->getName() == "Architecture") {
			if (card->getTypes() == Types::Merveille) {
				reductionFromToken = true;
			}
		}
	}
	if (reductionFromToken) {
		for (unsigned int i = 0; i < 2; i++) {
			Ressources ressource = chooseReduction(player, rsc, nums_LackItems);

			if (nums_LackItems[ressource] > 0) {
				nums_LackItems[ressource]--;
			}
		}
	}

	// Initialize a flag to indicate if items are sufficient
	bool itemsSufficientFlag = true;
	for (size_t i = 0; i < rsc.size(); i++) {
		if (nums_LackItems[rsc[i]] > 0) {
			itemsSufficientFlag = false;
		}
	}
	// Return the flag indicating if items are sufficient
	return itemsSufficientFlag;
}

Ressources GameController::chooseReduction(Joueur* player, std::vector<Ressources>& rsc, std::map<Ressources, int>& nums_LackItems) {
	std::map<Ressources, int> prix = player->getCout();
	Ressources r = rsc[0];

	int max = 0;
	size_t Indicemax = 0;
	for (size_t j = 0; j < rsc.size(); j++) {
		if ((prix[rsc[j]] >= max) && (nums_LackItems[rsc[j]] > 0)) {
			max = prix[rsc[j]];
			Indicemax = j;
		}
		r = rsc[Indicemax];
	}
	return r;
}


bool GameController::verifyCoins(Joueur* player, Card* card, std::map<Ressources, int>& nums_LackItems, unsigned int& extraCost){
	// Initialize an array to store items possessed by the competitor player
	std::map<Ressources,int> prix;

	// Determine the competitor player and get their items
	if (player == player1) {

		prix = player1->getCout();
	}
	else { prix = player2->getCout(); }

	// Initialize extraCost to zero
	extraCost = 0;

	// Iterate over each item type: clay, wood, stone, glass, papyrus
	std::vector<Ressources> rsc = { Ressources::brique, Ressources::bois , Ressources::pierre, Ressources::verre, Ressources::papier };
	for (int i = 0; i < 5; i++) {
		// If there are lacking items of this type
		for (int j = 0; j < nums_LackItems[rsc[i]]; j++) {
			// Calculate the extra cost based on the number of lacking items and the number of items possessed by the competitor player
			extraCost += prix[rsc[i]];
		}
	}
	
	// If the player's coins are less than the total cost (including extra cost) required to construct the card, return false; otherwise, return true
	if (player->getCoins() < (card->getCoutAchat()[Ressources::piece] + extraCost)) { return false; }
	else { 
		// Give the coins to the other player if they have the Economy token
		for (int i = 0; i < player1->getJetons().size(); i++) {
			Jeton* jeton = player1->getJetons()[i];
			if (jeton->getName() == "Economie")
				if (player != player1)
					player1->incCoins(extraCost);
		}
		for (int i = 0; i < player2->getJetons().size(); i++) {
			Jeton* jeton = player2->getJetons()[i];
			if (jeton->getName() == "Economie")
				if (player != player2)
					player2->incCoins(extraCost);
		}

		return true;
	}
}

bool GameController::verifySciSymbols(Joueur* player){

	// Check if the player has any progress tokens available
	if (player->getNumJetonsAchetables() > 0) { return true; }
	else { return false; }
}

bool GameController::verifyMilitarySupremacy(){
	if (sideBoard->getConflictPawnPosition() >= 9)
	{
		winner = player1;
		return true;
	}
	if (sideBoard->getConflictPawnPosition() <= -9)
	{
		winner = player2;
		return true;
	}
	return false;
}

bool GameController::verifyScientificSupremacy(Joueur* player){
	// Check if the player is the current player
	if (!player->getCurrentPlayerFlag()) { return false; }

	// Initialize a counter to count the number of different scientific symbols owned by the player
	unsigned int numSciSymDiff = 0;

	// Get the array of scientific symbols possessed by the player
	std::vector<Symboles_scientifique> plyrsSciSyms = player->getSsc();

	// Iterate over each scientific symbol type
	numSciSymDiff = plyrsSciSyms.size();

	// Check if the player has at least 6 different scientific symbols
	// If so, declare the player as the winner and return true; otherwise, return false
	if (numSciSymDiff >= 6){
		winner = player;
		return true;
	}
	else { return false; }
}

bool GameController::verifyCivilianVictory(){
	// Get the position of the conflict pawn
	int cpPosition = sideBoard->getConflictPawnPosition();

	// If the conflict pawn is on the right side
	if (cpPosition > 0)
	{
		// Increment player 1's victory points based on the conflict pawn position
		if ((1 <= cpPosition) && (cpPosition <= 2)) { player1->incVicPoint(2); }
		else if ((3 <= cpPosition) && (cpPosition <= 5)) { player1->incVicPoint(5); }
		else if (6 <= cpPosition) { player1->incVicPoint(10); }
	}
	// If the conflict pawn is on the left side
	else if (cpPosition < 0)
	{
		// Increment player 2's victory points based on the conflict pawn position
		if ((-2 <= cpPosition) && (cpPosition <= -1)) { player2->incVicPoint(2); }
		else if ((-5 <= cpPosition) && (cpPosition <= -3)) { player2->incVicPoint(5); }
		else if (cpPosition <= -6) { player2->incVicPoint(10); }
	}

	for (int i = 0; i < player1->getJetons().size(); i++){
		Jeton* jeton = player1->getJetons()[i];
		if (jeton->getName() == "Mathematiques")
			player1->incVicPoint(3*player1->getJetons().size());
	}

	for (int i = 0; i < player2->getJetons().size(); i++){
		Jeton* jeton = player2->getJetons()[i];
		if (jeton->getName() == "Mathematiques")
			player2->incVicPoint(3*player2->getJetons().size());
	}

	for (size_t i = 0; i < player1->getCards_Purple().size() ; i ++){
		Card* card = player1->getCards_Purple()[i];
		Guilde* guild = static_cast<Guilde*>(card);
		std::map<Types, unsigned int>::iterator it;
		for(it=guild->getEffet().begin(); it!=guild->getEffet().end(); ++it){
			if (it->first==Types::commerciaux){	
				if (player1->getCards_Yellow().size() > player2->getCards_Yellow().size()) player1->incVicPoint(player1->getCards_Yellow().size());
				else player1->incVicPoint(player2->getCards_Yellow().size());
			}
			else if (it->first==Types::Matiere_Premiere){
				if ((player1->getCards_Brown().size() + player1->getCards_Grey().size()) > (player2->getCards_Brown().size() + player2->getCards_Grey().size()))  player1->incVicPoint((player1->getCards_Brown().size() + player1->getCards_Grey().size()));
				else player1->incVicPoint((player2->getCards_Brown().size() + player2->getCards_Grey().size()));
			}
			else if (it->first==Types::civils){
				if (player1->getCards_Blue().size() > player2->getCards_Blue().size())  player1->incVicPoint(player1->getCards_Blue().size());
				else player1->incVicPoint(player2->getCards_Blue().size());
			}
			else if(it->first==Types::scientifique){
				if (player1->getCards_Green().size() > player2->getCards_Green().size())  player1->incVicPoint(player1->getCards_Green().size());
				else player1->incVicPoint(player2->getCards_Green().size());
			}
			else if (it->first==Types::militaires){
				if (player1->getCards_Red().size() > player2->getCards_Red().size())  player1->incVicPoint(player1->getCards_Red().size());
				else player1->incVicPoint(player2->getCards_Red().size());
			}
			else if (it->first==Types::Merveille){
				int cptMerveille1 = 0;
				int cptMerveille2 = 0;
				for (int i = 0; i < player1->getWonders().size(); i++){
					if (player1->getWonders()[i]->getConstructedFlag())
						cptMerveille1+=1;
				}
				for (int i = 0; i < player2->getWonders().size(); i++){
					if (player2->getWonders()[i]->getConstructedFlag())
						cptMerveille2+=1;
				}
				if (cptMerveille1 > cptMerveille2)  player1->incVicPoint(cptMerveille1*(it->second));
				else player1->incVicPoint(cptMerveille2*(it->second));
			}
			else if (it->first == Types::aucun){
				int nbPiece1 = (int)floor(player1->getCoins()/3);
				int nbPiece2 = (int)floor(player2->getCoins()/3);
				if (nbPiece1 > nbPiece2)  player1->incVicPoint(nbPiece1*(it->second));
				else player1->incVicPoint(nbPiece2*(it->second));
			}
		}
	}
	//meme chose pour le player2
	for (size_t i = 0; i < player2->getCards_Purple().size(); i++) {
		Card* card = player2->getCards_Purple()[i];
		Guilde* guild = static_cast<Guilde*>(card);
		std::map<Types, unsigned int>::iterator it;
		for (it = guild->getEffet().begin(); it != guild->getEffet().end(); ++it) {
			if (it->first == Types::commerciaux) {
				if (player1->getCards_Yellow().size() > player2->getCards_Yellow().size()) player2->incVicPoint(player1->getCards_Yellow().size());
				else player2->incVicPoint(player2->getCards_Yellow().size());
			}
			else if (it->first == Types::Matiere_Premiere) {
				if ((player1->getCards_Brown().size() + player1->getCards_Grey().size()) > (player2->getCards_Brown().size() + player2->getCards_Grey().size()))  player2->incVicPoint((player1->getCards_Brown().size() + player1->getCards_Grey().size()));
				else player2->incVicPoint((player2->getCards_Brown().size() + player2->getCards_Grey().size()));
			}
			else if (it->first == Types::civils) {
				if (player1->getCards_Blue().size() > player2->getCards_Blue().size())  player2->incVicPoint(player1->getCards_Blue().size());
				else player2->incVicPoint(player2->getCards_Blue().size());
			}
			else if (it->first == Types::scientifique) {
				if (player1->getCards_Green().size() > player2->getCards_Green().size())  player2->incVicPoint(player1->getCards_Green().size());
				else player2->incVicPoint(player2->getCards_Green().size());
			}
			else if (it->first == Types::militaires) {
				if (player1->getCards_Red().size() > player2->getCards_Red().size())  player2->incVicPoint(player1->getCards_Red().size());
				else player2->incVicPoint(player2->getCards_Red().size());
			}
			else if (it->first == Types::Merveille) {
				int cptMerveille1 = 0;
				int cptMerveille2 = 0;
				for (int i = 0; i < player1->getWonders().size(); i++) {
					if (player1->getWonders()[i]->getConstructedFlag())
						cptMerveille1 += 1;
				}
				for (int i = 0; i < player2->getWonders().size(); i++) {
					if (player2->getWonders()[i]->getConstructedFlag())
						cptMerveille2 += 1;
				}
				if (cptMerveille1 > cptMerveille2)  player2->incVicPoint(cptMerveille1 * (it->second));
				else player2->incVicPoint(cptMerveille2 * (it->second));
			}
			else if (it->first == Types::aucun) {
				int nbPiece1 = (int)floor(player1->getCoins() / 3);
				int nbPiece2 = (int)floor(player2->getCoins() / 3);
				if (nbPiece1 > nbPiece2)  player2->incVicPoint(nbPiece1 * (it->second));
				else player2->incVicPoint(nbPiece2 * (it->second));
			}
		}
	}

	// Increment player 1 and player 2's victory points based on their coins
	player1->incVicPoint((int)floor(player1->getCoins() / 3));
	player2->incVicPoint((int)floor(player2->getCoins() / 3));

	// Determine the winner based on their victory points
	if (player1->getVicPoint() > player2->getVicPoint()) { winner = player1; }
	else if (player1->getVicPoint() < player2->getVicPoint()) { winner = player2; }
	// If the victory points are equal, compare the number of blue cards
	else{
		size_t num_p1_blueCards = player1->getCards_Blue().size();
		size_t num_p2_blueCards = player2->getCards_Blue().size();
		if (num_p1_blueCards > num_p2_blueCards) { winner = player1; }
		//////////else if (num_p1_blueCards = num_p2_blueCards)
		else { winner = player2; }
	}

	// Return true indicating the verification of civilian victory
	return true;
}

void GameController::handleCardObtained_Brown(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag)
{
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the brown card and confirms card acquisition
	player->obtainCard_Brown(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);
	const Bat_normal* bat = static_cast<const Bat_normal*>(card);
	// Get the reference to the array of items produced by the card
	std::map<Ressources, int> itemsObtained(bat->getProduction());

	// Get the reference to the player's array of items
	std::map<Ressources, int>& playersItems(player->getRessourceJoueur());

	std::map<Ressources, int>::iterator it1;
	//on va ajouter les productions aux matériaux posséder par le joueur1
	for (it1 = itemsObtained.begin(); it1 != itemsObtained.end(); ++it1) {
		Ressources productionType = it1->first;
		int quantity = it1->second;
		playersItems[productionType] += quantity;
		if (player != player1)
			player1->modif_CoutAchat({ { productionType, quantity } });
		else player2->modif_CoutAchat({ { productionType, quantity } });
	}
	// Deduct the card's coin cost and extra cost from the player's coins
	player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost);
}

void GameController::handleCardObtained_Grey(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the grey card and confirms card acquisition
	player->obtainCard_Grey(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	const Bat_normal* bat = static_cast<const Bat_normal*>(card);
	// Get the reference to the array of items produced by the card
	std::map<Ressources, int> itemsObtained(bat->getProduction());

	// Get the reference to the player's array of items
	std::map<Ressources, int>& playersItems(player->getRessourceJoueur());

	std::map<Ressources, int>::iterator it1;
	//on va ajouter les productions aux matériaux posséder par le joueur1
	for (it1 = itemsObtained.begin(); it1 != itemsObtained.end(); ++it1) {
		Ressources productionType = it1->first;
		int quantity = it1->second;
		playersItems[productionType] += quantity;
		if (player != player1)
			player1->modif_CoutAchat({ { productionType, quantity } });
		else player2->modif_CoutAchat({ { productionType, quantity } });
	}
	// Deduct the card's coin cost and extra cost from the player's coins
	player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost);
}

void GameController::handleCardObtained_Blue(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the blue card and confirms card acquisition
	player->obtainCard_Blue(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	const Bat_normal* bat = static_cast<const Bat_normal*>(card);

	std::map<Ressources, int> prod = bat->getProduction();

	player->incVicPoint(prod[Ressources::point_victoire]);


	// If the card isn't constructed for free, deduct the card's coin cost and extra cost from the player's coins
	if (!freeFlag) { player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost); }
}

void GameController::handleCardObtained_Green(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the green card and confirms card acquisition
	player->obtainCard_Green(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	// Increment player's victory points based on the card's victory point value
	const Bat_Scientifique* bat = static_cast<const Bat_Scientifique*>(card);

	std::map<Ressources, int> prod = bat->getProduction();

	player->incVicPoint(prod[Ressources::point_victoire]);

	// Obtain the scientific symbol from the card and add it to the player's collection

	

	// If the player has a pair of identical obtained scientific symbols, increase the number of progress tokens available
	bool identique = false;
	if (bat->getSymbolesci() != Symboles_scientifique::aucun) {
		for (unsigned int i = 0; i < player->getSsc().size(); i++) {
			if (bat->getSymbolesci() == player->getSsc()[i]) {
				player->incNumJetonsAchetables();
				identique = true;
			}
		}
		if (!identique) player->ajout_SymSci(bat->getSymbolesci());
	}

	// If the card isn't constructed for free, deduct the card's coin cost and extra cost from the player's coins
	if (!freeFlag) { player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost); }
}

void GameController::handleCardObtained_Yellow(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the yellow card and confirms card acquisition
	player->obtainCard_Yellow(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	const Bat_Commercial* bat = static_cast<const Bat_Commercial*>(card);

	std::map<Ressources, int> prod = bat->getProduction();

	// Increment player's coins based on the card's coin production value
	player->incCoins(prod[Ressources::piece]);

	// Increment player's victory points based on the card's victory point value
	player->incVicPoint(prod[Ressources::point_victoire]);

	std::map<Ressources, int> solde_carte = bat->getRessourceEnSolde();
	std::map<Ressources, int>::iterator it1;
	//on va ajouter les productions aux matériaux posséder par le joueur1
	for (it1 = solde_carte.begin(); it1 != solde_carte.end(); ++it1){
		player->reduction_ressource(it1->first);
	}

	std::map<Types, unsigned int> bonus = bat->getBonus();
	std::map<Types, unsigned int>::iterator it2;
	//on va ajouter le bonus de piece au joueur1
	for (it2 = bonus.begin(); it2 != bonus.end(); ++it2) {
		if (it2->first == Types::Produit_manufacture) {
			player->incCoins(it2->second * (player->getCards_Brown().size()));
		}
		else if (it2->first == Types::Matiere_Premiere) {
			player->incCoins(it2->second * (player->getCards_Grey().size()));
		}
		else if (it2->first == Types::militaires) {
			player->incCoins(it2->second * (player->getCards_Red().size()));
		}
		else if (it2->first == Types::commerciaux) {
			player->incCoins(it2->second * (player->getCards_Yellow().size()));
		}
		if (it2->first == Types::Merveille) {
			int cptMerveille = 0;
			for (int i = 0; i < player->getWonders().size(); i++) {
				if (player->getWonders()[i]->getConstructedFlag())
					cptMerveille += 1;
			}
			player->incCoins(it2->second * cptMerveille);
		}
	}
	

	player->ajout_Ressource_Choix(bat->getRessourceProduite());

	// If the card isn't constructed for free, deduct the card's coin cost and extra cost from the player's coins
	if (!freeFlag) { player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost); }
}

void GameController::handleCardObtained_Red(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the red card and confirms card acquisition
	player->obtainCard_Red(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	for (int i = 0; i < player->getJetons().size(); i++){
		if (player->getJetons()[i]->getName() == "Strategie"){
			player->incMilPower(1);
		}
	}

	// Increase player's military power based on the card's military power value
	const Bat_normal* bat = static_cast<const Bat_normal*>(card);
	std::map<Ressources,int> prod = bat->getProduction();

	player->incMilPower(prod[Ressources::puissance_millitaire]);

	// If the card isn't constructed for free, deduct the card's coin cost and extra cost from the player's coins
	if (!freeFlag) { player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost); }
}

void GameController::handleCardObtained_Purple(Joueur* player, Card* card, bool freeFlag, unsigned int extraCost, bool confirmFlag){
	// If the card construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Player obtains the purple card and confirms card acquisition
	player->obtainCard_Purple(card, confirmFlag);

	// Set the constructed flag of the card to true
	card->setConstructedFlag(true);

	const Guilde* guilde = static_cast<const Guilde*>(card);

	std::map<Types, unsigned int>::iterator it;
	for(it=guilde->getEffet().begin(); it!=guilde->getEffet().end(); ++it){
		if (it->first==Types::commerciaux){	
			if (player1->getCards_Yellow().size() > player2->getCards_Yellow().size()) player1->incCoins(player1->getCards_Yellow().size());
			else player1->incCoins(player2->getCards_Yellow().size());
		}
		else if (it->first==Types::Matiere_Premiere){
			if ((player1->getCards_Brown().size() + player1->getCards_Grey().size()) > (player2->getCards_Brown().size() + player2->getCards_Grey().size()))  player1->incCoins((player1->getCards_Brown().size() + player1->getCards_Grey().size()));
			else player1->incCoins((player2->getCards_Brown().size() + player2->getCards_Grey().size()));
		}
		else if (it->first==Types::civils){
			if (player1->getCards_Blue().size() > player2->getCards_Blue().size())  player1->incCoins(player1->getCards_Blue().size());
			else player1->incCoins(player2->getCards_Blue().size());
		}
		else if(it->first==Types::scientifique){
			if (player1->getCards_Green().size() > player2->getCards_Green().size())  player1->incCoins(player1->getCards_Green().size());
			else player1->incCoins(player2->getCards_Green().size());
		}
		else if (it->first==Types::militaires){
			if (player1->getCards_Red().size() > player2->getCards_Red().size())  player1->incCoins(player1->getCards_Red().size());
			else player1->incCoins(player2->getCards_Red().size());
		}
	}
	// If the card isn't constructed for free, deduct the card's coin cost and extra cost from the player's coins
	if (!freeFlag) { player->decCoins(card->getCoutAchat()[Ressources::piece] + extraCost); }
}

void GameController::handleWonderObtained(Joueur* player, Card* building, Card* wonder, unsigned int extraCost, bool confirmFlag){
	// If the wonder construction isn't confirmed, return without doing anything
	if (!confirmFlag) { return; }

	// Increment the count of cards taken
	numCardTaken += 1;

	// Increment the count of wonders built
	numWonderBuilt += 1;

	// Set the constructed flag of the card to true
	building->setConstructedFlag(true);
	std::vector<Jeton*> jetons = player->getJetons();
	for (int i = 0; i < jetons.size(); i++){
		if (jetons[i]->getName() == "Theologie") rejouerFlag = true;
	}

	// Get the array of player's wonders
	std::array<Card*, 4>& playersWonders(player->getWonders());

	// Iterate over each wonder to find the wonder to be constructed
	for (size_t i = 0; i < 4; i += 1)
	{
		// If the wonder is found
		if (playersWonders.at(i) == wonder)	{
			// Set the constructed flag of the wonder to true
			playersWonders.at(i)->setConstructedFlag(true);

			if (wonder->getNom() == "Le Colosse"){
				player->incMilPower(2);
				player->incVicPoint(3);
			}
			else if (wonder->getNom() == "Le Temple D'Artemis"){
				player->incCoins(12);
				//faire rejouer le joueur actuel
				rejouerFlag = true;
			}
			else if (wonder->getNom() == "Le Piree"){
				player->incVicPoint(2);
				player->ajout_Ressource_Choix({Ressources::papier, Ressources::verre});
				//faire rejouer le joueur actuel
				rejouerFlag = true;
			}
			else if (wonder->getNom() == "La Statue De Zeus"){
				player->incMilPower(1);
				player->incVicPoint(3);
				//faire l'action piocher dans les cartes marron(matiere premiere) du joueur adverse et la retire
				std::vector<Card> c;
				

			}
			else if (wonder->getNom() == "Le Grand Phare"){
				player->incVicPoint(4);
				player->ajout_Ressource_Choix({Ressources::pierre, Ressources::bois, Ressources::brique});
			}
			else if (wonder->getNom() == "La Via Appia"){
				player->incCoins(3);
				if (player != player1){
					player1->decCoins(3);
				}
				else{
					player2->decCoins(3);
				}
				player->ajout_Ressource({{Ressources::point_victoire,3}});
				//faire rejouer le joueur actuel
				rejouerFlag = true;

			}
			else if (wonder->getNom() == "Le Circus Maximus"){
				player->incVicPoint(3);
				player->incMilPower(1);
				
				//faire l'action piocher dans les cartes grise(produit manufacturer) du joueur adverse et la retire
				std::vector<Card> c;
				
			}
			else if (wonder->getNom() == "Le Mausolee"){
				player->incVicPoint(2);
				//faire piocher dans la defausse

				std::vector<Card> c;
				

			}
			else if (wonder->getNom() == "La Grande Bibliotheque"){
				player->incVicPoint(4);
				//pioche 3 jetons et en choisi 1

			}
			else if (wonder->getNom() == "Le Sphinx"){
				player->incVicPoint(6);
				//fait rejouer le joueur
				rejouerFlag = true;

			}
			else if (wonder->getNom() == "Les Pyramides"){
				player->incVicPoint(9);

			}
			else if (wonder->getNom() == "Les Jardins Suspendus"){
				player->incCoins(6);
				player->incVicPoint(3);
				//fait rejouer le joueur actuel
				rejouerFlag = true;
			}

			// Deduct the extra cost from the player's coins
			player->decCoins(extraCost);
		}
	}
}

void GameController::init_Game(){
	if (deck){
		delete deck;
		deck = nullptr;
	}
	deck = new Deck;
	
	if (player1)
	{
		delete player1;
		player1 = nullptr;
	}
	player1 = new Joueur("Player 1");
	player1->setCurrentPlayerFlag(true);
	player1->init_achat();

	if (player2){
		delete player2;
		player2 = nullptr;
	}
	player2 = new Joueur("Player 2");
	player2->setCurrentPlayerFlag(false);
	player2->init_achat();

	winner = nullptr;

	if (sideBoard){
		delete sideBoard;
		sideBoard = nullptr;
	}
	sideBoard = new SideBoard;

	numCardTaken = 0;
	numWonderBuilt = 0;

	rejouerFlag = false;
	hasPlayedFlag = false;

	std::random_device rdSeed;
	std::mt19937 gen(rdSeed());

	std::vector<Card*> tmpWonders(deck->getWonders());
	std::shuffle(tmpWonders.begin(), tmpWonders.end(), gen);
	for (size_t i = 0; i < 4; i += 1) { player1->getWonders()[i] = tmpWonders[i]; }
	for (size_t i = 0; i < 4; i += 1) { player2->getWonders()[i] = tmpWonders[i + 4]; }
}

char GameController::constructBuilding(Joueur* player, Card* card)
{
	bool freeFlag = verifyChainSymbol(player, card);

	// If the card has already been discarded, return 'x' indicating an exception
	if (card->getDiscardFlag()) { freeFlag = true; }

	// If the card has already been constructed, return 'x' indicating an exception
	if (card->getConstructedFlag()) { return 'x'; }

	// If the player isn't the current player, return 'x' indicating an exception
	if (!player->getCurrentPlayerFlag()) { return 'x'; }

	unsigned int extraCost = 0;
	bool confirmFlag = freeFlag;

	if (!freeFlag) // If the card can't be constructed for free, then verify if it can be built by using items or coins
	{
		// Initialize an array who will track the numbers of lacking items
		std::map<Ressources,int> nums_LackItems = {};

		// Check if the player has the items needed to construct the card
		// The numbers of missing items will be stored in the nums_LackItems array
		confirmFlag = verifyItems(player, card, nums_LackItems);

		// Check if the player has enough coins to construct the card or purchase the missing items
		// Coins used to purchase the items will be stored in extraCost
		// The result will determine if the card can be built and is stored in confirmFlag
		if(!confirmFlag) confirmFlag = verifyCoins(player, card, nums_LackItems, extraCost);
	}



	// If the card cannot be constructed even with items and coins, return '0' indicating inability to construct
	if (!confirmFlag) { return '0'; }

	if (card->getSymbolespe1() != Symboles_special::aucun) {
		player->ajout_SymSp(card->getSymbolespe1());
	}
	if (card->getSymbolespe2() != Symboles_special::aucun) {
		player->ajout_SymSp(card->getSymbolespe2());
	}

	switch (card->getTypes())
	{
	case Types::Matiere_Premiere:
		handleCardObtained_Brown(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::Produit_manufacture:
		handleCardObtained_Grey(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::civils:
		handleCardObtained_Blue(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::scientifique:
		handleCardObtained_Green(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::commerciaux:
		handleCardObtained_Yellow(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::militaires:
		handleCardObtained_Red(player, card, freeFlag, extraCost, confirmFlag);
		break;
	case Types::guilde:
		handleCardObtained_Purple(player, card, freeFlag, extraCost, confirmFlag);
		break;
	default:
		// If the card's colour doesn't match the above types, return 'x' indicating an exception
		return 'x';
		break;
	}

	// If all checks pass and the card can be constructed, return '1' indicating success
	return '1';
}

void GameController::discardBuilding(Joueur* player, Card* card){
	if (card->getDiscardFlag()) { return; }
	if (!player->getCurrentPlayerFlag()) { return; }
	numCardTaken += 1;
	card->setDiscardFlag(true);
	unsigned int bonus = player->getCards_Yellow().size();
	player->incCoins(2 + bonus);
}

char GameController::constructWonder(Joueur* player, Card* building, Card* wonder){
	// If the wonder card passed in is not a wonder, return 'x' indicating an exception
	if (wonder->getTypes() != Types::Merveille) { return 'x'; }

	// If the building card has already been already constructed or discarded, return 'x' indicating an exception
	if (building->getConstructedFlag() || building->getDiscardFlag()) { return 'x'; }

	// If the wonder card is already constructed or not constructible, return 'x' indicating an exception
	if (wonder->getConstructedFlag() || !wonder->getConstructibleFlag()) { return 'x'; }

	// If the player isn't the current player, return 'x' indicating an exception
	if (!player->getCurrentPlayerFlag()) { return 'x'; }

	// Check if the number of wonders built is less than 8
	if (numWonderBuilt < 8)
	{
		// Initialize an array to track lacking items
		std::map<Ressources, int> nums_LackItems ={};

		// Initialize an extra cost variable
		unsigned int extraCost = 0;

		// Check if the player has the items needed to construct the card
		// The numbers of missing items will be stored in the nums_LackItems array
		verifyItems(player, wonder, nums_LackItems);

		// Check if the player has enough coins to construct the card or purchase the missing items
		// Coins used to purchase the items will be stored in extraCost
		// The result will determine if the card can be built and is stored in confirmFlag
		bool confirmFlag = verifyCoins(player, wonder, nums_LackItems, extraCost);

		// If the card cannot be constructed even with items and coins, return '0' indicating inability to construct
		if (!confirmFlag) { return '0'; }

		// Handle the process of obtaining the wonder
		handleWonderObtained(player, building, wonder, extraCost, confirmFlag);

		// If all checks pass and the wonder can be constructed, return '1' indicating success
		return '1';
	}
	// Return '0' if the number of wonders built exceeds the limit
	return '0';
}

void GameController::checkLootingToken(){
	// Get the conflict pawn position
	int cpPosition = sideBoard->getConflictPawnPosition();

	// Get the flags indicating whether coins have been looted from each side
	bool l_2CFlag = sideBoard->getLeft2CoinsTaken();
	bool l_5CFlag = sideBoard->getLeft5CoinsTaken();
	bool r_2CFlag = sideBoard->getRight2CoinsTaken();
	bool r_5CFlag = sideBoard->getRight5CoinsTaken();

	// If the conflict pawn is on the left side and the 2 coins haven't been taken yet
	if ((cpPosition <= -3) && !l_2CFlag)
	{
		// Loot 2 coins from player 1
		player1->decCoins(2);
		// Set the flag indicating that the 2 coins on the left side have been taken
		sideBoard->setLeft2CoinsTaken(true);
	}

	// If the conflict pawn is on the left side and the 5 coins haven't been taken yet
	if ((cpPosition <= -6) && !l_5CFlag)
	{
		// Loot 5 coins from player 1
		player1->decCoins(5);
		// Set the flag indicating that the 5 coins on the left side have been taken
		sideBoard->setLeft5CoinsTaken(true);
	}

	// If the conflict pawn is on the right side and the 2 coins haven't been taken yet
	if ((cpPosition >= 3) && !r_2CFlag)
	{
		// Loot 2 coins from player 2
		player2->decCoins(2);
		// Set the flag indicating that the 2 coins on the right side have been taken
		sideBoard->setRight2CoinsTaken(true);
	}

	// If the conflict pawn is on the right side and the 5 coins haven't been taken yet
	if ((cpPosition >= 6) && !r_5CFlag)
	{
		// Loot 5 coins from player 2
		player2->decCoins(5);
		// Set the flag indicating that the 5 coins on the right side have been taken
		sideBoard->setRight5CoinsTaken(true);
	}
}

int GameController::updateSideBoard(){
	// Calculate the difference in military power between player 1 and player 2
	int MilPowerDiff = player1->getMilPower() - player2->getMilPower();

	// Set the conflict pawn position on the side board based on the military power difference
	sideBoard->setConflictPawnPosition(MilPowerDiff);

	// Check if any coins need to be looted based on the conflict pawn position
	checkLootingToken();

	// Return the military power difference
	return MilPowerDiff;
}

char GameController::takeJeton(Joueur* player, Jeton* jeton) {
	// If the progress token has already been taken, return '0' indicating inability to take
	if (jeton->getTakenFlag()) { return '0'; }

	// Verify if the player has pairs of scientific symbols to take the progress token
	bool confirmFlag = verifySciSymbols(player);
	bool freeFlag = false;
	if (jeton->getDiscardedFlag())
	{
		confirmFlag = true;
		freeFlag = true;
	}

	// If the player doesn't have pairs of scientific symbols, return '0' indicating inability to take
	if (!confirmFlag) { return '0'; }

	// Obtain the progress token and mark it as taken by the player
	player->obtainJetons(jeton, confirmFlag, freeFlag);

	jeton->setTakenFlag(true);

	// Return '1' indicating success in taking the progress token
	return '1';
}

bool GameController::checkVictoryConditions(){
	// Check military supremacy condition
	bool condition1 = verifyMilitarySupremacy();

	// Check scientific supremacy condition for player 1
	bool condition2 = verifyScientificSupremacy(player1);

	// Check scientific supremacy condition for player 2
	bool condition3 = verifyScientificSupremacy(player2);

	// If all cards have been taken, verify civilian victory condition
	if (numCardTaken == 60) { return verifyCivilianVictory(); }

	// Otherwise, return true if any of the victory conditions are met
	return condition1 || condition2 || condition3;
}


void GameController::destructBuilding(Joueur* player, Card* card) {
	Bat_normal* carte = static_cast<Bat_normal*>(card);
	std::map<Ressources, int> ressource = carte->getProduction();
	
	std::map<Ressources, int>& playersItems(player->getRessourceJoueur());

	std::map<Ressources, int>::iterator it1;
	//on va ajouter les productions aux matériaux posséder par le joueur1
	for (it1 = ressource.begin(); it1 != ressource.end(); ++it1) {
		Ressources productionType = it1->first;
		int quantity = it1->second;
		playersItems[productionType] -= quantity;
		
	}


}