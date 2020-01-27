#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <limits.h>

void error_socket_open()	//send error message when fail to open the socket and exit with code 1
{
	printf("Error on opening socket.\n");
	exit(1);
}

void error_read()	//send error message when fail to read from the socket and exit with code 4
{
	printf("Error on reading from socket.\n");
	exit(4);
}

void error_write()	//send error message when fail to write to the socket and exit with code 5
{
	printf("Error on writing to socket.\n");
	exit(5);
}

void error_connect()	//send error message when fail to connect with server and exit with code 6
{
	printf("Error on connecting.\n");
	exit(6);
}

void allocate_error()
{
	printf("Unable to allocate memory.\n"); 	//error when allocate memory with exit code -1 
	exit(-1);
}

char *prompt_unlimit(const char *mesg) 	//unlimited prompt function to use malloc and realloc to make enough space to store string and prompt
{
	int size = 10; 	//initial size = 10
	char *buffer = malloc(sizeof(char) * size); 	//allocate the string buffer
	if(buffer == NULL)
	{
		allocate_error(); 	//check allocate memory
		return NULL;
	}

	printf("%s", mesg); 	// print the prompt

	int position = 0, out_number = 0, scan_char_number = 0; 	//position to repersent position in buffer, out_number to check if can exit the loop, scan_char_number to sum the input text length
	do
	{
		if (scan_char_number + 1 > size) 	//if size is not enough, realloc to get a bigger space
		{
			size = size + 10;
			buffer = realloc(buffer, size);
			if(buffer == NULL)
			{
				allocate_error(); 	//check allocate memory
				return NULL;
			} 
		}

		char tmp;
		scanf("%c", &tmp); 	//scan the input text by element
		scan_char_number++;
		if(tmp == '\n') 	// Pressed return
		{
			buffer[position] = '\0';   // Add nul byte at current location
			out_number = 1;
			return buffer;
		}
		else 	// Pressed a different key
		{
			buffer[position] = tmp; 	//Add the char at current location
			position++;
		}
	} while(out_number == 0);
	return NULL;
}

int read_char(const char *mesg, char **text)
{
	*text = prompt_unlimit(mesg);
	if(*text[0] == '\0')
	{
		return 0;	//return 0 if text is empty
	}
	return 1; 	//return 1 if not empty
}

int check_int(int *value, char *argument)
{
	char *endptr;
	long v = strtol(argument, &endptr, 10);
	if(endptr == argument) 	// error in converting to a number
	{
		return 0; 	//return 0 to say error in converting to a number
	}
	else 	// got a number, return it if within int bounds
	{
		if(v > INT_MAX || v < INT_MIN)
		{
			return 0;
		}
		else
		{
			*value = (int)v;
			if (v < 0)
			{
				return -1;
			}
			else
			{
				return 1; 	//return 1 to say sucessfully in converting to a  non-negative number
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)	//if type only one argument, prompt to type ip address
	{
		printf("Please enter server ip address.\n");
	}
	else
	{
		int sockfd, n;	// declare necessary variables
		char sendline[15000];
		struct sockaddr_in servaddr; // socket address struct

		sockfd = socket(AF_INET, SOCK_STREAM, 0);	// create a socket with the appropriate protocol
		if (sockfd < 0)
		{
			error_socket_open();	//if fail to open the socket, call error_socket_open() to prompt and exit
		}

		bzero(&servaddr, sizeof servaddr);	//clear the servaddr

		servaddr.sin_family = AF_INET;		//use IPv4 network protocols
		servaddr.sin_port = htons(12108);	//use port 12108

		inet_pton(AF_INET, argv[1], &(servaddr.sin_addr));	//convert addresses from text to binary form

		char str[15000];	//declare variable for read from socket

		if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)	//connect through the socket
		{
			error_connect();	//if fail to connect, call error_connect() to prompt and exit
		}
		printf("You are connected to the server.\n");	//if successful, print to prompt connect to server

		bzero(str, 15000);		//read the welcome message and menu from the server
		if (read(sockfd, str, 15000) < 0)
		{
			error_read();	//if fail to read, call error_read() to prompt and exit
		}
		printf("[Server Message]: %s\n", str);	//print the message received

		char *command;	//declare necessary variables
		do
		{
			int read_return = read_char("[Your command]: ", &command);	//read user input command to select functions

			bzero(sendline, 2);	//clear string every loop for new command
			if (strcmp(command, "GET TIME") == 0)	//if input "GET TIME", send "-2" to server
			{
				strcpy(sendline, "-2");
			}
			else if(strcmp(command, "GET IP") == 0)	//if input "GET IP", send "-3" to server
			{
				strcpy(sendline, "-3");
			}
			else if (strcmp(command, "GET SPACE") == 0)	//if input "GET SPACE", send "-4" to server
			{
				strcpy(sendline, "-4");
			}
			else if (strcmp(command, "GET MEMORY") == 0)	//if input "GET MEMORY", send "-5" to server
			{
				strcpy(sendline, "-5");
			}
			else if (strcmp(command, "GET SYS") == 0)	//if input "GET SYS", send "-6" to server
			{
				strcpy(sendline, "-6");
			}
			else if (strcmp(command, "GET ECHO") == 0)	//if input "GET ECHO", send "-7" to server
			{
				strcpy(sendline, "-7");
			}
			else if (strcmp(command, "GET CPU") == 0)	//if input "GET CPU", send "-8" to server
			{
				strcpy(sendline, "-8");
			}
			else if (strcmp(command, "QUIT") == 0)	//if input "QUIT", break the while loop
			{
				break;
			}
			else
			{
				if (strncmp(command, "FILE ", 5) == 0)	//check if is "FILE x"
				{
					char *command_split = strtok(command, " ");	//split the string and get characters after "FILE "
					command_split = strtok(NULL, " ");
					int file_number;
					int is_int = check_int(&file_number, command_split);	//check if is integer, if is, store it

					if (is_int == 1)	//if left string is integer, send the line number to server
					{
						strcpy(sendline, command_split);
					}
					else
					{
						strcpy(sendline, "0");	//if not, send "0" to represent invalid command
					}
				}
				else
				{
					strcpy(sendline, "0");
				}
			}

			if (write(sockfd, sendline, strlen(sendline) + 1) < 0)	//write sendline message to server
			{
				error_write();	//if fail to write, call error_write() to prompt and exit
			}

			bzero(str, 15000);	//clear and read return message from server
			if (read(sockfd, str, 15000) < 0)
			{
				error_read();	//if fail to read, call error_read() to prompt and exit
			}
			printf("[Server Message]: %s\n", str);	//print the message received
		}while(strcmp(command, "QUIT") != 0);

		free(command);	//free memory for command
		close(sockfd);	//close the socket

		printf("You have now disconnected from the server.\n");	//prompt to disconnected from the server
	}
}
