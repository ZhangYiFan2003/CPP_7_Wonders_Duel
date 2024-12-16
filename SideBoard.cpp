#include "SideBoard.h"

SideBoard::SideBoard() {
    //initialisation des jetons
    Jetons.at(0) = new Jeton(1, "Agriculture");
    Jetons.at(1) = new Jeton(2, "Architecture");
    Jetons.at(2) = new Jeton(3, "Economie");
    Jetons.at(3) = new Jeton(4, "Loi");
    Jetons.at(4) = new Jeton(5, "Maconnerie");
    Jetons.at(5) = new Jeton(6, "Mathematiques");
    Jetons.at(6) = new Jeton(7, "Philosophie");
    Jetons.at(7) = new Jeton(8, "Strategie");
    Jetons.at(8) = new Jeton(9, "Theologie");
    Jetons.at(9) = new Jeton(10, "Urbanisme");

    std::random_device rdSeed;
    std::mt19937 gen(rdSeed());
    std::array<Jeton*, 10> tmpDeck(Jetons);
    std::shuffle(tmpDeck.begin(), tmpDeck.end(), gen);
    for (size_t i = 0; i < 5; i += 1) {
        JetonsDeck.at(i) = tmpDeck.at(i);
        JetonsDeck.at(i)->setDiscardedFlag(false);
    }
    for (size_t i = 5; i < 8; i++) {
        JetonsNonPris.at(i - 5) = tmpDeck.at(i);
        JetonsNonPris.at(i - 5)->setDiscardedFlag(true);
    }
}

unsigned int SideBoard::getNumJetonsRestants(){
    unsigned int n = 0;
    for (size_t i = 0; i < JetonsDeck.size(); i++) {
        if (!JetonsDeck[i]->getTakenFlag()) {
            n++;
        }
    }
    return n;
}

