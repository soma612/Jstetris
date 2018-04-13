#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef __xlinux__
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<Windows.h>
#include "SingleMode.h"
#include "MultiMode.h"

#else
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#endif

#define PORT 12345
HANDLE client_send;
HANDLE client_recv;

SOCKET sock;
struct sockaddr_in addr, client_addr;
char sendBuffer[1024];
char recvBuffer[1024];
int len, addr_len, recv_len;
int mod = MOD_WAIT;

int CreceiveData() {
	while (isConnected) {
		recv_len = recv(sock, recvBuffer, 1024, 0);
		if (recv_len < 0) return 0;
		recvBuffer[recv_len] = '\0';
		if (mod == MOD_WAIT) {
			printf("�ٸ� ����� ������ ��ٸ��� ��.. ");
			if (strcmp(recvBuffer, "ok") == 0) {
				clrscr();
				printf("��� ���� �Ϸ�! ������ �����մϴ�.");
				delay(2000);
				initGame();
			}
		}
		else if (mod == MOD_GAME) {
			printf("%s\n", recvBuffer);
		}
	}
	return 0;
}

int CsendData() {
	while (isConnected) {
		//printf("������ �޼��� : ");
		//scanf_s("%s", sendBuffer, sizeof(sendBuffer));
		char ch = _getch();
		sprintf_s(sendBuffer, sizeof(sendBuffer), "%d", ch);

		send(sock, sendBuffer, strlen(sendBuffer), 0);
	}
	return 0;
}

int client() {
	clrscr();
	printf("���� ip : 127.0.0.1\n");
	char ip[200] = "127.0.0.1";
	//scanf_s("%s",ip, sizeof(ip));
	
#ifndef __linux__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("���� ���� ����\n");
		return 1;
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(PORT);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("���� ���� ����\n");
		return 1;
	}
	else {
		printf("���� ����\n");
		client_recv = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)CreceiveData, NULL, 0, NULL);
		client_send = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)CsendData, NULL, 0, NULL);
	}
	
	WaitForSingleObject(client_recv, INFINITE);
	WaitForSingleObject(client_send, INFINITE);

#ifndef __linux__
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif
	return 0;
}
