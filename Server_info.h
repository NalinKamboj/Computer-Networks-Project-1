#include <iostream>

class Server_info
{
private:
    char *name;
    int  port;
    char *dir;

public:
    Server_info(int, char**);
    Server_info();
    char* getname();
    int  getport();
    char* getdir();
};