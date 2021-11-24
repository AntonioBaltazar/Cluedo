#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include "Account.h"
#include "Utils.h"

// Constructors & Destructor
Account::Account() {}
Account::~Account() {
    writingDatas();
}

// Getters
std::vector<std::pair<std::string, std::string>>& Account::getLogins() { return m_logins; }

// Methods
bool Account::accountExists(std::string username)
{
    for (auto& logs : getLogins())
        if (logs.first == username)
            return true;
    return false;
}

bool Account::matches(std::string username, std::string password)
{
    for (auto& logs : getLogins())
        if (logs.first == username)
            return logs.second == password;
    return false;
}

void Account::loadingDatas()
{
    std::ifstream f;
    std::string content;
    f.open("account.txt");
    while (std::getline(f, content)) {
        std::pair<std::string, std::string> log;
        log.first = strSplit(content, ":")[0];
        log.second = strSplit(content, ":")[1];
        getLogins().push_back(log);
    }
    f.close();
}

void Account::writingDatas()
{
    std::ofstream f("account.txt");
    for (auto& acc : getLogins())
        f << acc.first << ":" << acc.second << "\n";
    f.close();
}


std::string Account::askLogs(int x, int y) {
    int saisie(0), index(0);
    std::string pseudo;
    do {
        saisie = getInput();

        if (((saisie >= 'a' && saisie <= 'z') || (saisie >= 'A' && saisie <= 'Z') || saisie == ' ') && index < 19)
        {
            pseudo += (char)saisie;
            printAt(x + index, y, std::string(1, char(saisie)));
            index++;
        }
        else if (saisie == 8 && index > 0)
        {
            pseudo.pop_back();
            index--;
            printAt(x + index, y, " ");
        }
    } while (saisie != 13 || saisie < 2);
    return pseudo;
}
