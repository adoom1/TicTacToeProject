// User.h
#ifndef USER_H
#define USER_H

#include <string>
#include "DBManager.h"

class User {
private:
    std::string currentUsername;
    bool isLoggedIn;

public:
    User();
    ~User();

    bool login(const std::string& username, const std::string& password);
    bool signup(const std::string& username, const std::string& password);
    bool logout();
    bool isUserLoggedIn() const;
    std::string getUsername() const;
};

#endif // USER_H
