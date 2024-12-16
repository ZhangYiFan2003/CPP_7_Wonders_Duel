#include "VGameElements.h"


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Pop_Up_Notification::Pop_Up_Notification(QWidget* parent, QString msg) : QWidget(parent)
{
    setFixedSize(parent->width() / 2, parent->height() / 15);

    messageLabel = new QLabel;
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setScaledContents(true);
    messageLabel->setFixedHeight(parent->height() / 15);
    messageLabel->setText(msg);
    messageLabel->setStyleSheet
    (
        "QLabel { background-color: rgba(0, 32, 40, 128);"
        "color: white;"
        "font-family: Arial;"
        "font-size: 16px;"
        "font-weight: bold; }"
    );

    pop_up_NotificationLayout = new QVBoxLayout(this);
    pop_up_NotificationLayout->setAlignment(Qt::AlignCenter);
    pop_up_NotificationLayout->setContentsMargins(10, 0, 10, 0);
    pop_up_NotificationLayout->addWidget(messageLabel);

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true); // Assure que la minuterie ne se déclenche qu'une seule fois
    connect(timer, &QTimer::timeout, this, &Pop_Up_Notification::startFadeOut);
    timer->start(1500);
}

void Pop_Up_Notification::startFadeOut()
{
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
    messageLabel->setGraphicsEffect(opacityEffect);
    QPropertyAnimation* animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(1500);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    connect(animation, &QPropertyAnimation::finished, this, &QWidget::close);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VJeton::VJeton(QWidget* parent, Jeton* pt, GameController* gc) : QPushButton(parent), jeton(pt), selectableFlag(true), gameController(gc)
{
    connect(this, &QPushButton::clicked, this, &VJeton::handleClicked);

    switch (pt->getID())
    {
    case 0:
        setIcon(QIcon(QPixmap("icons/Progress_Token/deck_tokens.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 1:
        setIcon(QIcon(QPixmap("icons/Progress_Token/agriculture.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 2:
        setIcon(QIcon(QPixmap("icons/Progress_Token/architecture.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 3:
        setIcon(QIcon(QPixmap("icons/Progress_Token/economy.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 4:
        setIcon(QIcon(QPixmap("icons/Progress_Token/law.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 5:
        setIcon(QIcon(QPixmap("icons/Progress_Token/masonry.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 6:
        setIcon(QIcon(QPixmap("icons/Progress_Token/mathematics.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 7:
        setIcon(QIcon(QPixmap("icons/Progress_Token/philosophy.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 8:
        setIcon(QIcon(QPixmap("icons/Progress_Token/strategy.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 9:
        setIcon(QIcon(QPixmap("icons/Progress_Token/theology.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    case 10:
        setIcon(QIcon(QPixmap("icons/Progress_Token/urbanism.png")));
        setStyleSheet("QPushButton { background-color: rgba(0, 0, 0, 0); border: none; }");
        break;
    default:
        break;
    }
}

void VJeton::enterEvent(QEnterEvent* event)
{
    if (selectableFlag && !isSelected)
    {
        setCursor(Qt::PointingHandCursor);
        QPushButton::enterEvent(event);
    }
}

void VJeton::leaveEvent(QEvent* event)
{
    unsetCursor();
    QPushButton::leaveEvent(event);
}

void VJeton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QColor color(0, 0, 0, 0);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect());
    QPushButton::paintEvent(event);
}

void VJeton::setFixedDiameter(int diameter)
{
    QPushButton::setFixedSize(diameter, diameter);
    QRegion region(rect(), QRegion::Ellipse);
    setMask(region);
}

void VJeton::handleClicked()
{
    qDebug() << "jeton->getDiscardedFlag() = " << jeton->getDiscardedFlag();
    if (jeton->getDiscardedFlag()) { emit sendProgressTokenInfo(jeton); }
    else
    {
        Joueur* currentPlayer = gameController->getCurrentPlayer();
        ptk_OK_Flag = gameController->takeJeton(currentPlayer, jeton);

        if (ptk_OK_Flag == '1')
        {
            setEnabled(false);  // Désactive le bouton
            selectableFlag = false;
            isSelected = true;
            setIcon(QIcon());
            emit istaken();
        }
        else if (ptk_OK_Flag == '0')
        {
            QWidget* widget = this->parentWidget()->parentWidget();
            Pop_Up_Notification* message = new Pop_Up_Notification(widget, "Vous n'avez pas de paire de symboles scientifiques identiques…");
            int x = widget->geometry().x() + (widget->geometry().width() - message->width()) / 2;
            int y = widget->geometry().height() - message->height() - 10;
            message->move(x, y);
            message->show();
        }
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void VConflictPawn::setVisibility(bool visable)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
    if (visable)
    {
        effect->setOpacity(1);
        setGraphicsEffect(effect);
    }
    else
    {
        effect->setOpacity(0);
        setGraphicsEffect(effect);
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void VLootingToken::setVisibility(bool visable)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
    if (visable)
    {
        effect->setOpacity(1);
        setGraphicsEffect(effect);
    }
    else
    {
        effect->setOpacity(0);
        setGraphicsEffect(effect);
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VSideBoard::VSideBoard(GameController* gc) : JetonSize(0), conflictPawnWidth(0), lootingTokenWidth(0), conflictPawnPosition(9), gameController(gc)
{
    init_Jetons();
    init_ConflictPawns();
    init_LootingTokens();
    init_JetonLayout();
    init_ConflictPawnLayout();
    init_LootingTokenLayout();
    init_SideBoardLayout();
    sideBoardGeometry.resize(4);
}

void VSideBoard::init_Jetons()
{
    std::array<Jeton*, 5> pt = gameController->getSideBoard()->getJetonsDeck();
    for (int i = 0; i < 5; i += 1)
    {
        VJeton* Jeton = new VJeton(nullptr, pt[i], gameController);
        jetons.append(Jeton);
    }
}

void VSideBoard::init_ConflictPawns()
{
    for (int i = 0; i < 19; i += 1)
    {
        VConflictPawn* conflictPawn = new VConflictPawn;
        conflictPawn->setPixmap(QPixmap("icons/Others/conflict_pawn.png"));
        conflictPawn->setVisibility(false);
        conflictPawn->setAlignment(Qt::AlignCenter);
        conflictPawn->setScaledContents(true);
        conflictPawns.append(conflictPawn);
    }
}

void VSideBoard::init_LootingTokens()
{
    lootingPlaceholder = new QLabel;
    for (int i = 0; i < 4; i += 1)
    {
        VLootingToken* lootingToken = new VLootingToken;
        lootingToken->setAlignment(Qt::AlignCenter);
        lootingToken->setScaledContents(true);
        lootingTokens.append(lootingToken);
    }
    lootingTokens[0]->setPixmap(QPixmap("icons/Others/looting_1.png"));
    lootingTokens[1]->setPixmap(QPixmap("icons/Others/looting_2.png"));
    lootingTokens[2]->setPixmap(QPixmap("icons/Others/looting_3.png"));
    lootingTokens[3]->setPixmap(QPixmap("icons/Others/looting_4.png"));
}

void VSideBoard::init_JetonLayout()
{
    JetonLayout = new QHBoxLayout;
    JetonLayout->setAlignment(Qt::AlignCenter);
    for (auto it = jetons.begin(); it != jetons.end(); ++it) { JetonLayout->addWidget((*it)); }
}

void VSideBoard::init_ConflictPawnLayout()
{
    conflictPawnLayout = new QHBoxLayout;
    conflictPawnLayout->setAlignment(Qt::AlignCenter);
    for (auto it = conflictPawns.begin(); it != conflictPawns.end(); ++it) { conflictPawnLayout->addWidget((*it)); }
    conflictPawns[9]->setVisibility(true);
}

void VSideBoard::init_LootingTokenLayout()
{
    lootingTokenLayout = new QHBoxLayout;
    lootingTokenLayout->setAlignment(Qt::AlignCenter);
    lootingTokenLayout->addWidget(lootingTokens[0]);
    lootingTokenLayout->addWidget(lootingTokens[1]);
    lootingTokenLayout->addWidget(lootingPlaceholder);
    lootingTokenLayout->addWidget(lootingTokens[2]);
    lootingTokenLayout->addWidget(lootingTokens[3]);
}

void VSideBoard::init_SideBoardLayout()
{
    sideBoardLayout = new QVBoxLayout;
    sideBoardLayout->addLayout(JetonLayout);
    sideBoardLayout->addLayout(conflictPawnLayout);
    sideBoardLayout->addLayout(lootingTokenLayout);
    sideBoardLayout->setSpacing(0);
    setLayout(sideBoardLayout);
}

const QVector<VJeton*>& VSideBoard::getJetons() const
{
    return jetons;
}

void VSideBoard::setConflictPawn(int mpDiff_P1P2)
{
    int index = mpDiff_P1P2 + 9;
    if (index < 0) { index = 0; }
    else if (index > 18) { index = 18; }
    conflictPawns[conflictPawnPosition]->setVisibility(false);
    conflictPawns[index]->setVisibility(true);
    conflictPawnPosition = index;
}

void VSideBoard::moveConflictPawn(char direction, int step)
{
    if ((conflictPawnPosition != 0) && (conflictPawnPosition != 18) && (step != 0))
    {
        int index = conflictPawnPosition;
        switch (direction)
        {
        case 'L':
            index -= step;
            if (index < 0) { index = 0; }
            else if (index > 18) { index = 18; }
            break;
        case 'R':
            index += step;
            if (index < 0) { index = 0; }
            else if (index > 18) { index = 18; }
            break;
        default:
            break;
        }
        conflictPawns[conflictPawnPosition]->setVisibility(false);
        conflictPawns[index]->setVisibility(true);
        conflictPawnPosition = index;
    }
}

void VSideBoard::loseLootingToken(unsigned int index)
{
    if (!lootingTokens[index]->getLossFlag())
    {
        lootingTokens[index]->setVisibility(false);
        lootingTokens[index]->setLossFlag(true);
    }
}

void VSideBoard::calculateSideBoardGeometry()
{
    QRect geometry = this->geometry();
    sideBoardGeometry[0] = geometry.topLeft();
    sideBoardGeometry[1] = geometry.topRight();
    sideBoardGeometry[2] = geometry.bottomLeft();
    sideBoardGeometry[3] = geometry.bottomRight();
}

void VSideBoard::calculateJetonSize()
{
    int diff = sideBoardGeometry[1].x() - sideBoardGeometry[0].x();
    JetonSize = diff / 12;
}

void VSideBoard::calculateConflictPawnWidth()
{
    int diff = sideBoardGeometry[1].x() - sideBoardGeometry[0].x();
    conflictPawnWidth = diff / 40;
}

void VSideBoard::calculateLootingWidth()
{
    int diff = sideBoardGeometry[1].x() - sideBoardGeometry[0].x();
    lootingTokenWidth = diff / 11;
}

void VSideBoard::updateSideBoard()
{
    calculateSideBoardGeometry();
    calculateJetonSize();
    calculateConflictPawnWidth();
    calculateLootingWidth();

    sideBoardLayout->setContentsMargins(0, 0, 0, lootingTokenWidth / 6);
    JetonLayout->setContentsMargins(0, JetonSize / 10, 0, 0);
    JetonLayout->setSpacing(JetonSize / 8);
    conflictPawnLayout->setContentsMargins(0, conflictPawnWidth / 1.25, 0, 0);
    conflictPawnLayout->setSpacing(8 + conflictPawnWidth / 2.4); ///// ¨¤ tester
    lootingTokenLayout->setContentsMargins(0, 0, 0, 0);
    lootingTokenLayout->setSpacing(lootingTokenWidth / 2.25);

    for (unsigned int i = 0; i < 5; i += 1)
    {
        jetons[i]->setFixedDiameter(JetonSize);
        jetons[i]->setIconSize(QSize(JetonSize, JetonSize));
    }
    for (unsigned int i = 0; i < 19; i += 1)
    {
        conflictPawns[i]->setFixedSize(conflictPawnWidth, conflictPawnWidth * 3);
    }
    lootingTokens[0]->setFixedSize(lootingTokenWidth * 1.225, lootingTokenWidth * 1.225 / 2.3);
    lootingTokens[1]->setFixedSize(lootingTokenWidth, lootingTokenWidth / 2.3);
    lootingPlaceholder->setFixedWidth(lootingTokenWidth * 1.95);
    lootingTokens[2]->setFixedSize(lootingTokenWidth, lootingTokenWidth / 2.3);
    lootingTokens[3]->setFixedSize(lootingTokenWidth * 1.225, lootingTokenWidth * 1.225 / 2.3);
}

void VSideBoard::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updateSideBoard();
}

void VSideBoard::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap pixmap("icons/Others/side_board");
    if (!pixmap.isNull()) {
        QPixmap scaledPixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (width() - scaledPixmap.width()) / 2;
        int y = (height() - scaledPixmap.height()) / 2;
        painter.drawPixmap(x, y, scaledPixmap);
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VPlayerInfo::VPlayerInfo(char plyrNumber, Joueur* plyr) : nb_resource(5, 0), nb_scientificSymbol(7, 0), nb_chainSymbol(17, 0), player(plyr)
{
    init_PlayerName(plyrNumber);
    init_CurrentPlayerBar();
    init_WonderEffectIcons();
    init_VictoryPointIcon();
    init_MilitaryPowerIcon();
    init_ResourcesIcons();
    init_CoinsIcon();
    init_VictoryPointLabel();
    init_MilitaryPowerLabel();
    init_ResourcesLabels();
    init_CoinsLabel();
    init_ScientificSymbolIcons();
    init_ChainSymbolIcons();
    init_WonderEffectLayout(plyrNumber);
    init_TopLayout(plyrNumber);
    init_BottomLayout(plyrNumber);
    init_ScientificSymbolLayout(plyrNumber);
    init_ChainSymbolLayout(plyrNumber);
    init_PlayerInfoLayout();
    setPlayerInfo();
    playerInfoGeometry.resize(4);
}

void VPlayerInfo::init_PlayerName(char plyrNumber)
{

    playerName = new QLabel(QString::fromStdString(player->getName()));
    playerName->setAlignment(Qt::AlignVCenter);
    playerName->setScaledContents(true);
    playerName->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(57, 24, 23); background-color: rgba(0, 0, 0, 0);");
    if (plyrNumber == '1') { playerName->setAlignment(Qt::AlignLeft); }
    else if (plyrNumber == '2') { playerName->setAlignment(Qt::AlignRight); }
}


void VPlayerInfo::init_CurrentPlayerBar()
{
    currentPlayerBar = new QWidget;
    currentPlayerBar->setStyleSheet("background-color: rgba(57, 24, 23, 95);");
}

void VPlayerInfo::init_WonderEffectIcons()
{
    for (int i = 0; i < 2; i += 1)
    {
        QLabel* icon = new QLabel;
        icon->setAlignment(Qt::AlignCenter);
        icon->setScaledContents(true);
        icon->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
        wonderEffectIcons.append(icon);
    }
    wonderEffectIcons[0]->setPixmap(QPixmap("icons/Wonder_Effect/Wonder_Effect_01.png"));
    wonderEffectIcons[1]->setPixmap(QPixmap("icons/Wonder_Effect/Wonder_Effect_02.png"));
}

void VPlayerInfo::init_VictoryPointIcon()
{
    victoryPointIcon = new QLabel;
    victoryPointIcon->setScaledContents(true);
    victoryPointIcon->setAlignment(Qt::AlignCenter);
    victoryPointIcon->setPixmap(QPixmap("icons/Others/victory_point.png"));
}

void VPlayerInfo::init_MilitaryPowerIcon()
{
    militaryPowerIcon = new QLabel;
    militaryPowerIcon->setScaledContents(true);
    militaryPowerIcon->setAlignment(Qt::AlignCenter);
    militaryPowerIcon->setPixmap(QPixmap("icons/Others/military_power.png"));
}

void VPlayerInfo::init_ResourcesIcons()
{
    for (int i = 0; i < 5; i += 1)
    {
        QLabel* icon = new QLabel;
        icon->setAlignment(Qt::AlignCenter);
        icon->setScaledContents(true);
        resourcesIcons.append(icon);
    }
    resourcesIcons[0]->setPixmap(QPixmap("icons/Resource_Icon/clay.png"));
    resourcesIcons[1]->setPixmap(QPixmap("icons/Resource_Icon/wood.png"));
    resourcesIcons[2]->setPixmap(QPixmap("icons/Resource_Icon/stone.png"));
    resourcesIcons[3]->setPixmap(QPixmap("icons/Resource_Icon/glass.png"));
    resourcesIcons[4]->setPixmap(QPixmap("icons/Resource_Icon/papyrus.png"));
}

void VPlayerInfo::init_CoinsIcon()
{
    coinsIcon = new QLabel;
    coinsIcon->setScaledContents(true);
    coinsIcon->setAlignment(Qt::AlignCenter);
    coinsIcon->setPixmap(QPixmap("icons/Others/coin.png"));
}

void VPlayerInfo::init_VictoryPointLabel()
{
    victoryPointLabel = new QLabel(QString::number(victoryPoint));
    victoryPointLabel->setStyleSheet("font-weight: bold; color: rgb(57, 24, 23);");
    victoryPointLabel->setAlignment(Qt::AlignCenter);
}

void VPlayerInfo::init_MilitaryPowerLabel()
{
    militaryPowerLabel = new QLabel(QString::number(militaryPower));
    militaryPowerLabel->setStyleSheet("font-weight: bold; color: rgb(57, 24, 23);");
    militaryPowerLabel->setAlignment(Qt::AlignCenter);
}

void VPlayerInfo::init_ResourcesLabels()
{
    for (unsigned int i = 0; i < 5; i += 1)
    {
        QLabel* label = new QLabel(QString::number(nb_resource[i]));
        label->setStyleSheet("font-weight: bold; color: rgb(57, 24, 23);");
        label->setAlignment(Qt::AlignCenter);
        resourcesLabels.append(label);
    }
}

void VPlayerInfo::init_CoinsLabel()
{
    coinsLabel = new QLabel(QString::number(coins));
    coinsLabel->setStyleSheet("font-weight: bold; color: rgb(57, 24, 23);");
    coinsLabel->setAlignment(Qt::AlignCenter);
}

void VPlayerInfo::init_ScientificSymbolIcons()
{
    for (int i = 0; i < 7; i += 1)
    {
        QLabel* icon = new QLabel;
        icon->setScaledContents(true);
        icon->setAlignment(Qt::AlignCenter);
        scientificSymbolIcons.append(icon);
    }
    scientificSymbolIcons[0]->setPixmap(QPixmap("icons/Scientific_Symbol/armillary_sphere.png"));
    scientificSymbolIcons[1]->setPixmap(QPixmap("icons/Scientific_Symbol/balance.png"));
    scientificSymbolIcons[2]->setPixmap(QPixmap("icons/Scientific_Symbol/sundial.png"));
    scientificSymbolIcons[3]->setPixmap(QPixmap("icons/Scientific_Symbol/mortar_and_pestle.png"));
    scientificSymbolIcons[4]->setPixmap(QPixmap("icons/Scientific_Symbol/plumb_bob.png"));
    scientificSymbolIcons[5]->setPixmap(QPixmap("icons/Scientific_Symbol/quill.png"));
    scientificSymbolIcons[6]->setPixmap(QPixmap("icons/Scientific_Symbol/wheel.png"));
    for (int i = 0; i < 7; i += 1)
    {
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
        effect->setOpacity(0.25);
        scientificSymbolIcons[i]->setGraphicsEffect(effect);
    }
}

void VPlayerInfo::init_ChainSymbolIcons()
{
    for (unsigned int i = 0; i < 17; i += 1)
    {
        QLabel* icon = new QLabel;
        icon->setScaledContents(true);
        icon->setAlignment(Qt::AlignCenter);
        chainSymbolIcons.append(icon);
    }
    chainSymbolIcons[0]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_01.png"));
    chainSymbolIcons[1]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_02.png"));
    chainSymbolIcons[2]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_03.png"));
    chainSymbolIcons[3]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_04.png"));
    chainSymbolIcons[4]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_05.png"));
    chainSymbolIcons[5]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_06.png"));
    chainSymbolIcons[6]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_07.png"));
    chainSymbolIcons[7]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_08.png"));
    chainSymbolIcons[8]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_09.png"));
    chainSymbolIcons[9]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_10.png"));
    chainSymbolIcons[10]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_11.png"));
    chainSymbolIcons[11]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_12.png"));
    chainSymbolIcons[12]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_13.png"));
    chainSymbolIcons[13]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_14.png"));
    chainSymbolIcons[14]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_15.png"));
    chainSymbolIcons[15]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_16.png"));
    chainSymbolIcons[16]->setPixmap(QPixmap("icons/Chain_Symbol/Chain_Symbol_17.png"));
    for (int i = 0; i < 17; i += 1)
    {
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
        effect->setOpacity(0.25);
        chainSymbolIcons[i]->setGraphicsEffect(effect);
    }
}

void VPlayerInfo::init_WonderEffectLayout(char plyrNumber)
{
    wonderEffectLayout = new QHBoxLayout;
    wonderEffectLayout->setAlignment(Qt::AlignCenter);

    ///////////////////////////////////////////////////////
    wonderEffectLayout->addWidget(wonderEffectIcons[0]);
    wonderEffectLayout->addWidget(wonderEffectIcons[1]);
    ///////////////////////////////////////////////////////
}

void VPlayerInfo::init_TopLayout(char plyrNumber)
{
    topLayout = new QHBoxLayout(currentPlayerBar);
    topLayout->setAlignment(Qt::AlignCenter);////////
    if (plyrNumber == '1') { topLayout->setDirection(QBoxLayout::LeftToRight); }
    else if (plyrNumber == '2') { topLayout->setDirection(QBoxLayout::RightToLeft); }
    topLayout->addWidget(playerName, 3);
    topLayout->addLayout(wonderEffectLayout, 2);
}

void VPlayerInfo::init_BottomLayout(char plyrNumber)
{
    bottomLayout = new QGridLayout;
    bottomLayout->setAlignment(Qt::AlignCenter);
    bottomLayout->setSpacing(5);
    if (plyrNumber == '1')
    {
        bottomLayout->addWidget(victoryPointIcon, 0, 0);
        bottomLayout->addWidget(militaryPowerIcon, 0, 1);
        bottomLayout->addWidget(resourcesIcons[0], 0, 2);
        bottomLayout->addWidget(resourcesIcons[1], 0, 3);
        bottomLayout->addWidget(resourcesIcons[2], 0, 4);
        bottomLayout->addWidget(resourcesIcons[3], 0, 5);
        bottomLayout->addWidget(resourcesIcons[4], 0, 6);
        bottomLayout->addWidget(coinsIcon, 0, 7);

        bottomLayout->addWidget(victoryPointLabel, 1, 0);
        bottomLayout->addWidget(militaryPowerLabel, 1, 1);
        bottomLayout->addWidget(resourcesLabels[0], 1, 2);
        bottomLayout->addWidget(resourcesLabels[1], 1, 3);
        bottomLayout->addWidget(resourcesLabels[2], 1, 4);
        bottomLayout->addWidget(resourcesLabels[3], 1, 5);
        bottomLayout->addWidget(resourcesLabels[4], 1, 6);
        bottomLayout->addWidget(coinsLabel, 1, 7);
    }
    else if (plyrNumber == '2')
    {
        bottomLayout->addWidget(coinsIcon, 0, 0);
        bottomLayout->addWidget(resourcesIcons[4], 0, 1);
        bottomLayout->addWidget(resourcesIcons[3], 0, 2);
        bottomLayout->addWidget(resourcesIcons[2], 0, 3);
        bottomLayout->addWidget(resourcesIcons[1], 0, 4);
        bottomLayout->addWidget(resourcesIcons[0], 0, 5);
        bottomLayout->addWidget(militaryPowerIcon, 0, 6);
        bottomLayout->addWidget(victoryPointIcon, 0, 7);

        bottomLayout->addWidget(coinsLabel, 1, 0);
        bottomLayout->addWidget(resourcesLabels[4], 1, 1);
        bottomLayout->addWidget(resourcesLabels[3], 1, 2);
        bottomLayout->addWidget(resourcesLabels[2], 1, 3);
        bottomLayout->addWidget(resourcesLabels[1], 1, 4);
        bottomLayout->addWidget(resourcesLabels[0], 1, 5);
        bottomLayout->addWidget(militaryPowerLabel, 1, 6);
        bottomLayout->addWidget(victoryPointLabel, 1, 7);
    }
}

void VPlayerInfo::init_ScientificSymbolLayout(char plyrNumber)
{
    scientificSymbolLayout = new QHBoxLayout;
    scientificSymbolLayout->setAlignment(Qt::AlignCenter);
    if (plyrNumber == '1'){ scientificSymbolLayout->setDirection(QBoxLayout::LeftToRight); }
    else if (plyrNumber == '2'){ scientificSymbolLayout->setDirection(QBoxLayout::RightToLeft); }
    for (auto it = scientificSymbolIcons.begin(); it != scientificSymbolIcons.end(); ++it) { scientificSymbolLayout->addWidget((*it)); }
}

void VPlayerInfo::init_ChainSymbolLayout(char plyrNumber)
{
    chainSymbolLayout = new QHBoxLayout;
    chainSymbolLayout->setAlignment(Qt::AlignCenter);
    if (plyrNumber == '1'){ chainSymbolLayout->setDirection(QBoxLayout::LeftToRight); }
    else if (plyrNumber == '2'){ chainSymbolLayout->setDirection(QBoxLayout::RightToLeft); }
    for (auto it = chainSymbolIcons.begin(); it != chainSymbolIcons.end(); ++it) { chainSymbolLayout->addWidget((*it)); }
}

void VPlayerInfo::init_PlayerInfoLayout()
{
    playerInfoLayout = new QVBoxLayout(this);
    playerInfoLayout->setAlignment(Qt::AlignCenter);
    playerInfoLayout->addWidget(currentPlayerBar);
    playerInfoLayout->addLayout(bottomLayout);
    playerInfoLayout->addLayout(scientificSymbolLayout);
    playerInfoLayout->addLayout(chainSymbolLayout);
}

void VPlayerInfo::setCurrentPlayerFlag(const bool flag)
{
    currentPlayerFlag = flag;
    if (flag) { currentPlayerBar->setStyleSheet("background-color: rgba(57, 24, 23, 95);"); }
    else { currentPlayerBar->setStyleSheet("background-color: rgba(0, 0, 0, 0);"); }
}

void VPlayerInfo::setCurrentPlayerFlag()
{
    currentPlayerFlag = player->getCurrentPlayerFlag();
    if (currentPlayerFlag) { currentPlayerBar->setStyleSheet("background-color: rgba(57, 24, 23, 95);"); }
    else { currentPlayerBar->setStyleSheet("background-color: rgba(0, 0, 0, 0);"); }
}

void VPlayerInfo::setVictoryPoint(const unsigned int nb)
{
    victoryPoint = nb;
    victoryPointLabel->setText(QString::number(nb));
}

void VPlayerInfo::setVictoryPoint()
{
    victoryPoint = player->getVicPoint();
    victoryPointLabel->setText(QString::number(victoryPoint));
}

void VPlayerInfo::setMilitaryPower(const unsigned int nb)
{
    militaryPower = nb;
    militaryPowerLabel->setText(QString::number(nb));
}

void VPlayerInfo::setMilitaryPower()
{
    militaryPower = player->getMilPower();
    militaryPowerLabel->setText(QString::number(militaryPower));
}

void VPlayerInfo::setResources(size_t index, const unsigned int nb)
{
    nb_resource[index] = nb;
    resourcesLabels[index]->setText(QString::number(nb));
}

void VPlayerInfo::setResources()
{
    std::map<Ressources, int> plyrsRsrs = player->getRessourceJoueur();
    std::map<Ressources, int>::iterator it;

    for (auto it = plyrsRsrs.begin(); it != plyrsRsrs.end(); ++it) {
        // Convertir l'énumération en int (index)
        int ressourceIndex = static_cast<int>(it->first);
        // Mettre à jour le tableau nb_resource
        nb_resource[ressourceIndex] = it->second;
        resourcesLabels[ressourceIndex]->setText(QString::number(it->second));
    }
}

void VPlayerInfo::setCoins(const unsigned int nb)
{
    coins = nb;
    coinsLabel->setText(QString::number(nb));
}

void VPlayerInfo::setCoins()
{
    coins = player->getCoins();
    coinsLabel->setText(QString::number(coins));
}

void VPlayerInfo::obtainScientificSymbol(unsigned int ssID)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1);
    switch (ssID)
    {
    case 0:
        if (nb_scientificSymbol[0] == 0) { scientificSymbolIcons[0]->setGraphicsEffect(effect); }
        nb_scientificSymbol[0] += 1;
        break;
    case 1:
        if (nb_scientificSymbol[1] == 0) { scientificSymbolIcons[1]->setGraphicsEffect(effect); }
        nb_scientificSymbol[1] += 1;
        break;
    case 2:
        if (nb_scientificSymbol[2] == 0) { scientificSymbolIcons[2]->setGraphicsEffect(effect); }
        nb_scientificSymbol[2] += 1;
        break;
    case 3:
        if (nb_scientificSymbol[3] == 0) { scientificSymbolIcons[3]->setGraphicsEffect(effect); }
        nb_scientificSymbol[3] += 1;
        break;
    case 4:
        if (nb_scientificSymbol[4] == 0) { scientificSymbolIcons[4]->setGraphicsEffect(effect); }
        nb_scientificSymbol[4] += 1;
        break;
    case 5:
        if (nb_scientificSymbol[5] == 0) { scientificSymbolIcons[5]->setGraphicsEffect(effect); }
        nb_scientificSymbol[5] += 1;
        break;
    case 6:
        if (nb_scientificSymbol[6] == 0) { scientificSymbolIcons[6]->setGraphicsEffect(effect); }
        nb_scientificSymbol[6] += 1;
        break;
    default:
        break;
    }
}

void VPlayerInfo::setScientificSymbols()
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1);

    std::vector<Symboles_scientifique> plyrsSS = player->getSsc();
    
    for (size_t i = 0; i < plyrsSS.size(); i += 1)
    {
        if (plyrsSS[i] != Symboles_scientifique::aucun) { scientificSymbolIcons[(int)plyrsSS[i]]->setGraphicsEffect(effect); }
        nb_scientificSymbol[i] = 1;
    }
}

void VPlayerInfo::obtainChainSymbol(unsigned int csID)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1);
    switch (csID)
    {
    case 0:
        if (nb_chainSymbol[0] == 0) { chainSymbolIcons[0]->setGraphicsEffect(effect); }
        nb_chainSymbol[0] += 1;
        break;
    case 1:
        if (nb_chainSymbol[1] == 0) { chainSymbolIcons[1]->setGraphicsEffect(effect); }
        nb_chainSymbol[1] += 1;
        break;
    case 2:
        if (nb_chainSymbol[2] == 0) { chainSymbolIcons[2]->setGraphicsEffect(effect); }
        nb_chainSymbol[2] += 1;
        break;
    case 3:
        if (nb_chainSymbol[3] == 0) { chainSymbolIcons[3]->setGraphicsEffect(effect); }
        nb_chainSymbol[3] += 1;
        break;
    case 4:
        if (nb_chainSymbol[4] == 0) { chainSymbolIcons[4]->setGraphicsEffect(effect); }
        nb_chainSymbol[4] += 1;
        break;
    case 5:
        if (nb_chainSymbol[5] == 0) { chainSymbolIcons[5]->setGraphicsEffect(effect); }
        nb_chainSymbol[5] += 1;
        break;
    case 6:
        if (nb_chainSymbol[6] == 0) { chainSymbolIcons[6]->setGraphicsEffect(effect); }
        nb_chainSymbol[6] += 1;
        break;
    case 7:
        if (nb_chainSymbol[7] == 0) { chainSymbolIcons[7]->setGraphicsEffect(effect); }
        nb_chainSymbol[7] += 1;
        break;
    case 8:
        if (nb_chainSymbol[8] == 0) { chainSymbolIcons[8]->setGraphicsEffect(effect); }
        nb_chainSymbol[8] += 1;
        break;
    case 9:
        if (nb_chainSymbol[9] == 0) { chainSymbolIcons[9]->setGraphicsEffect(effect); }
        nb_chainSymbol[9] += 1;
        break;
    case 10:
        if (nb_chainSymbol[10] == 0) { chainSymbolIcons[10]->setGraphicsEffect(effect); }
        nb_chainSymbol[10] += 1;
        break;
    case 11:
        if (nb_chainSymbol[11] == 0) { chainSymbolIcons[11]->setGraphicsEffect(effect); }
        nb_chainSymbol[11] += 1;
        break;
    case 12:
        if (nb_chainSymbol[12] == 0) { chainSymbolIcons[12]->setGraphicsEffect(effect); }
        nb_chainSymbol[12] += 1;
        break;
    case 13:
        if (nb_chainSymbol[13] == 0) { chainSymbolIcons[13]->setGraphicsEffect(effect); }
        nb_chainSymbol[13] += 1;
        break;
    case 14:
        if (nb_chainSymbol[14] == 0) { chainSymbolIcons[14]->setGraphicsEffect(effect); }
        nb_chainSymbol[14] += 1;
        break;
    case 15:
        if (nb_chainSymbol[15] == 0) { chainSymbolIcons[15]->setGraphicsEffect(effect); }
        nb_chainSymbol[15] += 1;
        break;
    case 16:
        if (nb_chainSymbol[16] == 0) { chainSymbolIcons[16]->setGraphicsEffect(effect); }
        nb_chainSymbol[16] += 1;
        break;
    default:
        break;
    }
}

void VPlayerInfo::setChainSymbols()
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1);

    std::vector<Symboles_special> plyrsCS = player->getSp();
    for (size_t i = 0; i < plyrsCS.size(); i += 1)
    {
        if (plyrsCS[i] != Symboles_special::aucun) { chainSymbolIcons[(int)plyrsCS[i]]->setGraphicsEffect(effect); }
        nb_chainSymbol[i] = 1;
    }
}

void VPlayerInfo::obtainWonderEffect(std::string symbolName)
{
    /////
}

void VPlayerInfo::loseScientificSymbol(unsigned int ssID)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.25);
    switch (ssID)
    {
    case 0:
        if (nb_scientificSymbol[0] > 0)
        {
            if (nb_scientificSymbol[0] == 1) { scientificSymbolIcons[0]->setGraphicsEffect(effect); }
            nb_scientificSymbol[0] -= 1;
        }
        break;
    case 1:
        if (nb_scientificSymbol[1] > 0)
        {
            if (nb_scientificSymbol[1] == 1) { scientificSymbolIcons[1]->setGraphicsEffect(effect); }
            nb_scientificSymbol[1] -= 1;
        }
        break;
    case 2:
        if (nb_scientificSymbol[2] > 0)
        {
            if (nb_scientificSymbol[2] == 1) { scientificSymbolIcons[2]->setGraphicsEffect(effect); }
            nb_scientificSymbol[2] -= 1;
        }
        break;
    case 3:
        if (nb_scientificSymbol[3] > 0)
        {
            if (nb_scientificSymbol[3] == 1) { scientificSymbolIcons[3]->setGraphicsEffect(effect); }
            nb_scientificSymbol[3] -= 1;
        }
        break;
    case 4:
        if (nb_scientificSymbol[4] > 0)
        {
            if (nb_scientificSymbol[4] == 1) { scientificSymbolIcons[4]->setGraphicsEffect(effect); }
            nb_scientificSymbol[4] -= 1;
        }
        break;
    case 5:
        if (nb_scientificSymbol[5] > 0)
        {
            if (nb_scientificSymbol[5] == 1) { scientificSymbolIcons[5]->setGraphicsEffect(effect); }
            nb_scientificSymbol[5] -= 1;
        }
        break;
    case 6:
        if (nb_scientificSymbol[6] > 0)
        {
            if (nb_scientificSymbol[6] == 1) { scientificSymbolIcons[6]->setGraphicsEffect(effect); }
            nb_scientificSymbol[6] -= 1;
        }
        break;
    default:
        break;
    }
}

void VPlayerInfo::loseChainSymbol(unsigned int csID)
{
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    effect->setOpacity(0.25);
    switch (csID)
    {
    case 0:
        if (nb_chainSymbol[0] > 0)
        {
            if (nb_chainSymbol[0] == 1) { chainSymbolIcons[0]->setGraphicsEffect(effect); }
            nb_chainSymbol[0] -= 1;
        }
        break;
    case 1:
        if (nb_chainSymbol[1] > 0)
        {
            if (nb_chainSymbol[1] == 1) { chainSymbolIcons[1]->setGraphicsEffect(effect); }
            nb_chainSymbol[1] -= 1;
        }
        break;
    case 2:
        if (nb_chainSymbol[2] > 0)
        {
            if (nb_chainSymbol[2] == 1) { chainSymbolIcons[2]->setGraphicsEffect(effect); }
            nb_chainSymbol[2] -= 1;
        }
        break;
    case 3:
        if (nb_chainSymbol[3] > 0)
        {
            if (nb_chainSymbol[3] == 1) { chainSymbolIcons[3]->setGraphicsEffect(effect); }
            nb_chainSymbol[3] -= 1;
        }
        break;
    case 4:
        if (nb_chainSymbol[4] > 0)
        {
            if (nb_chainSymbol[4] == 1) { chainSymbolIcons[4]->setGraphicsEffect(effect); }
            nb_chainSymbol[4] -= 1;
        }
        break;
    case 5:
        if (nb_chainSymbol[5] > 0)
        {
            if (nb_chainSymbol[5] == 1) { chainSymbolIcons[5]->setGraphicsEffect(effect); }
            nb_chainSymbol[5] -= 1;
        }
        break;
    case 6:
        if (nb_chainSymbol[6] > 0)
        {
            if (nb_chainSymbol[6] == 1) { chainSymbolIcons[6]->setGraphicsEffect(effect); }
            nb_chainSymbol[6] -= 1;
        }
        break;
    case 7:
        if (nb_chainSymbol[7] > 0)
        {
            if (nb_chainSymbol[7] == 1) { chainSymbolIcons[7]->setGraphicsEffect(effect); }
            nb_chainSymbol[7] -= 1;
        }
        break;
    case 8:
        if (nb_chainSymbol[8] > 0)
        {
            if (nb_chainSymbol[8] == 1) { chainSymbolIcons[8]->setGraphicsEffect(effect); }
            nb_chainSymbol[8] -= 1;
        }
        break;
    case 9:
        if (nb_chainSymbol[9] > 0)
        {
            if (nb_chainSymbol[9] == 1) { chainSymbolIcons[9]->setGraphicsEffect(effect); }
            nb_chainSymbol[9] -= 1;
        }
        break;
    case 10:
        if (nb_chainSymbol[10] > 0)
        {
            if (nb_chainSymbol[10] == 1) { chainSymbolIcons[10]->setGraphicsEffect(effect); }
            nb_chainSymbol[10] -= 1;
        }
        break;
    case 11:
        if (nb_chainSymbol[11] > 0)
        {
            if (nb_chainSymbol[11] == 1) { chainSymbolIcons[11]->setGraphicsEffect(effect); }
            nb_chainSymbol[11] -= 1;
        }
        break;
    case 12:
        if (nb_chainSymbol[12] > 0)
        {
            if (nb_chainSymbol[12] == 1) { chainSymbolIcons[12]->setGraphicsEffect(effect); }
            nb_chainSymbol[12] -= 1;
        }
        break;
    case 13:
        if (nb_chainSymbol[13] > 0)
        {
            if (nb_chainSymbol[13] == 1) { chainSymbolIcons[13]->setGraphicsEffect(effect); }
            nb_chainSymbol[13] -= 1;
        }
        break;
    case 14:
        if (nb_chainSymbol[14] > 0)
        {
            if (nb_chainSymbol[14] == 1) { chainSymbolIcons[14]->setGraphicsEffect(effect); }
            nb_chainSymbol[14] -= 1;

        }
        break;
    case 15:
        if (nb_chainSymbol[15] > 0)
        {
            if (nb_chainSymbol[15] == 1) { chainSymbolIcons[15]->setGraphicsEffect(effect); }
            nb_chainSymbol[15] -= 1;
        }
        break;
    case 16:
        if (nb_chainSymbol[16] > 0)
        {
            if (nb_chainSymbol[16] == 1) { chainSymbolIcons[16]->setGraphicsEffect(effect); }
            nb_chainSymbol[16] -= 1;
        }
        break;
    default:
        break;
    }
}

void VPlayerInfo::calculatePlayerInfoGeometry()
{
    QRect geometry = this->geometry();
    playerInfoGeometry[0] = geometry.topLeft();
    playerInfoGeometry[1] = geometry.topRight();
    playerInfoGeometry[2] = geometry.bottomLeft();
    playerInfoGeometry[3] = geometry.bottomRight();
}

void VPlayerInfo::calculateIconSize()
{
    calculatePlayerInfoGeometry();
    iconSize = (playerInfoGeometry[1].x() - playerInfoGeometry[0].x()) / 9;
}

void VPlayerInfo::setPlayerInfo()
{
    setCurrentPlayerFlag();
    setVictoryPoint();
    setMilitaryPower();
    setResources();
    setCoins();
    setScientificSymbols();
    setChainSymbols();
}

void VPlayerInfo::updatePlayerInfo()
{
    calculateIconSize();
    playerName->setFixedHeight(iconSize);
    wonderEffectIcons[0]->setFixedSize(iconSize * 1.95, iconSize / 2);
    wonderEffectIcons[1]->setFixedSize(iconSize * 1.22, iconSize / 2);
    victoryPointIcon->setFixedSize(iconSize, iconSize);
    militaryPowerIcon->setFixedSize(iconSize, iconSize);
    playerInfoLayout->setSpacing(iconSize / 5);
    wonderEffectLayout->setSpacing(iconSize / 2);
    for (int i = 0; i < 5; i += 1) { resourcesIcons[i]->setFixedSize(iconSize, iconSize); }
    coinsIcon->setFixedSize(iconSize, iconSize);
    for (int i = 0; i < scientificSymbolIcons.size(); i += 1) { scientificSymbolIcons[i]->setFixedSize(iconSize, iconSize); }
    for (int i = 0; i < chainSymbolIcons.size(); i += 1) { chainSymbolIcons[i]->setFixedSize(iconSize / 2, iconSize / 2); }
    playerInfoLayout->setSpacing(iconSize / 5);
}

void VPlayerInfo::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updatePlayerInfo();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VWonderDetails::VWonderDetails(QWidget* parent, VWonder* vwd, VBuilding* vbld, GameController* gc, Joueur* p, char type) : QWidget(parent), wonder(vwd), building(vbld), gameController(gc), player(p)
{
    init_WonderImageLabel();
    init_WonderNameLabel();
    init_ConstructStateLabel();
    init_Buttons(type);
    init_TopLayout();
    init_BottomLayout();
    init_WonderDetailsLayout();
}

void VWonderDetails::init_WonderImageLabel()
{
    wonderImageLabel = new QLabel;
    wonderImageLabel->setAlignment(Qt::AlignCenter);
    wonderImageLabel->setScaledContents(true);
    switch (wonder->getWonder()->getID())
    {
    case 1:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/circus_maximus.png);");
        break;
    case 2:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_colossus.png);");
        break;
    case 3:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_great_lighthouse.png);");
        break;
    case 4:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_hanging_gardens.png);");
        break;
    case 5:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_great_library.png);");
        break;
    case 6:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_mausoleum.png);");
        break;
    case 7:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/piraeus.png);");
        break;
    case 8:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_pyramids.png);");
        break;
    case 9:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_sphinx.png);");
        break;
    case 10:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_statue_of_zeus.png);");
        break;
    case 11:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_temple_of_artemis.png);");
        break;
    case 12:
        wonderImageLabel->setStyleSheet("border-image:url(icons/Wonder/the_appian_way.png);");
        break;
    default:
        break;
    }
}

void VWonderDetails::init_WonderNameLabel()
{
    wonderNameLabel = new QLabel;
    wonderNameLabel->setAlignment(Qt::AlignCenter);
    wonderNameLabel->setScaledContents(true);
    wonderNameLabel->setStyleSheet("background-color: white;");
    wonderNameLabel->setFont(QFont("Times New Roman", 20, QFont::Bold));
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    wonderNameLabel->setPalette(palette);
    wonderNameLabel->setText(QString::fromStdString(wonder->getWonder()->getNom()));
}

void VWonderDetails::init_ConstructStateLabel()
{
    constructStateLabel = new QLabel;
    constructStateLabel->setAlignment(Qt::AlignCenter);
    constructStateLabel->setScaledContents(true);
    constructStateLabel->setMargin(5);
    constructStateLabel->setFont(QFont("Arial", 16, QFont::Bold));
    if (wonder->getConstructionState())
    {
        constructStateLabel->setText("Construit");
        constructStateLabel->setStyleSheet("color: rgb(255, 255, 136); background-color: rgb(200, 170, 20); border: 2px solid rgba(0, 0, 0, 63);");
    }
    else
    {
        constructStateLabel->setText("Non Construit");
        constructStateLabel->setStyleSheet("color: rgb(200, 170, 20); background-color: rgb(129, 93, 41); border: 2px solid rgba(0, 0, 0, 63);");
    }
}

void VWonderDetails::init_Buttons(char type)
{
    if (type == '0')
    {
        QPushButton* constructButton = new QPushButton("Construire");
        constructButton->setFont(QFont("Arial", 16));
        QPalette palette;
        palette.setColor(QPalette::ButtonText, Qt::white);
        constructButton->setPalette(palette);
        constructButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(constructButton);
        connect(constructButton, &QPushButton::clicked, this, &VWonderDetails::handleConstructionButtonCliked);

        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 16));
        palette.setColor(QPalette::ButtonText, Qt::white);
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
    else if (type == '1')
    {
        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 16));
        QPalette palette;
        palette.setColor(QPalette::ButtonText, Qt::white);
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
}

void VWonderDetails::init_TopLayout()
{
    topLayout = new QVBoxLayout;
    topLayout->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(wonderImageLabel);
    topLayout->addWidget(wonderNameLabel);
}

void VWonderDetails::init_BottomLayout()
{
    bottomLayout = new QVBoxLayout;
    bottomLayout->setAlignment(Qt::AlignCenter);
    bottomLayout->addWidget(constructStateLabel);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) { bottomLayout->addWidget((*it)); }
}

void VWonderDetails::init_WonderDetailsLayout()
{
    wonderDetailsLayout = new QVBoxLayout(this);
    wonderDetailsLayout->setAlignment(Qt::AlignCenter);
    wonderDetailsLayout->addLayout(topLayout);
    wonderDetailsLayout->addLayout(bottomLayout);
}

void VWonderDetails::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    wonderImageLabel->setFixedSize(width / 3, (width / 3) * 24 / 37);
    wonderNameLabel->setFixedWidth(width / 3);
    constructStateLabel->setFixedWidth(width / 6.5);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) { (*it)->setFixedSize(width / 6.5, height / 15); }
    wonderDetailsLayout->setSpacing(height / 100);
}

void VWonderDetails::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void VWonderDetails::handleConstructionButtonCliked()
{
    wdr_OK_Flag = gameController->constructWonder(player, building->getBuilding(), wonder->getWonder());
    if (wdr_OK_Flag == '1')
    {
        emit constructSucceeded(wonder);
        this->parentWidget()->parentWidget()->close();
    }
    else if (wdr_OK_Flag == '0') { emit exceptionHappened("Ressources ou pièces insuffisantes…"); }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VWonderConstruction::VWonderConstruction(QWidget* parent, VBuilding* vbld, GameController* gc, Joueur* p) : QWidget(parent), building(vbld), gameController(gc), player(p)
{
    init_Wonders(p);
    init_ContentArea();
    init_CloseButton();
    init_ContentAreaLayout();
    init_WonderConstructionLayout();
}

void VWonderConstruction::init_Wonders(Joueur* p)
{
    std::array<Card*, 4> plyrsWonders = p->getWonders();
    for (size_t i = 0; i < 4; i += 1)
    {
        VWonder* wonder = new VWonder(this, plyrsWonders.at(i));
        if (plyrsWonders.at(i)->getConstructedFlag())
        {
            wonder->setConstructionState(true);
            wonder->setEnabled(false);
        }
        else { connect(wonder, &VWonder::showDetails, this, &VWonderConstruction::openWonderDetails); }
        wonders.append(wonder);
    }
}

void VWonderConstruction::init_ContentArea()
{
    contentArea = new QWidget;
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentArea->setStyleSheet
    (
        "QWidget {"
        "   border-radius: 15px;"
        "   border: 2px solid black;"
        "   background-image: url(icons/Background/general_background.png); }"
    );
}

void VWonderConstruction::init_CloseButton()
{
    closeButton = new QPushButton("Fermer");
    closeButton->setFont(QFont("Arial", 16));
    QPalette palette;
    palette.setColor(QPalette::ButtonText, Qt::white);
    closeButton->setPalette(palette);
    closeButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(57, 24, 23, 255); }"
        "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
    );
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
}

void VWonderConstruction::init_ContentAreaLayout()
{
    contentAreaLayout = new QGridLayout(contentArea);
    contentAreaLayout->setAlignment(Qt::AlignCenter);
    contentAreaLayout->addWidget(wonders[0], 0, 0);
    contentAreaLayout->addWidget(wonders[1], 0, 1);
    contentAreaLayout->addWidget(wonders[2], 1, 0);
    contentAreaLayout->addWidget(wonders[3], 1, 1);
}

void VWonderConstruction::init_WonderConstructionLayout()
{
    wonderConstructionLayout = new QVBoxLayout(this);
    wonderConstructionLayout->setAlignment(Qt::AlignCenter);
    wonderConstructionLayout->setSpacing(10);
    wonderConstructionLayout->addWidget(contentArea);
    wonderConstructionLayout->addWidget(closeButton);
}

void VWonderConstruction::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    contentArea->setFixedSize(width * 0.75, height * 0.75);
    closeButton->setFixedWidth(width * 0.75);
    for (unsigned int i = 0; i < 4; i += 1)
    {
        wonders[i]->setFixedSize(width / 5, (width / 5) * 24 / 37);
        wonders[i]->setIconSize(QSize(width / 5, (width / 5) * 24 / 37));
    }
    contentAreaLayout->setSpacing(width / 10);
    if (wonderDetails) { wonderDetails->setFixedSize(this->width(), this->height()); }
}

void VWonderConstruction::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void VWonderConstruction::openWonderDetails(VWonder* vwdr)
{
    wonderDetails = new VWonderDetails(this, vwdr, building, gameController, player, '0');
    connect(wonderDetails, &VWonderDetails::constructSucceeded, vwdr, &VWonder::handleConstruction);
    connect(wonderDetails, &VWonderDetails::constructSucceeded, this, &VWonderConstruction::handleConstruction);
    connect(wonderDetails, &VWonderDetails::exceptionHappened, this, &VWonderConstruction::showMessage);
    wonderDetails->setFixedSize(this->width(), this->height());
    wonderDetails->show();
}

void VWonderConstruction::handleConstruction(VWonder* vwdr)
{
    emit isConstructed(vwdr->getWonder()->getID());
}

void VWonderConstruction::showMessage(QString msg)
{
    Pop_Up_Notification* message = new Pop_Up_Notification(this, msg);
    int x = geometry().x() + (geometry().width() - message->width()) / 2;
    int y = geometry().height() - message->height() - 10;
    message->move(x, y);
    message->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VCardDetails::VCardDetails(QWidget* parent, VBuilding* vbld, GameController* gc, Joueur* p, char type) : QWidget(parent), building(vbld), gameController(gc), player(p), detailsType(type)
{
    QPalette palette;
    palette.setColor(QPalette::ButtonText, Qt::white);
    init_CardImageLabel();
    init_CardNameLabel(palette);
    init_Buttons(palette, type);
    init_ButtonLayout();
    init_CardDetailsLayout();
}

void VCardDetails::init_CardImageLabel()
{
    cardImageLabel = new QLabel;
    cardImageLabel->setAlignment(Qt::AlignCenter);
    cardImageLabel->setScaledContents(true);
    switch (building->getBuilding()->getID())
    {
    case 13:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/lumber_yard.png);");
        break;
    case 14:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/logging_camp.png);");
        break;
    case 15:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/clay_pool.png);");
        break;
    case 16:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/clay_pit.png);");
        break;
    case 17:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/quarry.png);");
        break;
    case 18:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/stone_pit.png);");
        break;
    case 19:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/glassworks.png);");
        break;
    case 20:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/press.png);");
        break;
    case 21:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/guard_tower.png);");
        break;
    case 22:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/workshop.png);");
        break;
    case 23:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/apothecary.png);");
        break;
    case 24:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/stone_reserve.png);");
        break;
    case 25:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/clay_reserve.png);");
        break;
    case 26:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/Without_Chain_Symbol/wood_reserve.png);");
        break;
    case 27:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/stable.png);");
        break;
    case 28:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/garrison.png);");
        break;
    case 29:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/palisade.png);");
        break;
    case 30:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/scriptorium.png);");
        break;
    case 31:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/pharmacist.png);");
        break;
    case 32:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/theater.png);");
        break;
    case 33:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/altar.png);");
        break;
    case 34:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/baths.png);");
        break;
    case 35:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_1/With_Chain_Symbol/tavern.png);");
        break;
    case 36:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/sawmill.png);");
        break;
    case 37:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/brickyard.png);");
        break;
    case 38:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/shelf_quarry.png);");
        break;
    case 39:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/glassblower.png);");
        break;
    case 40:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/drying_room.png);");
        break;
    case 41:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/walls.png);");
        break;
    case 42:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/forum.png);");
        break;
    case 43:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/caravansery.png);");
        break;
    case 44:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/customs_house.png);");
        break;
    case 45:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/Without_Chain_Symbol/courthouse.png);");
        break;
    case 46:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/horse_breeders.png);");
        break;
    case 47:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/barracks.png);");
        break;
    case 48:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/archery_range.png);");
        break;
    case 49:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/parade_ground.png);");
        break;
    case 50:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/library.png);");
        break;
    case 51:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/dispensary.png);");
        break;
    case 52:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/school.png);");
        break;
    case 53:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/laboratory.png);");
        break;
    case 54:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/statue.png);");
        break;
    case 55:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/temple.png);");
        break;
    case 56:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/aqueduct.png);");
        break;
    case 57:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/rostrum.png);");
        break;
    case 58:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_2/With_Chain_Symbol/brewery.png);");
        break;
    case 59:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/arsenal.png);");
        break;
    case 60:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/pretorium.png);");
        break;
    case 61:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/academy.png);");
        break;
    case 62:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/study.png);");
        break;
    case 63:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/chamber_of_commerce.png);");
        break;
    case 64:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/port.png);");
        break;
    case 65:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/armory.png);");
        break;
    case 66:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/palace.png);");
        break;
    case 67:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/town_hall.png);");
        break;
    case 68:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/Without_Chain_Symbol/obelisk.png);");
        break;
    case 69:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/fortifications.png);");
        break;
    case 70:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/siege_workshop.png);");
        break;
    case 71:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/circus.png);");
        break;
    case 72:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/university.png);");
        break;
    case 73:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/observatory.png);");
        break;
    case 74:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/gardens.png);");
        break;
    case 75:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/pantheon.png);");
        break;
    case 76:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/senate.png);");
        break;
    case 77:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/lighthouse.png);");
        break;
    case 78:
        cardImageLabel->setStyleSheet("border-image:url(icons/Building/Age_3/With_Chain_Symbol/arena.png);");
        break;
    case 79:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/merchants_guild.png);");
        break;
    case 80:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/shipowners_guild.png);");
        break;
    case 81:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/builders_guild.png);");
        break;
    case 82:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/magistrates_guild.png);");
        break;
    case 83:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/scientists_guild.png);");
        break;
    case 84:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/moneylenders_guild.png);");
        break;
    case 85:
        cardImageLabel->setStyleSheet("border-image:url(icons/Guild/tacticians_guild.png);");
        break;
    default:
        break;
    }
}

