#include <iostream>
#include <conio.h>
#include <cstring>
#include <algorithm>
#include <time.h>
#include <string>

#include "../Game.h"
#include "../Account.h"

void Game::start2() {
    // Getting datas of game
    askNbOfPlayers();
    askAccountOfPlayers();

    // Setup card
    setAllPackages();
    cardDistrib();
    setSolution();

    system("cls");

    // Setup board
    World board(16, 11, "Board", "maps/main");
    for (auto& p : getPlayers())
        board.addPlayer(&p, true);

    // Setup animated element : dice, notepad & dashboard
    Dice d(2, 1, 12, 6);
    Dashboard db(94, 3, 25, 17);
    getDashboard() = db;
    Notepad np(2, 25, 25, 3);
    np.renderTurn();
    getElements().push_back(&d);
    getElements().push_back(&db);
    getElements().push_back(&np);

    int nbTurn = 0;
    while(!isFinish())
    {
        handlePlayerTurn(&getPlayers()[nbTurn % getPlayers().size()], &d,getPlayers()[nbTurn % getPlayers().size()+1]);

        //Hypothese
        //getPlayers()[nbTurn % getPlayers().size()].setHypothesis(getAllCard());
        //HypothesisVerification(getPlayers()[nbTurn % getPlayers().size()],true);

        nbTurn++;
    }

    while(!kbhit());
}

void Game::askAccountOfPlayers()
{
    // Loading datas from accounts
    Account acc;
    acc.loadingDatas();

    system("cls");
    std::string adjectives[] = {"Premier", "Second", "Troisi", "Quatri", "Cinqui", "Sixi"};
    AnimatedElement sharp(16, 11);
    AnimatedElement nb;
    sharp.render("numbers/sharp");
    int saisie, index;
    enum State { USERNAME, PASSWORD, REGISTER, COLOR, DONE};
    std::vector<std::vector<int>> spawnCoords = {{16, 11}, {18, 11}, {16, 12}, {18, 12}, {20, 11}, {14, 12}};

    for (int i = 0; i < getNbOfPlayers(); i++)
    {
        State state = State::USERNAME;
        std::string pseudo, password;
        Color playerColor;
        // Clearing old text
        for (int j = 0; j < 2; j++)
            printAt(85, 13 + j, std::string(30, ' '));
        nb.init("numbers/" + std::to_string(i+1));
        nb.setTranslated(32, 11);
        nb.clearArea(0, 0);
        nb.render("numbers/" + std::to_string(i+1));
        printAt(48, 12, std::string(34, ' '));
        gotoxy(48, 12);
        std::cout << color(adjectives[i], Color::Bright_Yellow);
        if (i > 1) std::cout << color(char(138), Color::Bright_Yellow) << color("me", Color::Bright_Yellow);
        std::cout << color(" joueur,", Color::Bright_White);

        while (state != State::DONE) {
            if (state == State::USERNAME)
            {
                for (int i = 0; i < 6; i++)
                    printAt(48, 13 + i, std::string(34, ' '));
                printAt(48, 13, color("saississez votre nom :", Color::Bright_White));
                pseudo = acc.askLogs(48, 14);
                if (acc.accountExists(pseudo))
                    state = State::PASSWORD;
                else {
                    std::string resp;
                    printAt(48, 15, "Pas de compte trouve.");
                    printAt(48, 16, "Voulez-vous en creer un ?");
                    printAt(48, 17, "Oui / Non");
                    do {
                        resp = acc.askLogs(48, 18);
                    } while (!(strcasecmp("oui", resp.c_str()) == 0 || strcasecmp("non", resp.c_str()) == 0));
                    if (strcasecmp("oui", resp.c_str()) == 0) {
                        state = State::REGISTER;
                    }
                }
            } else if (state == State::PASSWORD)
            {
                printAt(48, 16, std::string(28, ' '));
                printAt(48, 15, color("Saississez votre mot de passe :", Color::Bright_White));
                password = acc.askLogs(48, 16);
                if (acc.matches(pseudo, password))
                    state = State::COLOR;
            } else if (state == State::REGISTER) {
                for (int i = 0; i < 5; i++)
                    printAt(48, 15 + i, std::string(34, ' '));
                printAt(48, 15, "Choississez un mot de passe :");
                password = acc.askLogs(48, 16);
                std::pair<std::string, std::string> newP;
                newP.first = pseudo;
                newP.second = password;
                acc.getLogins().push_back(newP);
                state = State::COLOR;
            } else if (state == State::COLOR) {
                printAt(85, 13, color("Choississez un pion :", Color::Bright_White));

                int input, choice = 1;
                std::vector<Color> colors = {Color::Bright_Blue, Color::Green, Color::Yellow, Color::Bright_Magenta, Color::Bright_Cyan, Color::Bright_Red};
                do
                {
                    if (input == 75 && choice > 1) choice--;
                    if (input == 77 && choice < 6) choice++;
                    for (int i = 0; i < 40; i++) printAt(40+i, 20, " ");
                    printAt(90, 14, std::string(5, ' '));
                    printAt(90, 14, (choice > 1 ? char(17) : ' '));
                    printAt(96, 14, (choice < colors.size() ? char(16) : ' '));
                    printAt(93, 14, color("\xffe", colors[choice]));
                    input = getInput();
                } while (input != 13);
                playerColor = colors[choice];
                state = State::DONE;
            }
        }

        getPlayers().push_back(Player(pseudo, playerColor, spawnCoords[i][0], spawnCoords[i][1], ""));
    }
}

void Game::askNbOfPlayers()
{
    system("cls");
    int nbOfPlayers = 2;
    int saisie = -1;
    gotoxy(40, 12);
    std::cout << char(16);
    std::cout << color(" Nombre de joueurs ?", Color::Bright_White);
    gotoxy(42,13);
    std::cout << "De 2 " << char(133) <<" 6";
    AnimatedElement nb(65, 11);
    do
    {
        nb.clearArea(14, 7);
        nb.render("numbers/" + std::to_string(nbOfPlayers));
        gotoxy(42, 15);
        for (int i = 0; i < 12; i++) std::cout << " ";
        gotoxy(42, 15);
        for (int i = 0; i < nbOfPlayers; i++) std::cout << color(char(3), Color::Red) << " ";
        saisie = getInput();
        if (saisie == 72 && nbOfPlayers < 6) nbOfPlayers++;
        if (saisie == 80 && nbOfPlayers > 2) nbOfPlayers--;
    } while (saisie != 13);
    setNbOfPlayers(nbOfPlayers);
}
