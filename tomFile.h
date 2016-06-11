//
// Created by 任豪 on 16/6/8.
// 自定义文件类(文件和目录统一为此类,通过type标识)
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include <string>
#include <map>
#include <time.h>
#include <vector>

using namespace std;

class tomFile {
private:
    //种类,用来标记是文件夹还是文件(file、dir)
    string type;
    //大小,以字节为单位计算
    //刚创建的时候大小,以178byte计算
    long size = 178;
    //位置
    string location;
    //创建时间,在显示的时候需要转为字符串
    time_t createTime;
    //修改时间,同上
    time_t modifyTime;
    //名称
    string name;
    //文件内容,只有file有这个,dir是没有的
    string content;
    //权限,此为一个map,标记>=1种权限使用者(everyone、当前用户、其他用户...),权限种类(读与写rw、无访问权限x、只读r)
    map<string, string> permissions;
    //记录父节点
    tomFile *parent;
    //记录位于其下的文件,用来建树和查询
    vector<tomFile *> children;

public:

/**
        * 指定permissions的构造函数
        */
    tomFile(const string &type, const string &location, const string &name, const pair<string, string> &permission,
            tomFile *parent) : type(type), location(location), name(name), parent(parent) {
        time(&createTime);//指定为当前系统时间,下同
        time(&modifyTime);
        content = "";//刚创建时无内容
        permissions.insert(permission);
    }

/**
     * 默认不指定permissions的构造函数
     */
    tomFile(const string &type, const string &location, const string &name, tomFile *parent) : type(type),
                                                                                               location(location),
                                                                                               name(name),
                                                                                               parent(parent) {
        time(&createTime);//指定为当前系统时间,下同
        time(&modifyTime);
        content = "";
        permissions.insert(map<string, string>::value_type("everyone", "rw"));//默认创建的文件为所有人可读可写

    }

    /**
     * 这个构造函数也是用在copy时,方便权限的直接复制
     */
    tomFile(const string &type, const string &location, const string &name, const map<string, string> &permission,
            tomFile *parent) : type(type), location(location), name(name), parent(parent) {
        //刚创建的时候大小,以178byte计算
        size = 178;
        time(&createTime);//指定为当前系统时间,下同
        time(&modifyTime);
        content = "";//刚创建时无内容
        permissions = permission;
    }


    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        tomFile::type = type;
    }


    const map<string, string> &getPermissions() const {
        return permissions;
    }

    long getSize() const {
        //简单的以content内容大小来计算
        return size + content.length();
    }

    void setSize(long size) {
        tomFile::size = size;
    }

    const string &getLocation() const {
        return location;
    }

    void setLocation(const string &location) {
        tomFile::location = location;
    }

    string getCreateTime() const {
        return ctime(&createTime);
    }

    time_t getCTime() const {
        return createTime;
    }

    void setCreateTime(time_t createTime) {
        tomFile::createTime = createTime;
    }

    string getModifyTime() const {
        return ctime(&modifyTime);
    }

    time_t getMTime() const {
        return modifyTime;
    }

    void setModifyTime(time_t modifyTime) {
        tomFile::modifyTime = modifyTime;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        tomFile::name = name;
    }

    const string &getContent() const {
        return content;
    }

    void setContent(const string &content) {
        tomFile::content = content;
    }

    const vector<tomFile *> &getChildren() const {
        return children;
    }

    tomFile *getParent() const {
        return parent;
    }

    void setParent(tomFile *parent) {
        tomFile::parent = parent;
    }

    /**
    * 这个函数要特殊注意,不能是set而是add,搞了好久,不然添加的话很麻烦
    */
    void addChildren(tomFile *child) {
        children.push_back(child);
    }

    /**
     * 移除一个child,用了种麻烦的方法,因为erase()方法会很奇葩出问题
     */
    void deleteChildren(int position) {
        vector<tomFile *> n;
        for (int i = 0; i < children.size(); ++i) {
            if (i != position)
                n.push_back(children[i]);
        }
        children = n;
    }

    /**
   * 这个函数也要特殊注意,不能是set而是add
   */
    void addPermissions(const pair<string, string> &permission) {
        permissions.insert(permission);
    }

    /**
     * 获取全路径,方便后面使用
     */
    string getPath() {
        //根节点下面的那些文件要注意一下,比较特殊,因为根节点的名字刚好是/
        if (parent == NULL) {
            return name;
        } else {
            if (parent->getLocation() != "")
                return location + "/" + name;
            else
                return location + name;
        }
    }

};


#endif //FILESYSTEM_FILE_H
