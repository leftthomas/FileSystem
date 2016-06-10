//
// Created by 任豪 on 16/6/8.
//

#ifndef FILESYSTEM_UTIL_H
#define FILESYSTEM_UTIL_H

#include <string>
#include <vector>
using namespace std;

class util {

public:


    /**
    * 显示欢迎和说明界面
    */
    static void showMenu() {
        cout << "welcome to the FileSystem" << endl;
        cout << "login————login the system" << endl;
        cout << "register————register the system" << endl;
        cout << "help————get the guide of all commands" << endl;
        cout << "exit————exit the system" << endl;
        cout << "copyright@left thomas 2016" << endl;
    }


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
     * 判断是否是有效的文件路径
     */
    static bool findIllegalPath(string s) {
        return s.find("!") != string::npos || s.find("~") != string::npos || s.find("`") != string::npos ||
               s.find("#") != string::npos || s.find("@") != string::npos || s.find("$") != string::npos ||
               s.find("%") != string::npos || s.find("^") != string::npos || s.find("&") != string::npos ||
               s.find("*") != string::npos || s.find("(") != string::npos || s.find(")") != string::npos ||
               s.find("+") != string::npos || s.find("{") != string::npos || s.find("}") != string::npos ||
               s.find("[") != string::npos || s.find("]") != string::npos || s.find("|") != string::npos ||
               s.find("\\") != string::npos || s.find(":") != string::npos || s.find(";") != string::npos ||
               s.find("\"") != string::npos || s.find("'") != string::npos || s.find(",") != string::npos ||
               s.find("?") != string::npos || s.find("<") != string::npos || s.find(">") != string::npos;
    }

    /**
     * 根据不同命令显示不同命令usage
     */
    static void help(string command) {
        if (command == "cd")
            cout << "cd:cd dir——change directory" << endl;
        else if (command == "exit")
            cout << "exit:exit——exit the system" << endl;
        else if (command == "show")
            cout << "show:show——show the system-tree" << endl;
        else if (command == "login")
            cout << "login:login——login the system" << endl;
        else if (command == "pwd")
            cout << "pwd:pwd——print working directory" << endl;
        else if (command == "register")
            cout << "register:register——register the system" << endl;
        else if (command == "help")
            cout << "help:help——get the guide of all commands" << endl;
        else if (command == "read")
            cout << "read:read file [dir]——read file" << endl;
        else if (command == "write")
            cout << "write:write file [dir]——write file" << endl;
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
 * 显示帮助文档
 */
    static void help() {
        cout << "cd:cd dir——change directory" << endl;
        cout << "exit:exit——exit the system" << endl;
        cout << "show:show——show the system-tree" << endl;
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
        cout << "mv:mv filename1|dirname1 filename2|dirname2 [dir]——change the name of file1|dir1 to file2|dir2" <<
        endl;
    }


    //字符串分割函数
    static vector<string> split(string str, string pattern) {
        string::size_type pos;
        vector<string> result;
        str += pattern;//扩展字符串以方便操作
        int size = str.size();

        for (int i = 0; i < size; i++) {
            pos = str.find(pattern, i);
            if (pos < size) {
                string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
        return result;
    }

};


#endif //FILESYSTEM_UTIL_H
