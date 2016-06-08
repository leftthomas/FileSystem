#include <cstdio>
#include <cstring>

#define SizeOfUserName 255
#define SizeOfUser 10
#define SizeOfFile 10
#define SizeOfCommand 255
#define SizeOfFileName 255
char UserName[SizeOfUser][SizeOfUserName];
long User;
struct InfoOfFile {
    char Name[SizeOfFileName];
    bool safe[3];
    //Read,Write,Execute
    long status;//ready,open;
} UFD[SizeOfUser][SizeOfFile];
long num[SizeOfUser];
long num_open[SizeOfUser];
char z[4] = "rwe";

void ls()//列文件目录
{
    char tmp[100];
    long i, j;
    printf("%20s%20s%20s\n", "Name", "Property", "Status");
    for (i = 0; i < num[User]; i++) {
        printf("%20s", UFD[User][i].Name);
        for (j = 0; j < 3; j++) {
            if (UFD[User][i].safe[j]) {
                tmp[j] = z[j];
            }
            else {
                tmp[j] = '-';
            }
}
        tmp[3] = '\0';
        printf("%20s", tmp);
        if (UFD[User][i].status) {
            printf("%20s\n", "Opened");
        }
        else {
            printf("%20s\n", "Ready");
        }
    }
    printf("%ld file(s) in total\n", num[User]);
}

long login()//切换用户
{
    long i;
    char NameInput[SizeOfUserName];
    do {
        printf("Please input your ID:");
        scanf("%s", NameInput);
        i = 0;
        while (i < SizeOfUser && strcmp(NameInput, UserName[i]) != 0) {
            i++;
        }
        if (strcmp(NameInput, UserName[i]) != 0) {
            printf("Bad UserID.\n");
        }
    } while (strcmp(NameInput, UserName[i]) != 0);
    return i;
}

void init()//初始化
{
    long i, j, k;
    char tmp[4];
    memset(num_open, 0, sizeof(num_open)); //读入用户名列表
    freopen("record.txt", "r", stdin);
    for (i = 0; i < SizeOfUser; i++) {
        scanf("%s", UserName[i]);
    }
//读入文件列表
    for (i = 0; i < SizeOfUser; i++) {
        scanf("%ld", &num[i]);
        for (j = 0; j < num[i]; j++) {
            scanf("%s%s", UFD[i][j].Name, tmp);
            for (k = 0; k < 3; k++) {
                if (tmp[k] == '-') {
                    UFD[i][j].safe[k] = 0;
                }
                else {
                    UFD[i][j].safe[k] = 1;
                }
            }
            UFD[i][j].status = 0;
        }
    }
    freopen("con", "r", stdin);
    User = login();
    ls();
}

void create()//创建文件
{
    long i;
    char filename[SizeOfFileName];
    char prop[128];
    if (num[User] == SizeOfFile)//保存已满
    {
        printf("Failed... You can only save %ld files\n", SizeOfFile);
        return;
    }
    printf("Input filename and property>");
    scanf("%s%s", filename, prop);
    for (i = 0; i < num[User]; i++) {
        if (strcmp(filename, UFD[User][i].Name) == 0)//重名
        {
            printf("Failed... File %s already exists\n", filename);
            return;
        }
    }
    strcpy(UFD[User][num[User]].Name, filename);
    for (i = 0; i < 3; i++)//设置属性
    {
        if (prop[i] == '-') {
            UFD[User][num[User]].safe[i] = 0;
        }
        else {
            UFD[User][num[User]].safe[i] = 1;
        }
    }
    UFD[User][num[User]].status = 0;
    ++num[User];
    printf("Success!\n");
}

void open()//打开文件
{
    long i;
    char filename[SizeOfFileName];
    if (num_open[User] == 5) {
        printf("Failed... You have already opened 5 files\n"); //打开文件数已到上限
        return;
    }
    printf("Input filename>");
    scanf("%s", filename);
    for (i = 0; i < num[User]; i++) {
        if (strcmp(filename, UFD[User][i].Name) == 0) {
            if (UFD[User][i].status == 0)//文件未占用
            {
                UFD[User][i].status = 1;
                num_open[User]++;
                printf("Success!\n");
            } else//已被打开
            {
                printf("Failed... File %s is already opened\n", filename);
            }
            return;
        }
    }
    printf("Failed... No such file\n");
    void close()//关闭文件
    {
        long i;
        char filename[SizeOfFileName];
        printf("Input filename>");
//找不到文件
    }
}

