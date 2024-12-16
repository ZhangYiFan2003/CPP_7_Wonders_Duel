#ifndef VGameElements_h
#define VGameElements_h

#include "QtHeader.h"
#include "VBuilding.h"
#include "SideBoard.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
struct CardSize
{
    int width = 0;
    int height = 0;
};

struct CardOverlap
{
    int vertical = 0;
    int horizontal = 0;
};

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class Pop_Up_Notification : public QWidget // Classe de notification pop-up pour afficher des messages temporaires
{
    Q_OBJECT
private:
    QLabel* messageLabel = nullptr;                     // Message à afficher
    QVBoxLayout* pop_up_NotificationLayout = nullptr;   // Mise en page de la notification pop-up
    void startFadeOut();                                // Démarre le fondu en sortie

public:
    Pop_Up_Notification(QWidget* parent, QString msg);  // Constructeur de la classe Pop_Up_Notification
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VJeton : public QPushButton // Classe de jetons progrès visualisés
{
    Q_OBJECT
private:
    Jeton* jeton;
    char ptk_OK_Flag = '0';
    bool selectableFlag = true;                     // Indique si le jeton progrès est sélectionnable ou non ; devient faux si les conditions ne sont pas remplies ou si le jeton a déjà été sélectionné       
    bool isSelected = false;                        // Indique si le jeton progrès est sélectionné ou non
    GameController* gameController = nullptr;
    void enterEvent(QEnterEvent* event) override;   // Redéfinir enterEvent() pour définir le style de la souris lorsque la souris entre dans le bouton
    void leaveEvent(QEvent* event) override;        // Redéfinir leaveEvent() pour rétablir le style de souris par défaut lorsque la souris quitte le bouton
    void paintEvent(QPaintEvent* event) override;   // Redéfinis paintEvent() pour mettre en place des boutons ronds

public:
    VJeton(QWidget* parent, Jeton* pt, GameController* gc); // Constructeur de la classe Jeton
    void setFixedDiameter(int diameter);            // Définit le diamètre fixe du jeton progrès

signals:
    void sendProgressTokenInfo(Jeton* jeton);
    void istaken();                                 // Signal personnalisé pour indiquer que le jeton a été pris

private slots:
    void handleClicked();
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VConflictPawn : public QLabel // Classe de pions conflit visualisés
{
    Q_OBJECT
public:
    void setVisibility(bool visable);               // Définit la visibilité du pion conflit
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VLootingToken : public QLabel // Classe de jetons saccage visualisés
{
    Q_OBJECT
private:
    bool lossFlag = false;                          // Indique si le jeton saccage est perdu ou non

public:
    bool getLossFlag() const { return lossFlag; }   // Obtient l'état du drapeau de perte
    void setLossFlag(bool lf) { lossFlag = lf; }    // Définit l'état du drapeau de perte
    void setVisibility(bool visable);               // Définit la visibilité du jeton saccage
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VSideBoard : public QFrame // Classe de tableau latéral
{
    Q_OBJECT
private:
    QVector<VJeton*> jetons;        // Vecteur de pointeurs vers les jetons progrès
    QVector<VConflictPawn*> conflictPawns;          // Vecteur de pointeurs vers les pions conflit
    QVector<VLootingToken*> lootingTokens;          // Vecteur de pointeurs vers les jetons saccage
    QLabel* lootingPlaceholder = nullptr;           // Étiquette de remplacement pour le jeton saccage
    QHBoxLayout* JetonLayout = nullptr;     // Mise en page des jetons progrès
    QHBoxLayout* conflictPawnLayout = nullptr;      // Mise en page des pions conflit
    QHBoxLayout* lootingTokenLayout = nullptr;      // Mise en page des jetons saccage
    QVBoxLayout* sideBoardLayout = nullptr;         // Mise en page du tableau latéral
    QVector<QPoint> sideBoardGeometry;              // Géométrie du tableau latéral
    GameController* gameController = nullptr;
    unsigned int JetonSize = 0;             // Taille du jeton progrès
    unsigned int conflictPawnWidth = 0;             // Largeur du pion conflit
    unsigned int lootingTokenWidth = 0;             // Largeur du jeton saccage
    unsigned int conflictPawnPosition = 10;         // Position du pion conflit

    void init_Jetons();                     // Initialise les jetons progrès
    void init_ConflictPawns();                      // Initialise les pions conflit
    void init_LootingTokens();                      // Initialise les jetons saccage
    void init_JetonLayout();                // Initialise la mise en page des jetons progrès
    void init_ConflictPawnLayout();                 // Initialise la mise en page des pions conflit
    void init_LootingTokenLayout();                 // Initialise la mise en page des jetons saccage
    void init_SideBoardLayout();                    // Initialise la mise en page du tableau latéral
    void resizeEvent(QResizeEvent* event) override; // Redéfinir resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinir paintEvent() pour dessiner l'arrière-plan du QFrame

public:
    VSideBoard(GameController* gc);                             // Constructeur de la classe SideBoard
    const QVector<VJeton*>& getJetons() const;  // Obtient une référence constante au vecteur de jetons progrès
    void setConflictPawn(int mpDiff_P1P2);                      // Déplace le pion conflit dans la direction spécifiée d'un certain nombre d'étapes
    void moveConflictPawn(char direction, int step);            // Déplace le pion conflit dans la direction spécifiée d'un certain nombre d'étapes
    void loseLootingToken(unsigned int index);                  // Fait perdre au joueur le jeton saccage
    void calculateSideBoardGeometry();                          // Calcule la géométrie du tableau latéral
    void calculateJetonSize();                          // Calcule la taille du jeton progrès
    void calculateConflictPawnWidth();                          // Calcule le largeur du pion conflit
    void calculateLootingWidth();                               // Calcule le largeur du jeton saccage
    void updateSideBoard();                                     // Met à jour le tableau latéral
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VPlayerInfo : public QFrame // Classe d'informations du joueur visualisés
{
    Q_OBJECT
private:
    QLabel* playerName = nullptr;                   // Nom du joueur
    QWidget* currentPlayerBar = nullptr;            // Barre du joueur actuel qui indique le joueur actuel
    QLabel* victoryPointIcon = nullptr;             // Icône du point de victoire
    QLabel* militaryPowerIcon = nullptr;            // Icône de la puissance militaire
    QVector<QLabel*> wonderEffectIcons;             // Vecteur de pointeurs vers les icône des effets des merveilles
    QVector<QLabel*> resourcesIcons;                // Vecteur de pointeurs vers les icône de ressources
    QLabel* coinsIcon = nullptr;                    // Icône de la pièce de monnaie
    QLabel* victoryPointLabel = nullptr;            // Affiche le point de victoire
    QLabel* militaryPowerLabel = nullptr;           // Affiche la puissance militaire
    QVector<QLabel*> resourcesLabels;               // Affiche les nombres des ressources
    QLabel* coinsLabel = nullptr;                   // Affiche le montant d'argent
    QVector<QLabel*> scientificSymbolIcons;         // Affiche les symboles scientifiques
    QVector<QLabel*> chainSymbolIcons;              // Affiche les symboles de chaînage
    QHBoxLayout* wonderEffectLayout = nullptr;      // Mise en page des effets des merveilles
    QHBoxLayout* topLayout = nullptr;               // Mise en page horizontal supérieur
    QGridLayout* bottomLayout = nullptr;            // Mise en page horizontal inférieur
    QHBoxLayout* scientificSymbolLayout = nullptr;  // Mise en page des symboles scientifiques
    QHBoxLayout* chainSymbolLayout = nullptr;       // Mise en page des symboles de chaînage
    QVBoxLayout* playerInfoLayout = nullptr;        // Mise en page des informations du joueur
    QVector<QPoint> playerInfoGeometry;             // Géométrie des informations du joueur
    Joueur* player;
    bool currentPlayerFlag = false;                 // Indique si le joueur est le joueur actuel
    unsigned int victoryPoint = 0;                  // Point de victoire
    unsigned int militaryPower = 0;                 // Puissance militaire
    std::vector<unsigned int> nb_resource;          // Stocke la quantité de chaque ressource
    unsigned int coins = 0;                         // Montant d'argent
    std::vector<unsigned int> nb_scientificSymbol;  // Stocke le nombre de chaque symbole scientifique
    std::vector<unsigned int> nb_chainSymbol;       // Stocke le nombre de chaque symbole de chaînage
    unsigned int iconSize = 0;                      // Taille des icônes

    //void init_PlayerName(char plyrNumber, QString plyrName); //////paramètre à changer à Joueur*
    void init_PlayerName(char plyrNumber);                      // Initialise le nom du joueur
    void init_CurrentPlayerBar();                               // Initialise la barre du joueur actuel
    void init_VictoryPointIcon();                               // Initialise l'icône du point de victoire
    void init_MilitaryPowerIcon();                              // Initialise l'icône de la puissance militaire
    void init_WonderEffectIcons();                              // Initialise les icônes des effets des merveilles
    void init_ResourcesIcons();                                 // Initialise les icônes des ressources
    void init_CoinsIcon();                                      // Initialise l'icône de la pièce de monnaie
    void init_VictoryPointLabel();                              // Initialise l'affichage du point de victoire
    void init_MilitaryPowerLabel();                             // Initialise l'affichage de la puissance militaire
    void init_ResourcesLabels();                                // Initialise l'affichage des nombres de ressources
    void init_CoinsLabel();                                     // Initialise l'affichage du montant d'argent
    void init_ScientificSymbolIcons();                          // Initialise les icônes des symboles scientifiques
    void init_ChainSymbolIcons();                               // Initialise les icônes des symboles de chaînage
    void init_WonderEffectLayout(char plyrNumber);              // Initialise la mise en page des effets des merveilles
    void init_TopLayout(char plyrNumber);                       // Initialise la mise en page supérieure
    void init_BottomLayout(char plyrNumber);                    // Initialise la mise en page inférieure
    void init_ScientificSymbolLayout(char plyrNumber);          // Initialise la mise en page des symboles scientifiques
    void init_ChainSymbolLayout(char plyrNumber);               // Initialise la mise en page des symboles de chaînage
    void init_PlayerInfoLayout();                               // Initialise la mise en page des informations du joueur
    void resizeEvent(QResizeEvent* event) override;             // Redéfinir resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre

public:
    VPlayerInfo(char plyrNumber, Joueur* plyr);                     // Constructeur de la classe PlayerInfo
    void setCurrentPlayerFlag(const bool flag);                     // Définit le drapeau du joueur actuel
    void setCurrentPlayerFlag();                                    // Définit le drapeau du joueur actuel
    void setVictoryPoint(const unsigned int nb);                    // Définit le point de victoire
    void setVictoryPoint();                                         // Définit le point de victoire
    void setMilitaryPower(const unsigned int nb);                   // Définit la puissance militaire
    void setMilitaryPower();                                        // Définit la puissance militaire
    void setResources(size_t index, const unsigned int nb);         // Définit les ressources
    void setResources();                                            // Définit les ressources
    void setCoins(const unsigned int nb);                           // Définit le montant d'argent
    void setCoins();                                                // Définit le montant d'argent
    void obtainScientificSymbol(unsigned int ssID);                 // Permet au joueur d'obtenir le symbole scientifique
    void setScientificSymbols();                                    // Permet au joueur d'obtenir le symbole scientifique
    void obtainChainSymbol(unsigned int csID);                      // Permet au joueur d'obtenir le symbole de chaînage
    void setChainSymbols();                                         // Permet au joueur d'obtenir le symbole de chaînage
    void obtainWonderEffect(std::string symbolName);                // Permet au joueur d'obtenir l'effet de merveilles
    void loseChainSymbol(unsigned int csID);                        // Fait perdre au joueur le symbole de chaînage
    void loseScientificSymbol(unsigned int ssID);                   // Fait perdre au joueur le symbole scientifique
    void calculatePlayerInfoGeometry();                             // Calcule la géométrie des informations du joueur
    void calculateIconSize();                                       // Calcule la taille des icônes
    void setPlayerInfo();
    void updatePlayerInfo();                                        // Met à jour les informations du joueur
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VWonderDetails : public QWidget // Classe de détails de la merveille
{
    Q_OBJECT
private:
    QLabel* wonderImageLabel = nullptr;             // Image de la merveille
    QLabel* wonderNameLabel = nullptr;              // Nom de la merveille
    QLabel* constructStateLabel = nullptr;          // État de construction de la merveille
    QVector<QPushButton*> buttons;                  // Boutons pour exécuter les actions
    QVBoxLayout* topLayout = nullptr;               // Mise en page pour y mettre l'image et le nom de la merveille
    QVBoxLayout* bottomLayout = nullptr;            // Mise en page pour y mettre l'état de construction de la merveille et le bouton
    QVBoxLayout* wonderDetailsLayout = nullptr;     // Mise en page de la page des détails de la merveille
    VWonder* wonder = nullptr;                      // Merveille dont les détails doivent être affichés
    VBuilding* building = nullptr;
    GameController* gameController = nullptr;
    Joueur* player = nullptr;
    char wdr_OK_Flag = '0';

    void init_WonderImageLabel();                   // Initialise l'image de la merveille
    void init_WonderNameLabel();                    // Initialise le nom de la merveille
    void init_ConstructStateLabel();                // Initialise l'état de construction de la merveille
    void init_Buttons(char type);                   // Initialise les boutons pour exécuter les actions
    void init_TopLayout();                          // Initialise la mise en page pour y mettre l'image et le nom de la merveille
    void init_BottomLayout();                       // Initialise la mise en page pour y mettre l'état de construction de la merveille et le bouton
    void init_WonderDetailsLayout();                // Initialise la mise en page de la page des détails de la merveille
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    VWonderDetails(QWidget* parent, VWonder* vwd, VBuilding* vbld, GameController* gc, Joueur* p, char type);    // Constructeur de la classe VWonderDetails

signals:
    void constructSucceeded(VWonder* vwdr);
    void exceptionHappened(QString msg);   // Signal personnalisé pour afficher un message lorsqu'une exception se produit

public slots:
    void handleConstructionButtonCliked();
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VWonderConstruction : public QWidget
{
    Q_OBJECT
private:
    QVector<VWonder*> wonders;
    QWidget* contentArea = nullptr;
    QPushButton* closeButton = nullptr;
    QGridLayout* contentAreaLayout = nullptr;
    QVBoxLayout* wonderConstructionLayout = nullptr;
    VWonderDetails* wonderDetails = nullptr;
    VBuilding* building = nullptr;
    GameController* gameController = nullptr;
    Joueur* player = nullptr;

    void init_Wonders(Joueur* p);
    void init_ContentArea();
    void init_CloseButton();
    void init_ContentAreaLayout();
    void init_WonderConstructionLayout();
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    VWonderConstruction(QWidget* parent, VBuilding* vbld, GameController* gc, Joueur* p);  // Constructeur de la classe VWonderDetails

signals:
    void isConstructed(int wonderID);

public slots:
    void openWonderDetails(VWonder* vwdr);
    void handleConstruction(VWonder* vwdr);
    void showMessage(QString msg);
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VCardDetails : public QWidget // Classe de détails de la carte
{
    Q_OBJECT
private:
    QLabel* cardImageLabel = nullptr;               // Image de la carte
    QLabel* cardNameLabel = nullptr;                // Nom de la carte
    QVector<QPushButton*> buttons;                  // Boutons pour exécuter les actions
    QVBoxLayout* buttonLayout = nullptr;            // Mise en page des boutons
    QVBoxLayout* cardDetailsLayout = nullptr;       // Mise en page de la page des détails de la carte
    VBuilding* building = nullptr;                  // Bâtiment dont les détails doivent être affichés
    VWonderConstruction* wonderConstruction = nullptr;
    GameController* gameController = nullptr;
    Joueur* player;
    char bld_OK_Flag = '0';
    char detailsType = '0';                         // Type de la page des détails de la carte

    void init_CardImageLabel();                     // Initialise l'image de la carte
    void init_CardNameLabel(QPalette palette);      // Initialise le nom de la carte
    void init_Buttons(QPalette palette, char type); // Initialise les boutons pour exécuter les actions
    void init_ButtonLayout();                       // Initialise la mise en page des boutons
    void init_CardDetailsLayout();                  // Initialise la mise en page des détails de la carte
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    VCardDetails(QWidget* parent, VBuilding* vbld, GameController* gc, Joueur* p, char type);  // Constructeur de la classe VCardDetails
    const QVector<QPushButton*>& getButtons() const;            // Obtient les boutons
    const char& getDetailsType() const { return detailsType; }  // Obtient le type de détails

signals:
    void constructSucceeded();
    void discardSucceeded();
    void wonderConstructionSucceeded(int wonderID);
    void discardedConstructSucceeded();
    void destructOpponentsCardSucceeded();
    void exceptionHappened(QString msg);   // Signal personnalisé pour afficher un message lorsqu'une exception se produit

public slots:
    void handleConstructionButtonCliked();
    void handleDiscardButtonCliked();
    void handleConstructWonder(int wonderID);
    void handleDestructOpponentsCard();
    void handleDiscardedCliked();
    void openVWonderConstruction(Joueur* p);
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VPlayersCards : public QScrollArea // Classe de visualisation des cartes possédées par le joueur
{
    Q_OBJECT
private:
    QVector<VBuilding_Purchased*> plyrCards;                // Vecteur de pointeurs vers les cartes du joueur
    QGridLayout* playersCardsLayout;                        // Mise en page des cartes du joueur
    QVector<QPoint> playersCardsGeometry;                   // Géométrie des cartes du joueur
    VCardDetails* cardDetails = nullptr;                    // Page des détails de la carte
    CardSize cardSize;                                      // Taille de la carte
    GameController* gameController = nullptr;
    Joueur* player = nullptr;
    void resizeEvent(QResizeEvent* event) override;         // Redéfinir resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre

public:
    VPlayersCards(QWidget* parent, GameController* gc, Joueur* p);  // Constructeur de la classe PlayersCards
    void calculatePlayersCardsGeometry();                   // Calcule la géométrie des cartes du joueur
    void calculateCardSize();                               // Calcule la taille de la carte
    void updatePlayersCards();                              // Met à jour les positions des cartes

public slots:
    void constructCard(Card* card);                         // Slot personnalisé pour gérer l'achat de cartes
    void loseCard(VBuilding_Purchased* vbld);
    void openCardDetails(VBuilding_Purchased* vbld);        // Slot personnalisé pour ouvrir la page des détails de la carte
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VWonderFrame : public QFrame // Classe de merveilles visualisés
{
    Q_OBJECT
private:
    QVector<VWonder*> wonders;                      // Vecteur de pointeurs vers les merveilles
    QHBoxLayout* wonderFrameLayout;                 // Mise en page du cadre des merveilles
    QVector<QPoint> wonderFrameGeometry;            // Géométrie du cadre des merveilles
    CardSize wonderSize;                            // Taille de la merveille
    Joueur* player;
    void resizeEvent(QResizeEvent* event) override; // Redéfinir resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre

public:
    VWonderFrame(Joueur* p);                        // Constructeur de la classe VWonderFrame
    const QVector<VWonder*>& getWonders() const;    // Obtient les merveilles
    void calculateWonderFrameGeometry();            // Calcule la géométrie du cadre des merveilles
    void calculateWonderSize();                     // Calcule la taille de la merveille
    void setWonderFrame();
    void updateWonderFrame();                       // Met à jour le cadre de la merveille
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VCardPyramid : public QFrame // Classe de bâtiments visualisés non construits
{
    Q_OBJECT
private:
    QVector<QPoint> cardPyramidGeometry;            // Enregistre les coordonnées des quatre sommets du cadre
    Eres age;                                       // Ère actuelle
    QVector<VBuilding_Unpurchased*> cards_age1;     // Stocke les cartes de l'ère Ⅰ
    QVector<VBuilding_Unpurchased*> cards_age2;     // Stocke les cartes de l'ère Ⅱ
    QVector<VBuilding_Unpurchased*> cards_age3;     // Stocke les cartes de l'ère Ⅲ
    std::vector<bool> cardConstructedFlags_1;
    std::vector<bool> cardConstructedFlags_2;
    std::vector<bool> cardConstructedFlags_3;
    int levels_age1[5] = { 2, 3, 4, 5, 6 };         // Stocke le nombre de cartes dans chaque couche du jeu de l'ère Ⅰ
    int levels_age2[5] = { 6, 5, 4, 3, 2 };         // Stocke le nombre de cartes dans chaque couche du jeu de l'ère Ⅱ
    int levels_age3[7] = { 2, 3, 4, 2, 4, 3, 2 };   // Stocke le nombre de cartes dans chaque couche du jeu de l'ère Ⅲ
    int numLevels_age1 = 5;                         // Stocke le nombre de couches du jeu de l'ère Ⅰ
    int numLevels_age2 = 5;                         // Stocke le nombre de couches du jeu de l'ère Ⅱ
    int numLevels_age3 = 7;                         // Stocke le nombre de couches du jeu de l'ère Ⅲ
    CardSize cardSize;                              // Taille de la carte
    CardOverlap cardOverlap;                        // Taille de la partie de chevauchement
    
    void init_Cards(std::vector<Card*> c1, std::vector<Card*> c2, std::vector<Card*> c3);   // Initialise les cartes
    void calculateCardPyramidGeometry();            // Calcule la géométrie des quatre sommets du cadre
    void calculateCardSize();                       // Calcule la taille de la carte
    void calculateCardOverlap();                    // CalculE la taille de la partie de chevauchement
    void updateCardPyramid();                       // Met à jour l'emplacement des cartes
    void resizeEvent(QResizeEvent* event) override; // Redéfinir resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre

public:
    VCardPyramid(std::vector<Card*> c1, std::vector<Card*> c2, std::vector<Card*> c3);  // Constructeur de la classe CardPyramid
    const QVector<VBuilding_Unpurchased*>& getCards(Eres age) const;    // Obtient les cartes de l'ère spécifiée
    Eres getAge() const { return age; }                                 // Obtient l'ère actuelle
    void setAge(Eres a);

public slots:
    void handleConstruction();
};

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
#endif // !VGameElements_h