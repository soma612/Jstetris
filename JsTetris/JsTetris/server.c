#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#ifndef __linux__
#pragma comment(lib,"ws2_32.lib") 
#include<WinSock2.h>
#include<Windows.h>
#else
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#endif


#define PORT 12345

int server() {
	SOCKET sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int len, addr_len, recv_len;

#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("소켓 생성 실패\n");
		return 0;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("소켓 바인드 실패\n");
		return 1;
	}

	if (listen(sock, 5) < 0) {
		printf("소켓 리슨 실패\n");
		return 1;
	}

	addr_len = sizeof(client_addr);

	printf("waiting for client..\n");

	while ((client_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len)) > 0) {
		printf("client ip : %s\n", inet_ntoa(client_addr.sin_addr));

		if ((recv_len = recv(client_sock, buffer, 1024, 0)) < 0) {
			printf("recv 실패\n");
			break;
		}

		buffer[recv_len] = '\0';

		printf("received data: %s\n", buffer);

		send(client_sock, buffer, strlen(buffer), 0);

		closesocket(client_sock);
	}

#ifndef __linux__
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif
	return 0;
}

