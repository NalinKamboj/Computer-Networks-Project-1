#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>

#include "Server_info.h"

std::string http_parse(char* buf);
std::string http_response(std::string file);

int main(int argc, char** argv)
{
    //Server_info server_info(argc, argv);
    //std::cout << server_info.getname() << server_info.getport() << server_info.getdir() << std::endl;
   
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(40000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }

    std::cout << "listening " << std::endl;
    if(listen(sockfd, 10) == -1){
        perror("listen");
        return 2;
    }


    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);

    
    std::cout << "client fd: " << clientSockfd << std::endl;

    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Accept a connection from: " << ipstr << ":" <<
    ntohs(clientAddr.sin_port) << std::endl;

    char buf[256] = {0};
    std::stringstream ss;

    memset(buf, '\0', sizeof(buf));

    if (recv(clientSockfd, buf, 256, 0) == -1) {
      perror("recv");
      return 5;
    }
    std::cout << "Full buffer: " << buf << std::endl;
    std::cout << "parsed  file: " << http_parse(buf) << std::endl;

    if (send(clientSockfd, buf, 20, 0) == -1) {
      perror("send");
      return 6;
    }

    ss.str("");

    close(sockfd);
    return 0;
}

std::string http_parse(char* buf){
    char ret_file[256];
    memset(ret_file, '\0', sizeof(ret_file));
    int n=0;
    
    buf = buf + 4;
    
    while(*buf !=  ' '){
      ret_file[n] = *buf;
      n++;
      buf++;
    }


    return ret_file;
}

std::string http_response(string file){

}