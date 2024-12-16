#include "GUI.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
QFont GeneralTextStyle::font("Arial", 16, QFont::Bold);

QPalette GeneralTextStyle::palette = []() {QPalette p; p.setColor(QPalette::ButtonText, Qt::white); return p; }();
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
GeneralButton::GeneralButton(QString text, QWidget* parent) : QPushButton(text, parent), hover(false) {}

void GeneralButton::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
    if (hover)
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));
    }
}

void GeneralButton::enterEvent(QEnterEvent* event)
{
    hover = true;
    update();
    QPushButton::enterEvent(event);
}

void GeneralButton::leaveEvent(QEvent* event)
{
    hover = false;
    update();
    QPushButton::leaveEvent(event);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
ToggleButton::ToggleButton(QWidget* parent) : GeneralButton(QString(), parent), toggledFlag(false)
{
    setCheckable(true);
    setChecked(false);
    updateButtonText();

    connect(this, &QPushButton::clicked, this, &ToggleButton::toggle);
}

void ToggleButton::updateButtonText()
{
    setText(toggledFlag ? "Choisie" : "Non Choisie");
}

bool ToggleButton::getToggledFlag() const
{
    return toggledFlag;
}

void ToggleButton::toggle()
{
    toggledFlag = !toggledFlag;
    updateButtonText();
    emit toggledChanged(toggledFlag);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
FullscreenButton::FullscreenButton(QWidget* parent) : GeneralButton(QString(), parent)
{
    setCheckable(true);
    setChecked(false);
    connect(this, &QPushButton::clicked, this, &FullscreenButton::toggleFullScreen);
}

void FullscreenButton::resizeEvent(QResizeEvent* event)
{
    QWidget* mainWidget = QApplication::activeWindow();
    if (mainWidget)
    {
        if (mainWidget->isFullScreen()) { setChecked(true); setText("Plein Écran"); }
        else { setChecked(false); setText("Écran Non Plein"); }
    }
}

void FullscreenButton::toggleFullScreen()
{
    QWidget* mainWidget = QApplication::activeWindow();
    if (mainWidget)
    {
        if (mainWidget->isFullScreen()) { mainWidget->showNormal(); }
        else { mainWidget->showFullScreen(); }
    }
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
MainWindow::MainWindow(QWidget* parent) : QMainWindow(nullptr)
{
    setWindowTitle("7 Wonders Duel");   // Définition du titre de la fenêtre
    setFixedSize(1200, 675);            // Définition de la taille de la fenêtre

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F11)
    {
        if (isFullScreen()) { showNormal(); }
        else { showFullScreen(); }
    }
    else { QWidget::keyPressEvent(event); }
    if (!isFullScreen()) {
        resize(1200, 675);
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    // Calcule la taille 16:9 de la fenêtre
    int width = event->size().width();
    int height = event->size().height();
    int newWidth = width;
    int newHeight = width * 9 / 16;

    // Ajuste la largeur si la hauteur dépasse le ratio 16:9
    if (newHeight > height)
    {
        newWidth = height * 16 / 9;
        newHeight = height;
    }

    // Calcule la taille de la bordure noire
    int horizontalPadding = (width - newWidth) / 2;
    int verticalPadding = (height - newHeight) / 2;

    // Dessine des bordures noirs
    QRegion region(0, 0, width, height);
    region -= QRegion(horizontalPadding, 0, newWidth, height);
    region -= QRegion(0, verticalPadding, width, newHeight);
    setMask(region);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
MainMenu::MainMenu(QWidget* parent) : QWidget(nullptr)
{
    init_Logo();
    init_StartButton();
    init_SettingButton();
    init_QuitButton();
    init_MainMenuLayout();
}

void MainMenu::init_Logo()
{
    logo = new QLabel(this);
    logo->setPixmap(QPixmap("icons/LOGO/LOGO.png"));
    logo->setFixedSize(488, 240);
}

void MainMenu::init_StartButton()
{
    startButton = new GeneralButton("Commencer Le Jeu", nullptr);
    startButton->setFont(GeneralTextStyle::font);
    startButton->setPalette(GeneralTextStyle::palette);
    startButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(0, 114, 98, 127); }"
        "QPushButton:hover { background-color: rgba(0, 174, 150, 63); }"
    );
    connect(startButton, &QPushButton::clicked, [this]() { emit openSelection(); });
}

void MainMenu::init_SettingButton()
{
    settingButton = new GeneralButton("Paramètres Du Jeu", nullptr);
    settingButton->setFont(GeneralTextStyle::font);
    settingButton->setPalette(GeneralTextStyle::palette);
    settingButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(0, 114, 98, 127); }"
        "QPushButton:hover { background-color: rgba(0, 174, 150, 63); }"
    );
    connect(settingButton, &QPushButton::clicked, [this]() { emit openSettings(); });
}

void MainMenu::init_QuitButton()
{
    quitButton = new GeneralButton("Quitter Le Jeu", nullptr);
    quitButton->setFont(GeneralTextStyle::font);
    quitButton->setPalette(GeneralTextStyle::palette);
    quitButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(0, 114, 98, 127); }"
        "QPushButton:hover { background-color: rgba(0, 174, 150, 63); }"
    );
    connect(quitButton, &QPushButton::clicked, [this]() {QApplication::quit(); });
}

void MainMenu::init_MainMenuLayout()
{
    mainMenuLayout = new QVBoxLayout(this);
    mainMenuLayout->setAlignment(Qt::AlignHCenter);
    mainMenuLayout->addWidget(startButton);
    mainMenuLayout->addWidget(settingButton);
    mainMenuLayout->addWidget(quitButton);
}

void MainMenu::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);

    int width = this->width() / 5;
    int height = this->height() / 10;

    logo->move((this->width() - 488) / 2, this->height() / 6.75);
    startButton->setFixedSize(width, height);
    settingButton->setFixedSize(width, height);
    quitButton->setFixedSize(width, height);
    mainMenuLayout->setContentsMargins(0, this->height() / 2, 0, 0);
    mainMenuLayout->setSpacing(this->height() / 25);
}

void MainMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap("icons/Background/main_menu.png"), QRect());
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
SettingMenu::SettingMenu(QWidget* parent)
{
    init_PantheonLabel();
    init_AgoraLabel();
    init_RuleURL();
    init_PantheonButton();
    init_AgoraButton();
    init_FullscreenButton();
    init_MainMenuButton();
    init_SettingMenuLayout();
}