void VCardDetails::init_CardNameLabel(QPalette palette)
{
    cardNameLabel = new QLabel;
    cardNameLabel->setAlignment(Qt::AlignCenter);
    cardNameLabel->setScaledContents(true);
    cardNameLabel->setStyleSheet("background-color: white;");
    cardNameLabel->setFont(QFont("Times New Roman", 14, QFont::Bold));
    palette.setColor(QPalette::WindowText, Qt::black);
    cardNameLabel->setPalette(palette);
    cardNameLabel->setText(QString::fromStdString(building->getBuilding()->getNom()));
}

void VCardDetails::init_Buttons(QPalette palette, char type)
{
    if (type == '0') // type = '0' : ouvre la page d'achat
    {
        QPushButton* constructButton = new QPushButton("Construire un Bâtiment");
        constructButton->setFont(QFont("Arial", 12));
        constructButton->setPalette(palette);
        constructButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(constructButton);
        connect(constructButton, &QPushButton::clicked, this, &VCardDetails::handleConstructionButtonCliked);

        QPushButton* discardButton = new QPushButton("Défausser");
        discardButton->setFont(QFont("Arial", 12));
        discardButton->setPalette(palette);
        discardButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(discardButton);
        connect(discardButton, &QPushButton::clicked, this, &VCardDetails::handleDiscardButtonCliked);

        QPushButton* wonderButton = new QPushButton("Construire une Merveille");
        wonderButton->setFont(QFont("Arial", 12));
        wonderButton->setPalette(palette);
        wonderButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(wonderButton);
        if (gameController->getNumWonderBuilt() < 7)
        {
            connect(wonderButton, &QPushButton::clicked, [this]() {openVWonderConstruction(player); });
        }
        else
        {
            connect(wonderButton, &QPushButton::clicked, [this]() { emit exceptionHappened("Sept merveilles ont été construits…"); });
        }

        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 12));
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
    else if (type == '1') // type = '1' : ouvre la page de destruction
    {
        QPushButton* destructButton = new QPushButton("Détruire");
        destructButton->setFont(QFont("Arial", 12));
        destructButton->setPalette(palette);
        destructButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(destructButton);
        connect(destructButton, &QPushButton::clicked, this, &VCardDetails::handleDestructOpponentsCard);

        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 12));
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
    else if (type == '2') // type = '2' : ouvre la page de détails
    {
        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 12));
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
    else if (type == '3') // type = '3' : ouvre la page de détails de la carte défaussée
    {
        QPushButton* constructButton = new QPushButton("Construire");
        constructButton->setFont(QFont("Arial", 12));
        constructButton->setPalette(palette);
        constructButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(constructButton);
        connect(constructButton, &QPushButton::clicked, this, &VCardDetails::handleDiscardedCliked);//////////////////////////

        QPushButton* closeButton = new QPushButton("Fermer");
        closeButton->setFont(QFont("Arial", 12));
        closeButton->setPalette(palette);
        closeButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(57, 24, 23, 255); }"
            "QPushButton:hover { background-color: rgba(114, 48, 46, 255); }"
        );
        buttons.append(closeButton);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    }
}

