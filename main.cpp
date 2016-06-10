#include <iostream>
#include "util.h"
#include "user.h"

using namespace std;

//全局的变量,用来记录当前登录的用户,默认一开始没有用户登录,即username="",password=""
static user current_user("", "");
//文件系统
static fileSystem fSystem;

/**
 * 显示欢迎和说明界面
 */
void showMenu() {
    cout << "welcome to the FileSystem" << endl;
    cout << "login————login the system" << endl;
    cout << "register————register the system" << endl;
    cout << "help————get the guide of all commands" << endl;
    cout << "exit————exit the system" << endl;
    cout << "copyright@left thomas 2016" << endl;
}

/**
 * 显示登录之后的界面
 */
void showPanel(string username, string password) {
    //先清屏
    //TODO
    system("clear");
    //更新下当前登录的用户
    current_user.setUsername(username);
    current_user.setPassword(password);
    cout << "welcome to the MainPane,Enjoy it" << endl;
}

/**
 * 用户登录
 */
void login() {
    bool username_success = false;
    bool password_success = false;
    while (!username_success) {
        cout << "username:";
        string username;
        cin >> username;
        //检查用户是否存在
        if (!util::findUser(username)) {
            cout << "the user isn't exist,please confirm the username" << endl;
        } else {
            username_success = true;
            while (!password_success) {
                cout << "password:";
                string password;
                cin >> password;
                //判断密码是否正确
                if (!util::isPasswordMatch(username, password)) {
                    cout << "the password isn't correct,please confirm your password" << endl;
                } else {
                    password_success = true;
                    showPanel(username, password);
                }
            }
        }
    }
}

/**
 * 用户注册,register是关键字,所以命名的时候只能前面加_了
 */
void _register() {
    bool username_success = false;
    bool password_success = false;
    while (!username_success) {
        cout << "username:";
        string username;
        cin >> username;
        //先检查下输入的用户名有没有已经被注册了
        if (util::findUser(username)) {
            cout << "the username is existed,please try another" << endl;
        } else {
            //再检查下是否有非法字符
            if (util::findIllegalCharacter(username)) {
                cout << "the username contains illegal character,please input legal character(ie tom,le3a...)" << endl;
            } else {
                username_success = true;
                while (!password_success) {
                    cout << "password:";
                    string password;
                    cin >> password;
                    //先检查下是否有非法字符,且看长度是否大于6位
                    if (util::findIllegalCharacter(password) || password.length() < 6) {
                        cout <<
                        "the password contains illegal character or the length is too short(should>=6),please input legal character(ie 123456,abcdef...)" <<
                        endl;
                    } else {
                        password_success = true;
                        util::_register(username, password);
                        showPanel(username, password);
                    }
                }
            }
        }
    }
}

/**
 * 显示帮助文档
 */
void help() {
    cout << "cd:cd dir——change directory" << endl;
    cout << "exit:exit——exit the system" << endl;
    cout << "login:login——login the system" << endl;
    cout << "pwd:pwd——print working directory" << endl;
    cout << "register:register——register the system" << endl;
    cout << "help:help——get the guide of all commands" << endl;
    cout << "read:read file [dir]——read file" << endl;
    cout << "write:write file [dir]——write file" << endl;
    cout << "file:file file|dir [dir]——list file details" << endl;
    cout << "ls:ls [-la] [dir]——list directory contents" << endl;
    cout << "rmfile:rmfile filename [dir]——remove file" << endl;
    cout << "rmdir:rmdir dirname [dir]——remove directory" << endl;
    cout << "mkfile:mkfile filename permissions[rw|r|x] [dir]——make file" << endl;
    cout << "mkdir:mkdir dirname permissions[rw|r|x] [dir]——make directory" << endl;
    cout << "cp:cp dirname|filename ndir [odir]——copy file|dir [from odir] to ndir" << endl;
    cout << "mv:mv filename1|dirname1 filename2|dirname2 [dir]——change the name of file1|dir1 to file2|dir2" << endl;
}

/**
 * 退出系统
 */
void _exit() {
    //记得退出系统的时候把当前用户给清除了
    current_user.setUsername("");
    current_user.setPassword("");
    cout << "the system is exited" << endl;
}


int main() {
    showMenu();
    fSystem.init();

    bool over = false;
    string command;
    while (!over) {
        getline(cin, command);
        //首尾去下空格
        util::trim(command);
        if (command.length() > 0) {
            if (command == "login") {
                login();
            }
            else if (command == "register") {
                _register();
            }
            else if (command == "help") {
                help();
            }
            else if (command == "exit") {
                _exit();
                over = true;
            }
            else if (command.length() > 2 && command.substr(command.length() - 2, command.length() - 1) == "+?") {
                util::help(command.substr(0, command.length() - 2));
            }
            else if (command == "pwd") {
                //做下登录验证
                if (current_user.getUsername() == "")
                    cout << "please login in first" << endl;
                else {
                    //TODO
                }
            }
                //由于"+?"的条件if判断了,这里是else,所以条件可以直接判断是不是以某个命令打头
            else if (command.find("cd") == 0 || command.find("read") == 0 || command.find("write") == 0 ||
                     command.find("file") == 0 || command.find("ls") == 0 || command.find("rmfile") == 0 ||
                     command.find("rmdir") == 0 || command.find("mkfile") == 0 || command.find("mkdir") == 0
                     || command.find("cp") == 0 || command.find("mv") == 0) {
                util::dispatchCommand(command);
            }
            else {
                cout << "command not found" << endl;
            }
        }
    }
    return 0;
}