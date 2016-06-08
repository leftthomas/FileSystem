//
// Created by 任豪 on 16/6/8.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <string>
#include "fileSystem.h"

using namespace std;

class fileSystem {


public:
    /**
     * 用户鉴权,用来判断user是否有权访问或操作此目录或文件
     */
    static bool authUser(string username, string filename) {
        //TODO
        return true;

    }
};


#endif //FILESYSTEM_FILESYSTEM_H