void VCardDetails::init_ButtonLayout()
{
    buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(cardNameLabel);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) { buttonLayout->addWidget((*it)); }
}

void VCardDetails::init_CardDetailsLayout()
{
    cardDetailsLayout = new QVBoxLayout(this);
    cardDetailsLayout->setAlignment(Qt::AlignCenter);
    cardDetailsLayout->addWidget(cardImageLabel);
    cardDetailsLayout->addLayout(buttonLayout);
}

const QVector<QPushButton*>& VCardDetails::getButtons() const
{
    return buttons;
}

void VCardDetails::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    cardImageLabel->setFixedSize(width / 6, (width / 6) * 128 / 83);
    cardNameLabel->setFixedWidth(width / 6.5);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) { (*it)->setFixedSize(width / 6.5, height / 15); }
    buttonLayout->setSpacing(height / 100);
    cardDetailsLayout->setSpacing(height / 100);
    if (wonderConstruction) { wonderConstruction->setFixedSize(width, height); }
}

void VCardDetails::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void VCardDetails::handleConstructionButtonCliked()
{
    bld_OK_Flag = gameController->constructBuilding(player, building->getBuilding());
    if (bld_OK_Flag == '1')
    {
        emit constructSucceeded();
        this->close();
    }
    else if (bld_OK_Flag == '0') { emit exceptionHappened("Ressources ou pièces insuffisantes…"); }
}

