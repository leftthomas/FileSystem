//
// Created by 任豪 on 16/6/8.
//

#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H

#include <string>

using namespace std;

class user {
private:
    string username;
    //用户名
    string password;//密码

public:

    /**
     * 构造函数
     */
    user(const string &username, const string &password) : username(username), password(password) { }

    const string &getUsername() const {
        return username;
    }

    void setUsername(const string &username) {
        user::username = username;
    }

    const string &getPassword() const {
        return password;
    }

    void setPassword(const string &password) {
        user::password = password;
    }
};


#endif //FILESYSTEM_USER_H