void SettingMenu::init_PantheonLabel()
{
    pantheonLabel = new QLabel;
    pantheonLabel->setAlignment(Qt::AlignCenter);
    pantheonLabel->setPixmap(QPixmap("icons/LOGO/PANTHEON.png"));
}

void SettingMenu::init_AgoraLabel()
{
    agoraLabel = new QLabel;
    agoraLabel->setAlignment(Qt::AlignCenter);
    agoraLabel->setPixmap(QPixmap("icons/LOGO/AGORA.png"));
}

void SettingMenu::init_RuleURL()
{
    ruleURL = new QLabel;
    ruleURL->setAlignment(Qt::AlignCenter);
    ruleURL->setFont(GeneralTextStyle::font);
    ruleURL->setText("<a href=\"https://cdn.svc.asmodee.net/production-rprod/storage/downloads/games/7wonders-duel/fr/7du-rules-fr-1599056130lyX89.pdf\">RÈGLES DU JEU</a>");
    ruleURL->setOpenExternalLinks(true);    
}

void SettingMenu::init_PantheonButton()
{
    pantheonButton = new ToggleButton(nullptr);
    pantheonButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    pantheonButton->setFont(GeneralTextStyle::font);
    pantheonButton->setPalette(GeneralTextStyle::palette);
}

void SettingMenu::init_AgoraButton()
{
    agoraButton = new ToggleButton(nullptr);
    agoraButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    agoraButton->setFont(GeneralTextStyle::font);
    agoraButton->setPalette(GeneralTextStyle::palette);
}

void SettingMenu::init_FullscreenButton()
{
    fullscreenButton = new FullscreenButton(nullptr);
    fullscreenButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    fullscreenButton->setFont(GeneralTextStyle::font);
    fullscreenButton->setPalette(GeneralTextStyle::palette);
}

void SettingMenu::init_MainMenuButton()
{
    mainMenuButton = new GeneralButton("Menu Principal", nullptr);
    mainMenuButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    mainMenuButton->setFont(GeneralTextStyle::font);
    mainMenuButton->setPalette(GeneralTextStyle::palette);
    connect(mainMenuButton, &QPushButton::clicked, [this]() { emit openMainMenu(); });
}

void SettingMenu::init_SettingMenuLayout()
{
    settingMenuLayout = new QGridLayout(this);
    settingMenuLayout->setAlignment(Qt::AlignCenter);
    settingMenuLayout->addWidget(pantheonLabel, 0, 0);
    settingMenuLayout->addWidget(pantheonButton, 0, 1);
    settingMenuLayout->addWidget(agoraLabel, 1, 0);
    settingMenuLayout->addWidget(agoraButton, 1, 1);
    settingMenuLayout->addWidget(ruleURL, 2, 0);
    settingMenuLayout->addWidget(fullscreenButton, 2, 1);
    settingMenuLayout->addWidget(mainMenuButton, 3, 1);
}

void SettingMenu::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width() / 4;
    int height = this->height() / 10;

    pantheonButton->setFixedSize(width, height);
    agoraButton->setFixedSize(width, height);
    fullscreenButton->setFixedSize(width, height);
    mainMenuButton->setFixedSize(width, height);
    settingMenuLayout->setContentsMargins(this->height() / 15, 0, 0, 0);
    settingMenuLayout->setHorizontalSpacing(this->height() / 25);
    settingMenuLayout->setVerticalSpacing(this->height() / 10);
}

void SettingMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
SelectionMenu::SelectionMenu(QWidget* parent) : QWidget(nullptr)
{
    init_OnePlayerButton();
    init_TwoPlayersButton();
    init_MainMenuButton();
    init_SelectionButtonLayout();
    init_MainMenuButtonLayout();
    init_SelectionMenuLayout();
    setRandomBackground();
}

void SelectionMenu::init_OnePlayerButton()
{
    onePlayerButton = new GeneralButton("Un Joueur", nullptr);
    onePlayerButton->setFont(GeneralTextStyle::font);
    onePlayerButton->setPalette(GeneralTextStyle::palette);
    connect(onePlayerButton, &QPushButton::clicked, [this]() { emit openCardTablePage(); });
}

void SelectionMenu::init_TwoPlayersButton()
{
    twoPlayersButton = new GeneralButton("Deux Joueurs", nullptr);
    twoPlayersButton->setFont(GeneralTextStyle::font);
    twoPlayersButton->setPalette(GeneralTextStyle::palette);
    connect(twoPlayersButton, &QPushButton::clicked, [this]() { emit openCardTablePage(); });
}

void SelectionMenu::init_MainMenuButton()
{
    mainMenuButton = new GeneralButton("Menu Principal", nullptr);
    mainMenuButton->setFont(GeneralTextStyle::font);
    mainMenuButton->setPalette(GeneralTextStyle::palette);
    connect(mainMenuButton, &QPushButton::clicked, [this]() { emit openMainMenu(); });
}

void SelectionMenu::init_SelectionButtonLayout()
{
    selectionButtonLayout = new QHBoxLayout;
    selectionButtonLayout->addWidget(onePlayerButton);
    selectionButtonLayout->addWidget(twoPlayersButton);
}

void SelectionMenu::init_MainMenuButtonLayout()
{
    mainMenuButtonLayout = new QHBoxLayout;
    mainMenuButtonLayout->addWidget(mainMenuButton);
}

void SelectionMenu::init_SelectionMenuLayout()
{
    selectionMenuLayout = new QVBoxLayout(this);
    selectionMenuLayout->setAlignment(Qt::AlignCenter);
    selectionMenuLayout->addLayout(selectionButtonLayout);
    selectionMenuLayout->addLayout(mainMenuButtonLayout);
}