void VCardDetails::handleDiscardButtonCliked()
{
    emit discardSucceeded();
    this->close();
}

void VCardDetails::handleConstructWonder(int wonderID)
{
    emit wonderConstructionSucceeded(wonderID);
    this->close();
}

void VCardDetails::handleDestructOpponentsCard()
{
    gameController->destructBuilding(player, building->getBuilding());
    emit destructOpponentsCardSucceeded();
    this->parentWidget()->close();
}

void VCardDetails::handleDiscardedCliked()
{
    gameController->constructBuilding(player, building->getBuilding());
    emit discardedConstructSucceeded();
    this->parentWidget()->close();
}

void VCardDetails::openVWonderConstruction(Joueur* p)
{
    wonderConstruction = new VWonderConstruction(this, building, gameController, p);
    wonderConstruction->setFixedSize(this->width(), this->height());
    connect(wonderConstruction, &VWonderConstruction::isConstructed, this, &VCardDetails::handleConstructWonder);
    wonderConstruction->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VPlayersCards::VPlayersCards(QWidget* parent, GameController* gc, Joueur* p) : QScrollArea(parent), gameController(gc), player(p)
{
    QWidget* contentArea = new QWidget(this);
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    playersCardsLayout = new QGridLayout(contentArea);
    playersCardsLayout->setSpacing(5);
    playersCardsLayout->setContentsMargins(5, 0, 5, 0);

    setWidget(contentArea);
    setWidgetResizable(true);
    setStyleSheet("background-color: transparent;");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    playersCardsGeometry.resize(4);
    calculatePlayersCardsGeometry();
    calculateCardSize();
}

void VPlayersCards::calculatePlayersCardsGeometry()
{
    QRect geometry = this->geometry();
    playersCardsGeometry[0] = geometry.topLeft();
    playersCardsGeometry[1] = geometry.topRight();
    playersCardsGeometry[2] = geometry.bottomLeft();
    playersCardsGeometry[3] = geometry.bottomRight();
}

void VPlayersCards::calculateCardSize()
{
    int diff = playersCardsGeometry[1].x() - playersCardsGeometry[0].x();
    cardSize.width = diff / 5.5;
    cardSize.height = cardSize.width * 128 / 83;
}

void VPlayersCards::updatePlayersCards()
{
    calculatePlayersCardsGeometry();
    calculateCardSize();
    for (int i = 0; i < plyrCards.size(); i += 1)
    {
        plyrCards[i]->setFixedSize(cardSize.width, cardSize.height);
        plyrCards[i]->setIconSize(QSize(cardSize.width, cardSize.height));
    }
}

void VPlayersCards::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updatePlayersCards();
    if (cardDetails) { cardDetails->setFixedSize(parentWidget()->width(), parentWidget()->height()); }
}

