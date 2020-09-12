#include <conio.h>
#include <stdio.h>
#include "Socket.h"
#include "string_process.h"

void server_chat_func(char *buff_send, SOCKET client)
{
	memset(buff_send, 0, 256);
	printf_s("Server_chat: ");
	gets(buff_send);
	send(client, buff_send,250,0);
}

void server_recive_mess(char *buff_recive, SOCKET client)
{
	memset(buff_recive, 0, 256);
	recv(client, buff_recive, 250, 0);
	printf_s("%s\r\n", buff_recive);
}

int main()
{
	const int max_queue = 10;
	const int port = 9090;
	char begin_string[] = "Wellcome to chat room ^-^ \r\n1/Muon thoat truong trinh vui long go tu \"thoatkhoi\"\r\n2/Lua y moi tin nhan khong qua 250 tu\r\n3/Vui long doi phan hoi roi moi chat tiep\r\n";
	char* server_recive_buff = (char*)calloc(256,sizeof(char));
	char* server_send_buff = (char*)calloc(256, sizeof(char));
	char *search_key = (char*)calloc(30, sizeof(char));
	if (server_recive_buff == NULL || server_send_buff == NULL || search_key == NULL)
	{
		printf_s("cap phat bo nho bi loi!\r\n");
		exit(0);
	}
	
	search_key = "thoatkhoi";
	int search_len = Str_len(search_key);
	Socket_Server_Init(port);
	listen(s, max_queue);

	SOCKET new_connect = accept(s, NULL, NULL);
	send(new_connect,begin_string,sizeof(begin_string),0);
	int flag = 1;
	do {
		server_recive_mess(server_recive_buff,new_connect);
		if (find_SubStr_exit(server_recive_buff, search_key, search_len) == -1)
		{
			server_chat_func(server_send_buff, new_connect);
		}
		else {
			flag = 0;
		}
	} while (flag != 0);

	free(server_recive_buff);
	free(server_send_buff);
	return 0;
}