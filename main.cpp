#include<iostream>
#include <string>
#include "GUI.h"

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   
    GameController& gameController = GameController::getInstance();
    PageControler pageControler(&gameController);
    pageControler.pageGeneration();

    return app.exec();

}