void VPlayersCards::constructCard(Card* card)
{
    if (!player->getCurrentPlayerFlag()) { return; }
    VBuilding_Purchased* newCard = new VBuilding_Purchased(this, card);
    newCard->setFixedSize(cardSize.width, cardSize.height);
    newCard->setIconSize(QSize(cardSize.width, cardSize.height));

    connect(newCard, &VBuilding_Purchased::showDetails, this, &VPlayersCards::openCardDetails);
    playersCardsLayout->addWidget(newCard, plyrCards.size() / 5, plyrCards.size() % 5);
    plyrCards.append(newCard);
}

void VPlayersCards::loseCard(VBuilding_Purchased* vbld)
{
    bool hasErased = false;
    int id_CardToBeLost = vbld->getBuilding()->getID();
    for (auto it = plyrCards.begin(); it != plyrCards.end(); ++it)
    {
        if ((*it)->getBuilding()->getID() == id_CardToBeLost)
        {
            plyrCards.erase(it);
            hasErased = true;
            break;
        }
    }
    if (!hasErased) { return; }
    while (QLayoutItem* item = playersCardsLayout->takeAt(0))
    {
        QWidget* widget = item->widget();
        playersCardsLayout->removeWidget(widget);
        widget->setParent(nullptr);
        delete item;
    }
    for (int i = 0; i < plyrCards.size(); i += 1)
    {
        playersCardsLayout->addWidget(plyrCards[i], i / 5, i % 5);
    }
}

