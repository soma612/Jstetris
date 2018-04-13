#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef __xlinux__
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<Windows.h>
#include "MultiPlay.h"
#include "mBlockEvent.h"
#include "mPrintInfo.h"
#include "MultiMode.h"
#else
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#endif

#define PORT 12345
HANDLE server_send;
HANDLE server_recv[4];
HANDLE server_accept;
SOCKET sock;
SOCKET client_sock[4];

boolean connectSw = FALSE;
int client_sock_count = 0;
int pcount = 0;
struct sockaddr_in addr, client_addr;
char sendBuffer[1024];
char recvBuffer[1024];
int len, addr_len, recv_len;

int acceptClient();
int sendData(char buffer[1024]);
int inputData();
int receiveData();
int playMultiGame();
void multiPlaying();
int mAutoDownBlock();
void mListenMsg();


int sendData(char buffer[1024]) {
	int i;
	for (i = 0; i < client_sock_count; i++) {
		send(client_sock[i], buffer, strlen(buffer), 0);
	}

	return 0;
}

int acceptClient() {
	while (pcount == client_sock_count + 1) {
		if ((client_sock[client_sock_count] = accept(sock, (struct sockaddr*)&client_addr, &addr_len)) > 0) {
			printf("client ip : %s client_sock : %d\n", inet_ntoa(client_addr.sin_addr), client_sock[client_sock_count]);
			server_recv[client_sock_count] = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)receiveData, NULL, 0, NULL);
		}
	}
	
}
int receiveData() {
	int client_num = client_sock_count;
	client_sock_count++;
	putixy(38, 0, client_sock_count+1);
	connectSw = TRUE;
	//printf("recevieData 의 client_num : %d\n", client_num);
	while (isConnected) {
		recv_len = recv(client_sock[client_num], recvBuffer, 1024, 0);
		if (recv_len < 0) return 0;
		recvBuffer[recv_len] = '\0';
		printf("%d,%s\n", client_num,recvBuffer);
		//sprintf_s(recvBuffer, sizeof(recvBuffer), "%d,%s\n", client_num, recvBuffer);
		sendData(recvBuffer);
	}
	return 0;
}

int inputData() {
	while (isConnected) {
		char ch = _getch();
		sprintf_s(sendBuffer, sizeof(sendBuffer), "%d", ch);
		//scanf_s("%s", sendBuffer, sizeof(sendBuffer));
		sendData(sendBuffer);
	}
	return 0;
}


int server(int playerCount) {
	pcount = playerCount;
#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("소켓 생성 실패\n");
		return 1;
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("바인드 실패\n");
		return 1;
	}
	if (listen(sock, 5) < 0) {
		printf("소켓 리슨 실패\n");
		return 1;
	}
	addr_len = sizeof(client_addr);
	clrscr();
	putsxy(0, 0, "상대방을 기다리는중.. 현재 접속자 수: 1");
	while (playerCount != client_sock_count + 1) {
		if ((client_sock[client_sock_count] = accept(sock, (struct sockaddr*)&client_addr, &addr_len)) > 0) {
			//printf("client ip : %s client_sock : %d\n", inet_ntoa(client_addr.sin_addr), client_sock[client_sock_count]);
			server_recv[client_sock_count] = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)receiveData, NULL, 0, NULL);
			while (!connectSw) { delay(1); }
			connectSw = FALSE;
		}
	}
	clrscr();

	putsxy(0, 0, "모두 접속 완료! 게임을 시작합니다.");
	sendData("ok");
	delay(2000);
	playMultiGame();

	//server_accept = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)acceptClient, NULL, 0, NULL);
	server_send = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)inputData, NULL, 0, NULL);
	WaitForSingleObject(server_accept, INFINITE);
	WaitForSingleObject(server_send, INFINITE);

#ifndef __linux__
	closesocket(sock);
	WSACleanup();
	#else
	close(sock);
	#endif
	return 0;
}

