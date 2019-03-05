#include <iostream>

class Client_request
{
private:
    char server_name[64];
    int server_port;
    char file_name[64];


public:
    Client_request(int, char**);
    Client_request();
    char* getServer_name();
    int*  getServer_port();
    char* getFile_name();
};