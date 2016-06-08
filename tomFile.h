//
// Created by 任豪 on 16/6/8.
// 自定义文件类(文件和目录统一为此类,通过type标识)
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include <string>
#include <map>
#include <time.h>

using namespace std;

class tomFile {
private:
    string type;
    //种类,用来标记是文件夹还是文件、其他可执行文件等
    long size;
    //大小,以字节为单位计算
    string location;
    //位置
    bool locked;
    //锁定情况,在write操作时需要设置
    time_t createTime;
    //创建时间,在显示的时候需要转为字符串
    time_t modifyTime;
    //修改时间,同上
    string name;
    //名称
    //权限,此为一个map,标记>=1种权限使用者(everyone、当前用户、其他用户...),权限种类(读与写rw、无访问权限x、只读r)
    map<string, string> permissions;

public:
    /**
     * 指定permissions的构造函数
     */
    tomFile(const string &type, const string &location, const string &name, const map<string, string> &permissions)
            : type(type), location(location), name(name), permissions(permissions) {
        size = 0;//刚创建的时候大小为 0 byte
        locked = false;//默认没锁定
        time(&createTime);//指定为当前系统时间,下同
        time(&modifyTime);
    }

    /**
     * 默认不指定permissions的构造函数
     */
    tomFile(const string &type, const string &location, const string &name) : type(type), location(location),
                                                                              name(name) {
        size = 0;//刚创建的时候大小为 0 byte
        locked = false;//默认没锁定
        time(&createTime);//指定为当前系统时间,下同
        time(&modifyTime);
        permissions.insert(map<string, string>::value_type("everyone", "rw"));//默认创建的文件为所有人可读可写
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

    void setPermissions(const map<string, string> &permissions) {
        tomFile::permissions = permissions;
    }

    long getSize() const {
        return size;
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

    bool isLocked() const {
        return locked;
    }

    void setLocked(bool locked) {
        tomFile::locked = locked;
    }

    time_t getCreateTime() const {
        return createTime;
    }

    void setCreateTime(time_t createTime) {
        tomFile::createTime = createTime;
    }

    time_t getModifyTime() const {
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
};


#endif //FILESYSTEM_FILE_H
