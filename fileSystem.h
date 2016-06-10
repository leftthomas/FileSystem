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
    //当前路径
    string current_path;
    //根节点
    tomFile *root;

public:


    /**
 *  查找是否存在此用户,其实质就是读config.txt文件
 */
    static bool findUser(string username) {
        //TODO
        return true;
    }

    /**
     * 判断密码与对应用户名是否匹配,其实质就是读config.txt文件
     */
    static bool isPasswordMatch(string username, string password) {
        //TODO
        return true;
    }

    /**
     * 用户注册,其实质就是将用户名和密码写进config.txt
     */
    static bool _register(string username, string password) {
        //TODO
        return true;
    }


    /**
     * 用户鉴权,用来判断user是否有权访问或操作此目录或文件
     * 0:无权限
     * 1:只读
     * 2:读写
     */
    int authUser(string username, tomFile file) {
//        //没找到此用户
//        if (file.getPermissions().find(username) == file.getPermissions().end()) {
//            //找下everyone
//            if (file.getPermissions().find("everyone") == file.getPermissions().end()) {
//                return 0;
//            } else {
//                if ( file.getPermissions().find("everyone")->second == "x")
//                    return 0;
//                else if ( file.getPermissions().find("everyone")->second == "r")
//                    return 1;
//                else if ( file.getPermissions().find("everyone")->second == "rw")
//                    return 2;
//            }
//        }
//        else {
//            if (file.getPermissions().find(username)->second == "x")
//                return 0;
//            else if (file.getPermissions().find(username)->second == "r")
//                return 1;
//            else if (file.getPermissions().find(username)->second == "rw")
//                return 2;
//        }
//        return true;
    }

    /**
    * 创建文件系统函数,初始化
    */
    fileSystem() : root(0), current_path("/") { }

    fileSystem(tomFile *node) : root(node), current_path("/") { }

    /**
     * 析构函数,记得释放内存
     */
    ~fileSystem() {
        destroy(root);
    }

    //注意传position的引用
    void insert(tomFile *parent, tomFile *tmp) {
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

/**
     * 添加文件,只有在type为dir时才有用
     * 4:表示此文件不是dir
     * 0:表示无权限
     * 1:表示此目录只读
     * 2:表示同名文件已存在
     * 3:表示添加成功
     */
    int addFile(tomFile *file, tomFile *parent, string username) {
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
    }


    const string &getCurrent_path() const {
        return current_path;
    }

    void setCurrent_path(const string &current_path) {
        fileSystem::current_path = current_path;
    }

    tomFile *getRoot() const {
        return root;
    }

    void setRoot(tomFile *root) {
        fileSystem::root = root;
    }
};


#endif //FILESYSTEM_FILESYSTEM_H
