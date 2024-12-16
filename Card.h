#ifndef Card_h
#define Card_h

#include "GameLogicHeader.h"


enum class Types { Matiere_Premiere, Produit_manufacture, civils, scientifique, commerciaux, militaires, guilde, Merveille, aucun };
enum class Eres { I = 1, II = 2, III = 3 };
enum class Ressources {brique, bois, pierre, verre, papier, piece, point_victoire, puissance_millitaire };
enum class Symboles_scientifique { planetaire, balance, cadran, pilon, equerre, plume, roue, aucun};
enum class Symboles_special { amphore, barrique , masque, batiment, soleil, goutte, pateau, lune, cible, casque, fer, epee, tour, harpe, roue, livre, lampe, aucun};

class Card
{
protected:
	int id;
	std::string nom;
	Types type;
	std::map<Ressources, int> achat;
	Symboles_special sym_spe1;
	Symboles_special sym_spe2;
	bool constructedFlag = false;
	bool constructibleFlag = true;
	bool discardFlag = false;


public:
	Card(int i, Types t, std::string n, std::map<Ressources, int> a, Symboles_special sp = Symboles_special::aucun, Symboles_special sp2 = Symboles_special::aucun) : id(i), type(t), nom(n), achat(a), sym_spe1(sp), sym_spe2(sp2), constructedFlag(false), discardFlag(false) {};
	const int getID() const { return id; }
	Types getTypes() const { return type; }
	std::string getNom() const { return nom; }
	Symboles_special getSymbolespe1() const { return sym_spe1; }
	Symboles_special getSymbolespe2() const { return sym_spe2; }
	std::map<Ressources, int> getCoutAchat() const { return achat; }

	virtual ~Card() = default; 
	Card(const Card& c) = default; 
	Card& operator=(const Card& c) = default;

	const bool& getConstructedFlag() { return constructedFlag; }
	const bool& getConstructibleFlag() { return constructibleFlag; }
	const bool& getDiscardFlag() { return discardFlag; }

	void setConstructedFlag(bool flag) { constructedFlag = flag; }
	void setConstructibleFlag(bool flag) { constructibleFlag = flag; }
	void setDiscardFlag(bool flag) { discardFlag = flag; }
};

class Bat_Scientifique : public Card {
protected:
	std::map<Ressources, int> prod;
	Symboles_scientifique sym_scientifique;
	Eres ere;

public:
	Bat_Scientifique(int i, Types t, std::string n, Eres e, std::map<Ressources, int> a, std::map<Ressources, int> p, Symboles_scientifique s_sc, Symboles_special sp = Symboles_special::aucun, Symboles_special sp2 = Symboles_special::aucun) : 
		Card(i, t, n, a, sp, sp2), ere(e), prod(p), sym_scientifique(s_sc) {};

	const Eres getEre() const { return ere; }
	const std::map<Ressources, int> getProduction() const { return prod; }
	const Symboles_scientifique getSymbolesci() const { return sym_scientifique; }

};

class Bat_normal : public Card {
protected:
	std::map<Ressources, int> prod;
	Eres ere;

public:
	Bat_normal(int i, Types t, std::string n, Eres e, std::map<Ressources, int> a, std::map<Ressources, int> p, Symboles_special sp = Symboles_special::aucun, Symboles_special sp2 = Symboles_special::aucun) : 
		Card(i, t, n, a, sp, sp2), ere(e), prod(p) {};
	const std::map<Ressources, int> getProduction() const { return prod; }
};


class Bat_Commercial : public Card {
protected:
	std::map<Ressources, int> prod;
	std::map<Ressources, int> rscr_en_solde;        // les ressources que le joueur ach�te au co�t fixe de 1 pi�ce l�unit�
	std::vector<Ressources> rscr_produite;        // les mati�re que le b�timent commercial produit � chaque tour
	std::map<Types, unsigned int> bonus;   // types de construction requis et argent gagn� par construction
	Eres ere;

public:
	Bat_Commercial(int i, Types t, std::string n, Eres e, std::map<Ressources, int> a, std::map<Ressources, int> p, const std::map<Ressources, int>& res, const std::vector<Ressources>& rp, const std::map<Types, unsigned int>& b, Symboles_special sp = Symboles_special::aucun, Symboles_special sp2 = Symboles_special::aucun) :
		Card(i, t, n, a, sp, sp2), ere(e), prod(p), rscr_en_solde(res), rscr_produite(rp), bonus(b) {}

	Bat_Commercial(const Bat_Commercial& b) = delete; // il ne peut y avoir qu'un seul b�timent commercial de chaque type dans le jeu.
	~Bat_Commercial() = default;
	Bat_Commercial& operator=(const Bat_Commercial& b) = delete; //il ne peut y avoir qu'un seul b�timent commercial de chaque type dans le jeu.

	const Eres getEre() const { return ere; }
	const std::map<Ressources, int> getProduction() const { return prod; }
	const std::map<Ressources, int> getRessourceEnSolde() const { return rscr_en_solde; }
	const std::vector<Ressources> getRessourceProduite() const { return rscr_produite; }
	const std::map<Types, unsigned int> getBonus() const { return bonus; }
};

class Guilde : public Card {
protected:
	std::map<Types, unsigned int> effet;
	Eres ere;
public:
	Guilde(int i, Types t, std::string n, Eres e, std::map<Ressources, int> a, std::map<Types, unsigned int> ef, Symboles_special sp = Symboles_special::aucun, Symboles_special sp2 = Symboles_special::aucun) :
		Card(i, t, n, a, sp, sp2), ere(e), effet(ef) {}

	Guilde(const Guilde& g) = delete; // il ne peut y avoir qu'un seul b�timent commercial de chaque type dans le jeu.
	~Guilde() = default;
	Guilde& operator=(const Guilde& g) = delete; //il ne peut y avoir qu'un seul b�timent commercial de chaque type dans le jeu.

	const Eres getEre() const { return ere; }
	std::map<Types, unsigned int> getEffet() const { return effet; }

};


#endif // !Card_h