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
#include <netdb.h>

#include "Client_request.h"

std::string GET_request(Client_request Client_request);

int main(int argc, char** argv)
{
  Client_request user_request(argc, argv);
  std::cout << "Starting client\n";
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(*user_request.getServer_port());   
  //std::cout << user_request.getServer_name() << std::endl << *user_request.getServer_port() << std::endl << user_request.getFile_name() << std::endl;
  serverAddr.sin_addr.s_addr = inet_addr(inet_ntop(AF_INET, &(serverAddr.sin_addr), user_request.getServer_name(), INET_ADDRSTRLEN));
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

  


  // connect to the server
  if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    perror("connect");
    return 2;
  }
  std::cout << "D!\n";


  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
    perror("getsockname");
    return 3;
  }



  // send/receive data to/from connection
  std::string input;
  char buf[20] = {0};
  std::stringstream ss;
  input = GET_request(user_request);
  std::cout << input << std::endl;
  

  memset(buf, '\0', sizeof(buf));

  if (send(sockfd, input.c_str(), input.size(), 0) == -1) {
    perror("send");
    return 4;
  }


  if (recv(sockfd, buf, 20, 0) == -1) {
    perror("recv");
    return 5;
  }
  ss << buf << std::endl;

  ss.str("");
 


  
  close(sockfd);
   
  return 0;
}

std::string GET_request(Client_request Client_request)
{
  std::string get_string, temp_string;
  
  temp_string = Client_request.getFile_name();
  get_string = "GET " + temp_string + " HTTP/1.0 \r\n";

  return get_string;
}