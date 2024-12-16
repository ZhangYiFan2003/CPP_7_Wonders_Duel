#ifndef Deck_h
#define Deck_h

#include "Card.h"


class Deck
{
private:
	std::vector<Card*> wonders;
	std::vector<Card*> cards_age1;
	std::vector<Card*> cards_age2;
	std::vector<Card*> cards_age3;
	std::vector<Card*> guilde;


	std::vector<Card*> deck_age1;
	std::vector<Card*> deck_age2;
	std::vector<Card*> deck_age3;


public:
	Deck();
	~Deck();

	void init_Wonders();
	void init_Cards_Age1();
	void init_Cards_Age2();
	void init_Cards_Age3();
	void init_Guilds();

	void init_Deck_Age1();
	void init_Deck_Age2();
	void init_Deck_Age3();

	void ajout_card(Eres e, Card* c);

	std::vector<Card*>& getWonders() { return wonders; }
	std::vector<Card*>& getCards_Age1() { return cards_age1; }
	std::vector<Card*>& getCards_Age2() { return cards_age2; }
	std::vector<Card*>& getCards_Age3() { return cards_age3; }
	std::vector<Card*>& getGuilds() { return guilde; }
	std::vector<Card*>& getDeck_Age1() { return deck_age1; }
	std::vector<Card*>& getDeck_Age2() { return deck_age2; }
	std::vector<Card*>& getDeck_Age3() { return deck_age3; }
	std::vector<Card*> getDiscardedCards();

};

#endif // !Deck_h