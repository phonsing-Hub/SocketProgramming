// 64028780
//https://www.geeksforgeeks.org/socket-programming-cc
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#define PORT 8081
int main(int argc, char const* argv[]){
	int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	openlog("echo", LOG_PID, LOG_USER);
 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET,
				//SO_REUSEADDR | SO_REUSEPORT, &opt,
                SO_REUSEADDR , &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    for(;;){
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen))< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read(new_socket, buffer,1024 - 1);				
	printf("%s\n", buffer);
	syslog(LOG_INFO,"%s\n",buffer);
    closelog();
	send(new_socket, buffer, strlen(buffer), 0);
	close(new_socket);

	FILE *file = fopen("/tmp/echo.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s: %s\n", strtok(buffer, " "), strtok(NULL, "\0"));
    fclose(file);
	memset(buffer, 0, sizeof(buffer));
    }
	close(server_fd);
	return 0;
}
