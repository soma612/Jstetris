#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#ifndef __xlinux__
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

SOCKET sock, client_sock;
struct sockaddr_in addr, client_addr;
char buffer[1024];
const char *msg = "hello! I'm Client";
int len, addr_len, recv_len;
boolean isConnected = TRUE;

int testServer() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return 0;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) return 1;
	if (listen(sock, 5) < 0) return 1;

	addr_len = sizeof(client_addr);

	printf("waiting for client..\n");

	if ((client_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len)) > 0) {
		printf("client ip : %s\n", inet_ntoa(client_addr.sin_addr));
		while (isConnected) {
			scanf_s("전송할 메세지 : %s", buffer, sizeof(buffer));
			if (strcmp(buffer, "exit")) isConnected = FALSE;
			else send(client_sock, buffer, strlen(buffer), 0);	
		}
	}

	#ifndef __linux__
		closesocket(sock);
		WSACleanup();
	#else
		close(sock);
	#endif
	return 0;	
}

int testClient() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return 0;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) > 0) {
		while (isConnected) {
			//if (send(sock, msg, strlen(msg), 0) < 0) return 0;
			if ((recv_len = recv(sock, buffer, 1024, 0)) < 0) return 0;
			buffer[recv_len] = '\0';
			printf("수신받은 메세지 : %s\n", buffer);
		}	
	}
	#ifndef __linux__
		closesocket(sock);
		WSACleanup();
	#else
		close(sock);
	#endif
		return 0;
}
