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
std::vector<std::pair<std::string, std::string>>& Account::getLogins(int &score) { score = m_score; return m_logins; }
int Account::getScore()const {return m_score;};
std::vector<std::pair<std::string, int>>& Account::getScores() { return m_scores; }

//Setter
void Account::setScore(int score) {m_score = score;};

// Methods
bool Account::accountExists(std::string username)
{
    int score;
    for (auto& logs : getLogins(score))
        if (logs.first == username)
            return true;
    return false;
}

bool Account::matches(std::string username, std::string password)
{
    int score;
    for (auto& logs : getLogins(score))
        if (logs.first == username)
            return logs.second == password;
    return false;
}

void Account::loadingDatas()
{
    loadingScores();
    std::ifstream f;
    std::string content;
    int score;
    f.open("account.txt");
    while (std::getline(f, content)) {
        std::pair<std::string, std::string> log;
        log.first = strSplit(content, ":")[0];
        log.second = strSplit(content, ":")[1];
        setScore(std::stoi(strSplit(content, ":")[2]));
        getLogins(score).push_back(log);
    }
    f.close();
}

void Account::loadingScores()
{
    std::ifstream f;
    std::string content;
    int score;
    f.open("account.txt");
    while (std::getline(f, content)) {
        std::pair<std::string, int> log;
        log.first = strSplit(content, ":")[0];
        log.second = stoi(strSplit(content, ":")[2]);
        getScores().push_back(log);
    }
    f.close();
}

void Account::writingDatas()
{
    std::ofstream f("account.txt");
    int score = 0;
    int index = 0;
    for (auto& acc : getLogins(score))
    {
        f << acc.first << ":" << acc.second << ":" << std::to_string(getScores()[index].second) << "\n";
        index++;
    }
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
