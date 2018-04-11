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

int client2() {
	SOCKET sock;
	struct sockaddr_in addr;
	char buffer[1024];
	const char *msg = "hello! I'm Client";
	int recv_len;

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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//addr.sin_addr.s_addr = inet_addr("114.199.27.36");
	addr.sin_port = htons(PORT);

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("소켓 연결 실패\n");
		return 0;
	}

	if (send(sock, msg, strlen(msg), 0) < 0) {
		printf("소켓 전송 실패\n");
		return 0;
	}

	if ((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
		printf("소켓 수신 실패\n");
		return 0;
	}

	buffer[recv_len] = '\0';

	printf("recived data : %s\n", buffer);

#ifndef __linux__
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif

	return 0;
}

