//
// Created by 任豪 on 16/6/8.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <string>
#include "tomFile.h"

using namespace std;

class fileSystem {

private:
    //根节点
    tomFile *root;

    //当前节点,这个变量可以方便后续使用
    tomFile *current_file;
public:


    /**
   * 创建文件系统函数,初始化
   */
    fileSystem() : root(0), current_file(0) { }

    fileSystem(tomFile *node) : root(node), current_file(node) { }

    /**
     * 析构函数,记得释放内存
     */
    ~fileSystem() {
        destroy(root);
    }

    /**
 *  查找是否存在此用户,其实质就是读config.txt文件,使用的时候一定要记得查找起点在root,这样设置主要是为了递归调用方便
 */
    bool findUser(string username) {
        bool found = false;
        tomFile *current = findFile("config.txt", root);
        //找到config文件
        if (current != NULL) {
            //按;分割成username password格式的字符串数组
            vector<string> result = util::split(current->getContent(), ";");
            for (int i = 0; i < result.size(); ++i) {
                //按-分割成username和password
                vector<string> result2 = util::split(result[i], "-");
                if (result2[0] == username) {
                    found = true;
                    break;
                }
            }
        }
        return found;
    }

    /**
     * 判断密码与对应用户名是否匹配,其实质就是读config.txt文件
     */
    bool isPasswordMatch(string username, string password) {
        bool match = false;
        tomFile *current = findFile("config.txt", root);
        //找到config文件
        if (current != NULL) {
            //按;分割成username password格式的字符串数组
            vector<string> result = util::split(current->getContent(), ";");
            for (int i = 0; i < result.size(); ++i) {
                //按-分割成username和password
                vector<string> result2 = util::split(result[i], "-");
                if (result2[0] == username) {
                    if (password == result2[1])
                        match = true;
                    break;
                }
            }
        }
        return match;
    }

    /**
     * 用户注册,其实质就是将用户名和密码写进config.txt
     */
    bool _register(string username, string password) {
        bool success = false;
        tomFile *current = findFile("config.txt", root);
        if (current != NULL) {
            current->setContent(current->getContent() + username + "-" + password + ";");
            success = true;
        }
        return success;
    }


    //这个函数只在初始化的时候调用,其他时候都需要鉴权
    void insert(tomFile *parent, tomFile *tmp) {
        //先看下有没有同名文件
        bool found = false;
        for (int i = 0; i < parent->getChildren().size(); ++i) {
            if (parent->getChildren()[i]->getName() == tmp->getName()) {
                found = true;
                break;
            }
        }
        if (!found)
            parent->addChildren(tmp);
    }

    //先序递归输出
    void pre_recurs_render(tomFile *some, unsigned recurs_level) {
        for (int i = 0; i < recurs_level; i++)
            cout << "  ";
        cout << some->getName() << endl;
        for (unsigned i = 0; i < some->getChildren().size(); i++)
            pre_recurs_render(some->getChildren()[i], recurs_level + 1);
    }

    //后序删除
    void destroy(tomFile *some) {
        for (unsigned i = 0; i < some->getChildren().size(); i++)
            destroy(some->getChildren()[i]);
        if (some) {
            delete some;
        }
    }


    tomFile *getCurrent_file() const {
        return current_file;
    }

    void setCurrent_file(tomFile *current_file) {
        fileSystem::current_file = current_file;
    }

    tomFile *getRoot() const {
        return root;
    }

    void setRoot(tomFile *root) {
        fileSystem::root = root;
    }

    /**
     * 通过文件名递归查找文件
     */
    tomFile *findFile(string filename, tomFile *head) {
        tomFile *temp = NULL;
        int i = 0;
        if (head != NULL) {
            // 如果名字匹配
            if (filename == head->getName()) {
                temp = head;
            }
                // 如果不匹配，则查找其子节点
            else {   /*如果temp不为空，则结束查找*/
                for (i = 0; i < head->getChildren().size() && temp == NULL; ++i) {
                    // 递归查找子节点
                    temp = findFile(filename, head->getChildren()[i]);
                }
            }
        }
        // 将查找到的节点指针返回，也有可能没有找到，此时temp为NULL
        return temp;
    }

    /**
     * 这是通过全路径查找,即/xxx/xxx的形式
     */
    tomFile *findFileByPath(string path, tomFile *head) {
        tomFile *temp = NULL;
        int i = 0;
        if (head != NULL) {
            // 如果路径匹配
            if (path == head->getPath()) {
                temp = head;
            }
            else {
                for (i = 0; i < head->getChildren().size() && temp == NULL; ++i) {
                    // 递归查找子节点
                    temp = findFileByPath(path, head->getChildren()[i]);
                }
            }
        }
        // 将查找到的节点指针返回，也有可能没有找到，此时temp为NULL
        return temp;
    }


