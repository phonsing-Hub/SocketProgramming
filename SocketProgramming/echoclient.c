// 64028780
//https://www.geeksforgeeks.org/socket-programming-cc
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#define PORT 8081

int main(int argc, char const* argv[]){
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char res[100] = "";
	for (int i = 1; i < argc; ++i) {
            strcat(res, argv[i]);
            strcat(res, " ");	  
    }
	char buffer[1024] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	if (res[0] != '\0') {
        res[strlen(res) - 1] = '\0';
        send(client_fd, res, strlen(res), 0);
    }
	valread = read(client_fd, buffer, 1024 - 1); 						
	printf("%s\n", buffer);
	close(client_fd);
	return 0;
}
