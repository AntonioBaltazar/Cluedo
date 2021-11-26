#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

#include <vector>

class Account {
private:
    std::vector<std::pair<std::string, std::string>> m_logins;
public:
    // Destructors & Destructor
    Account();
    ~Account();
    // Getters
    std::vector<std::pair<std::string, std::string>>& getLogins();
    // Methods
    void loadingDatas();
    void writingDatas();
    bool accountExists(std::string username);
    bool matches(std::string username, std::string password);
    std::string askLogs(int x, int y);
};


#endif // ACCOUNT_H_INCLUDED