void SelectionMenu::setRandomBackground()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    switch (dis(gen))
    {
    case 1:
        backgroundPixmap = QPixmap("icons/Background/selection_menu_arene.png");
        onePlayerButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(144, 88, 24, 159); }"
            "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
        );
        twoPlayersButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(144, 88, 24, 159); }"
            "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
        );
        mainMenuButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(144, 88, 24, 159); }"
            "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
        );
        break;
    case 2:
        backgroundPixmap = QPixmap("icons/Background/selection_menu_jardins.png");
        onePlayerButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(62, 104, 41, 159); }"
            "QPushButton:hover { background-color: rgba(119, 179, 66, 127); }"
        );
        twoPlayersButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(62, 104, 41, 159); }"
            "QPushButton:hover { background-color: rgba(119, 179, 66, 127); }"
        );
        mainMenuButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(62, 104, 41, 159); }"
            "QPushButton:hover { background-color: rgba(119, 179, 66, 127); }"
        );
        break;
    case 3:
        backgroundPixmap = QPixmap("icons/Background/selection_menu_mausolee.png");
        onePlayerButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(3, 16, 24, 159); }"
            "QPushButton:hover { background-color: rgba(32, 58, 59, 127); }"
        );
        twoPlayersButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(3, 16, 24, 159); }"
            "QPushButton:hover { background-color: rgba(32, 58, 59, 127); }"
        );
        mainMenuButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(3, 16, 24, 159); }"
            "QPushButton:hover { background-color: rgba(32, 58, 59, 127); }"
        );
        break;
    case 4:
        backgroundPixmap = QPixmap("icons/Background/selection_menu_phare.png");
        onePlayerButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(49, 79, 79, 159); }"
            "QPushButton:hover { background-color: rgba(118, 141, 124, 127); }"
        );
        twoPlayersButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(49, 79, 79, 159); }"
            "QPushButton:hover { background-color: rgba(118, 141, 124, 127); }"
        );
        mainMenuButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(49, 79, 79, 159); }"
            "QPushButton:hover { background-color: rgba(118, 141, 124, 127); }"
        );
        break;
    default:
        break;
    }
}

void SelectionMenu::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width() / 5;
    int height = this->height() / 3;

    onePlayerButton->setFixedSize(width, height);
    twoPlayersButton->setFixedSize(width, height);
    mainMenuButton->setFixedSize(width, height / 5);
    selectionButtonLayout->setSpacing(this->width() / 10);
    selectionMenuLayout->setSpacing(this->height() / 10);
    selectionMenuLayout->setContentsMargins(0, (this->height() / 2) - height, 0, 0);
}

void SelectionMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), backgroundPixmap, QRect());
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
DestructionPage::DestructionPage(QWidget* parent, GameController* gc, Joueur* p, Types c) : QWidget(parent), gameController(gc), player(p)
{
    init_PlayerNameLabel();
    init_ContentArea();
    init_SelectionArea();
    init_HintLabel();
    init_ContentLayout(c);
    init_DestructionPageLayout();
}