void VPlayersCards::openCardDetails(VBuilding_Purchased* vbld)
{
    cardDetails = new VCardDetails(parentWidget(), vbld, gameController, player, '2'); // type = '2' : ouvre la page de détails
    cardDetails->setFixedSize(parentWidget()->width(), parentWidget()->height());
    cardDetails->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VWonderFrame::VWonderFrame(Joueur* p) : player(p){
    std::array<Card*, 4> plyrsWdrs = player->getWonders();
    wonderFrameLayout = new QHBoxLayout;
    for (unsigned int i = 0; i < 4; i += 1)
    {
        VWonder* wonder = new VWonder(nullptr, plyrsWdrs[i]);
        wonders.append(wonder);
        wonderFrameLayout->addWidget(wonder);
    }

    wonderFrameLayout->setSpacing(3);
    setLayout(wonderFrameLayout);

    wonderFrameGeometry.resize(4);
    calculateWonderFrameGeometry();
    calculateWonderSize();
}

const QVector<VWonder*>& VWonderFrame::getWonders() const
{
    return wonders;
}

void VWonderFrame::calculateWonderFrameGeometry()
{
    QRect geometry = this->geometry();
    wonderFrameGeometry[0] = geometry.topLeft();
    wonderFrameGeometry[1] = geometry.topRight();
    wonderFrameGeometry[2] = geometry.bottomLeft();
    wonderFrameGeometry[3] = geometry.bottomRight();
}

void VWonderFrame::calculateWonderSize()
{
    int diff = wonderFrameGeometry[1].x() - wonderFrameGeometry[0].x();
    wonderSize.width = diff / 4.25;
    wonderSize.height = wonderSize.width * 24 / 37;
}

void VWonderFrame::setWonderFrame()
{
    if (!player->getCurrentPlayerFlag()) { return; }
    std::array<Card*, 4> plyrsWdrs = player->getWonders();
    for (size_t i = 0; i < 4; i += 1) { wonders[i]->setVWonder(plyrsWdrs[i]); }
}

void VWonderFrame::updateWonderFrame()
{
    calculateWonderFrameGeometry();
    calculateWonderSize();
    for (unsigned int i = 0; i < 4; i += 1)
    {
        wonders[i]->setFixedSize(wonderSize.width, wonderSize.height);
        wonders[i]->setIconSize(QSize(wonderSize.width, wonderSize.height));
    }
}

void VWonderFrame::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updateWonderFrame();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VCardPyramid::VCardPyramid(std::vector<Card*> c1, std::vector<Card*> c2, std::vector<Card*> c3) : age(Eres::I)
{
    cardSize.width = 0;
    cardSize.height = 0;
    cardOverlap.horizontal = 0;
    cardOverlap.vertical = 0;
    init_Cards(c1, c2, c3);

    cardPyramidGeometry.resize(4);
    calculateCardPyramidGeometry();
}


void VCardPyramid::init_Cards(std::vector<Card*> c1, std::vector<Card*> c2, std::vector<Card*> c3)
{
    int index = 0;
    for (int i = 0; i < numLevels_age1; ++i)
    {
        int numCards = levels_age1[i];
        for (int j = 0; j < numCards; ++j)
        {
            VBuilding_Unpurchased* card = new VBuilding_Unpurchased(this, c1[index++]);
            connect(card, &VBuilding_Unpurchased::isConstructed, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isDiscarded, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isUsedByWonder, this, &VCardPyramid::handleConstruction);
            if (i % 2 == 1) { card->setFaceFlag(false); }
            if (i != (numLevels_age1 - 1)) { card->setSelectableFlag(false); }
            cards_age1.append(card);
            card->hide();
            cardConstructedFlags_1.push_back(false);
        }
    }

    index = 0;
    for (int i = 0; i < numLevels_age2; ++i)
    {
        int numCards = levels_age2[i];
        for (int j = 0; j < numCards; ++j)
        {
            VBuilding_Unpurchased* card = new VBuilding_Unpurchased(this, c2[index++]);
            connect(card, &VBuilding_Unpurchased::isConstructed, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isDiscarded, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isUsedByWonder, this, &VCardPyramid::handleConstruction);
            if (i % 2 == 1) { card->setFaceFlag(false); }
            if (i != (numLevels_age2 - 1)) { card->setSelectableFlag(false); }
            cards_age2.append(card);
            card->hide();
            cardConstructedFlags_2.push_back(false);
        }
    }

    index = 0;
    for (int i = 0; i < numLevels_age3; ++i)
    {
        int numCards = levels_age3[i];
        for (int j = 0; j < numCards; ++j)
        {
            VBuilding_Unpurchased* card = new VBuilding_Unpurchased(this, c3[index++]);
            connect(card, &VBuilding_Unpurchased::isConstructed, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isDiscarded, this, &VCardPyramid::handleConstruction);
            connect(card, &VBuilding_Unpurchased::isUsedByWonder, this, &VCardPyramid::handleConstruction);
            if (i % 2 == 1) { card->setFaceFlag(false); }
            if (i != (numLevels_age3 - 1)) { card->setSelectableFlag(false); }
            cards_age3.append(card);
            card->hide();
            cardConstructedFlags_3.push_back(false);
        }
    }
}


const QVector<VBuilding_Unpurchased*>& VCardPyramid::getCards(Eres ere) const
{
    switch (ere)
    {
        case Eres::I:
        return cards_age1;
        case Eres::II:
        return cards_age2;
        case Eres::III:
        return cards_age3;
    default:
        break;
    }
}

void VCardPyramid::setAge(Eres a)
{
    age = a;
    updateCardPyramid();
}


void VCardPyramid::calculateCardPyramidGeometry()
{
    QRect geometry = this->geometry();
    cardPyramidGeometry[0] = geometry.topLeft();
    cardPyramidGeometry[1] = geometry.topRight();
    cardPyramidGeometry[2] = geometry.bottomLeft();
    cardPyramidGeometry[3] = geometry.bottomRight();
}

void VCardPyramid::calculateCardSize()
{
    calculateCardPyramidGeometry();
    int diff = cardPyramidGeometry[2].y() - cardPyramidGeometry[0].y();
    cardSize.width = diff / 7.5;
    cardSize.height = (diff / 7.5) / 0.65;
}

void VCardPyramid::calculateCardOverlap()
{
    int diff = cardPyramidGeometry[2].y() - cardPyramidGeometry[0].y();
    if (age != Eres::III) { cardOverlap.vertical = diff / 10; }
    else { cardOverlap.vertical = diff / 7; }
    cardOverlap.horizontal = diff / 180;
}

void VCardPyramid::updateCardPyramid()
{
    int* levels = nullptr;
    int numLevels = 0;
    QVector<VBuilding_Unpurchased*>* cards = nullptr;
    switch (age)
    {
    case Eres::I:
        levels = levels_age1;
        numLevels = numLevels_age1;
        cards = &cards_age1;
        break;
    case Eres::II:
        levels = levels_age2;
        numLevels = numLevels_age2;
        cards = &cards_age2;
        break;
    case Eres::III:
        levels = levels_age3;
        numLevels = numLevels_age3;
        cards = &cards_age3;
        break;
    default:
        break;
    }


    calculateCardSize();
    calculateCardOverlap();
    int width = cardPyramidGeometry[1].x() - cardPyramidGeometry[0].x();
    int height = cardPyramidGeometry[2].y() - cardPyramidGeometry[0].y();
    int startX = (width - (numLevels * cardSize.width)) / 2;
    int startY = (height - (numLevels * cardSize.height - cardOverlap.vertical * (numLevels - 1))) / 2;
    int currentY = startY;
    int cardIndex = 0;

    for (int i = 0; i < numLevels; ++i)
    {
        int numCards = levels[i];
        int currentX = startX + (numLevels - numCards) * (cardSize.width / 2);
        for (int j = 0; j < numCards; ++j)
        {
            VBuilding_Unpurchased* card = (*cards)[cardIndex++];
            if (!card->getConstructionState() && !card->getDiscardFlag()) { card->show(); }
            card->setGeometry(currentX, currentY, cardSize.width, cardSize.height);
            card->setIconSize(QSize(cardSize.width, cardSize.height));
            currentX += cardSize.width + cardOverlap.horizontal;
        }
        currentY += cardSize.height - cardOverlap.vertical;
    }
}


void VCardPyramid::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updateCardPyramid();
}

