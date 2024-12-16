#include "Deck.h"

Deck::Deck() {
	init_Wonders();
	init_Cards_Age1();
	init_Cards_Age2();
	init_Cards_Age3();
	init_Guilds();
	init_Deck_Age1();
	init_Deck_Age2();
	init_Deck_Age3();
}

Deck::~Deck() {
	for (size_t i = 0; i < wonders.size(); i += 1) { delete wonders[i]; }
	for (size_t i = 0; i < cards_age1.size(); i += 1) { delete cards_age1[i]; }
	for (size_t i = 0; i < cards_age2.size(); i += 1) { delete cards_age2[i]; }
	for (size_t i = 0; i < cards_age3.size(); i += 1) { delete cards_age3[i]; }
	for (size_t i = 0; i < guilde.size(); i += 1) { delete guilde[i]; }
}
	//cr�ation des wonders

void Deck::init_Wonders(){
	wonders.push_back(new Card(1, Types::Merveille, "Le Circus Maximus", std::map<Ressources, int>{{Ressources::pierre, 2}, { Ressources::bois,1 }, { Ressources::verre,1 }}));
	wonders.push_back(new Card(2, Types::Merveille, "Le Colosse", std::map<Ressources, int>{{Ressources::brique, 3}, { Ressources::verre,1 }}));
	wonders.push_back(new Card(3, Types::Merveille, "Le Grand Phare", std::map<Ressources, int>{{Ressources::bois, 1}, { Ressources::pierre,1 }, { Ressources::papier,2 }}));
	wonders.push_back(new Card(4, Types::Merveille, "Les Jardins Suspendus", std::map<Ressources, int>{{Ressources::bois, 2}, { Ressources::verre,1 }, { Ressources::papier,1 }}));
	wonders.push_back(new Card(5, Types::Merveille, "La Grande Bibliotheque", std::map<Ressources, int>{{ Ressources::bois, 3}, { Ressources::verre,1 }, { Ressources::papier,1 }}));
	wonders.push_back(new Card(6, Types::Merveille, "Le Mausolee", std::map<Ressources, int>{{Ressources::brique, 2}, { Ressources::verre,2 }, { Ressources::papier,1 }}));
	wonders.push_back(new Card(7, Types::Merveille, "Le Piree", std::map<Ressources, int>{{Ressources::bois, 2}, { Ressources::pierre,1 }, { Ressources::brique,1 }}));
	wonders.push_back(new Card(8, Types::Merveille, "Les Pyramides", std::map<Ressources, int>{{Ressources::pierre, 3}, { Ressources::papier,1 }}));
	wonders.push_back(new Card(9, Types::Merveille, "Le Sphinx", std::map<Ressources, int>{{Ressources::pierre, 1}, { Ressources::brique,1 }, { Ressources::verre,2 }}));
	wonders.push_back(new Card(10, Types::Merveille, "La Statue De Zeus", std::map<Ressources, int>{{Ressources::bois, 1}, { Ressources::pierre,1 }, { Ressources::brique,1 }, { Ressources::papier,2 }}));
	wonders.push_back(new Card(11, Types::Merveille, "Le Temple D'Artemis", std::map<Ressources, int>{{Ressources::bois, 1}, { Ressources::pierre,1 }, { Ressources::verre,1 }, { Ressources::papier,1 }}));
	wonders.push_back(new Card(12, Types::Merveille, "La Via Appia", std::map<Ressources, int>{{Ressources::pierre, 2}, { Ressources::brique,2 }, { Ressources::papier,1 }}));
}

