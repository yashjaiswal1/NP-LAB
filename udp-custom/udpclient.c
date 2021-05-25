#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
int main()
{
	int sock, bytes_recv;
	struct sockaddr_in server_addr;
	char recv_data[1024], send_data[1024];
	char client_reply[100];
	char close_keyword[] = "close";
	struct hostent *host;
	host = gethostbyname("127.0.0.1");
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6119);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int n, len;
	while (1)
	{
		printf("\nEnter data to be sent to the server: \n");
		gets(client_reply);

		if (strcmp(client_reply, close_keyword) == 0)
		{
			break;
		}

		sendto(sock, (const char *)client_reply, strlen(client_reply),
			   0, (const struct sockaddr *)&server_addr,
			   sizeof(server_addr));
		printf("Message delivered\n");

		n = recvfrom(sock, (char *)recv_data, 1024,
					 0, (struct sockaddr *)&server_addr,
					 &len);
		recv_data[n] = '\0';
		printf("\nServer : %s\n", recv_data);
	}
	close(sock);
	return 0;
	// if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	// {
	// 	perror("connect");
	// 	exit(1);
	// }
	// printf("send Filename to send\n");
	// gets(send_data);

	// if (strcmp(send_data, "q") != 0)
	// 	send(sock, send_data, strlen(send_data), 0);

	// while ((bytes_recv = recv(sock, recv_data, 1024, 0)) > 0)
	// {
	// 	recv_data[bytes_recv] = '\0';
	// 	//printf("%s\n\n", recv_data);
	// 	//if(strcmp(recv_data,"q")==0)
	// 	//	{
	// 	//	close(sock);
	// 	//	break;
	// 	//	}
	// 	printf("%s\n", recv_data);
	// }
	// close(sock);
	// return 0;
}