void DestructionPage::init_PlayerNameLabel()
{
    playerNameLabel = new QLabel(QString("Les bâtiments de ") + QString::fromStdString(player->getName()));
    playerNameLabel->setAlignment(Qt::AlignCenter);
    playerNameLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DestructionPage::init_ContentArea()
{
    contentArea = new QWidget(selectionArea);
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentArea->setStyleSheet
    (
        "QWidget {"
        "   border-radius: 15px;"
        "   border: 2px solid black;"
        "   background-image: url(icons/Background/general_background.png); }"
    );
}

void DestructionPage::init_SelectionArea()
{
    selectionArea = new QScrollArea(this);
    selectionArea->setWidget(contentArea);
    selectionArea->setWidgetResizable(true);
    selectionArea->setStyleSheet("background-color: transparent;");
    selectionArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    selectionArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void DestructionPage::init_HintLabel()
{
    hintLabel = new QLabel("Sélectionnez un bâtiment à détruire");
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DestructionPage::init_ContentLayout(Types c)
{
    contentLayout = new QGridLayout(contentArea);
    contentLayout->setSpacing(5);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    std::vector<Card*> plyrCards;
    switch (c)
    {
    case Types::Matiere_Premiere:
        plyrCards = player->getCards_Brown();
        break;
    case Types::Produit_manufacture:
        plyrCards = player->getCards_Grey();
        break;
    default:
        break;
    }

    for (size_t i = 0; i < plyrCards.size(); ++i)
    {
        VBuilding_Purchased* vbld = new VBuilding_Purchased(nullptr, plyrCards[i]);
        connect(vbld, &VBuilding_Purchased::showDetails, this, &DestructionPage::openCardDetails);
        contentLayout->addWidget(vbld, i / 5, i % 5);
        cards.append(vbld);
    }
}

void DestructionPage::init_DestructionPageLayout()
{
    destructionPageLayout = new QVBoxLayout(this);
    destructionPageLayout->setSpacing(20);
    destructionPageLayout->setAlignment(Qt::AlignCenter);
    destructionPageLayout->addWidget(playerNameLabel, 0, Qt::AlignCenter);
    destructionPageLayout->addWidget(selectionArea, 0, Qt::AlignCenter);
    destructionPageLayout->addWidget(hintLabel, 0, Qt::AlignCenter);
}

void DestructionPage::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    playerNameLabel->setFixedSize(width / 2, height / 25);
    selectionArea->setFixedSize(width / 2, height / 2);
    for (auto it = cards.begin(); it != cards.end(); ++it)
    {
        (*it)->setFixedSize(width / 20, (width / 20) / 0.65);
        (*it)->setIconSize(QSize(width / 20, (width / 20) / 0.65));
    }
    hintLabel->setFixedSize(width / 2, height / 25);
    if (cardDetails) { cardDetails->setFixedSize(width, height); }
}

void DestructionPage::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void DestructionPage::openCardDetails(VBuilding_Purchased* vbld)
{
    cardDetails = new VCardDetails(this, vbld, gameController, player, '1'); // type = '1' : ouvre la page de destruction
    connect(cardDetails, &VCardDetails::destructOpponentsCardSucceeded, this, [this, vbld]() {this->handleCardDetailsSignalEmission(vbld); });
    cardDetails->setFixedSize(this->width(), this->height());
    cardDetails->show();
}

void DestructionPage::handleCardDetailsSignalEmission(VBuilding_Purchased* vbld)
{
    emit opponentsCardHasBeenDestructed(vbld);
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
DiscardedCardsPage::DiscardedCardsPage(QWidget* parent, CardTablePage* ctp, GameController* gc, Joueur* p) : QWidget(parent), gameController(gc), player(p), parentPage(ctp)
{
    init_PageNameLabel();
    init_ContentArea();
    init_SelectionArea();
    init_HintLabel();
    init_ContentLayout();
    init_DiscardedCardsPageLayout();
}

void DiscardedCardsPage::init_PageNameLabel()
{
    pageNameLabel = new QLabel("Les cartes défaussées");
    pageNameLabel->setAlignment(Qt::AlignCenter);
    pageNameLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DiscardedCardsPage::init_ContentArea()
{
    contentArea = new QWidget(selectionArea);
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentArea->setStyleSheet
    (
        "QWidget {"
        "   border-radius: 15px;"
        "   border: 2px solid black;"
        "   background-image: url(icons/Background/general_background.png); }"
    );
}

void DiscardedCardsPage::init_SelectionArea()
{
    selectionArea = new QScrollArea(this);
    selectionArea->setWidget(contentArea);
    selectionArea->setWidgetResizable(true);
    selectionArea->setStyleSheet("background-color: transparent;");
    selectionArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    selectionArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void DiscardedCardsPage::init_HintLabel()
{
    hintLabel = new QLabel("Sélectionnez un bâtiment à construire");
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DiscardedCardsPage::init_ContentLayout()
{
    contentLayout = new QGridLayout(contentArea);
    contentLayout->setSpacing(5);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    std::vector<Card*> discardedCards = gameController->getDeck()->getDiscardedCards();

    for (size_t i = 0; i < discardedCards.size(); ++i)
    {
        VBuilding_Unpurchased* vbld = new VBuilding_Unpurchased(nullptr, discardedCards[i]);
        connect(vbld, &VBuilding_Unpurchased::showDetails, this, &DiscardedCardsPage::openCardDetails);
        contentLayout->addWidget(vbld, i / 5, i % 5);
        cards.append(vbld);
    }

    VPlayerInfo* plyrInfo = nullptr;
    VPlayersCards* plyrsCards = nullptr;
    switch (parentPage->getCurrentPlayer())
    {
    case '1':
        plyrInfo = parentPage->getPlayerInfo1();
        plyrsCards = parentPage->getPlayersCards1();
        break;
    case '2':
        plyrInfo = parentPage->getPlayerInfo2();
        plyrsCards = parentPage->getPlayersCards2();
        break;
    default:
        break;
    }
    for (auto it = cards.begin(); it != cards.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::isConstructed, plyrsCards, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this, plyrInfo]() {plyrInfo->setPlayerInfo(); });
    }
}

void DiscardedCardsPage::init_DiscardedCardsPageLayout()
{
    discardedCardsPageLayout = new QVBoxLayout(this);
    discardedCardsPageLayout->setSpacing(20);
    discardedCardsPageLayout->setAlignment(Qt::AlignCenter);
    discardedCardsPageLayout->addWidget(pageNameLabel, 0, Qt::AlignCenter);
    discardedCardsPageLayout->addWidget(selectionArea, 0, Qt::AlignCenter);
    discardedCardsPageLayout->addWidget(hintLabel, 0, Qt::AlignCenter);
}

void DiscardedCardsPage::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    pageNameLabel->setFixedSize(width / 2, height / 25);
    selectionArea->setFixedSize(width / 2, height / 2);
    for (auto it = cards.begin(); it != cards.end(); ++it)
    {
        (*it)->setFixedSize(width / 20, (width / 20) / 0.65);
        (*it)->setIconSize(QSize(width / 20, (width / 20) / 0.65));
    }
    hintLabel->setFixedSize(width / 2, height / 25);
    if (cardDetails) { cardDetails->setFixedSize(width, height); }
}

void DiscardedCardsPage::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void DiscardedCardsPage::openCardDetails(VBuilding_Unpurchased* vbld)
{
    cardDetails = new VCardDetails(this, vbld, gameController, player, '3'); // type = '3' : ouvre la page de détails de la carte défaussée
    connect(cardDetails, &VCardDetails::discardedConstructSucceeded, vbld, &VBuilding_Unpurchased::handleDiscardedPurchase);
    cardDetails->setFixedSize(this->width(), this->height());
    cardDetails->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
DiscardedProgressTokensPage::DiscardedProgressTokensPage(QWidget* parent, GameController* gc, Joueur* p) : QWidget(parent), gameController(gc), player(p)
{
    init_PageNameLabel();
    init_ContentArea();
    init_HintLabel();
    init_ContentLayout();
    init_DiscardedProgressTokensPageLayout();
}

void DiscardedProgressTokensPage::init_PageNameLabel()
{
    pageNameLabel = new QLabel("Les jetons progrès écartés");
    pageNameLabel->setAlignment(Qt::AlignCenter);
    pageNameLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DiscardedProgressTokensPage::init_ContentArea()
{
    contentArea = new QWidget(this);
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentArea->setStyleSheet
    (
        "QWidget {"
        "   border-radius: 15px;"
        "   border: 2px solid black;"
        "   background-image: url(icons/Background/general_background.png); }"
    );
}

void DiscardedProgressTokensPage::init_HintLabel()
{
    hintLabel = new QLabel("Sélectionnez le jeton progrès à prendre");
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setStyleSheet("font-weight: bold; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(114, 48, 46);");
}

void DiscardedProgressTokensPage::init_ContentLayout()
{
    contentLayout = new QHBoxLayout(contentArea);
    contentLayout->setSpacing(5);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    std::array<Jeton*, 3> discardedPTs = gameController->getSideBoard()->getJetonsNonPris();

    for (size_t i = 0; i < discardedPTs.size(); ++i)
    {
        VJeton* vpt = new VJeton(nullptr, discardedPTs[i], gameController);
        connect(vpt, &VJeton::sendProgressTokenInfo, this, &DiscardedProgressTokensPage::handleProgressTokenInfo);
        contentLayout->addWidget(vpt);
        discardedProgressTokens.append(vpt);
    }
}

void DiscardedProgressTokensPage::init_DiscardedProgressTokensPageLayout()
{
    discardedProgressTokensPageLayout = new QVBoxLayout(this);
    discardedProgressTokensPageLayout->setSpacing(20);
    discardedProgressTokensPageLayout->setAlignment(Qt::AlignCenter);
    discardedProgressTokensPageLayout->addWidget(pageNameLabel, 0, Qt::AlignCenter);
    discardedProgressTokensPageLayout->addWidget(contentArea, 0, Qt::AlignCenter);
    discardedProgressTokensPageLayout->addWidget(hintLabel, 0, Qt::AlignCenter);
}

void DiscardedProgressTokensPage::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    pageNameLabel->setFixedSize(width / 2, height / 25);
    contentArea->setFixedSize(width / 2, height / 2);
    for (auto it = discardedProgressTokens.begin(); it != discardedProgressTokens.end(); ++it)
    {
        (*it)->setFixedDiameter(width / 10);
        (*it)->setIconSize(QSize(width / 10, width / 10));
    }
    hintLabel->setFixedSize(width / 2, height / 25);
}

void DiscardedProgressTokensPage::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setOpacity(0.8);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void DiscardedProgressTokensPage::handleProgressTokenInfo(Jeton* jeton)
{
    gameController->takeJeton(player, jeton);
    this->close();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
CardTablePage::CardTablePage(QWidget* parent, GameController* gc) : QWidget(nullptr), gameController(gc)
{
    init_SideBoard();
    init_PlayerInfo();
    init_PlayersCards();
    init_WonderFrame();
    init_CardPyramid();
    init_AgeInfo();
    init_TopLayout();
    init_PlayersPossessionLayout();
    init_BottomLayout();
    init_CardTablePageLayout();
    updateAgeInfo();
}

void CardTablePage::init_SideBoard()
{
    sideBoard = new VSideBoard(gameController);
    sideBoard->setFrameStyle(QFrame::Box);
    sideBoard->setFrameShape(QFrame::NoFrame);

}

void CardTablePage::init_PlayerInfo()
{
    playerInfo_1 = new VPlayerInfo('1', gameController->getPlayer1());
    playerInfo_1->setFrameStyle(QFrame::Box);
    playerInfo_1->setFrameShape(QFrame::NoFrame);

    playerInfo_2 = new VPlayerInfo('2', gameController->getPlayer2());
    playerInfo_2->setFrameStyle(QFrame::Box);
    playerInfo_2->setFrameShape(QFrame::NoFrame);

    if (currentPlayer == '1')
    {
        playerInfo_1->setCurrentPlayerFlag(true);
        playerInfo_2->setCurrentPlayerFlag(false);
    }
    else if (currentPlayer == '2')
    {
        playerInfo_1->setCurrentPlayerFlag(false);
        playerInfo_2->setCurrentPlayerFlag(true);
    }
}

void CardTablePage::init_PlayersCards()
{
    playersCards_1 = new VPlayersCards(nullptr, gameController, gameController->getPlayer1());
    playersCards_2 = new VPlayersCards(nullptr, gameController, gameController->getPlayer2());
}

void CardTablePage::init_WonderFrame()
{
    wonderFrame_1 = new VWonderFrame(gameController->getPlayer1());
    wonderFrame_1->setFrameStyle(QFrame::Box);
    wonderFrame_1->setFrameShape(QFrame::NoFrame);
    QVector<VWonder*> wonders_1 = wonderFrame_1->getWonders();
    for (auto it = wonders_1.begin(); it != wonders_1.end(); ++it) { connect((*it), &VWonder::showDetails, this, &CardTablePage::openWonderDetails); }

    wonderFrame_2 = new VWonderFrame(gameController->getPlayer2());
    wonderFrame_2->setFrameStyle(QFrame::Box);
    wonderFrame_2->setFrameShape(QFrame::NoFrame);
    QVector<VWonder*> wonders_2 = wonderFrame_2->getWonders();
    for (auto it = wonders_2.begin(); it != wonders_2.end(); ++it) { connect((*it), &VWonder::showDetails, this, &CardTablePage::openWonderDetails); }
}
void CardTablePage::init_CardPyramid()
{
    std::vector<Card*> c1(gameController->getDeck()->getDeck_Age1());
    std::vector<Card*> c2(gameController->getDeck()->getDeck_Age2());
    std::vector<Card*> c3(gameController->getDeck()->getDeck_Age3());
    cardPyramid = new VCardPyramid(c1, c2, c3);

    cardPyramid->setFrameStyle(QFrame::Box);
    cardPyramid->setFrameShape(QFrame::NoFrame);
    QVector<VBuilding_Unpurchased*> cards_age1 = cardPyramid->getCards(Eres::I);
    QVector<VBuilding_Unpurchased*> cards_age2 = cardPyramid->getCards(Eres::II);
    QVector<VBuilding_Unpurchased*> cards_age3 = cardPyramid->getCards(Eres::III);

    for (auto it = cards_age1.begin(); it != cards_age1.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_1, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer1(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_1->setWonderFrame(); });

        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_2, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer2(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_2->setWonderFrame(); });
    }

    for (auto it = cards_age2.begin(); it != cards_age2.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_1, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer1(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_1->setWonderFrame(); });

        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_2, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer2(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_2->setWonderFrame(); });
    }

    for (auto it = cards_age3.begin(); it != cards_age3.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_1, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer1(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_1->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_1->setWonderFrame(); });

        connect((*it), &VBuilding_Unpurchased::isConstructed, playersCards_2, &VPlayersCards::constructCard);
        connect((*it), &VBuilding_Unpurchased::isConstructed, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this](Card* vbld) {gameController->discardBuilding(gameController->getPlayer2(), vbld); });
        connect((*it), &VBuilding_Unpurchased::isDiscarded, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {playerInfo_2->setPlayerInfo(); });
        connect((*it), &VBuilding_Unpurchased::isUsedByWonder, [this]() {wonderFrame_2->setWonderFrame(); });
    }

    for (auto it = cards_age1.begin(); it != cards_age1.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::showDetails, this, &CardTablePage::openCardDetails);
        connect((*it), &VBuilding_Unpurchased::cannotBeChoosenByPlayer, this, &CardTablePage::showMessage);
    }
    for (auto it = cards_age2.begin(); it != cards_age2.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::showDetails, this, &CardTablePage::openCardDetails);
        connect((*it), &VBuilding_Unpurchased::cannotBeChoosenByPlayer, this, &CardTablePage::showMessage);
    }
    for (auto it = cards_age3.begin(); it != cards_age3.end(); ++it)
    {
        connect((*it), &VBuilding_Unpurchased::showDetails, this, &CardTablePage::openCardDetails);
        connect((*it), &VBuilding_Unpurchased::cannotBeChoosenByPlayer, this, &CardTablePage::showMessage);
    }
}