scanf("%s",filename);
for (
i = 0;
i<num[User];
i++) {
if (
strcmp(filename, UFD[User][i]
.Name)==0) {
if (UFD[User][i].status==1)//成功
{
UFD[User][i].
status = 0;
num_open[User]--; printf("Success!\n");
} else//文件并未打开
{
printf("Failed... File %s is not opened\n",filename); }
return; }
}
printf("Failed... No such file\n");

void read()//读文件
{
    long i;
    char filename[SizeOfFileName];
    printf("Input filename>");
    scanf("%s", filename);
    for (i = 0; i < num[User]; i++) {
//找不到文件
        if (strcmp(filename, UFD[User][i].Name) == 0) {
            if (UFD[User][i].safe[0] == 0)//属性设置为不可读
            {
                printf("Failed... File %s is not readable\n", filename);
                return;
            }
            if (UFD[User][i].status == 1)//文件已打开
            {
                printf("Failed... File %s is already opened\n", filename);
                return;
            }
            printf("Success!\n");//成功 return;
        }
    }
    printf("Failed... No such file\n");//找不到文件
}

void write()//写文件
{
    long i;
    char filename[SizeOfFileName];
    printf("Input filename>");
    scanf("%s", filename);
    for (i = 0; i < num[User]; i++) {
        if (strcmp(filename, UFD[User][i].Name) == 0) {
            if (UFD[User][i].safe[1] == 0)//属性设置为不可写
            {
                printf("Failed... File %s is not writable\n", filename);
                return;
            }
            if (UFD[User][i].status == 1)//已打开
            {
                printf("Failed... File %s is already opened\n", filename);
                return;
            }
            printf("Success!\n");//成功
            return;
        }
    }
    printf("Failed... No such file\n");//找不到文件
}

void mydelete()//删除文件
{
    long i, j;
    char filename[SizeOfFileName];
    printf("Input filename>");
    scanf("%s", filename);
    for (i = 0; i < num[User]; i++) {
        if (strcmp(filename, UFD[User][i].Name) == 0) {
            if (UFD[User][i].status == 1)//文件正被打开
            {
                printf("Failed... File %s is already opened\n", filename);
                return;
            }
            num[User]--;
            for (j = i; j < num[User]; j++) {
                UFD[User][j] = UFD[User][j + 1];
            }
            printf("Success!\n");//成功
            return;
        }
    }
    printf("Failed... No such file\n");//找不到文件
}

void save()//保存本次信息
{
    FILE *fp = fopen("record.txt", "w");
    long i, j, k;
    char tt[4] = "rwe";
    char tmp[4];
//保存用户列表
    for (i = 0; i < SizeOfUser; i++) {
        fprintf(fp, "%s\n", UserName[i]);
    }
//保存文件列表
    for (i = 0; i < SizeOfUser; i++) {
        fprintf(fp, "%ld\n", num[i]);
        for (j = 0; j < num[i]; j++) {
            for (k = 0; k < 3; k++) {
                if (UFD[i][j].safe[k]) {
                    tmp[k] = tt[k];
                }
                else {
                    tmp[k] = '-';
                }
            }
            tmp[3] = 0;
            fprintf(fp, "%s %s\n", UFD[i][j].Name, tmp);
        }
    }
    printf("Success!\n");//成功
    fclose(fp);
}

void work()//交互主函数
{
    bool over = 0;
    char command[SizeOfCommand];
    while (!over) {
        printf("%s>", UserName[User]);
        scanf("%s", command);
        if (strcmp(command, "login") == 0) {
            User = login();
            ls();
            continue;
        }
        if (strcmp(command, "bye") == 0) {
            printf("Byebye.\n");
            over = 1;
            continue;
        }
        if (strcmp(command, "ls") == 0 || strcmp(command, "dir") == 0) {
            ls();
            continue;
        }
        if (strcmp(command, "create") == 0) {
            create();
            continue;
        }
        if (strcmp(command, "delete") == 0) {
            mydelete();
            continue;
        }
        if (strcmp(command, "open") == 0) {
            open();
            continue;
        }
        if (strcmp(command, "close") == 0) {
            close();
            continue;
        }
        if (strcmp(command, "read") == 0) {
            read();
            continue;
        }
        if (strcmp(command, "write") == 0) {
            write();
            continue;
        }
        if (strcmp(command, "save") == 0) {
            save();
            continue;
        }
        printf("Bad command.\n");
    }
}

int main() {
    init();
    work();
    return 0;
}