void Deck::init_Cards_Age1() {
	//les cartes sans cha�nage
	cards_age1.push_back(new Bat_normal(13, Types::Matiere_Premiere, "chantier", Eres::I, std::map<Ressources, int>{}, std::map<Ressources, int>{{Ressources::bois, 1}}));
	cards_age1.push_back(new Bat_normal(14, Types::Matiere_Premiere, "exploitation", Eres::I, std::map<Ressources, int>{{Ressources::piece, 1} }, std::map<Ressources, int>{ {Ressources::bois, 1}}));
	cards_age1.push_back(new Bat_normal(15, Types::Matiere_Premiere, "bassin argileux", Eres::I, std::map<Ressources, int>{}, std::map<Ressources, int>{{Ressources::brique, 1} }));
	cards_age1.push_back(new Bat_normal(16, Types::Matiere_Premiere, "cavite", Eres::I, std::map<Ressources, int>{{Ressources::piece, 1} }, std::map<Ressources, int>{{Ressources::brique, 1} }));
	cards_age1.push_back(new Bat_normal(17, Types::Matiere_Premiere, "gisement", Eres::I, std::map<Ressources, int>{}, std::map<Ressources, int>{{Ressources::pierre, 1}}));
	cards_age1.push_back(new Bat_normal(18, Types::Matiere_Premiere, "mine", Eres::I, std::map<Ressources, int>{{Ressources::piece, 1} }, std::map<Ressources, int>{{Ressources::pierre, 1} }));
	cards_age1.push_back(new Bat_normal(19, Types::Produit_manufacture, "verrerie", Eres::I, std::map<Ressources, int>{ {Ressources::piece, 1} }, std::map<Ressources, int>{ {Ressources::verre, 1} }));
	cards_age1.push_back(new Bat_normal(20, Types::Produit_manufacture, "presse", Eres::I, std::map<Ressources, int>{{Ressources::piece, 1}}, std::map<Ressources, int>{ {Ressources::papier, 1} }));
	cards_age1.push_back(new Bat_normal(21, Types::militaires, "tour de garde", Eres::I, std::map<Ressources, int>{ }, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1} }));
	cards_age1.push_back(new Bat_Scientifique(22, Types::scientifique, "atelier", Eres::I, std::map<Ressources, int>{{Ressources::papier, 1} }, std::map<Ressources, int>{{Ressources::point_victoire, 1}}, Symboles_scientifique::equerre));
	cards_age1.push_back(new Bat_Scientifique(23, Types::scientifique, "apothicaire", Eres::I, std::map<Ressources, int>{{Ressources::verre, 1} }, std::map<Ressources, int>{ {Ressources::point_victoire, 1} }, Symboles_scientifique::roue));
	cards_age1.push_back(new Bat_Commercial(24, Types::commerciaux, "depot de pierre", Eres::I, std::map<Ressources, int>{{Ressources::piece, 3} }, std::map<Ressources, int>{}, std::map<Ressources, int>{ {Ressources::pierre, 1} }, { }, std::map<Types, unsigned int>{}));
	cards_age1.push_back(new Bat_Commercial(25, Types::commerciaux, "depot d'argile", Eres::I, std::map<Ressources, int>{{Ressources::piece, 3} }, std::map<Ressources, int>{}, std::map<Ressources, int>{ {Ressources::brique, 1} }, { }, std::map<Types, unsigned int>{}));
	cards_age1.push_back(new Bat_Commercial(26, Types::commerciaux, "depot de pierre", Eres::I, std::map<Ressources, int>{ {Ressources::piece, 3} }, std::map<Ressources, int>{}, std::map<Ressources, int>{ {Ressources::bois, 1}}, { }, std::map<Types, unsigned int>{}));
	//les cartes avec cha�nage
	cards_age1.push_back(new Bat_normal(27, Types::militaires, "ecuries", Eres::I, std::map<Ressources, int>{ {Ressources::bois, 1}}, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1} }, Symboles_special::fer));
	cards_age1.push_back(new Bat_normal(28, Types::militaires, "caserne", Eres::I, std::map<Ressources, int>{{Ressources::brique, 1} }, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1} }, Symboles_special::epee));
	cards_age1.push_back(new Bat_normal(29, Types::militaires, "palissade", Eres::I, std::map<Ressources, int>{ {Ressources::piece, 2}}, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1}}, Symboles_special::tour));
	cards_age1.push_back(new Bat_Scientifique(30, Types::scientifique, "scriptorium", Eres::I, std::map<Ressources, int>{ {Ressources::piece, 2} }, std::map<Ressources, int>{ }, Symboles_scientifique::plume, Symboles_special::livre));
	cards_age1.push_back(new Bat_Scientifique(31, Types::scientifique, "officine", Eres::I, std::map<Ressources, int>{{Ressources::piece, 2} }, std::map<Ressources, int>{ }, Symboles_scientifique::pilon, Symboles_special::roue));
	cards_age1.push_back(new Bat_normal(32, Types::civils, "theatre", Eres::I, std::map<Ressources, int>{ }, std::map<Ressources, int>{ }, Symboles_special::masque));
	cards_age1.push_back(new Bat_normal(33, Types::civils, "autel", Eres::I, std::map<Ressources, int>{  }, std::map<Ressources, int>{ {Ressources::point_victoire, 3} }, Symboles_special::lune));
	cards_age1.push_back(new Bat_normal(34, Types::civils, "bains", Eres::I, std::map<Ressources, int>{{Ressources::pierre, 1}}, std::map<Ressources, int>{ {Ressources::point_victoire, 3} }, Symboles_special::goutte));
	cards_age1.push_back(new Bat_Commercial(35, Types::commerciaux, "taverne", Eres::I, std::map<Ressources, int>{ }, std::map<Ressources, int>{{Ressources::piece, 3}}, std::map<Ressources, int>{}, { }, std::map<Types, unsigned int>{}, Symboles_special::amphore));
}
void Deck::init_Cards_Age2(){
	//les cartes sans cha�nage
	cards_age2.push_back(new Bat_normal(36, Types::Matiere_Premiere, "scierie", Eres::II, std::map<Ressources, int>{{Ressources::piece, 2}}, std::map<Ressources, int>{{Ressources::bois, 2} }));
	cards_age2.push_back(new Bat_normal(37, Types::Matiere_Premiere, "briqueterie", Eres::II, std::map<Ressources, int>{ {Ressources::piece, 2} }, std::map<Ressources, int>{{Ressources::brique, 2} }));
	cards_age2.push_back(new Bat_normal(38, Types::Matiere_Premiere, "carriere", Eres::II, std::map<Ressources, int>{{Ressources::piece, 2} }, std::map<Ressources, int>{ {Ressources::pierre, 2} }));
	cards_age2.push_back(new Bat_normal(39, Types::Produit_manufacture, "soufflerie", Eres::II, std::map<Ressources, int>{ }, std::map<Ressources, int>{ {Ressources::verre, 1} }));
	cards_age2.push_back(new Bat_normal(40, Types::Produit_manufacture, "sechoir", Eres::II, std::map<Ressources, int>{ }, std::map<Ressources, int>{ {Ressources::papier, 1} }));
	cards_age2.push_back(new Bat_normal(41, Types::militaires, "muraille", Eres::II, std::map<Ressources, int>{ {Ressources::pierre, 2}}, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 2} }));
	cards_age2.push_back(new Bat_Commercial(42, Types::commerciaux, "forum", Eres::II, std::map<Ressources, int>{ {Ressources::piece, 3}, { Ressources::brique,1 } }, std::map<Ressources, int>{}, std::map<Ressources, int>{}, { Ressources::verre,Ressources::papier }, std::map<Types, unsigned int>{}));
	cards_age2.push_back(new Bat_Commercial(43, Types::commerciaux, "caravanserail", Eres::II, std::map<Ressources, int>{ {Ressources::piece, 2}, { Ressources::verre,1 }, { Ressources::papier,1 }}, std::map<Ressources, int>{}, std::map<Ressources, int>{}, { Ressources::bois,Ressources::brique,Ressources::pierre }, std::map<Types, unsigned int>{}));
	cards_age2.push_back(new Bat_Commercial(44, Types::commerciaux, "douanes", Eres::II, std::map<Ressources, int>{ {Ressources::piece, 4} }, std::map<Ressources, int>{}, std::map<Ressources, int>{ {Ressources::papier, 1}, { Ressources::verre,1 } }, { }, std::map<Types, unsigned int>{}));
	cards_age2.push_back(new Bat_normal(45, Types::civils, "tribunal", Eres::II, std::map<Ressources, int>{ {Ressources::bois, 2}, { Ressources::verre,1 }}, std::map<Ressources, int>{{Ressources::point_victoire, 5}}));
	//les cartes avec cha�nage
	cards_age2.push_back(new Bat_normal(46, Types::militaires, "haras", Eres::II, std::map<Ressources, int>{{Ressources::brique, 1}, { Ressources::bois,1 }}, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1}}, Symboles_special::fer));
	cards_age2.push_back(new Bat_normal(47, Types::militaires, "baraquements", Eres::II, std::map<Ressources, int>{ {Ressources::piece, 3} }, std::map<Ressources, int>{{Ressources::puissance_millitaire, 1} }, Symboles_special::epee));
	cards_age2.push_back(new Bat_normal(48, Types::militaires, "champ de tir", Eres::II, std::map<Ressources, int>{ {Ressources::pierre, 1}, { Ressources::bois,1 }, { Ressources::papier,1 } }, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 2 }}, Symboles_special::cible));
	cards_age2.push_back(new Bat_normal(49, Types::militaires, "place d'arme", Eres::II, std::map<Ressources, int>{ {Ressources::brique, 2}, { Ressources::verre,1 }}, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 2} }, Symboles_special::casque));
	cards_age2.push_back(new Bat_Scientifique(50, Types::scientifique, "bibliotheque", Eres::II, std::map<Ressources, int>{ {Ressources::pierre, 1}, { Ressources::bois,1 }, { Ressources::papier,1 }}, std::map<Ressources, int>{{Ressources::point_victoire, 2} }, Symboles_scientifique::plume, Symboles_special::livre));
	cards_age2.push_back(new Bat_Scientifique(51, Types::scientifique, "dispensaire", Eres::II, std::map<Ressources, int>{{Ressources::brique, 2}, { Ressources::pierre,1 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 2} }, Symboles_scientifique::pilon, Symboles_special::roue));
	cards_age2.push_back(new Bat_Scientifique(52, Types::scientifique, "ecole", Eres::II, std::map<Ressources, int>{{Ressources::bois, 1}, { Ressources::papier,2 }}, std::map<Ressources, int>{ {Ressources::point_victoire, 1}}, Symboles_scientifique::roue, Symboles_special::harpe));
	cards_age2.push_back(new Bat_Scientifique(53, Types::scientifique, "laboratoire", Eres::II, std::map<Ressources, int>{ {Ressources::bois, 1}, { Ressources::verre,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 1} }, Symboles_scientifique::equerre, Symboles_special::lampe));
	cards_age2.push_back(new Bat_normal(54, Types::civils, "statue", Eres::II, std::map<Ressources, int>{ {Ressources::brique, 2} }, std::map<Ressources, int>{ {Ressources::point_victoire, 4} }, Symboles_special::masque, Symboles_special::pateau));
	cards_age2.push_back(new Bat_normal(55, Types::civils, "temple", Eres::II, std::map<Ressources, int>{ {Ressources::bois, 1}, { Ressources::papier,1 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 4} }, Symboles_special::lune, Symboles_special::soleil));
	cards_age2.push_back(new Bat_normal(56, Types::civils, "aqueduc", Eres::II, std::map<Ressources, int>{ {Ressources::pierre, 3} }, std::map<Ressources, int>{ {Ressources::point_victoire, 5} }, Symboles_special::goutte));
	cards_age2.push_back(new Bat_normal(57, Types::civils, "rostres", Eres::II, std::map<Ressources, int>{ {Ressources::bois, 1}, { Ressources::pierre,1 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 4} }, Symboles_special::batiment));
	cards_age2.push_back(new Bat_Commercial(58, Types::commerciaux, "brasserie", Eres::II, std::map<Ressources, int>{}, std::map<Ressources, int>{{Ressources::piece, 6}}, std::map<Ressources, int>{}, {}, std::map<Types, unsigned int>{}, Symboles_special::barrique));
}
void Deck::init_Cards_Age3() {
	//les cartes sans cha�nage
	cards_age3.push_back(new Bat_normal(59, Types::militaires, "arsenal", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 3}, { Ressources::bois,2 } }, std::map<Ressources, int>{{Ressources::puissance_millitaire, 3} }));
	cards_age3.push_back(new Bat_normal(60, Types::militaires, "pretoire", Eres::III, std::map<Ressources, int>{ {Ressources::piece, 8} }, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 3}}));
	cards_age3.push_back(new Bat_Scientifique(61, Types::scientifique, "academie", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 1}, { Ressources::bois,1 }, { Ressources::verre,2 }}, std::map<Ressources, int>{ {Ressources::point_victoire, 3} }, Symboles_scientifique::cadran));
	cards_age3.push_back(new Bat_Scientifique(62, Types::scientifique, "etude", Eres::III, { {Ressources::bois,2},{Ressources::verre,1},{Ressources::papier,1} }, std::map<Ressources, int>{ {Ressources::point_victoire, 3}}, Symboles_scientifique::cadran));
	cards_age3.push_back(new Bat_Commercial(63, Types::commerciaux, "chambre de commerce", Eres::III, std::map<Ressources, int>{ {Ressources::papier, 2} }, std::map<Ressources, int>{{Ressources::point_victoire, 3}}, std::map<Ressources, int>{ }, { }, std::map<Types, unsigned int>{{Types::Produit_manufacture, 3}}));
	cards_age3.push_back(new Bat_Commercial(64, Types::commerciaux, "port", Eres::III, std::map<Ressources, int>{ {Ressources::bois, 1}, { Ressources::verre,1 }, { Ressources::papier,1 } }, std::map<Ressources, int>{{Ressources::point_victoire, 3}}, std::map<Ressources, int>{ }, {}, std::map<Types, unsigned int>{{Types::Matiere_Premiere, 2}}));
	cards_age3.push_back(new Bat_Commercial(65, Types::commerciaux, "armurerie", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::verre,1 }}, std::map<Ressources, int>{{Ressources::point_victoire, 3}}, std::map<Ressources, int>{  }, { }, std::map<Types, unsigned int>{{Types::militaires, 1}}));
	cards_age3.push_back(new Bat_normal(66, Types::civils, "palace", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::pierre,1 }, { Ressources::bois,1 }, { Ressources::verre,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 7} }));
	cards_age3.push_back(new Bat_normal(67, Types::civils, "hotel de ville", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 3}, { Ressources::bois,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 7} }));
	cards_age3.push_back(new Bat_normal(68, Types::civils, "obelisque", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::verre,1 }}, std::map<Ressources, int>{ {Ressources::point_victoire, 5} }));
	//les cartes avec cha�nage
	cards_age3.push_back(new Bat_normal(69, Types::militaires, "fortifications", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::brique,1 }, { Ressources::papier,1 } }, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 2} }, Symboles_special::tour));
	cards_age3.push_back(new Bat_normal(70, Types::militaires, "atelier de siege", Eres::III, std::map<Ressources, int>{ {Ressources::bois, 3}, { Ressources::verre,1 } }, std::map<Ressources, int>{ {Ressources::puissance_millitaire, 2} }, Symboles_special::cible));
	cards_age3.push_back(new Bat_normal(71, Types::militaires, "crique", Eres::III, std::map<Ressources, int>{{Ressources::brique, 2}, { Ressources::pierre,2 }}, std::map<Ressources, int>{{Ressources::puissance_millitaire, 2}}, Symboles_special::casque));
	cards_age3.push_back(new Bat_Scientifique(72, Types::scientifique, "universite", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::verre,1 }, { Ressources::papier,1 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 2} }, Symboles_scientifique::planetaire, Symboles_special::harpe));
	cards_age3.push_back(new Bat_Scientifique(73, Types::scientifique, "observatoire", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 1}, { Ressources::papier,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 2} }, Symboles_scientifique::planetaire, Symboles_special::lampe));
	cards_age3.push_back(new Bat_normal(74, Types::civils, "jardins", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 2}, { Ressources::bois,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 6} }, Symboles_special::pateau));
	cards_age3.push_back(new Bat_normal(75, Types::civils, "pantheon", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::bois,1 }, { Ressources::papier,2 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 6}}, Symboles_special::soleil));
	cards_age3.push_back(new Bat_normal(76, Types::civils, "senat", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 2}, { Ressources::pierre,1 }, { Ressources::papier,1 } }, std::map<Ressources, int>{ {Ressources::point_victoire, 5} }, Symboles_special::batiment));
	cards_age3.push_back(new Bat_Commercial(77, Types::commerciaux, "phare", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 2}, { Ressources::verre,1 } }, std::map<Ressources, int>{{Ressources::point_victoire, 3}}, std::map<Ressources, int>{}, { }, std::map<Types, unsigned int>{{Types::commerciaux, 1}}, Symboles_special::amphore));
	cards_age3.push_back(new Bat_Commercial(78, Types::commerciaux, "arene", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::pierre,1 }, { Ressources::bois,1 } }, std::map<Ressources, int>{{Ressources::point_victoire, 3}}, std::map<Ressources, int>{ }, { }, std::map<Types, unsigned int>{{Types::Merveille, 2}}, Symboles_special::barrique));
}
void Deck::init_Guilds(){
	//Guilde:
	guilde.push_back(new Guilde(79, Types::guilde, "guilde des commercants", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::bois,1 }, { Ressources::verre,1 }, { Ressources::papier,1 } }, std::map<Types, unsigned int>{{Types::commerciaux, 1} }));
	guilde.push_back(new Guilde(80, Types::guilde, "guilde des armateurs", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 1}, { Ressources::pierre,1 }, { Ressources::verre,1 }, { Ressources::papier,1 } }, std::map<Types, unsigned int>{{ Types::Matiere_Premiere, 1 }}));
	guilde.push_back(new Guilde(81, Types::guilde, "guilde des batisseurs", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::brique,1 }, { Ressources::bois,1 }, { Ressources::verre,1 } }, std::map<Types, unsigned int>{ {Types::Merveille, 2} }));
	guilde.push_back(new Guilde(82, Types::guilde, "guilde des magistrats", Eres::III, std::map<Ressources, int>{ {Ressources::bois, 2}, { Ressources::brique,1 }, { Ressources::papier,1 } }, std::map<Types, unsigned int>{ {Types::civils, 1} }));
	guilde.push_back(new Guilde(83, Types::guilde, "guilde des scientifiques", Eres::III, std::map<Ressources, int>{ {Ressources::brique, 2}, { Ressources::bois,2 }}, std::map<Types, unsigned int>{ {Types::scientifique, 1}}));
	guilde.push_back(new Guilde(84, Types::guilde, "guilde des usuriers", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::bois,2 }}, std::map<Types, unsigned int>{ {Types::aucun, 1} }));
	guilde.push_back(new Guilde(85, Types::guilde, "guilde des tacticiens", Eres::III, std::map<Ressources, int>{ {Ressources::pierre, 2}, { Ressources::brique,1 }, { Ressources::papier,1 } }, std::map<Types, unsigned int>{ {Types::militaires, 1} }));
}