void CardTablePage::init_AgeInfo()
{
    ageInfo = new QLabel(this);
    ageInfo->setAlignment(Qt::AlignCenter);
    ageInfo->setFont(GeneralTextStyle::font);
    ageInfo->setStyleSheet("color: rgb(57, 24, 23)");
}

void CardTablePage::init_TopLayout()
{
    topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(playerInfo_1, 1);
    topLayout->addWidget(sideBoard, 3);
    topLayout->addWidget(playerInfo_2, 1);
}

void CardTablePage::init_PlayersPossessionLayout()
{
    playersPossessionLayout_1 = new QVBoxLayout;
    playersPossessionLayout_1->setSpacing(10);
    playersPossessionLayout_1->addWidget(playersCards_1, 9);
    playersPossessionLayout_1->addWidget(wonderFrame_1, 1);

    playersPossessionLayout_2 = new QVBoxLayout;
    playersPossessionLayout_2->setSpacing(10);
    playersPossessionLayout_2->addWidget(playersCards_2, 9);
    playersPossessionLayout_2->addWidget(wonderFrame_2, 1);
}

void CardTablePage::init_BottomLayout()
{
    bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->addLayout(playersPossessionLayout_1, 1);
    bottomLayout->addWidget(cardPyramid, 2);
    bottomLayout->addLayout(playersPossessionLayout_2, 1);
}