void VCardPyramid::handleConstruction()
{
    QPushButton* bld_Constructed = qobject_cast<QPushButton*>(sender());
    switch (age)
    {
    case Eres::I:
        for (size_t i = 0; i < cardConstructedFlags_1.size(); i += 1)
        {
            if (bld_Constructed == cards_age1[i])
            {
                cardConstructedFlags_1[i] = true;
                break;
            }
        }
        // Cartes dans le niveau 1
        if (cardConstructedFlags_1[2] && cardConstructedFlags_1[3]) { cards_age1[0]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[3] && cardConstructedFlags_1[4]) { cards_age1[1]->setSelectableFlag(true); }
        // Cartes dans le niveau 2
        if (cardConstructedFlags_1[5] && cardConstructedFlags_1[6]) { cards_age1[2]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[6] && cardConstructedFlags_1[7]) { cards_age1[3]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[7] && cardConstructedFlags_1[8]) { cards_age1[4]->setSelectableFlag(true); }
        // Cartes dans le niveau 3
        if (cardConstructedFlags_1[9] && cardConstructedFlags_1[10]) { cards_age1[5]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[10] && cardConstructedFlags_1[11]) { cards_age1[6]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[11] && cardConstructedFlags_1[12]) { cards_age1[7]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[12] && cardConstructedFlags_1[13]) { cards_age1[8]->setSelectableFlag(true); }
        // Cartes dans le niveau 4
        if (cardConstructedFlags_1[14] && cardConstructedFlags_1[15]) { cards_age1[9]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[15] && cardConstructedFlags_1[16]) { cards_age1[10]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[16] && cardConstructedFlags_1[17]) { cards_age1[11]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[17] && cardConstructedFlags_1[18]) { cards_age1[12]->setSelectableFlag(true); }
        if (cardConstructedFlags_1[18] && cardConstructedFlags_1[19]) { cards_age1[13]->setSelectableFlag(true); }
        break;
    case Eres::II:
        for (size_t i = 0; i < cardConstructedFlags_2.size(); i += 1)
        {
            if (bld_Constructed == cards_age2[i])
            {
                cardConstructedFlags_2[i] = true;
                break;
            }
        }
        // Cartes dans le niveau 1
        if (cardConstructedFlags_2[6]) { cards_age2[0]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[6] && cardConstructedFlags_2[7]) { cards_age2[1]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[7] && cardConstructedFlags_2[8]) { cards_age2[2]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[8] && cardConstructedFlags_2[9]) { cards_age2[3]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[9] && cardConstructedFlags_2[10]) { cards_age2[4]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[10]) { cards_age2[5]->setSelectableFlag(true); }
        // Cartes dans le niveau 2
        if (cardConstructedFlags_2[11]) { cards_age2[6]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[11] && cardConstructedFlags_2[12]) { cards_age2[7]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[12] && cardConstructedFlags_2[13]) { cards_age2[8]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[13] && cardConstructedFlags_2[14]) { cards_age2[9]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[14]) { cards_age2[10]->setSelectableFlag(true); }
        // Cartes dans le niveau 3
        if (cardConstructedFlags_2[15]) { cards_age2[11]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[15] && cardConstructedFlags_2[16]) { cards_age2[12]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[16] && cardConstructedFlags_2[17]) { cards_age2[13]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[17]) { cards_age2[14]->setSelectableFlag(true); }
        // Cartes dans le niveau 4
        if (cardConstructedFlags_2[18]) { cards_age2[15]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[18] && cardConstructedFlags_2[19]) { cards_age2[16]->setSelectableFlag(true); }
        if (cardConstructedFlags_2[19]) { cards_age2[17]->setSelectableFlag(true); }
        break;
    case Eres::III:
        for (size_t i = 0; i < cardConstructedFlags_3.size(); i += 1)
        {
            if (bld_Constructed == cards_age3[i])
            {
                cardConstructedFlags_3[i] = true;
                break;
            }
        }
        // Cartes dans le niveau 1
        if (cardConstructedFlags_3[2] && cardConstructedFlags_3[3]) { cards_age3[0]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[3] && cardConstructedFlags_3[4]) { cards_age3[1]->setSelectableFlag(true); }
        // Cartes dans le niveau 2
        if (cardConstructedFlags_3[5] && cardConstructedFlags_3[6]) { cards_age3[2]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[6] && cardConstructedFlags_3[7]) { cards_age3[3]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[7] && cardConstructedFlags_3[8]) { cards_age3[4]->setSelectableFlag(true); }
        // Cartes dans le niveau 3
        if (cardConstructedFlags_3[9])
        {
            cards_age3[5]->setSelectableFlag(true);
            cards_age3[6]->setSelectableFlag(true);
        }
        if (cardConstructedFlags_3[10])
        {
            cards_age3[7]->setSelectableFlag(true);
            cards_age3[8]->setSelectableFlag(true);
        }
        // Cartes dans le niveau 4
        if (cardConstructedFlags_3[11] && cardConstructedFlags_3[12]) { cards_age3[9]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[13] && cardConstructedFlags_3[14]) { cards_age3[10]->setSelectableFlag(true); }
        // Cartes dans le niveau 5
        if (cardConstructedFlags_3[15]) { cards_age3[11]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[15] && cardConstructedFlags_3[16]) { cards_age3[12]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[16] && cardConstructedFlags_3[17]) { cards_age3[13]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[17]) { cards_age3[14]->setSelectableFlag(true); }
        // Cartes dans le niveau 6
        if (cardConstructedFlags_3[18]) { cards_age3[15]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[18] && cardConstructedFlags_3[19]) { cards_age3[16]->setSelectableFlag(true); }
        if (cardConstructedFlags_3[19]) { cards_age3[17]->setSelectableFlag(true); }
        break;
    default:
        break;
    }

}

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/