void Deck::init_Deck_Age1()
	{
		std::random_device rdSeed;
		std::mt19937 gen(rdSeed());
		
		std::vector<Card*> tmpDeck(cards_age1);
		std::shuffle(tmpDeck.begin(), tmpDeck.end(), gen);
		deck_age1.insert(deck_age1.end(), tmpDeck.begin(), tmpDeck.begin() + 20);
	}
void Deck::init_Deck_Age2()
{
	std::random_device rdSeed;
	std::mt19937 gen(rdSeed());

	std::vector<Card*> tmpDeck(cards_age2);
	std::shuffle(tmpDeck.begin(), tmpDeck.end(), gen);
	deck_age2.insert(deck_age2.end(), tmpDeck.begin(), tmpDeck.begin() + 20);
}
void Deck::init_Deck_Age3()
{
	std::random_device rdSeed;
	std::mt19937 gen(rdSeed());

	std::vector<Card*> tmpDeck(cards_age3);
	std::shuffle(tmpDeck.begin(), tmpDeck.end(), gen);
	deck_age3.insert(deck_age3.end(), tmpDeck.begin(), tmpDeck.begin() + 17);

	std::vector<Card*> tmpGuilds(guilde);
	std::shuffle(guilde.begin(), guilde.end(), gen);
	deck_age3.insert(deck_age3.end(), tmpGuilds.begin(), tmpGuilds.begin() + 3);

	std::shuffle(deck_age3.begin(), deck_age3.end(), gen);
}

void Deck::ajout_card(Eres e, Card* c){
    if(e == Eres::I){
        cards_age1.push_back(c);
    }
    else if(e == Eres::II){
        cards_age2.push_back(c);
    }
    else if(e == Eres::III){
        cards_age3.push_back(c);
    }
    else return;

}

std::vector<Card*> Deck::getDiscardedCards()
{
	std::vector<Card*> discardedCards;
	for (auto it = deck_age1.begin(); it != deck_age1.end(); ++it)
	{
		if ((*it)->getDiscardFlag()) { discardedCards.push_back((*it)); }
	}
	for (auto it = deck_age2.begin(); it != deck_age2.end(); ++it)
	{
		if ((*it)->getDiscardFlag()) { discardedCards.push_back((*it)); }
	}
	for (auto it = deck_age3.begin(); it != deck_age3.end(); ++it)
	{
		if ((*it)->getDiscardFlag()) { discardedCards.push_back((*it)); }
	}
	return discardedCards;
}