void CardTablePage::init_CardTablePageLayout()
{
    cardTablePageLayout = new QVBoxLayout(this);
    cardTablePageLayout->setSpacing(0);
    cardTablePageLayout->setContentsMargins(0, 0, 0, 0);
    cardTablePageLayout->addLayout(topLayout, 3);
    cardTablePageLayout->addLayout(bottomLayout, 8);
}

void CardTablePage::updateAgeInfo()
{
    QString ageText("ÈRE　");
    switch (cardPyramid->getAge())
    {
        case Eres::I:
        ageText += QString("Ⅰ");
        ageInfo->setText(ageText);
        break;
        case Eres::II:
        ageText += QString("Ⅱ");
        ageInfo->setText(ageText);
        break;
        case Eres::III:
        ageText += QString("Ⅲ");
        ageInfo->setText(ageText);
        break;
    default:
        break;
    }
}

void CardTablePage::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) { emit openPauseMenu(); }
    else { QWidget::keyPressEvent(event); }

}

void CardTablePage::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();

    if (!endTurnButton)
    {
        endTurnButton = new GeneralButton("Finir le tour", this);
        endTurnButton->setFont(GeneralTextStyle::font);
        endTurnButton->setPalette(GeneralTextStyle::palette);
        endTurnButton->setStyleSheet
        (
            "QPushButton { background-color: rgba(0, 91, 78, 200); }"
            "QPushButton:hover { background-color: rgba(0, 174, 150, 127); }"
        );
        connect(endTurnButton, &QPushButton::clicked, this, &CardTablePage::endTurn);
    }

    sideBoard->setFixedSize(width * 3 / 5, height * 3 / 11);
    playerInfo_1->setFixedSize(width / 5, height * 3 / 11);
    playerInfo_2->setFixedSize(width / 5, height * 3 / 11);
    playersCards_1->setFixedSize(width / 4, height * 36 / 55 - 10);
    playersCards_2->setFixedSize(width / 4, height * 36 / 55 - 10);
    wonderFrame_1->setFixedWidth(width / 4);
    wonderFrame_2->setFixedWidth(width / 4);
    cardPyramid->setFixedWidth(width / 2);
    ageInfo->setGeometry((width - (width / 13)) / 2, height - height / 20, width / 13, height / 20);
    endTurnButton->setGeometry((width - (width / 10)) / 2, height - height / 10, width / 10, height / 20);
    if (cardDetails) { cardDetails->setFixedSize(width, height); }
    if (wonderDetails) { wonderDetails->setFixedSize(width, height); }
    if (destructionPage) { destructionPage->setFixedSize(width, height); }
    if (discardedCardsPage) { discardedCardsPage->setFixedSize(width, height); }
    if (discardedProgressTokensPage) { discardedProgressTokensPage->setFixedSize(width, height); }
}

void CardTablePage::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}

void CardTablePage::endTurn() {
    // Verifie si le joueur a effectue une action
    bool hasPlayedFlag = gameController->getHasPlayed();
    // Verifie si le joueur a recupere tous les jetons qu'il doit prendre
    unsigned int nbJetonsAchetables = gameController->getCurrentPlayer()->getNumJetonsAchetables();
    unsigned int nbJetonsRestants = gameController->getSideBoard()->getNumJetonsRestants();
    bool canBuyToken = (nbJetonsAchetables != 0) && (nbJetonsRestants != 0);
    if (hasPlayedFlag && !canBuyToken) {
        // Fin du tour possible
        gameController->setHasPlayed(false);
        int MilPowerDiff = gameController->updateSideBoard();
        sideBoard->setConflictPawn(MilPowerDiff);
        std::array<bool, 4> lootingFlags = gameController->getSideBoard()->getLootingFlags();
        for (size_t i = 0; i < 4; i += 1)
        {
            if (lootingFlags.at(i) == true) { sideBoard->loseLootingToken(i); }
        }
        if ((gameController->getNumCardTaken() >= 20) && !isAge2)
        {
            cardPyramid->setAge(Eres::II);
            updateAgeInfo();
            isAge2 = true;
        }
        if ((gameController->getNumCardTaken() >= 40) && !isAge3)
        {
            cardPyramid->setAge(Eres::III);
            updateAgeInfo();
            isAge3 = true;
        }
        if (gameController->getNumWonderBuilt() >= 7) {
            Joueur* p1 = gameController->getPlayer1();
            Joueur* p2 = gameController->getPlayer2();

            std::array<Card*, 4> p1Wonders = p1->getWonders();
            std::array<Card*, 4> p2Wonders = p2->getWonders();

            for (size_t i = 0; i < 4; i += 1)
            {
                if (!p1Wonders.at(i)->getConstructedFlag()) { p1Wonders.at(i)->setConstructibleFlag(false); }
                if (!p2Wonders.at(i)->getConstructedFlag()) { p2Wonders.at(i)->setConstructibleFlag(false); }
            }
        }
        bool gameEndFlag = gameController->checkVictoryConditions();
        if (gameEndFlag)
        {
            emit openVictoryPage(gameController->getWinner());
            return;
        }
        //verifie si le joueur peut rejouer 
        bool rejouerFlag = gameController->getRejouer();
        if (!rejouerFlag) {
            if (currentPlayer == '1')
            {
                currentPlayer = '2';
                playerInfo_1->setCurrentPlayerFlag(false);
                playerInfo_2->setCurrentPlayerFlag(true);
                gameController->getPlayer1()->setCurrentPlayerFlag(false);
                gameController->getPlayer2()->setCurrentPlayerFlag(true);
            }
            else if (currentPlayer == '2')
            {
                currentPlayer = '1';
                playerInfo_1->setCurrentPlayerFlag(true);
                playerInfo_2->setCurrentPlayerFlag(false);
                gameController->getPlayer1()->setCurrentPlayerFlag(true);
                gameController->getPlayer2()->setCurrentPlayerFlag(false);
            }
        }
        gameController->setRejouer(false);
        playerInfo_1->setPlayerInfo();
        playerInfo_2->setPlayerInfo();
    }
    else if (!hasPlayedFlag) { showMessage("Aucune action n'a été effectuée…"); }
    else { showMessage("Vous devez prendre un jeton..."); }
}

