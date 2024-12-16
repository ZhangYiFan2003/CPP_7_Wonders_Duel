#ifndef GUI_h
#define GUI_h

#include <random>
#include <windows.h>
#include "QtHeader.h"
#include "VGameElements.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class GeneralTextStyle // Classe de style général de text, qui gère le style de texte général
{
private:
    GeneralTextStyle() = default;   // Constructeur privé pour empêcher l'instanciation directe de la classe

public:
    static QFont font;              // Police de caractères statique utilisée pour le style de texte général
    static QPalette palette;        // Palette de couleurs statique utilisée pour le style de texte général
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class GeneralButton : public QPushButton // Classe de bouton avec un style général personnalisé
{
    Q_OBJECT
private:
    bool hover;                                     // Variable pour suivre l'état du survol de la souris
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner la bordure du bouton
    void enterEvent(QEnterEvent* event) override;   // Redéfinit enterEvent() pour gérer l'entrée de la souris
    void leaveEvent(QEvent* event) override;        // Redéfinit leaveEvent() pour gérer la sortie  de la souris

public:
    GeneralButton(QString text, QWidget* parent); // Constructeur de la classe GeneralButton
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class ToggleButton : public GeneralButton // Classe de bouton bascule, qui est utilisé pour basculer l'état de sélection du paramètre
{
    Q_OBJECT
private:
    bool toggledFlag;               // État de la sélection
    void updateButtonText();        // Met à jour le texte du bouton

public:
    ToggleButton(QWidget* parent);  // Constructeur de la classe ToggleButton
    bool getToggledFlag() const;    // Obtient l'état du bouton bascule

signals:
    void toggledChanged(bool);      // Signal personnalisé émis lorsque l'état bascule est modifié

public slots:
    void toggle();                  // Slot personnalisé pour changer l'état de la sélection
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class FullscreenButton : public GeneralButton // Classe de bouton plein écran, utilisé pour changer l'état plein écran de la fenêtre
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner le bouton en fonction de la taille de la fenêtre

public:
    FullscreenButton(QWidget* parent);              // Constructeur de la classe FullscreenButton

public slots:
    void toggleFullScreen();                        // Slot personnalisé pour changer l'état de l'écran
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class MainWindow : public QMainWindow // Classe de fenêtre principale dans laquelle se trouvent tous les widgets
{
    Q_OBJECT
    friend class PageControler;                     // Déclare la classe PageControler comme classe amie

private:
    void keyPressEvent(QKeyEvent* event) override;  // Redéfinit keyPressEvent() pour activer le plein écran en appuyant sur F11
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour que l'échelle de la fenêtre reste inchangée

public:
    MainWindow(QWidget* parent);                    // Constructeur de la classe MainWindow
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class MainMenu : public QWidget // Classe de menu principal, qui est l'écran initial du jeu
{
    Q_OBJECT
    friend class PageControler;                     // Déclare la classe PageControler comme classe amie

private:
    QLabel* logo = nullptr;                         // LOGO du jeu
    GeneralButton* startButton = nullptr;           // Bouton pour commencer le jeu
    GeneralButton* settingButton = nullptr;         // Bouton pour ouvrir le menu des paramètres du jeu
    GeneralButton* quitButton = nullptr;            // Bouton pour quitter le jeu
    QVBoxLayout* mainMenuLayout = nullptr;          // Mise en page du menu principal

    void init_Logo();                               // Initialise le logo du jeu
    void init_StartButton();                        // Initialise le bouton pour commencer le jeu
    void init_SettingButton();                      // Initialise le bouton pour ouvrir le menu des paramètres du jeu
    void init_QuitButton();                         // Initialise le bouton pour quitter le jeu
    void init_MainMenuLayout();                     // Initialise la mise en page du menu principal
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    MainMenu(QWidget* parent);                      // Constructeur de la classe MainMenu

signals:
    void openSelection();                           // Signal personnalisé pour ouvrir le menu de sélection du mode de jeu
    void openSettings();                            // Signal personnalisé pour ouvrir le menu des paramètres du jeu
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class SettingMenu : public QWidget // Classe de menu de paramètres, qui gère la page de gestion des paramètres de jeu
{
    Q_OBJECT
    friend class PageControler;                     // Déclare la classe PageControler comme classe amie

private:
    QLabel* pantheonLabel = nullptr;                // Étiquette  pour placer l'icône de l'extension PANTHEON
    QLabel* agoraLabel = nullptr;                   // Étiquette  pour placer l'icône de l'extension AGORA
    QLabel* ruleURL = nullptr;                      // Étiquette  pour placer l'URL des règles du jeu
    ToggleButton* pantheonButton = nullptr;         // Bouton pour activer l'extension PANTHEON
    ToggleButton* agoraButton = nullptr;            // Bouton pour activer l'extension AGORA
    FullscreenButton* fullscreenButton = nullptr;   // Bouton pour changer l'état de l'écran
    GeneralButton* mainMenuButton = nullptr;        // Bouton pour retourner au menu principal
    QGridLayout* settingMenuLayout = nullptr;       // Mise en page du menu des paramètres du jeu

    void init_PantheonLabel();                      // Initialise l'étiquette pour placer l'icône de l'extension PANTHEON
    void init_AgoraLabel();                         // Initialise l'étiquette pour placer l'icône de l'extension AGORA
    void init_RuleURL();                            // Initialise l'étiquette pour placer l'URL des règles du jeu
    void init_PantheonButton();                     // Initialise le bouton pour activer l'extension PANTHEON
    void init_AgoraButton();                        // Initialise le bouton pour activer l'extension AGORA
    void init_FullscreenButton();                   // Initialise le bouton pour changer l'état de l'écran
    void init_MainMenuButton();                     // Initialise le bouton pour retourner au menu principal
    void init_SettingMenuLayout();                  // Initialise la mise en page du menu des paramètres du jeu
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    SettingMenu(QWidget* parent);                   // Constructeur de la classe SettingMenu

signals:
    void openMainMenu();                            // Signal personnalisé pour ouvrir le menu principal
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class SelectionMenu : public QWidget // Classe de menu de sélection des joueurs, qui gère la page de sélection des joueurs du jeu
{
    Q_OBJECT
    friend class PageControler;                         // Déclare la classe PageControler comme classe amie

private:
    GeneralButton* onePlayerButton = nullptr;           // Bouton pour sélectionner le mode d'un joueur
    GeneralButton* twoPlayersButton = nullptr;          // Bouton pour sélectionner le mode de deux joueurs
    GeneralButton* mainMenuButton = nullptr;            // Bouton pour retourner au menu principal
    QHBoxLayout* selectionButtonLayout = nullptr;       // Mise en page des boutons de sélection
    QHBoxLayout* mainMenuButtonLayout = nullptr;        // Mise en page du bouton permettant retourner au menu principal
    QVBoxLayout* selectionMenuLayout = nullptr;         // Mise en page du menu de sélection du mode de jeu
    QPixmap backgroundPixmap;                           // Stocke l'arrière-plan du QWidget

    void init_OnePlayerButton();                        // Initialise le bouton pour sélectionner le mode d'un joueur
    void init_TwoPlayersButton();                       // Initialise le bouton pour sélectionner le mode de deux joueurs
    void init_MainMenuButton();                         // Initialise le bouton pour retourner au menu principal
    void init_SelectionButtonLayout();                  // Initialise la mise en page des boutons de sélection
    void init_MainMenuButtonLayout();                   // Initialise la mise en page du bouton permettant de retourner au menu principal
    void init_SelectionMenuLayout();                    // Initialise la mise en page du menu de sélection du mode de jeu
    void setRandomBackground();                         // Définit un arrière-plan aléatoire
    void resizeEvent(QResizeEvent* event) override;     // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;       // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    SelectionMenu(QWidget* parent);                     // Constructeur de la classe SelectionMenu

signals:
    void openMainMenu();                                // Signal personnalisé pour ouvrir le menu principal
    void openCardTablePage();                           // Signal personnalisé pour ouvrir la page de la table à cartes
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class DestructionPage : public QWidget // Classe de page de destruction où les cartes peuvent être visualisées et détruites
{
    Q_OBJECT
private:
    QLabel* playerNameLabel = nullptr;              // Étiquette pour afficher le nom du joueur
    QWidget* contentArea = nullptr;                 // Zone de contenu pour les cartes du joueur
    QScrollArea* selectionArea = nullptr;           // Zone de défilement pour les cartes du joueur
    QLabel* hintLabel = nullptr;                    // Étiquette pour afficher l'astuce
    QGridLayout* contentLayout = nullptr;           // Mise en page des cartes du joueur
    QVBoxLayout* destructionPageLayout = nullptr;   // Mise en page de la page des détails de la merveille
    QVector<VBuilding_Purchased*> cards;            // Vecteur des cartes du joueur
    VCardDetails* cardDetails = nullptr;            // Détails de la carte
    GameController* gameController = nullptr;
    Joueur* player = nullptr;

    void init_PlayerNameLabel();                    // Initialise l'étiquette pour afficher le nom du joueur
    void init_ContentArea();                        // Initialise la zone de contenu pour les cartes du joueur
    void init_SelectionArea();                      // Initialise la zone de défilement pour les cartes du joueur
    void init_HintLabel();                          // Initialise l'étiquette pour afficher l'astuce
    void init_ContentLayout(Types c);              // Initialise la mise en page des cartes du joueur
    void init_DestructionPageLayout();              // Initialise la mise en page de la page des détails de la carte
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    DestructionPage(QWidget* parent, GameController* gc, Joueur* p, Types c);   // Constructeur de la classe DestructionPage

signals:
    void opponentsCardHasBeenDestructed(VBuilding_Purchased* vbld);

public slots:
    void openCardDetails(VBuilding_Purchased* vbld);    // Slot personnalisé pour ouvrir la page des détails de la carte
    void handleCardDetailsSignalEmission(VBuilding_Purchased* vbld);
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class CardTablePage;
class DiscardedCardsPage : public QWidget
{
    Q_OBJECT
private:
    QLabel* pageNameLabel = nullptr;                // Étiquette pour afficher le nom de la page
    QWidget* contentArea = nullptr;                 // Zone de contenu pour les cartes du joueur
    QScrollArea* selectionArea = nullptr;           // Zone de défilement pour les cartes du joueur
    QLabel* hintLabel = nullptr;                    // Étiquette pour afficher l'astuce
    QGridLayout* contentLayout = nullptr;           // Mise en page des cartes du joueur
    QVBoxLayout* discardedCardsPageLayout = nullptr;// Mise en page de la page des détails de la merveille
    QVector<VBuilding_Unpurchased*> cards;          // Vecteur des cartes du joueur
    VCardDetails* cardDetails = nullptr;            // Détails de la carte
    CardTablePage* parentPage = nullptr;
    GameController* gameController = nullptr;
    Joueur* player = nullptr;

    void init_PageNameLabel();                      // Initialise l'étiquette pour afficher le nom du joueur
    void init_ContentArea();                        // Initialise la zone de contenu pour les cartes du joueur
    void init_SelectionArea();                      // Initialise la zone de défilement pour les cartes du joueur
    void init_HintLabel();                          // Initialise l'étiquette pour afficher l'astuce
    void init_ContentLayout();               // Initialise la mise en page des cartes du joueur
    void init_DiscardedCardsPageLayout();           // Initialise la mise en page de la page des détails de la carte
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    DiscardedCardsPage(QWidget* parent, CardTablePage* ctp, GameController* gc, Joueur* p);   // Constructeur de la classe DestructionPage

public slots:
    void openCardDetails(VBuilding_Unpurchased* vbld);   // Slot personnalisé pour ouvrir la page des détails de la carte
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class DiscardedProgressTokensPage : public QWidget
{
    Q_OBJECT
private:
    QLabel* pageNameLabel = nullptr;                // Étiquette pour afficher le nom de la page
    QWidget* contentArea = nullptr;                 // Zone de contenu pour les cartes du joueur
    QLabel* hintLabel = nullptr;                    // Étiquette pour afficher l'astuce
    QHBoxLayout* contentLayout = nullptr;           // Mise en page des cartes du joueur
    QVBoxLayout* discardedProgressTokensPageLayout = nullptr;
    QVector<VJeton*> discardedProgressTokens;
    GameController* gameController = nullptr;
    Joueur* player = nullptr;

    void init_PageNameLabel();                      // Initialise l'étiquette pour afficher le nom du joueur
    void init_ContentArea();                        // Initialise la zone de contenu pour les cartes du joueur
    void init_HintLabel();                          // Initialise l'étiquette pour afficher l'astuce
    void init_ContentLayout();
    void init_DiscardedProgressTokensPageLayout();
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    DiscardedProgressTokensPage(QWidget* parent, GameController* gc, Joueur* p);   // Constructeur de la classe DestructionPage

public slots:
    void handleProgressTokenInfo(Jeton* jeton);
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class CardTablePage : public QWidget // Classe de page de table à carte, qui gère l'écran pendant le jeu
{
    Q_OBJECT
    friend class PageControler;                         // Déclare la classe PageControler comme classe amie

private:
    VSideBoard* sideBoard = nullptr;                    // Cadre des jetons et du plateau
    VPlayerInfo* playerInfo_1 = nullptr;                // Cadre des information du joueur 1
    VPlayerInfo* playerInfo_2 = nullptr;                // Cadre des information du joueur 2
    VPlayersCards* playersCards_1 = nullptr;            // Cadre des cartes possédées par les joueurs
    VPlayersCards* playersCards_2 = nullptr;            // Cadre des cartes possédées par les joueurs
    VWonderFrame* wonderFrame_1 = nullptr;              // Cadre des merveilles du joueur 1
    VWonderFrame* wonderFrame_2 = nullptr;              // Cadre des merveilles du joueur 2
    VCardPyramid* cardPyramid = nullptr;                // Cadre des cartes
    QLabel* ageInfo = nullptr;                          // Affiche l'ère actuelle
    GeneralButton* endTurnButton = nullptr;
    QHBoxLayout* topLayout = nullptr;                   // Mise en page pour y mettre le cadre du jeton et du plateau
    QVBoxLayout* playersPossessionLayout_1 = nullptr;   // Mise en page pour y mettre les cartes du joueur 1 et les merveilles
    QVBoxLayout* playersPossessionLayout_2 = nullptr;   // Mise en page pour y mettre les cartes du joueur 2 et les merveilles
    QHBoxLayout* bottomLayout = nullptr;                // Mise en page pour y mettre les cadres des cartes et des cartes possédées par les joueurs
    QVBoxLayout* cardTablePageLayout = nullptr;         // Mise en page de la page de table à carte
    VCardDetails* cardDetails = nullptr;                // Page des détails de la carte
    VWonderDetails* wonderDetails = nullptr;            // Page des détails de la merveille
    DestructionPage* destructionPage = nullptr;         // Page de déstruction de cartes
    DiscardedCardsPage* discardedCardsPage = nullptr;
    DiscardedProgressTokensPage* discardedProgressTokensPage = nullptr;
    GameController* gameController = nullptr;
    char currentPlayer = '1';
    bool isAge2 = false;
    bool isAge3 = false;

    void init_SideBoard();                              // Initialise le cadre des jetons et du plateau
    void init_PlayerInfo();                             // Initialise les cadres des informations des joueurs
    void init_PlayersCards();                           // Initialise les cadres des cartes possédées par les joueurs
    void init_WonderFrame();                            // Initialise les cadres des merveilles des joueurs
    void init_CardPyramid();                            // Initialise le cadre des cartes non achetées
    void init_AgeInfo();                                // Initialise l'affichage de l'ère
    void init_TopLayout();                              // Initialise la mise en page supérieure
    void init_PlayersPossessionLayout();                // Initialise la mise en page des cartes et merveilles des joueurs
    void init_BottomLayout();                           // Initialise la mise en page inférieure
    void init_CardTablePageLayout();                    // Initialise la mise en page de la page de table à cartes
    void updateAgeInfo();                               // Met à jour l'affichage de l'ère actuelle
    void keyPressEvent(QKeyEvent* event) override;      // Redéfinit keyPressEvent() pour ouvrir le menu de pause en appuyant sur ESC
    void resizeEvent(QResizeEvent* event) override;     // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;       // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    CardTablePage(QWidget* parent, GameController* gc); // Constructeur de la classe CardTablePage
    VPlayerInfo* getPlayerInfo1() { return playerInfo_1; }
    VPlayerInfo* getPlayerInfo2() { return playerInfo_2; }
    VPlayersCards* getPlayersCards1() { return playersCards_1; }
    VPlayersCards* getPlayersCards2() { return playersCards_2; }
    const char& getCurrentPlayer() const { return currentPlayer; }

signals:
    void openPauseMenu();                               // Signal personnalisé pour ouvrir le menu de pause
    void openVictoryPage(Joueur* p);                    // Signal personnalisé pour ouvrir la page de victoire

public slots:
    void endTurn();
    void openCardDetails(VBuilding_Unpurchased* vbld);  // Slot personnalisé pour ouvrir la page des détails de la carte
    void openWonderDetails(VWonder* vwd);               // Slot personnalisé pour ouvrir la page des détails de la merveille
    void openDestructionPage(Joueur* p, int wonderID);    // Slot personnalisé pour ouvrir la page de déstruction de cartes
    void openDiscardedCardsPage(Joueur* p, int wonderID);
    void openDiscardedProgressTokensPage(Joueur* p, int wonderID);
    void showMessage(QString msg);                      // Slot personnalisé pour afficher un message
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class PauseMenu : public QWidget // Classe de menu de pause, qui affiche l'interface de pause
{
    Q_OBJECT
    friend class PageControler;                     // Déclare la classe PageControler comme classe amie

private:
    GeneralButton* cardTablePageButton = nullptr;   // Bouton pour revenir à l'interface du jeu
    FullscreenButton* fullscreenButton = nullptr;   // Bouton pour changer l'état de l'écran
    GeneralButton* mainMenuButton = nullptr;        // Bouton pour retourner au menu principal
    QVBoxLayout* pauseMenuLayout = nullptr;         // Mise en page du menu de pause

    void init_CardTablePageButton();                // Initialise le bouton pour revenir à l'interface du jeu
    void init_FullscreenButton();                   // Initialise le bouton pour changer l'état de l'écran
    void init_MainMenuButton();                     // Initialise le bouton pour retourner au menu principal
    void init_PauseMenuLayout();                    // Initialise la mise en page du menu de pause
    void keyPressEvent(QKeyEvent* event) override;  // Redéfinit keyPressEvent() pour retourner au jeu en appuyant sur ESC
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    PauseMenu(QWidget* parent);                     // Constructeur de la classe PauseMenu

signals:
    void openMainMenu();                            // Signal personnalisé pour ouvrir le menu principal
    void openCardTablePage();                       // Signal personnalisé pour ouvrir la page de la table à cartes
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VictoryPage : public QWidget // Classe de page de victoire, qui affiche le résultat du jeu
{
    Q_OBJECT
    friend class PageControler;                     // Déclare la classe PageControler comme classe amie

private:
    QLabel* winnerInfo = nullptr;                   // Étiquette pour afficher l'information du vainqueur
    GeneralButton* mainMenuButton = nullptr;        // Bouton pour retourner au menu principal
    QVBoxLayout* victoryPageLayout = nullptr;       // Mise en page de la page de victoire
    QPixmap backgroundPixmap;                       // Stocke l'arrière-plan du QWidget

    void init_WinnerInfo(Joueur* p);                // Initialise l'étiquette pour afficher l'information du vainqueur avec le nom du joueur
    void init_MainMenuButton();                     // Initialise le bouton pour retourner au menu principal
    void init_VictoryPageLayout();                  // Initialise la mise en page de la page de victoire
    void setRandomBackground();                     // Définit un arrière-plan aléatoire
    void resizeEvent(QResizeEvent* event) override; // Redéfinit resizeEvent() pour redimensionner les widget en fonction de la taille de la fenêtre
    void paintEvent(QPaintEvent* event) override;   // Redéfinit paintEvent() pour dessiner l'arrière-plan du QWidget

public:
    VictoryPage(QWidget* parent, Joueur* p); // Constructeur de la classe EndOfGamePage

signals:
    void openMainMenu();                            // Signal personnalisé pour ouvrir le menu principal
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class PageControler // Classe de contrôleur de page, qui gère toutes les pages
{
private:

    QMainWindow* mainWindow = nullptr;          // Fenêtre principale du jeu
    QStackedWidget* pages = nullptr;            // Widget pour enregistrer toutes les pages
    MainMenu* mainMenu = nullptr;               // Menu principal du jeu
    SettingMenu* settingMenu = nullptr;         // Menu des paramètres du jeu
    SelectionMenu* selectionMenu = nullptr;     // Menu de sélection du mode de jeu
    CardTablePage* cardTablePage = nullptr;     // Page de la table à cartes
    PauseMenu* pauseMenu = nullptr;             // Menu de pause
    VictoryPage* victoryPage = nullptr;         // Page de victoire
    GameController* gameController = nullptr;
    void resetSelectionMenu();                  // Réinitialise le menu de sélection
    void resetCardTablePage();// Réinitialise la page de la table à cartes
    void resetVictoryPage(QString plyrName);    // Réinitialise la page de victoire

public:
    PageControler(GameController* gc);          // Constructeur de la classe PageControler
    void pageGeneration();                      // Génère toutes les pages
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
#endif // !GUI_h