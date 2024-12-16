#include "VBuilding.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VBuilding::VBuilding(QWidget* parent, Card* bld) : QPushButton(parent), building(bld)
{
    //
}

Card* VBuilding::getBuilding()
{
    return building;
}

const Card* VBuilding::getBuilding() const
{
    return building;
}

void VBuilding::enterEvent(QEnterEvent* event)
{
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void VBuilding::leaveEvent(QEvent* event)
{
    unsetCursor();
    QPushButton::leaveEvent(event);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VBuilding_Unpurchased::VBuilding_Unpurchased(QWidget* parent, Card* c) : VBuilding(parent, c)
{
    setStyleSheet
    (
        "QPushButton {"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none; }"
    );
    set_BuildingIcon();
    setSelectableFlag(true);
    setDiscardFlag(building->getDiscardFlag());
    connect(this, &QPushButton::clicked, this, &VBuilding_Unpurchased::handleClicked);
    //connect(this, &QPushButton::clicked, this, &VBuilding_Unpurchased::handlePurchase);	///// cliced()źŴĳɱź
}

void VBuilding_Unpurchased::set_BuildingIcon()
{
    QIcon icon;
    int id = building->getID();
    if (faceFlag)
    {
        switch (id)
        {
        case 13:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/lumber_yard.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/lumber_yard.png"), QIcon::Disabled);
            break;
        case 14:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/logging_camp.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/logging_camp.png"), QIcon::Disabled);
            break;
        case 15:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pool.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pool.png"), QIcon::Disabled);
            break;
        case 16:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pit.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pit.png"), QIcon::Disabled);
            break;
        case 17:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/quarry.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/quarry.png"), QIcon::Disabled);
            break;
        case 18:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_pit.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_pit.png"), QIcon::Disabled);
            break;
        case 19:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/glassworks.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/glassworks.png"), QIcon::Disabled);
            break;
        case 20:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/press.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/press.png"), QIcon::Disabled);
            break;
        case 21:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/guard_tower.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/guard_tower.png"), QIcon::Disabled);
            break;
        case 22:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/workshop.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/workshop.png"), QIcon::Disabled);
            break;
        case 23:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/apothecary.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/apothecary.png"), QIcon::Disabled);
            break;
        case 24:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_reserve.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_reserve.png"), QIcon::Disabled);
            break;
        case 25:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_reserve.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_reserve.png"), QIcon::Disabled);
            break;
        case 26:
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/wood_reserve.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/wood_reserve.png"), QIcon::Disabled);
            break;
        case 27:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/stable.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/stable.png"), QIcon::Disabled);
            break;
        case 28:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/garrison.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/garrison.png"), QIcon::Disabled);
            break;
        case 29:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/palisade.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/palisade.png"), QIcon::Disabled);
            break;
        case 30:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/scriptorium.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/scriptorium.png"), QIcon::Disabled);
            break;
        case 31:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/pharmacist.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/pharmacist.png"), QIcon::Disabled);
            break;
        case 32:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/theater.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/theater.png"), QIcon::Disabled);
            break;
        case 33:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/altar.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/altar.png"), QIcon::Disabled);
            break;
        case 34:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/baths.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/baths.png"), QIcon::Disabled);
            break;
        case 35:
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/tavern.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/With_Chain_Symbol/tavern.png"), QIcon::Disabled);
            break;
        case 36:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/sawmill.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/sawmill.png"), QIcon::Disabled);
            break;
        case 37:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/brickyard.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/brickyard.png"), QIcon::Disabled);
            break;
        case 38:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/shelf_quarry.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/shelf_quarry.png"), QIcon::Disabled);
            break;
        case 39:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/glassblower.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/glassblower.png"), QIcon::Disabled);
            break;
        case 40:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/drying_room.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/drying_room.png"), QIcon::Disabled);
            break;
        case 41:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/walls.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/walls.png"), QIcon::Disabled);
            break;
        case 42:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/forum.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/forum.png"), QIcon::Disabled);
            break;
        case 43:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/caravansery.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/caravansery.png"), QIcon::Disabled);
            break;
        case 44:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/customs_house.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/customs_house.png"), QIcon::Disabled);
            break;
        case 45:
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/courthouse.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/courthouse.png"), QIcon::Disabled);
            break;
        case 46:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/horse_breeders.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/horse_breeders.png"), QIcon::Disabled);
            break;
        case 47:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/barracks.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/barracks.png"), QIcon::Disabled);
            break;
        case 48:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/archery_range.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/archery_range.png"), QIcon::Disabled);
            break;
        case 49:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/parade_ground.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/parade_ground.png"), QIcon::Disabled);
            break;
        case 50:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/library.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/library.png"), QIcon::Disabled);
            break;
        case 51:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/dispensary.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/dispensary.png"), QIcon::Disabled);
            break;
        case 52:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/school.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/school.png"), QIcon::Disabled);
            break;
        case 53:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/laboratory.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/laboratory.png"), QIcon::Disabled);
            break;
        case 54:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/statue.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/statue.png"), QIcon::Disabled);
            break;
        case 55:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/temple.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/temple.png"), QIcon::Disabled);
            break;
        case 56:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/aqueduct.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/aqueduct.png"), QIcon::Disabled);
            break;
        case 57:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/rostrum.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/rostrum.png"), QIcon::Disabled);
            break;
        case 58:
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/brewery.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/With_Chain_Symbol/brewery.png"), QIcon::Disabled);
            break;
        case 59:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/arsenal.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/arsenal.png"), QIcon::Disabled);
            break;
        case 60:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/pretorium.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/pretorium.png"), QIcon::Disabled);
            break;
        case 61:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/academy.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/academy.png"), QIcon::Disabled);
            break;
        case 62:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/study.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/study.png"), QIcon::Disabled);
            break;
        case 63:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/chamber_of_commerce.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/chamber_of_commerce.png"), QIcon::Disabled);
            break;
        case 64:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/port.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/port.png"), QIcon::Disabled);
            break;
        case 65:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/armory.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/armory.png"), QIcon::Disabled);
            break;
        case 66:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/palace.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/palace.png"), QIcon::Disabled);
            break;
        case 67:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/town_hall.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/town_hall.png"), QIcon::Disabled);
            break;
        case 68:
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/obelisk.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/obelisk.png"), QIcon::Disabled);
            break;
        case 69:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/fortifications.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/fortifications.png"), QIcon::Disabled);
            break;
        case 70:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/siege_workshop.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/siege_workshop.png"), QIcon::Disabled);
            break;
        case 71:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/circus.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/circus.png"), QIcon::Disabled);
            break;
        case 72:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/university.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/university.png"), QIcon::Disabled);
            break;
        case 73:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/observatory.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/observatory.png"), QIcon::Disabled);
            break;
        case 74:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/gardens.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/gardens.png"), QIcon::Disabled);
            break;
        case 75:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/pantheon.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/pantheon.png"), QIcon::Disabled);
            break;
        case 76:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/senate.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/senate.png"), QIcon::Disabled);
            break;
        case 77:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/lighthouse.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/lighthouse.png"), QIcon::Disabled);
            break;
        case 78:
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/arena.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/With_Chain_Symbol/arena.png"), QIcon::Disabled);
            break;
        case 79:
            icon.addPixmap(QPixmap("icons/Guild/merchants_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/merchants_guild.png"), QIcon::Disabled);
            break;
        case 80:
            icon.addPixmap(QPixmap("icons/Guild/shipowners_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/shipowners_guild.png"), QIcon::Disabled);
            break;
        case 81:
            icon.addPixmap(QPixmap("icons/Guild/builders_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/builders_guild.png"), QIcon::Disabled);
            break;
        case 82:
            icon.addPixmap(QPixmap("icons/Guild/magistrates_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/magistrates_guild.png"), QIcon::Disabled);
            break;
        case 83:
            icon.addPixmap(QPixmap("icons/Guild/scientists_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/scientists_guild.png"), QIcon::Disabled);
            break;
        case 84:
            icon.addPixmap(QPixmap("icons/Guild/moneylenders_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/moneylenders_guild.png"), QIcon::Disabled);
            break;
        case 85:
            icon.addPixmap(QPixmap("icons/Guild/tacticians_guild.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/tacticians_guild.png"), QIcon::Disabled);
            break;
        default:
            break;
        }
    }
    else
    {
        if ((13 <= id) && (id <= 35))
        {
            icon.addPixmap(QPixmap("icons/Building/Age_1/deck_age_1.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_1/deck_age_1.png"), QIcon::Disabled);
        }
        else if ((36 <= id) && (id <= 58))
        {
            icon.addPixmap(QPixmap("icons/Building/Age_2/deck_age_2.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_2/deck_age_2.png"), QIcon::Disabled);
        }
        else if ((59 <= id) && (id <= 78))
        {
            icon.addPixmap(QPixmap("icons/Building/Age_3/deck_age_3.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Building/Age_3/deck_age_3.png"), QIcon::Disabled);
        }
        else if ((79 <= id) && (id <= 85))
        {
            icon.addPixmap(QPixmap("icons/Guild/deck_guilds.png"), QIcon::Normal);
            icon.addPixmap(QPixmap("icons/Guild/deck_guilds.png"), QIcon::Disabled);
        }
    }
    setIcon(icon);
}

const bool VBuilding_Unpurchased::getFaceFlag() const
{
    return faceFlag;
}

const bool VBuilding_Unpurchased::getSelectableFlag() const
{
    return selectableFlag;
}
const bool VBuilding_Unpurchased::getConstructionState() const
{
    return constructionState;
}

const bool VBuilding_Unpurchased::getDiscardFlag() const
{
    return discardFlag;
}

void VBuilding_Unpurchased::setFaceFlag(const bool flag)
{
    faceFlag = flag;
    set_BuildingIcon();
}

void VBuilding_Unpurchased::setSelectableFlag(const bool flag)
{
    selectableFlag = flag;
    setEnabled(flag);
}

void VBuilding_Unpurchased::setConstructionState(const bool flag)
{
    constructionState = flag;
}

void VBuilding_Unpurchased::setDiscardFlag(const bool flag)
{
    discardFlag = flag;
}

void VBuilding_Unpurchased::enterEvent(QEnterEvent* event)
{
    if (selectableFlag && !constructionState)
    {
        setCursor(Qt::PointingHandCursor);
        QPushButton::enterEvent(event);
    }
}

void VBuilding_Unpurchased::leaveEvent(QEvent* event)
{
    unsetCursor();
    QPushButton::leaveEvent(event);
}

void VBuilding_Unpurchased::chosenByPlayer()
{
    emit showDetails(this);
}

void VBuilding_Unpurchased::handleClicked()
{
    bool hasPlayedFlag = GameController::getInstance().getHasPlayed();
    if ((!faceFlag) && selectableFlag) { setFaceFlag(true); }
    else if (faceFlag && selectableFlag && !hasPlayedFlag) { emit showDetails(this); }
    else if (discardFlag) { emit showDetails(this); }
    else if (hasPlayedFlag) { emit cannotBeChoosenByPlayer("Vous l'avez déjà fait dans ce tour…"); }
}

void VBuilding_Unpurchased::handlePurchase()
{
    if (faceFlag && !discardFlag)
    {
        GameController::getInstance().setHasPlayed(true);
        selectableFlag = false;
        constructionState = true;
        hide();
        emit isConstructed(building);
    }
}

void VBuilding_Unpurchased::handleDiscardedPurchase()
{
    //////if (!constructionState && discardFlag)
    //////{
    //////    qDebug() << "???????????????????????????????";
    //////    selectableFlag = false;
    //////    constructionState = true;
    //////    hide();
    //////    emit isConstructed(building);
    //////}
    selectableFlag = false;
    constructionState = true;
    hide();
    emit isConstructed(building);
}

void VBuilding_Unpurchased::handleDiscard()
{
    if (faceFlag && !discardFlag)
    {
        GameController::getInstance().setHasPlayed(true);
        selectableFlag = false;
        constructionState = false;
        discardFlag = true;
        hide();
        emit isDiscarded(building);
    }
}

void VBuilding_Unpurchased::handleWonderConstruction()
{
    if (faceFlag && !discardFlag)
    {
        GameController::getInstance().setHasPlayed(true);
        selectableFlag = false;
        constructionState = true;
        hide();
        emit isUsedByWonder(building);
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VBuilding_Purchased::VBuilding_Purchased(QWidget* parent, Card* c) : VBuilding(parent, c)
{
    set_BuildingIcon();
    setStyleSheet
    (
        "QPushButton {"
        "   border: 0px;"
        "   background-color: rgba(0, 0, 0, 0); }"
    );
    connect(this, &QPushButton::clicked, this, &VBuilding_Purchased::chosenByPlayer);
}

void VBuilding_Purchased::set_BuildingIcon()
{
    switch (building->getID())
    {
    case 13:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/lumber_yard.png")));
        break;
    case 14:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/logging_camp.png")));
        break;
    case 15:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pool.png")));
        break;
    case 16:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_pit.png")));
        break;
    case 17:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/quarry.png")));
        break;
    case 18:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_pit.png")));
        break;
    case 19:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/glassworks.png")));
        break;
    case 20:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/press.png")));
        break;
    case 21:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/guard_tower.png")));
        break;
    case 22:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/workshop.png")));
        break;
    case 23:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/apothecary.png")));
        break;
    case 24:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/stone_reserve.png")));
        break;
    case 25:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/clay_reserve.png")));
        break;
    case 26:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/Without_Chain_Symbol/wood_reserve.png")));
        break;
    case 27:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/stable.png")));
        break;
    case 28:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/garrison.png")));
        break;
    case 29:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/palisade.png")));
        break;
    case 30:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/scriptorium.png")));
        break;
    case 31:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/pharmacist.png")));
        break;
    case 32:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/theater.png")));
        break;
    case 33:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/altar.png")));
        break;
    case 34:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/baths.png")));
        break;
    case 35:
        setIcon(QIcon(QPixmap("icons/Building/Age_1/With_Chain_Symbol/tavern.png")));
        break;
    case 36:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/sawmill.png")));
        break;
    case 37:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/brickyard.png")));
        break;
    case 38:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/shelf_quarry.png")));
        break;
    case 39:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/glassblower.png")));
        break;
    case 40:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/drying_room.png")));
        break;
    case 41:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/walls.png")));
        break;
    case 42:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/forum.png")));
        break;
    case 43:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/caravansery.png")));
        break;
    case 44:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/customs_house.png")));
        break;
    case 45:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/Without_Chain_Symbol/courthouse.png")));
        break;
    case 46:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/horse_breeders.png")));
        break;
    case 47:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/barracks.png")));
        break;
    case 48:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/archery_range.png")));
        break;
    case 49:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/parade_ground.png")));
        break;
    case 50:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/library.png")));
        break;
    case 51:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/dispensary.png")));
        break;
    case 52:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/school.png")));
        break;
    case 53:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/laboratory.png")));
        break;
    case 54:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/statue.png")));
        break;
    case 55:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/temple.png")));
        break;
    case 56:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/aqueduct.png")));
        break;
    case 57:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/rostrum.png")));
        break;
    case 58:
        setIcon(QIcon(QPixmap("icons/Building/Age_2/With_Chain_Symbol/brewery.png")));
        break;
    case 59:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/arsenal.png")));
        break;
    case 60:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/pretorium.png")));
        break;
    case 61:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/academy.png")));
        break;
    case 62:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/study.png")));
        break;
    case 63:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/chamber_of_commerce.png")));
        break;
    case 64:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/port.png")));
        break;
    case 65:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/armory.png")));
        break;
    case 66:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/palace.png")));
        break;
    case 67:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/town_hall.png")));
        break;
    case 68:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/Without_Chain_Symbol/obelisk.png")));
        break;
    case 69:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/fortifications.png")));
        break;
    case 70:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/siege_workshop.png")));
        break;
    case 71:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/circus.png")));
        break;
    case 72:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/university.png")));
        break;
    case 73:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/observatory.png")));
        break;
    case 74:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/gardens.png")));
        break;
    case 75:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/pantheon.png")));
        break;
    case 76:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/senate.png")));
        break;
    case 77:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/lighthouse.png")));
        break;
    case 78:
        setIcon(QIcon(QPixmap("icons/Building/Age_3/With_Chain_Symbol/arena.png")));
        break;
    case 79:
        setIcon(QIcon(QPixmap("icons/Guild/merchants_guild.png")));
        break;
    case 80:
        setIcon(QIcon(QPixmap("icons/Guild/shipowners_guild.png")));
        break;
    case 81:
        setIcon(QIcon(QPixmap("icons/Guild/builders_guild.png")));
        break;
    case 82:
        setIcon(QIcon(QPixmap("icons/Guild/magistrates_guild.png")));
        break;
    case 83:
        setIcon(QIcon(QPixmap("icons/Guild/scientists_guild.png")));
        break;
    case 84:
        setIcon(QIcon(QPixmap("icons/Guild/moneylenders_guild.png")));
        break;
    case 85:
        setIcon(QIcon(QPixmap("icons/Guild/tacticians_guild.png")));
        break;
    default:
        break;
    }
}

void VBuilding_Purchased::chosenByPlayer()
{
    emit showDetails(this);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VWonder::VWonder(QWidget* parent, Card* wdr) : QPushButton(parent), wonder(wdr)
{
    setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
    set_WonderIcon();
    setConstructionState(wdr->getConstructedFlag());
    connect(this, &QPushButton::clicked, this, &VWonder::chosenByPlayer);
}

void VWonder::set_WonderIcon()
{
    QIcon icon;
    switch (wonder->getID())
    {
    case 1:
        icon.addPixmap(QPixmap("icons/Wonder/circus_maximus.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/circus_maximus.png"), QIcon::Disabled);
        break;
    case 2:
        icon.addPixmap(QPixmap("icons/Wonder/the_colossus.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_colossus.png"), QIcon::Disabled);
        break;
    case 3:
        icon.addPixmap(QPixmap("icons/Wonder/the_great_lighthouse.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_great_lighthouse.png"), QIcon::Disabled);
        break;
    case 4:
        icon.addPixmap(QPixmap("icons/Wonder/the_hanging_gardens.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_hanging_gardens.png"), QIcon::Disabled);
        break;
    case 5:
        icon.addPixmap(QPixmap("icons/Wonder/the_great_library.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_great_library.png"), QIcon::Disabled);
        break;
    case 6:
        icon.addPixmap(QPixmap("icons/Wonder/the_mausoleum.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_mausoleum.png"), QIcon::Disabled);
        break;
    case 7:
        icon.addPixmap(QPixmap("icons/Wonder/piraeus.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/piraeus.png"), QIcon::Disabled);
        break;
    case 8:
        icon.addPixmap(QPixmap("icons/Wonder/the_pyramids.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_pyramids.png"), QIcon::Disabled);
        break;
    case 9:
        icon.addPixmap(QPixmap("icons/Wonder/the_sphinx.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_sphinx.png"), QIcon::Disabled);
        break;
    case 10:
        icon.addPixmap(QPixmap("icons/Wonder/the_statue_of_zeus.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_statue_of_zeus.png"), QIcon::Disabled);
        break;
    case 11:
        icon.addPixmap(QPixmap("icons/Wonder/the_temple_of_artemis.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_temple_of_artemis.png"), QIcon::Disabled);
        break;
    case 12:
        icon.addPixmap(QPixmap("icons/Wonder/the_appian_way.png"), QIcon::Normal);
        icon.addPixmap(QPixmap("icons/Wonder/the_appian_way.png"), QIcon::Disabled);
        break;
    default:
        break;
    }
    setIcon(icon);
}

Card* VWonder::getWonder()
{
    return wonder;
}

const bool VWonder::getConstructionState() const
{
    return constructionState;
}

void VWonder::setConstructionState(const bool flag)
{
    constructionState = flag;
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    if (flag) { effect->setOpacity(1); }
    else { effect->setOpacity(0.25); }
    setGraphicsEffect(effect);
}

void VWonder::setVWonder(Card* wdr)
{
    setConstructionState(wdr->getConstructedFlag());
}

void VWonder::enterEvent(QEnterEvent* event)
{
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void VWonder::leaveEvent(QEvent* event)
{
    unsetCursor();
    QPushButton::leaveEvent(event);
}

void VWonder::handleConstruction()
{
    emit isConstructed(this);
}

void VWonder::chosenByPlayer()
{
    emit showDetails(this);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/