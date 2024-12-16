#ifndef VBuilding_h
#define VBuilding_h

#include "GameController.h"
#include "QtHeader.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VBuilding : public QPushButton // Classe de bâtiments visualisés de base
{
    Q_OBJECT
protected:
    Card* building = nullptr;                       // Pointeur vers un objet Card représentant le bâtiment 
    virtual void set_BuildingIcon() = 0;            // Définit l'icône du bâtiment
    void enterEvent(QEnterEvent* event) override;   // Redéfinir enterEvent() pour définir le style de la souris lorsque la souris entre dans le bouton
    void leaveEvent(QEvent* event) override;        // Redéfinir leaveEvent() pour rétablir le style de souris par défaut lorsque la souris quitte le bouton

public:
    VBuilding(QWidget* parent, Card* bld);          // Constructeur de la classe VBuilding
    Card* getBuilding();                            // Obtient un pointeur vers le bâtiment
    const Card* getBuilding() const;                // Obtient un pointeur constant vers le bâtiment
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VBuilding_Unpurchased : public VBuilding // Classe de bâtiments visualisés non construits
{
    Q_OBJECT
private:
    bool faceFlag = true;                           // Indique si la carte est face visible ou face cachée
    bool selectableFlag = false;                    // Indique si le bâtiment est sélectionnable ou non
    bool constructionState = false;	                // Indique si le bâtiment est construit par le joueur ou non
    bool discardFlag = false;

    
    void enterEvent(QEnterEvent* event) override;   // Redéfinir enterEvent() pour définir le style de la souris lorsque la souris entre dans le bouton
    void leaveEvent(QEvent* event) override;        // Redéfinir leaveEvent() pour rétablir le style de souris par défaut lorsque la souris quitte le bouton

public:
    void set_BuildingIcon() override;               // Définit l'icône du bâtiment non construit
    VBuilding_Unpurchased(QWidget* parent, Card* card); // Constructeur de la classe VBuilding_Unpurchased
    const bool getFaceFlag() const;                     // Obtient l'état recto-verso de la carte
    const bool getSelectableFlag() const;               // Obtient la sélectionnabilité du bâtiment non construit
    const bool getConstructionState() const;            // Obtient l'état de construction du bâtiment non construit
    const bool getDiscardFlag() const;
    void setFaceFlag(const bool flag);                  // Définit l'état recto-verso de la carte
    void setSelectableFlag(const bool flag);            // Définit la sélectionnabilité du bâtiment non construit
    void setConstructionState(const bool flag);         // Définit l'état de construction du bâtiment non construit
    void setDiscardFlag(const bool flag);


signals:
    void showDetails(VBuilding_Unpurchased* vbld);      // Signal personnalisé pour afficher les détails du bâtiment non construit
    void isConstructed(Card* vbld);                     // Signal personnalisé émis lorsque le bâtiment est construit
    void isDiscarded(Card* vbld);
    void isUsedByWonder(Card* vbld);
    void cannotBeChoosenByPlayer(QString msg);

public slots:
    void chosenByPlayer();                              // Signal personnalisé émis avec Card* lorsque le bouton est choisi par le joueur
    void handleClicked();
    void handlePurchase();                              // Slot personnalisé pour gérer l'achat du bâtiment
    void handleDiscardedPurchase();
    void handleDiscard();
    void handleWonderConstruction();
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VBuilding_Purchased : public VBuilding  // Classe de bâtiments visualisés construits
{
    Q_OBJECT
private:
    void set_BuildingIcon() override;                   // Définit l'icône du bâtiment construit

public:
    VBuilding_Purchased(QWidget* parent, Card* card);   // Constructeur de la classe VBuilding_Purchased

signals:
    void showDetails(VBuilding_Purchased* vbld);        // Signal personnalisé pour afficher les détails du bâtiment non construit

private slots:
    void chosenByPlayer();                              // Signal personnalisé émis avec Card* lorsque le bouton est choisi par le joueur
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
class VWonder : public QPushButton  // Classe de merveilles visualisés
{
    Q_OBJECT
private:
    Card* wonder = nullptr;                         // Pointeur vers un objet Card représentant la merveille
    bool constructionState = false;                 // Indique si la merveille est construit par le joueur
    void set_WonderIcon();                          // Définit l'icône de la merveille
    void enterEvent(QEnterEvent* event) override;	// Redéfinir enterEvent() pour définir le style de la souris lorsque la souris entre dans le bouton
    void leaveEvent(QEvent* event) override;        // Redéfinir leaveEvent() pour rétablir le style de souris par défaut lorsque la souris quitte le bouton

public:
    VWonder(QWidget* parent, Card* wdr);            // Constructeur de la classe VWonder
    Card* getWonder();                              // Obtient un pointeur constant vers la merveille
    const bool getConstructionState() const;        // Obtient l'état de construction de la merveille
    void setConstructionState(const bool flag);     // Définit l'état de construction de la merveille
    void setVWonder(Card* wdr);

signals:
    void isConstructed(VWonder* vwd);               // Signal personnalisé émis lorsque le bâtiment est construit
    void showDetails(VWonder* vwd);                 // Signal personnalisé pour afficher les détails de la merveille

public slots:
    void handleConstruction();
    void chosenByPlayer();                          // Slot personnalisé appelé lorsque le bâtiment est sélectionné par le joueur
};
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#endif // !VBuilding_h