void CardTablePage::openCardDetails(VBuilding_Unpurchased* vbld)
{
    Joueur* p1 = gameController->getPlayer1();
    Joueur* p2 = gameController->getPlayer2();
    Joueur* currentPlayer = p1->getCurrentPlayerFlag() ? p1 : p2;
    Joueur* opponentPlayer = p1->getCurrentPlayerFlag() ? p2 : p1;
    cardDetails = new VCardDetails(this, vbld, gameController, currentPlayer, '0'); // type = '0' : ouvre la page d'achat
    connect(cardDetails, &VCardDetails::constructSucceeded, vbld, &VBuilding_Unpurchased::handlePurchase);
    connect(cardDetails, &VCardDetails::discardSucceeded, vbld, &VBuilding_Unpurchased::handleDiscard);
    connect(cardDetails, &VCardDetails::discardSucceeded, vbld, &VBuilding_Unpurchased::handleDiscard);
    connect(cardDetails, &VCardDetails::wonderConstructionSucceeded, vbld, &VBuilding_Unpurchased::handleWonderConstruction);
    connect(cardDetails, &VCardDetails::wonderConstructionSucceeded, this, [this, opponentPlayer](const int& wonderID) {openDestructionPage(opponentPlayer, wonderID); });
    connect(cardDetails, &VCardDetails::wonderConstructionSucceeded, this, [this, currentPlayer](const int& wonderID) {openDiscardedCardsPage(currentPlayer, wonderID); });
    connect(cardDetails, &VCardDetails::wonderConstructionSucceeded, this, [this, currentPlayer](const int& wonderID) {openDiscardedProgressTokensPage(currentPlayer, wonderID); });
    connect(cardDetails, &VCardDetails::exceptionHappened, this, &CardTablePage::showMessage);
    cardDetails->setFixedSize(this->width(), this->height());
    cardDetails->show();
}

void CardTablePage::openWonderDetails(VWonder* vwd)
{
    wonderDetails = new VWonderDetails(this, vwd, nullptr, nullptr, nullptr, '1');
    wonderDetails->setFixedSize(this->width(), this->height());
    wonderDetails->show();
}

void CardTablePage::openDestructionPage(Joueur* p, int wonderID)
{
    if ((wonderID != 1) && (wonderID != 10)) { return; }
    Types c;
    if (wonderID == 10)
    {
        if (p->getCards_Brown().size() == 0) {
            showMessage("L'adversaire n'a aucune carte marron à défausser…");
            return;
        }
        c = Types::Matiere_Premiere;
    }
    else if (wonderID == 1)
    {
        if (p->getCards_Grey().size() == 0) {
            showMessage("L'adversaire n'a aucune carte grise à défausser…");
            return;
        }
        c = Types::Produit_manufacture;
    }

    destructionPage = new DestructionPage(this, gameController, p, c);
    if (gameController->getPlayer1() == p)
    {
        connect(destructionPage, &DestructionPage::opponentsCardHasBeenDestructed, playersCards_1, &VPlayersCards::loseCard);
        connect(destructionPage, &DestructionPage::opponentsCardHasBeenDestructed, [this]() {playerInfo_1->setPlayerInfo(); });
    }
    else if (gameController->getPlayer2() == p)
    {
        connect(destructionPage, &DestructionPage::opponentsCardHasBeenDestructed, playersCards_2, &VPlayersCards::loseCard);
        connect(destructionPage, &DestructionPage::opponentsCardHasBeenDestructed, [this]() {playerInfo_2->setPlayerInfo(); });
    }
    else { return; }
    destructionPage->setFixedSize(this->width(), this->height());
    destructionPage->show();
}

void CardTablePage::openDiscardedCardsPage(Joueur* p, int wonderID)
{
    if (wonderID != 6) { return; }
    if (gameController->getDeck()->getDiscardedCards().size() == 0)
    {
        showMessage("La pile de défausse est vide…");
        return;
    }
    discardedCardsPage = new DiscardedCardsPage(this, this, gameController, p);
    discardedCardsPage->setFixedSize(this->width(), this->height());
    discardedCardsPage->show();
}

void CardTablePage::openDiscardedProgressTokensPage(Joueur* p, int wonderID)
{
    if (wonderID != 5) { return; }
    discardedProgressTokensPage = new DiscardedProgressTokensPage(this, gameController, p);
    discardedProgressTokensPage->setFixedSize(this->width(), this->height());
    discardedProgressTokensPage->show();
}

void CardTablePage::showMessage(QString msg)
{
    Pop_Up_Notification* message = new Pop_Up_Notification(this, msg);
    int x = geometry().x() + (geometry().width() - message->width()) / 2;
    int y = geometry().height() - message->height() - 10;
    message->move(x, y);
    message->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
PauseMenu::PauseMenu(QWidget* parent) : QWidget(nullptr)
{
    init_CardTablePageButton();
    init_FullscreenButton();
    init_MainMenuButton();
    init_PauseMenuLayout();
}

void PauseMenu::init_CardTablePageButton()
{
    cardTablePageButton = new GeneralButton("Retour Au Jeu", nullptr);
    cardTablePageButton->setFont(GeneralTextStyle::font);
    cardTablePageButton->setPalette(GeneralTextStyle::palette);
    cardTablePageButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    connect(cardTablePageButton, &QPushButton::clicked, [this]() { emit openCardTablePage(); });
}

void PauseMenu::init_FullscreenButton()
{
    fullscreenButton = new FullscreenButton(nullptr);
    fullscreenButton->setFont(GeneralTextStyle::font);
    fullscreenButton->setPalette(GeneralTextStyle::palette);
    fullscreenButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
}

void PauseMenu::init_MainMenuButton()
{
    mainMenuButton = new GeneralButton("Menu Principal", nullptr);
    mainMenuButton->setFont(GeneralTextStyle::font);
    mainMenuButton->setPalette(GeneralTextStyle::palette);
    mainMenuButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    connect(mainMenuButton, &QPushButton::clicked, [this]() { emit openMainMenu(); });
}

void PauseMenu::init_PauseMenuLayout()
{
    pauseMenuLayout = new QVBoxLayout(this);
    pauseMenuLayout->setAlignment(Qt::AlignCenter);
    pauseMenuLayout->addWidget(cardTablePageButton);
    pauseMenuLayout->addWidget(fullscreenButton);
    pauseMenuLayout->addWidget(mainMenuButton);
}

void PauseMenu::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) { emit openCardTablePage(); }
    else { QWidget::keyPressEvent(event); }
}

