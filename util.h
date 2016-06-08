//
// Created by 任豪 on 16/6/8.
//

#ifndef FILESYSTEM_UTIL_H
#define FILESYSTEM_UTIL_H

#include <string>

using namespace std;

class util {
public:
    /**
     * 查找某个字符串中是否有非法字符
     */
    static bool findIllegalCharacter(string s) {
        return s.find("!") != string::npos || s.find("~") != string::npos || s.find("`") != string::npos ||
               s.find("#") != string::npos || s.find("@") != string::npos || s.find("$") != string::npos ||
               s.find("%") != string::npos || s.find("^") != string::npos || s.find("&") != string::npos ||
               s.find("*") != string::npos || s.find("(") != string::npos || s.find(")") != string::npos ||
               s.find("+") != string::npos || s.find("{") != string::npos || s.find("}") != string::npos ||
               s.find("[") != string::npos || s.find("]") != string::npos || s.find("|") != string::npos ||
               s.find("\\") != string::npos || s.find(":") != string::npos || s.find(";") != string::npos ||
               s.find("\"") != string::npos || s.find("'") != string::npos || s.find(",") != string::npos ||
               s.find("?") != string::npos || s.find("<") != string::npos || s.find(">") != string::npos ||
               s.find("/") != string::npos;
    }

    /**
     *  查找是否存在此用户
     */
    static bool findUser(string username) {
        //TODO
        return true;
    }

    /**
     * 判断密码与对应用户名是否匹配
     */
    static bool isPasswordMatch(string username, string password) {
        //TODO
        return true;
    }

    /**
     * 用户注册
     */
    static bool _register(string username, string password) {
        //TODO
        return true;
    }

    /**
     * 根据不同命令显示不同命令usage
     */
    static void help(string command) {
        if (command == "cd")
            cout << "cd:cd dir——change directory" << endl;
        else if (command == "exit")
            cout << "exit:exit——exit the system" << endl;
        else if (command == "login")
            cout << "login:login——login the system" << endl;
        else if (command == "pwd")
            cout << "pwd:pwd——print working directory" << endl;
        else if (command == "register")
            cout << "register:register——register the system" << endl;
        else if (command == "help")
            cout << "help:help——get the guide of all commands" << endl;
        else if (command == "read")
            cout << "read:read file|dir [dir]——read file|dir" << endl;
        else if (command == "write")
            cout << "write:write file|dir [dir]——write file|dir" << endl;
        else if (command == "file")
            cout << "file:file file|dir [dir]——list file details" << endl;
        else if (command == "ls")
            cout << "ls:ls [-la] [dir]——list directory contents" << endl;
        else if (command == "rmfile")
            cout << "rmfile:rmfile filename [dir]——remove file" << endl;
        else if (command == "rmdir")
            cout << "rmdir:rmdir dirname [dir]——remove directory" << endl;
        else if (command == "mkfile")
            cout << "mkfile:mkfile filename permissions[rw|r|x] [dir]——make file" << endl;
        else if (command == "mkdir")
            cout << "mkdir:mkdir dirname permissions[rw|r|x] [dir]——make directory" << endl;
        else if (command == "cp")
            cout << "cp:cp dirname|filename ndir [odir]——copy file|dir [from odir] to ndir" << endl;
        else if (command == "mv")
            cout << "mv:mv filename1|dirname1 filename2|dirname2 [dir]——change the name of file1|dir1 to file2|dir2" <<
            endl;
        else
            cout << "command guide not found,the command isn't exist" << endl;
    }

    /**
     * 去字符串首尾空格
     */
    static void trim(string &str) {
        if (!str.empty()) {
            str.erase(0, str.find_first_not_of(" "));
            str.erase(str.find_last_not_of(" ") + 1);
        }
    }

    /**
     * 命令分发,这是一个大部分命令的总分派函数,承担很大任务量,需要先做command的校验,再做用户鉴权
     */
    static void dispatchCommand(string command) {
        //TODO 记得做用户鉴权
        if (command == "cd")
            cout << "cd:cd dir——change directory" << endl;
        else if (command == "read")
            cout << "read:read file|dir [dir]——read file|dir" << endl;
        else if (command == "write")
            cout << "write:write file|dir [dir]——write file|dir" << endl;
        else if (command == "file")
            cout << "file:file file|dir [dir]——list file details" << endl;
        else if (command == "ls")
            cout << "ls:ls [-la] [dir]——list directory contents" << endl;
        else if (command == "rmfile")
            cout << "rmfile:rmfile filename [dir]——remove file" << endl;
        else if (command == "rmdir")
            cout << "rmdir:rmdir dirname [dir]——remove directory" << endl;
        else if (command == "mkfile")
            cout << "mkfile:mkfile filename permissions[rw|r|x] [dir]——make file" << endl;
        else if (command == "mkdir")
            cout << "mkdir:mkdir dirname permissions[rw|r|x] [dir]——make directory" << endl;
        else if (command == "cp")
            cout << "cp:cp dirname|filename ndir [odir]——copy file|dir [from odir] to ndir" << endl;
        else if (command == "mv")
            cout << "mv:mv filename1|dirname1 filename2|dirname2 [dir]——change the name of file1|dir1 to file2|dir2" <<
            endl;
        else
            cout << "command error" << endl;
    }

};


#endif //FILESYSTEM_UTIL_H