    /*
     * 显示文件系统当前路径
     */
    string getCurrent_path() {
        return current_file->getPath();
    }


    /**
     * cd命令,其实质是改变current_file
     */
    void changeDirectory(string username, string path) {
        if (util::findIllegalPath(path)) {
            cout << "the path is illegal" << endl;
        } else {
            tomFile *file;
            //第一种cd方法,在当前路径下输入子文件夹名就行了,例如left、left/data...
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + path, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + path, current_file);
            if (file != NULL) {
                //鉴权
                if (authUser(username, file) == "x")
                    authOut("x");
                else {
                    //有权操作
                    if (file->getType() == "file")
                        cout << "this path is a file,not a dir" << endl;
                    else
                        //改变current_file
                        current_file = file;
                }
            } else {
                //第二种cd方法,输入全路径,例如/home/left
                file = findFileByPath(path, root);
                if (file != NULL) {
                    //鉴权
                    if (authUser(username, file) == "x")
                        authOut("x");
                    else {
                        //有权操作
                        if (file->getType() == "file")
                            cout << "this path is a file,not a dir" << endl;
                        else
                            //改变current_file
                            current_file = file;
                    }
                }
                else
                    cout << "this path is not existed" << endl;
            }
        }
    }


    /**
   * 用户鉴权,用来判断user是否有权访问或操作此目录或文件
   * x:无权限
   * r:只读
   * rw:读写
   */
    string authUser(string username, tomFile *file) {
        //没找到此用户
        if (file->getPermissions().find(username) == file->getPermissions().end()) {
            //找下everyone
            if (file->getPermissions().find("everyone") == file->getPermissions().end())
                return "x";
            else
                return file->getPermissions().find("everyone")->second;
        }
        else
            return file->getPermissions().find(username)->second;
    }

    /**
     * 根据不同权限输出不同提示
     */
    void authOut(string q) {
        if (q == "x")
            cout << "you have no access to this file|dir" << endl;
        else if (q == "r")
            cout << "you can read this file|dir only" << endl;
        else if (q == "rw")
            cout << "you can read or write this file|dir" << endl;
    }

    /**
     * 列出路径下的全部文件,可指定是否详细,含默认参数,不需要做鉴权,因为ls前提就是cd到了此目录,本身做了鉴权
     */
    void ls(string username, string parameter = "") {
        //第一种情况,无参,显示当前路径下的所有文件简略信息
        if (parameter == "") {
            if (current_file->getChildren().size() == 0) {
                cout << "no files" << endl;
            } else {
                for (int i = 0; i < current_file->getChildren().size(); ++i) {
                    cout << current_file->getChildren()[i]->getName() + "   ";
                }
                cout << endl;
            }
        }
            //第二种情况,一个参数为"-la",显示当前路径下的所有文件详细信息
        else if (parameter == "-la") {
            if (current_file->getChildren().size() == 0) {
                cout << "no files" << endl;
            } else {
                for (int i = 0; i < current_file->getChildren().size(); ++i) {
                    cout << current_file->getChildren()[i]->getName() + "   " << current_file->
                            getChildren()[i]->getType() + "   " << authUser(username, current_file
                            ->getChildren()[i]) + "   " << current_file->getChildren()[i]->
                            getCreateTime() + "   " << current_file->getChildren()[i]->getModifyTime() + "   "
                    << current_file->getChildren()[i]->getSize() << "byte" << endl;
                }
            }
        }
        else {
            cout << "please input the correct command,refer to 'ls+?'" << endl;
        }
    }

/**
     * 添加文件,只有在type为dir时才有用
     * 4:表示此文件不是dir
     * 0:表示无权限
     * 1:表示此目录只读
     * 2:表示同名文件已存在
     * 3:表示添加成功
     */
//    int addFile(tomFile *file, tomFile *parent, string username) {
//        if (parent->getType() != "dir")
//            return 4;
//        else if (authUser(username, parent) == 0) {
//            return 0;
//        }
//        else if (authUser(username, parent) == 1) {
//            return 1;
//        }
//        else if (authUser(username, parent) == 2) {
//            for (int i = 0; i < parent.getChildren().size(); ++i) {
//                if (parent.getChildren()[i]->getName() == file.getName()) {
//                    return 2;
//                }
//            }
//            //表示没有找到同名文件,这时候可以添加了
//            parent->getChildren().push_back(file);
//        }
//        return 3;
//    }

};


#endif //FILESYSTEM_FILESYSTEM_H
