#include "Client_request.h"
#include <string.h>

Client_request::Client_request(int argc, char** argv){
    argv[1] = argv[1] + 7;

    char buffer[64];
    int n = 0;
    memset(buffer, '\0', 64);


    while(*argv[1] != ':')
    {
        buffer[n] = *argv[1];
        n++;
        argv[1]++;
    }
    *argv[1]++;
    strcpy(server_name, buffer);
    n=0;
    memset(buffer, '\0', 64);


    while(*argv[1] != '/')
    {
        buffer[n] = *argv[1];
        n++;
        argv[1]++;
    }
    server_port = atoi(buffer);
    n=0;


    
    strcpy(file_name, argv[1]);

    //std::cout << server_name << std::endl << server_port << std::endl << file_name << std::endl;

}

Client_request::Client_request(){
    std::cout<< "no url given";
}

char* Client_request::getFile_name(){
    return file_name;
}

char* Client_request::getServer_name(){
    return server_name;
}

int* Client_request::getServer_port(){
    return &server_port;
}


