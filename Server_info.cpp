#include "Server_info.h"

Server_info::Server_info(int argc, char** argv){

    if(argc != 0)
    {
        name = argv[1];
        port = atoi(argv[2]);
        dir = argv[3];
    }    
}

Server_info::Server_info(){
        char hostname[] = "hostname";
        char directory[] = ".";
        name = hostname;
        port  = 40000;
        dir   =directory; 
    
}

char* Server_info::getname(){
    return name;
}

int Server_info::getport(){
    return port;
}

char* Server_info::getdir(){
    return dir;
}