void PauseMenu::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width() / 5;
    int height = this->height() / 10;

    cardTablePageButton->setFixedSize(width, height);
    fullscreenButton->setFixedSize(width, height);
    mainMenuButton->setFixedSize(width, height);
    pauseMenuLayout->setSpacing(height);
}

void PauseMenu::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap("icons/Background/general_background.png"), QRect());
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
VictoryPage::VictoryPage(QWidget* parent, Joueur* p) : QWidget(nullptr)
{
    init_WinnerInfo(p);
    init_MainMenuButton();
    init_VictoryPageLayout();
    setRandomBackground();
}

void VictoryPage::init_WinnerInfo(Joueur* p)
{
    winnerInfo = new QLabel;
    winnerInfo->setAlignment(Qt::AlignCenter);
    winnerInfo->setFont(GeneralTextStyle::font);
    winnerInfo->setStyleSheet("color: rgb(57, 24, 23)");
    QString winnerInfoText;
    if (p) { winnerInfoText = QString("Vainqueur : ") + QString::fromStdString(p->getName()); }
    else { winnerInfoText = QString("Vainqueur : ###"); }
    winnerInfo->setText(winnerInfoText);
}

void VictoryPage::init_MainMenuButton()
{
    mainMenuButton = new GeneralButton("Menu Principal", nullptr);
    mainMenuButton->setFont(GeneralTextStyle::font);
    mainMenuButton->setPalette(GeneralTextStyle::palette);
    mainMenuButton->setStyleSheet
    (
        "QPushButton { background-color: rgba(144, 88, 24, 127); }"
        "QPushButton:hover { background-color: rgba(209, 147, 78, 127); }"
    );
    connect(mainMenuButton, &QPushButton::clicked, [this]() { emit openMainMenu(); });
}

void VictoryPage::init_VictoryPageLayout()
{
    victoryPageLayout = new QVBoxLayout(this);
    victoryPageLayout->setAlignment(Qt::AlignCenter);
    victoryPageLayout->addWidget(winnerInfo, 1);
    victoryPageLayout->addWidget(mainMenuButton, 1);
}

void VictoryPage::setRandomBackground()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);
    switch (dis(gen))
    {
    case 1:
        backgroundPixmap = QPixmap("icons/Background/victory_page_01.png");
        break;
    case 2:
        backgroundPixmap = QPixmap("icons/Background/victory_page_02.png");
        break;
    case 3:
        backgroundPixmap = QPixmap("icons/Background/victory_page_03.png");
        break;
    case 4:
        backgroundPixmap = QPixmap("icons/Background/victory_page_04.png");
        break;
    default:
        break;
    }
}

void VictoryPage::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    int width = this->width() / 5;
    int height = this->height() / 10;

    mainMenuButton->setFixedSize(width, height);
    victoryPageLayout->setContentsMargins(0, width / 1.5, 0, width / 1.5);
}

void VictoryPage::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), backgroundPixmap, QRect());
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
PageControler::PageControler(GameController* gc) : gameController(gc)
{
    mainWindow = new MainWindow(nullptr);
    pages = new QStackedWidget(nullptr);
    mainMenu = new MainMenu(nullptr);
    settingMenu = new SettingMenu(nullptr);
    pauseMenu = new PauseMenu(nullptr);
}

void PageControler::resetSelectionMenu()
{
    gameController->init_Game();
    if (selectionMenu)
    {
        pages->removeWidget(selectionMenu);
        delete selectionMenu;
        selectionMenu = nullptr;
    }
    selectionMenu = new SelectionMenu(nullptr);
    pages->addWidget(selectionMenu);
    QObject::connect(selectionMenu, &SelectionMenu::openCardTablePage, [&]() { resetCardTablePage(); });
    QObject::connect(selectionMenu, &SelectionMenu::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });
    pages->setCurrentWidget(selectionMenu);
}

void PageControler::resetCardTablePage()
{
    if (cardTablePage)
    {
        pages->removeWidget(cardTablePage);
        delete cardTablePage;
        cardTablePage = nullptr;
    }
    cardTablePage = new CardTablePage(nullptr, gameController);
    pages->addWidget(cardTablePage);
    QObject::connect(cardTablePage, &CardTablePage::openPauseMenu, [&]() { pages->setCurrentWidget(pauseMenu); });
    QObject::connect(cardTablePage, &CardTablePage::openVictoryPage, [&]() { resetVictoryPage("player_1"); }); //////////////////change "player_1" to controler.getWinner(); 
    pages->setCurrentWidget(cardTablePage);
}

void PageControler::resetVictoryPage(QString plyrName)
{
    if (victoryPage)
    {
        pages->removeWidget(victoryPage);
        delete victoryPage;
        victoryPage = nullptr;
    }
    victoryPage = new VictoryPage(nullptr, gameController->getWinner());
    pages->addWidget(victoryPage);
    QObject::connect(victoryPage, &VictoryPage::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });
    pages->setCurrentWidget(victoryPage);
}

void PageControler::pageGeneration()
{
    pages->setParent(mainWindow);
    pages->addWidget(mainMenu);
    pages->addWidget(settingMenu);
    pages->addWidget(pauseMenu);

    QObject::connect(mainMenu, &MainMenu::openSettings, [&]() { pages->setCurrentWidget(settingMenu); });
    QObject::connect(mainMenu, &MainMenu::openSelection, [&]() { resetSelectionMenu(); });
    QObject::connect(settingMenu, &SettingMenu::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });
    QObject::connect(selectionMenu, &SelectionMenu::openCardTablePage, [&]() { resetCardTablePage(); });
    QObject::connect(selectionMenu, &SelectionMenu::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });
    QObject::connect(cardTablePage, &CardTablePage::openPauseMenu, [&]() { pages->setCurrentWidget(pauseMenu); });
    QObject::connect(cardTablePage, &CardTablePage::openVictoryPage, [&]() { resetVictoryPage("player_1"); });//////////////////change "player_1" to controler.getWinner(); 
    QObject::connect(pauseMenu, &PauseMenu::openCardTablePage, [&]() { pages->setCurrentWidget(cardTablePage); });
    QObject::connect(pauseMenu, &PauseMenu::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });
    QObject::connect(victoryPage, &VictoryPage::openMainMenu, [&]() { pages->setCurrentWidget(mainMenu); });

    mainWindow->setCentralWidget(pages);
    mainWindow->show();
}
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/