#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	FILE *fptr;
	int sock, connected, bytes_recv;
	char ch, send_data[1024], recv_data[1024];
	char server_reply[100];
	int sin_size, flag = 0;
	char close_keyword[] = "close";

	// Creating a socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6119);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Binding the socket address to the server
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("unable to bind");
		exit(1);
	}

	int len, n;
	while (1)
	{
		// Initializes client address with zero values
		memset(&client_addr, 0, sizeof(client_addr));

		len = sizeof(client_addr);

		n = recvfrom(sock, (char *)recv_data, 1024,
					 0, (struct sockaddr *)&client_addr,
					 &len);
		recv_data[n] = '\0';

		printf("Client : %s\n", recv_data);

		printf("\nEnter data to be sent to the client: \n");
		gets(server_reply);

		if (strcmp(server_reply, close_keyword) == 0)
		{
			break;
		}

		sendto(sock, (const char *)server_reply, strlen(server_reply),
			   0, (const struct sockaddr *)&client_addr,
			   len);
		printf("Message Delivered\n");
	}
	// if (listen(sock, 5) == -1)
	// {
	// 	perror("lsten");
	// 	exit(1);
	// }

	// printf("tcp server is waiting for client on port XXXX\n");
	// sin_size = sizeof(struct sockaddr_in);
	// connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

	// while (1)
	// {

	// 	bytes_recv = recv(connected, recv_data, 1024, 0);
	// 	recv_data[bytes_recv] = '\0';

	// 	printf("reciecved data is %s\n\n\n", recv_data);

	// 	fptr = fopen(recv_data, "r");
	// 	if (fptr == NULL)
	// 	{
	// 		strcpy(send_data, "FILE");
	// 		send(connected, send_data, strlen(send_data), 0);
	// 	}
	// 	ch = fgetc(fptr);

	// 	while (ch != EOF) //this loop searches the for the current word
	// 	{
	// 		// fscanf(fptr,"%s",send_data);
	// 		send_data[flag] = ch;
	// 		flag++;
	// 		ch = fgetc(fptr);
	// 		//send(connected,send_data,strlen(send_data),0);
	// 	}
	// 	send(connected, send_data, strlen(send_data), 0);
	// 	//send_data[0] = 'q';
	// 	//strcpy(send_data,"q");
	// 	//send(connected,send_data,strlen(send_data),0);
	// 	close(connected);
	// 	break;
	// }
}
