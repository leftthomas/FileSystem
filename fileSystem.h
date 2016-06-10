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

    //这个函数只在初始化的时候调用不鉴权,其他时候调用都需要鉴权
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
     * 根据文件名找在此dir一层的文件
     */
    tomFile *findFileInDir(string filename, tomFile *dir) {
        if (dir == NULL || dir->getChildren().size() == 0)
            return NULL;
        else {
            for (int i = 0; i < dir->getChildren().size(); ++i) {
                if (dir->getChildren()[i]->getName() == filename)
                    return dir->getChildren()[i];
            }
        }
        return NULL;
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
        if (util::findIllegalCharacter(path, true)) {
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
        if (q == "r")
            cout << "you can read this file|dir only" << endl;
        else if (q == "rw")
            cout << "you can read or write this file|dir" << endl;
        else
            cout << "you have no access to this file|dir" << endl;
    }

    /**
     * ls命令,列出路径下的全部文件,可指定是否详细,含默认参数,不需要做鉴权,因为ls前提就是cd到了此目录,本身做了鉴权
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
                    showFileDetail(current_file->getChildren()[i], username);
                }
            }
        }
        else {
            cout << "please input the correct command,refer to 'ls+?'" << endl;
        }
    }


    /**
     * 显示文件的detail
     */
    void showFileDetail(tomFile *file, string username) {
        cout << file->getName() + "   " << file->getType() + "   " << authUser(username, file) + "   "
        << file->getCreateTime() + "   " << file->getModifyTime() + "   "
        << file->getSize() << "byte" << endl;
    }

    /**
     * file命令,显示某一个文件的详情,只能是当前路径下的文件,不需要鉴权
     */
    void file(string filename, string username) {
        if (util::findIllegalCharacter(filename, true))
            cout << "the filename|dirname is illegal" << endl;
        else {
            tomFile *file;
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + filename, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + filename, current_file);
            if (file != NULL) {
                showFileDetail(file, username);
            } else
                cout << "this file|dir is not existed" << endl;
        }
    }

    /**
     * read命令,显示某一个文件的内容,只能是当前路径下的文件,需要鉴权,可以是data/a.txt,b.txt形式
     */
    void read(string filename, string username) {
        if (util::findIllegalCharacter(filename, true))
            cout << "the filename is illegal" << endl;
        else {
            tomFile *file;
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + filename, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + filename, current_file);
            if (file != NULL) {
                if (file->getType() == "dir") {
                    cout << "it's a dir,not a file" << endl;
                } else {
                    //鉴权
                    if (authUser(username, file) != "x") {
                        if (file->getContent() == "") {
                            cout << "this file is empty" << endl;
                        } else
                            cout << file->getContent() << endl;
                    } else {
                        cout << "you have no access to read this file" << endl;
                    }
                }
            } else
                cout << "this file is not existed" << endl;
        }
    }

    /**
     * write命令,其他情况同read
     */
    void write(string filename, string username) {
        if (util::findIllegalCharacter(filename, true))
            cout << "the filename is illegal" << endl;
        else {
            tomFile *file;
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + filename, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + filename, current_file);
            if (file != NULL) {
                if (file->getType() == "dir") {
                    cout << "it's a dir,not a file" << endl;
                } else {
                    //鉴权
                    if (authUser(username, file) == "rw") {
                        //write
                        cout << "===here are the contents of this file,you can append some other words to it===" <<
                        endl;
                        cout << file->getContent() << endl;
                        cout << "input:";
                        string s;
                        getline(cin, s);
                        file->setContent(file->getContent() + s);
                    } else {
                        cout << "you have no access to write this file" << endl;
                    }
                }
            } else
                cout << "this file is not existed" << endl;
        }
    }

    /**
     * mkfile命令,有两种形式,一种指定权限,一种不指定,首先自身权限是rw,指定的权限是其他人的访问权everyone,默认rw
     * 文件建立在当前路径下,需要鉴权,得看current_file是否可写
     */
    void mkfile(string filename, string username, string permission = "rw") {
        //只有dir下才可以新建文件,其实这个不可能....
        if (current_file->getType() == "dir") {
            //先判断当前目录是否可写,即鉴权
            if (authUser(username, current_file) == "rw") {
                //再判断文件名是否合法
                if (util::findIllegalCharacter(filename))
                    cout << "the filename is illegal" << endl;
                else {
                    //然后判断下本目录有没有重名文件
                    tomFile *file = findFileInDir(filename, current_file);
                    if (file == NULL) {
                        //最后判断下权限定义是否正确
                        if (permission != "r" && permission != "rw" && permission != "x")
                            cout << "the permission is illegal" << endl;
                        else {
                            file = new tomFile("file", current_file->getPath(), filename,
                                               pair<string, string>(username, "rw"), current_file);
                            //对非本用户设置权限
                            file->addPermissions(pair<string, string>("everyone", permission));
                            current_file->addChildren(file);
                        }
                    } else
                        cout << "the file already exists" << endl;
                }
            } else
                cout << "you have no access to make file in this dir" << endl;
        } else
            cout << "this path is a file,not a dir" << endl;
    }

    /**
     * mkdir命令,其他同上
     */
    void mkdir(string dirname, string username, string permission = "rw") {
        //只有dir下才可以新建目录
        if (current_file->getType() == "dir") {
            //先判断当前目录是否可写,即鉴权
            if (authUser(username, current_file) == "rw") {
                //再判断目录名是否合法
                if (util::findIllegalCharacter(dirname))
                    cout << "the dirname is illegal" << endl;
                else {
                    //然后判断下本目录有没有重名文件
                    tomFile *file = findFileInDir(dirname, current_file);
                    if (file == NULL) {
                        //最后判断下权限定义是否正确
                        if (permission != "r" && permission != "rw" && permission != "x")
                            cout << "the permission is illegal" << endl;
                        else {
                            file = new tomFile("dir", current_file->getPath(), dirname,
                                               pair<string, string>(username, "rw"), current_file);
                            //对非本用户设置权限
                            file->addPermissions(pair<string, string>("everyone", permission));
                            current_file->addChildren(file);
                        }
                    } else
                        cout << "the dir already exists" << endl;
                }
            } else
                cout << "you have no access to make dir in this dir" << endl;
        } else
            cout << "this path is a file,not a dir" << endl;
    }

    /**
  * rmfile命令,删除一个文件,只能是当前路径下的文件,需要鉴权,可以是data/a.txt,b.txt形式
  */
    void rmfile(string filename, string username) {
        if (util::findIllegalCharacter(filename, true))
            cout << "the filename is illegal" << endl;
        else {
            tomFile *file;
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + filename, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + filename, current_file);
            if (file != NULL) {
                if (file->getType() == "dir") {
                    cout << "it's a dir,not a file" << endl;
                } else {
                    //鉴权
                    if (authUser(username, file) == "rw") {
                        for (int i = 0; i < file->getParent()->getChildren().size(); ++i) {
                            if (file->getParent()->getChildren()[i]->getName() == file->getName()) {
                                file->getParent()->deleteChildren(i);
                                break;
                            }
                        }
                        delete file;
                    } else {
                        cout << "you have no access to remove this file" << endl;
                    }
                }
            } else
                cout << "this file is not existed" << endl;
        }
    }

    /**
 * 只用在rmdir时,用来判断是否此目录下的文件都有权限删除
 */
