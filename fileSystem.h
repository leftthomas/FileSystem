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
     * 用户鉴权,用来判断user是否有权访问或操作此目录或文件
     * 0:无权限
     * 1:只读
     * 2:读写
     */
    int authUser(string username, tomFile *file) {
        map<string, string>::iterator l_it;
        l_it = file->getPermissions().find(username);
        //没找到此用户
        if (l_it == file->getPermissions().end()) {
            //找下everyone
            l_it = file->getPermissions().find("everyone");
            if (l_it == file->getPermissions().end()) {
                return 0;
            } else {
                if (l_it->second == "x")
                    return 0;
                else if (l_it->second == "r")
                    return 1;
                else if (l_it->second == "rw")
                    return 2;
            }
        }
        else {
            if (l_it->second == "x")
                return 0;
            else if (l_it->second == "r")
                return 1;
            else if (l_it->second == "rw")
                return 2;
        }
        return true;
    }


    /**
    * 创建文件系统函数,初始化
    */
    void init() {
        //指定root文件的权限
        map<string, string> rootp;
        rootp.insert(map<string, string>::value_type("root", "rw"));
        //根节点没location,parent
        tomFile _root = tomFile("dir", "", "/", rootp, 0);
        root = &_root;
        current_path = "/";
        //配置文件
        tomFile config = tomFile("file", "/", "config.txt", rootp, &_root);
        //设置配置文件里面的用户数据
        config.setContent("root 123456;");
        addFile(&config, &_root, "root");
        //home文件夹
        tomFile home = tomFile("dir", "/", "home", rootp, &_root);
        addFile(&home, &_root, "root");
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
        if (parent->getType() != "dir")
            return 4;
        else if (authUser(username, parent) == 0) {
            return 0;
        }
        else if (authUser(username, parent) == 1) {
            return 1;
        }
        else if (authUser(username, parent) == 2) {
            for (int i = 0; i < parent->getChildren().size(); ++i) {
                if (parent->getChildren()[i]->getName() == file->getName()) {
                    return 2;
                }
            }
            //表示没有找到同名文件,这时候可以添加了
            parent->getChildren().push_back(file);
        }
        return 3;
    }


    void printq() {
        cout << current_path << root->getName() << root->getChildren()[0]->getName() <<
        root->getChildren()[1]->getName() << endl;
    }
};


#endif //FILESYSTEM_FILESYSTEM_H
