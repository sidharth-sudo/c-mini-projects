#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<unistd.h>
#include <netinet/in.h>

 int main(){
      
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr = {
     AF_INET,
     0x901f,
     0
    };
    
    bind(socket_fd,(sockaddr*)&addr,sizeof(addr));
    listen(socket_fd,10);
    int client_fd = accept(socket_fd,0,0);
    char buffer[256]={0};
    recv(client_fd,buffer,256,0);

    // GET /file.html ....
    char* f = buffer + 5; //get to the file
    *strchr(f,' ')=0;

    int open_fd = open(f,O_RDONLY);

    sendfile(client_fd,open_fd,0,256);
    close(open_fd);
    close(client_fd);
    close(socket_fd);
    return 0;
}