//    bool authAll(string username,tomFile *dir){
//        if (dir->getPermissions().find(username) == dir->getPermissions().end()) {
//            //找下everyone
//            if (dir->getPermissions().find("everyone") == dir->getPermissions().end())
//                return false;
//            else{
//                if(dir->getPermissions().find("everyone")->second!="rw")
//                    return false;
//                else
//                    for (int i = 0; i < dir->getChildren().size(); ++i) {
//                         authAll(username,dir->getChildren()[i]);
//                    }
//            }
//
//        }
//        else{
//            if(dir->getPermissions().find(username)->second!="rw")
//                return false;
//        }
//    }

    /**
     * rmdir命令,删除一个目录,只能是当前路径下的目录,需要鉴权,可以是data/a,b形式
     * 特别需要注意的是删除时必须目录下的全部文件都有权才可以删除
     */
    void rmdir(string dirname, string username) {
        if (util::findIllegalCharacter(dirname, true))
            cout << "the dirname is illegal" << endl;
        else {
            tomFile *file;
            //注意一下这种特殊情况,这是根节点的情况
            if (current_file == root)
                file = findFileByPath(current_file->getPath() + dirname, current_file);
            else
                file = findFileByPath(current_file->getPath() + "/" + dirname, current_file);
            if (file != NULL) {
                if (file->getType() == "file") {
                    cout << "it's a file,not a dir" << endl;
                } else {
                    //TODO 这个与其它不一样 鉴权
                    if (authUser(username, file) == "rw") {
                        for (int i = 0; i < file->getParent()->getChildren().size(); ++i) {
                            if (file->getParent()->getChildren()[i]->getName() == file->getName()) {
                                file->getParent()->deleteChildren(i);
                                break;
                            }
                        }
                        //删除所有节点
                        destroy(file);
                    } else {
                        cout << "you have no access to remove this dir" << endl;
                    }
                }
            } else
                cout << "this dir is not existed" << endl;
        }
    }


};


#endif //FILESYSTEM_FILESYSTEM_H
