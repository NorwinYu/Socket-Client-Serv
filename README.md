# Readme

This code is my assignment when I was studying **COMPUTER FUNDAMENTALS** at **University of Nottingham, Ningbo, CHINA** in 2016 as a second year undergraduate student. Because I was looking for a job to write a resume and backed up my school day code, the code was uploaded and made public on January 27, 2020.

Part of the code involves student ID, name, and specific server information has been changed, which may affect a small part of reading.

#CSF Coursework2 Report

Name:	************

ID:	************

2016/12/2

## Introduction

This is a report related to the code for **coursework 2** in CSF moudle. It is a **C** program implement a **client-server** information retrieval system using the **Linux** Berkeley Socket Application Programming Interface *API*. 

The server provide two information client can request from:

* contents of the text file
  - return the target line **content** of the file
* server information
  - return the current **date and time** of the server
  - return the **IP address** of the server
  - return the **hard disk** space of the server
  - return the **memory** information of the server
  - return the **OS/System** information(OS type, versions, etc) of the server
  - return the **network** information of the server
  - reruen the **CPU** information of the server



## Overview

To use the server successfully, it needs `client.c` for client , `serv.c` for server and  `test.txt` for finding the content. 



### Compile and start 

`client.c`  can be compiled with `gcc` , and let the client program name as `client` , and use command `./client xx.xxx.x.xx` to strat the client program. `xx.xxx.x.xx` is the IP address of the cs-linux server.

*compile:*	

```powershell
[xxxxxx@cs-linux ~]$ gcc client.c -o client
```

*start:*	

```powershell
[xxxxxx@cs-linux ~]$ ./client xx.xxx.x.xx
```



Also,  `serv.c` can be compiled  with `gcc` , and let the client program name as `serv` , and use command `./serv ` to strat the client program.

*compile:*	

```powershell
[xxxxxx@cs-linux ~]$ gcc serv.c -o serv
```

*start:*	

```powershell
[xxxxxx@cs-linux ~]$ ./serv
```



### Connect

#### socket basic konwledge

“*A **network socket** is an endpoint of a connection in a computer network. In Internet Protocol (IP) networks, these are often called **Internet sockets**. It is a handle that a program can pass to the networking application programming interface(API) to use the connection for receiving and sending data. Sockets are often represented internally as integers.* ” From  [Network socket](https://en.wikipedia.org/wiki/Network_socket).

Following is the diagram showing the complete Client and Server interaction. From [Unix Socket - Client Server Model](https://www.tutorialspoint.com/unix_sockets/client_server_model.htm)

![socket](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)



- To make a client
  - Create a socket with the **socket()** system call.
  - Connect the socket to the address of the server using the **connect()**system call.
  - Send and receive data. There are a number of ways to do this, but the simplest way is to use the **read()** and **write()** system calls as used in the code.
    ​
- To make a server
  - Create a socket with the **socket()** system call.
  - Bind the socket to an address using the **bind()** system call. For a server socket on the Internet, an address consists of a port number on the host machine.
  - Listen for connections with the **listen()** system call.
  - Accept a connection with the **accept()** system call. This call typically blocks the connection until a client connects with the server.
  - Send and receive data using the **read()** and **write()** system calls.



#### connect using clinet and server

To connect successfully,  `serv`  should be start first, or `client` will get error message 

```powershell
[xxxxxx@cs-linux ~]$ ./client xx.xxx.x.xx
Error on connecting.
[xxxxxx@cs-linux ~]$
```



First, start  `serv`  

```powershell
[xxxxxx@cs-linux ~]$ ./serv
Bind done.
Waiting for incoming connections...
```

Then, start `client`

*client received*:

```powershell
[xxxxxx@cs-linux ~]$ ./client xx.xxx.x.xx
You are connected to the server.
[Server Message]:
||==========================================================================================||
||00000=========================| Welcome to supper server!|===========================00000||
||>>| Functions:   |                                       | Hint:                |      |<<||
||<<| -------------| --------------------------------------|----------------------|      |>>||
||>>| GET TIME     |  get server current time              |  Users should type   |      |<<||
||>>| GET IP       |  get server ip                        |  corret instructions |      |<<||
||>>| GET SPACE    |  get server hard disk space           |  OR server retuen    |      |<<||
||>>| GET MEMORY   |  get server memory (ram + swap)       |  error message       |      |<<||
||>>| GET SYS      |  get server system information        |----------------------|      |<<||
||>>| GET ECHO     |  get server network card MAC address  |                             |<<||
||<<| GET CPU      |  get cpu information                  |          /~                 |>>||
||>>| -------      |  -------                              |         C oo                |<<||
||<<| FILE x       |  get content on line x in file        |         _( ^)               |>>||
||>>| -------------|---------------------------------------|     _ /   ~  _              |<<||
||<<                                                       _____/           ________     />>||
||>>|                                                     ~|     xxxxxxxxxxx     |~     /|<<||
||00000=====================================================       xxxxxxx        =====00000||
||==========================================================================================||
Client ip: 10.178.1.73
Time: Fri Dec  2 01:36:55 2016
[Your command]:
```

*And server waiting for command*:

```powershell
[xxxxxx@cs-linux ~]$ ./serv
Bind done.
Waiting for incoming connections...
Connect to client.
Sendline:
||==========================================================================================||
||00000=========================| Welcome to supper server!|===========================00000||
||>>| Functions:   |                                       | Hint:                |      |<<||
||<<| -------------| --------------------------------------|----------------------|      |>>||
||>>| GET TIME     |  get server current time              |  Users should type   |      |<<||
||>>| GET IP       |  get server ip                        |  corret instructions |      |<<||
||>>| GET SPACE    |  get server hard disk space           |  OR server retuen    |      |<<||
||>>| GET MEMORY   |  get server memory (ram + swap)       |  error message       |      |<<||
||>>| GET SYS      |  get server system information        |----------------------|      |<<||
||>>| GET ECHO     |  get server network card MAC address  |                             |<<||
||<<| GET CPU      |  get cpu information                  |          /~                 |>>||
||>>| -------      |  -------                              |         C oo                |<<||
||<<| FILE x       |  get content on line x in file        |         _( ^)               |>>||
||>>| -------------|---------------------------------------|     _ /   ~  _              |<<||
||<<                                                       _____/           ________     />>||
||>>|                                                     ~|     xxxxxxxxxxx     |~     /|<<||
||00000=====================================================       xxxxxxx        =====00000||
||==========================================================================================||
Client ip: xx.xxx.x.xx
Time: Fri Dec  2 01:36:55 2016
Waiting for command...
```

**Successfully connect!**



## Client

The client program is write to connect to the server, read the input command sending to the server and read the server message to display to users, loop done when user input **QUIT**, and then disconnect from the server.

### header files

Include some header files for internet connecting, string functions, check  integer, etc.

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <limits.h>
```

- include `sys/types.h`  and `sys/socket.h`  to use socket

  The `sys/types.h`  header include some definitions of types in Linux.

  The `sys/socket.h` header include function:  **socket()** to create an endpoint for communication and returns a file descriptor that refers to that endpoint.

  ```c
  int socket(int domain, int type, int protocol);
  ```

- The `netdb.h ` header include definitions for network database operations.

- The `stdio.h` header include standard input/output library functions like **printf()**.

- The `string.h` header inclued string operations like **strcmp()**.

- The `unistd.h` header inclued standard symbolic constants and types.

- The `arpa/inet.h` header inclued definitions for internet operations related to **inet_aton()** or more.

- The `stdlib.h` header inclued standard library definitions like **exit()**.

- The `limits.h` header inclued implementation-defined constants used in checking integer.



### error functions

Error functions is called when fail to do operations. In this program, mostly used related to socket.

```c
void error_socket_open()	//send error message when fail to open the socket and exit with code 1
{
	printf("Error on opening socket.\n");
	exit(1);
}

/*use in server*/
void error_bind()	//send error message when fail to bind and exit with code 2
{
	printf("Error on binding.\n");
	exit(2);
}

/*use in server*/
 void error_accept()	//send error message when fail to accept and exit with code 3
 {
 	printf("Error on accept.\n");
 	exit(3);
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
```

*This table represent the exit code and related error reason.*

| EXIT CODE | ERROR REASON                 |
| :-------: | :--------------------------- |
|     1     | Error on opening socket      |
|     2     | Error on binding             |
|     3     | Error on accept              |
|     4     | Error on reading from socket |
|     5     | Error on writing to socket   |
|     6     | Error on connecting          |
|    -1     | Unable to allocate memory    |



### other functions

#### prompt_unlimit

**prompt_unlimit() **is called whenever the program needs to prompt something and allocate memory for unkown length string.

```c
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
```



#### read_char

**read_char()** is called when program needs to prompt  and read input character.

```c
int read_char(const char *mesg, char **text)
{
	*text = prompt_unlimit(mesg);
	if(*text[0] == '\0')
	{
		return 0;	//return 0 if text is empty
	}
	return 1; 	//return 1 if not empty
}
```



#### check_int

**check_int()** is called when program needs to check the content of string is non-negative integer or not.

```c
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
```



### main function

use numbers of arguments to check if users type ip address

```c
int main(int argc, char *argv[])
{
	if (argc == 1)	//if type only one argument, prompt to type ip address
	{
		printf("Please enter server ip address.\n");
	}
	else
	{
      //...
    }
}
```

declare variables and socket address struct

```c
int sockfd, n;	// declare necessary variables
char sendline[15000];
struct sockaddr_in servaddr; // socket address struct
```

use **socket()** to create a socket with ipv4 and socket stream, if fail to open, prompt and exit

```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);	// create a socket with the appropriate protocol
if (sockfd < 0)
{
	error_socket_open();	//if fail to open the socket, call error_socket_open() to prompt and exit
}
```

use **bzero()** to clear the servaddr before used and then define the network protocols ,port and convert address to binary using **inet_pton()**.

use **connect()** to connect to the server through socket, if failed, prompt and exit, if successful, print to prompt to users

```c
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
```

use **read()** to read the welcome message and menu from the server, if fail, prompt and exit, if successful, print the receives message

```c
bzero(str, 15000);		//read the welcome message and menu from the server
if (read(sockfd, str, 15000) < 0)
{
	error_read();	//if fail to read, call error_read() to prompt and exit
}
printf("[Server Message]: %s\n", str);	//print the message received
```

use *do_while* loop to read users input command, send messages related to the command to server  and read the return message to print server information

loop done when input command is **QUIT**

```c
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
```

*This table represent the send message and related function.*

| send message | related function |
| :----------: | :--------------: |
|      -2      |     GET TIME     |
|      -3      |      GET IP      |
|      -4      |    GET SPACE     |
|      -5      |    GET MEMORY    |
|      -6      |     GET SYS      |
|      -7      |     GET ECHO     |
|      -8      |     GET CPU      |
|      0       |       QUIT       |
| positive int |    FILE LINEx    |

free memory ,close the socket and prompt to disconnect from the server

```c
free(command);	//free memory for command
close(sockfd);	//close the socket

printf("You have now disconnected from the server.\n");	//prompt to disconnected from the server
```

**CLIENT DONE**



## Server

The server program is write to accept the client, read the command message from the client, do related functions and write the message return to client.

### header files

Include some header files for internet connecting, linux system information, etc.

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/vfs.h>
#include <mntent.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
```

*see* **Client** > **header files**

`sys/types.h`   `sys/socket.h`   `netdb.h `  `stdio.h`  `string.h`  `unistd.h`  `arpa/inet.h`  `stdlib.h`  `limits.h` 

- The `time.h` header include time types to get current date and time.
- The `sys/vfs.h  ` header include operations to get filesystem statistics.
- The `mntent.h` header include definition of filesystem statistics.
- The `sys/utsname.h` header include system name structure
- The `pwd.h` header include password structure
- The `ioctl` header include operations to control device
- The `net/if.h` header include sockets local interfaces
-  The `netinet/in.h` header include Internet address family



### error functions

*see* **Client** > **error functions**



### other functions

#### check_int

*see* **Client** > **other functions** > **check_int**



#### get_client_ip

**get_client_ip()** is write to get client ip using **getpeername()** through the socket with address structure and use **inet_ntoa()** to convert the address specified by in to a string in the Internet standard dot notation

```c
int get_client_ip(int socket, char clientip[20])
{
	struct sockaddr_in addr;	//declare sockaddr_in struct
	socklen_t addr_size = sizeof(struct sockaddr_in);	//get size of sockaddr_in struct
	int is_get_clientip = getpeername(socket, (struct sockaddr *)&addr, &addr_size);	//get client ip address
	if (is_get_clientip != 0)
	{
		return 0;	//if fail, return 0
	}
	else	//if get successful, copy the converted ip adress and retuen 1
	{
		strcpy(clientip, inet_ntoa(addr.sin_addr));	//convert the address specified by in to a string in the Internet standard dot notation
		return 1;
	}
}
```

The DESCRIPTION of [getpeername()](http://man7.org/linux/man-pages/man2/getpeername.2.html)

```mathematica
getpeername() returns the address of the peer connected to the socket sockfd, in the buffer pointed to by addr.  The addrlen argument should be initialized to indicate the amount of space pointed to by addr.  On return it contains the actual size of the name returned (in bytes).  The name is truncated if the buffer provided is too small.

The returned address is truncated if the buffer provided is too small; in this case, addrlen will return a value greater than was supplied to the call.
```



#### get_server_ip

**get_server_ip()** is write to get server ip using **getsockname()**  with address structure and use **inet_ntoa()** to convert the address specified by in to a string in the Internet standard dot notation

```c
int get_server_ip(int socket, char serverip[20])
{
	struct sockaddr_in addr;	//declare sockaddr_in struct
	socklen_t addr_size = sizeof(struct sockaddr_in);	//get size of sockaddr_in struct
	int is_get_serverip = getsockname(socket, (struct sockaddr *)&addr, &addr_size);	//get server ip address
	if (is_get_serverip != 0)
	{
		return 0;	//if fail, return 0
	}
	else	//if get successful, copy the converted ip adress and retuen 1
	{
		strcpy(serverip, inet_ntoa(addr.sin_addr));	//convert the address specified by in to a string in the Internet standard dot notation
		return 1;
	}
}
```

The DESCRIPTION of [getsockname()](http://man7.org/linux/man-pages/man2/getsockname.2.html)

```mathematica
getsockname() returns the current address to which the socket sockfd is bound, in the buffer pointed to by addr.  The addrlen argument should be initialized to indicate the amount of space (in bytes) pointed to by addr.  On return it contains the actual size of the
socket address.

The returned address is truncated if the buffer provided is too small; in this case, addrlen will return a value greater than was supplied to the call.
```



#### get_server_time

**get_server_time()** is write to get the current date and time string of server using **time()** to get and **ctime()** to convert

```c
int get_server_time(char servertime[26])
{
	time_t result = time(NULL);	//get current date and time of server
	if (result == -1)
	{
		return 0;	//if fail, return 0
	}
	else
	{
		strcpy(servertime, ctime(&result));	//copy the converted given time
		servertime[strlen(servertime) - 1] = '\0';	//clear the new line on the end of string
		return 1;	//if get successful, return 1
	}
}
```

The DESCRIPTION of [time()](http://man7.org/linux/man-pages/man2/time.2.html)

```mathematica
time() returns the time as the number of seconds since the Epoch,1970-01-01 00:00:00 +0000 (UTC).
If tloc is non-NULL, the return value is also stored in the memory pointed to by tloc.
```



#### get_server_disk_info and kscale

**kscale()** is a help function to get_server_disk_info for hard desk space

```c
char str_number[25];

char *kscale(unsigned long b, unsigned long bs)
{
	const unsigned long long G = 1024 * 1024 * 1024;	//1GB
	const unsigned long long M = 1024 * 1024;		//1MB
	const unsigned long long K = 1024;		//1KB

	unsigned long long size = b * (unsigned long long)bs; //get size by multiply
	if (size > G)		//if size > 1GB, represent by GB
	{
		sprintf(str_number, "%0.2fG", size/(G*1.0));	//save size in str_number and return, represent by GB
		return str_number;
	}
	else if (size > M)		//if 1GB > size > 1MB, represent by MB
	{
		sprintf(str_number, "%0.2fM", size/(1.0*M));	//save size in str_number and return, represent by MB
		return str_number;
	}
	else if (size > K)		//if 1MB > size > 1KB, represent by KB
	{
		sprintf(str_number, "%0.2fK", size/(1.0*K));	//save size in str_number and return, represent by KB
		return str_number;
	}
	else					//if 1KB > size > 1B, represent by B
	{
		sprintf(str_number, "%0.2fB", size*1.0);	//save size in str_number and return, represent by B
		return str_number;
	}  
}
```



**get_server_disk_info()** is write to print the hard disk information of the server, whose output same as the system call `df` using **setmntent()**, **getmntent()**, **endmntent()** and **statfs()**

```c
int get_server_disk_info(char disk_whole[15000])
{
	bzero(disk_whole, 15000);	//clear string
	FILE* mount_table;			// declare necessary variables
	struct mntent *mount_entry;
	struct statfs s;
	unsigned long blocks_used;
	unsigned blocks_percent_used;
	const char *disp_units_hdr = NULL;
	mount_table = NULL;
	mount_table = setmntent("/etc/mtab", "r");	//opens the filesystem description file
	if (!mount_table)
	{
		return 0;	//if fail, return 0
	}
	
	char title[100];	// declare to store title characters
	disp_units_hdr = "          Size";
	sprintf(title, "Filesystem           %-20sUsed Available %s Mounted on\n", disp_units_hdr, "Use%");	//save characters into title string
	strcat(disk_whole, title);	//append the whole string and title string

	while (1)	//loop to get every hard disk space information
	{
		const char *device;			// declare necessary variables
		const char *mount_point;
		if (mount_table)
		{
			mount_entry = getmntent(mount_table);	//reads the next line of the filesystem description file
			if (!mount_entry) {
				endmntent(mount_table);		//if read the end of the file, closes the stream associated with the file and break exit the loop
				break;
			}
		}
		else
		{
			continue;
		}

		device = mount_entry->mnt_fsname;	//get device name
		mount_point = mount_entry->mnt_dir;	//get mount point
		if (statfs(mount_point, &s) != 0)	//get information according to the path
		{
			return 0;
			continue;
		}
		if ((s.f_blocks > 0) || !mount_table )
		{
			blocks_used = s.f_blocks - s.f_bfree;	//calculate used space
			blocks_percent_used = 0;		// declare percent
			if (blocks_used + s.f_bavail)	
			{
				blocks_percent_used = (blocks_used * 100ULL + (blocks_used + s.f_bavail) / 2) / (blocks_used + s.f_bavail);	//calculate used percent
			}

			if (strcmp(device, "rootfs") == 0)
			{
				continue;
			}

			char disk_oneline[300];
			if (sprintf(disk_oneline, "\n%-25s" + 1, device) > 25) //store disk name
			{
				sprintf(disk_oneline, "\n%-25s", "");
			}

			char disk_size[25];	// declare necessary variables
			char disk_used[25];
			char disk_available[25];
			strcpy(disk_size, kscale(s.f_blocks, s.f_bsize));		//store size information 
			strcpy(disk_used, kscale(s.f_blocks - s.f_bfree, s.f_bsize));	//store used information
			strcpy(disk_available, kscale(s.f_bavail, s.f_bsize));		//store available information
			char disk_oneline_two[200];					//store all information in a string
			sprintf(disk_oneline_two, " %9s %9s %9s %3u%% %s\n", disk_size, disk_used, disk_available, blocks_percent_used, mount_point);
			strcat(disk_oneline, disk_oneline_two);
			strcat(disk_whole, disk_oneline);	//append the whole string and one_line string
		}
	}
	disk_whole[strlen(disk_whole) - 1] = '\0';	//clear the new line on the end of string
	return 1;	//if get successful, return 1
}
```

The DESCRIPTION of [setmntent()](http://man7.org/linux/man-pages/man3/getmntent.3.html)

```mathematica
The setmntent() function opens the filesystem description file filename and returns a file pointer which can be used by getmntent().
The argument type is the type of access required and can take the same values as the mode argument of fopen(3).
```

The DESCRIPTION of [getmntent()](http://man7.org/linux/man-pages/man3/getmntent.3.html)

```mathematica
The getmntent() function reads the next line of the filesystem description file from stream and returns a pointer to a structure containing the broken out fields from a line in the file.
The pointer points to a static area of memory which is overwritten by subsequent calls to getmntent().
```

The DESCRIPTION of [endmntent()](http://man7.org/linux/man-pages/man3/getmntent.3.html)

```mathematica
The endmntent() function closes the stream associated with the filesystem description file.
```

The DESCRIPTION of [statfs](http://man7.org/linux/man-pages/man2/fstatfs64.2.html)

```mathematica
The statfs() system call returns information about a mounted filesystem.  path is the pathname of any file within the mounted filesystem. buf is a pointer to a statfs structure defined approximately.
```



`struct mntent` and  `struct statfs` used in **get_server_disk_info()**

The `struct mntent` in [mntent.h](http://www.delorie.com/djgpp/doc/incs/mntent.h)

```c
struct mntent
{
  char *mnt_fsname;
  char *mnt_dir;
  char *mnt_type;
  char *mnt_opts;
  int  mnt_freq;
  int  mnt_passno;
  long mnt_time;
};
```

The`struct statfs` in [sys/vfs.h](http://man7.org/linux/man-pages/man2/fstatfs64.2.html)

```c
struct statfs 
{
               __fsword_t f_type;    /* Type of filesystem (see below) */
               __fsword_t f_bsize;   /* Optimal transfer block size */
               fsblkcnt_t f_blocks;  /* Total data blocks in filesystem */
               fsblkcnt_t f_bfree;   /* Free blocks in filesystem */
               fsblkcnt_t f_bavail;  /* Free blocks available to
                                        unprivileged user */
               fsfilcnt_t f_files;   /* Total file nodes in filesystem */
               fsfilcnt_t f_ffree;   /* Free file nodes in filesystem */
               fsid_t     f_fsid;    /* Filesystem ID */
               __fsword_t f_namelen; /* Maximum length of filenames */
               __fsword_t f_frsize;  /* Fragment size (since Linux 2.6) */
               __fsword_t f_flags;   /* Mount flags of filesystem
                                        (since Linux 2.6.36) */
               __fsword_t f_spare[xxx];
                               /* Padding bytes reserved for future use */
};
```

`/etc/mtab` in cs-linux

```powershell
[xxxxxx@cs-linux ~]$ cat /etc/mtab
/dev/mapper/vg_cslinux-lv_root / ext4 rw 0 0
proc /proc proc rw 0 0
sysfs /sys sysfs rw 0 0
devpts /dev/pts devpts rw,gid=5,mode=620 0 0
tmpfs /dev/shm tmpfs rw 0 0
/dev/sda1 /boot ext4 rw 0 0
/dev/mapper/vg_cslinux-lv_home /home ext4 rw,usrquota,grpquota 0 0
none /proc/sys/fs/binfmt_misc binfmt_misc rw 0 0
```



#### get_server_memory_info and memory_info

**memory_info()** is a help function to **get_server_memory_info()** to search for target memory type and read  the size

```c
int memory_info(const char *memory_type, long *value)
{
	FILE* fp = fopen("/proc/meminfo", "r");	//open memory information file
	if (fp != NULL)		//if open successful
	{
		size_t bufsize = 1024 * sizeof(char);	//get memory information
		char* buf = (char*)malloc(bufsize);
		while (getline(&buf, &bufsize, fp) >= 0)
		{
			if (strncmp(buf, memory_type, strlen(memory_type)) != 0)	//search for target memory type
				continue;
			sscanf(buf, "%*s%ld", value);	//store size in value
				break;
		}
		fclose(fp);
		free((void*)buf);
		if (value != NULL)
		{
			return 1;	//if successful, return 1
		}
		else
		{
			return 0;	//if fail, return 0
		}
	}
	else
	{
		return 0;	//if fail, return 0
	}
}
```

`/proc/meminfo` in cs-linux

```powershell
[xxxxxx@cs-linux ~]$ cat /proc/meminfo
MemTotal:       65977548 kB
MemFree:        60192700 kB
Buffers:          810688 kB
Cached:          1186328 kB
SwapCached:       264640 kB
Active:          3012176 kB
Inactive:        1328692 kB
Active(anon):    2163328 kB
Inactive(anon):   291868 kB
Active(file):     848848 kB
Inactive(file):  1036824 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:      31457276 kB
SwapFree:       30191448 kB
Dirty:               344 kB
Writeback:             0 kB
AnonPages:       2126716 kB
Mapped:           220696 kB
Shmem:            111344 kB
Slab:             690740 kB
SReclaimable:     464228 kB
SUnreclaim:       226512 kB
KernelStack:       25456 kB
PageTables:       267856 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:    64446048 kB
Committed_AS:   29368636 kB
VmallocTotal:   34359738367 kB
VmallocUsed:      255560 kB
VmallocChunk:   34325072792 kB
HardwareCorrupted:     0 kB
AnonHugePages:    604160 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
DirectMap4k:       10240 kB
DirectMap2M:    67098624 kB
```



**get_server_memory_info()** is write to print memory information of the server, whose output same as the system call `free	` 

```c
int get_server_memory_info(char memory_information[500])
{
	long kb_main_total;			// declare necessary variables
	long kb_main_used;
	long kb_main_free;
	long kb_main_shared;
	long kb_main_buffers;
	long kb_main_cached;
	long kb_swap_total;
	long kb_swap_used;
	long kb_swap_free;

	int is_kb_main_total = memory_info("MemTotal", &kb_main_total);		//get size related to memeory type
	int is_kb_main_free = memory_info("MemFree", &kb_main_free);
	int is_kb_main_shared = memory_info("Shmem", &kb_main_shared);
	int is_kb_main_buffers = memory_info("Buffers", &kb_main_buffers);
	int is_kb_main_cached = memory_info("Cached", &kb_main_cached);
	kb_main_used = kb_main_total - kb_main_free;

	int is_kb_swap_total = memory_info("SwapTotal", &kb_swap_total);
	int is_kb_swap_free = memory_info("SwapFree", &kb_swap_free);
	kb_swap_used = kb_swap_total - kb_swap_free;

	if (is_kb_main_total == 0 || is_kb_main_free == 0 || is_kb_main_shared == 0 || is_kb_main_buffers == 0 || is_kb_main_cached == 0 || is_kb_swap_total == 0 || is_kb_swap_free == 0)
	{
		return 0;	//if fail, return 0
	}
	else
	{
		char title[125];	// declare to store title characters
		sprintf(title, "             total       used       free     shared    buffers     cached\n");//save characters into title string
		char memory_Line[125];
		sprintf(memory_Line,
				"%-7s %10ld %10ld %10ld %10ld %10ld %10ld\n", "Mem:",	//store ram information
				kb_main_total,
 				kb_main_used,
				kb_main_free,
				kb_main_shared,
				kb_main_buffers,
				kb_main_cached
		);

		long buffers_plus_cached = kb_main_buffers + kb_main_cached;
		char buffer_line[125];
		sprintf(buffer_line,
				"-/+ buffers/cache: %10ld %10ld\n", 	//store buffers/cache information
				kb_main_used - buffers_plus_cached,
				kb_main_free + buffers_plus_cached
		);

		char swap_line[125];
		sprintf(swap_line,
 				"%-7s %10ld %10ld %10ld", "Swap:",	//store swap information
				kb_swap_total,
    			kb_swap_used,
				kb_swap_free
		);
		strcpy(memory_information, title);	//store all information in a string 
		strcat(memory_information, memory_Line);
		strcat(memory_information, buffer_line);
		strcat(memory_information, swap_line);
		return 1;	//if successful, return 1
    }
}
```



#### get_server_system_info

**get_server_system_info()** is write to print system information of the server using **gethostname()**

```c
int get_server_system_info(char system_information[500])
{
	char hname[256];	// declare necessary variables
	struct utsname uts;

	if (gethostname(hname,255)!=0||uname(&uts)<0)	//get system information
	{
		return 0;	//if fail ,return 0
	}
	else
	{
		sprintf(system_information, "Host Name:   %s\nSystem:      %s\nMachine:     %s\nNode Name:   %s\nRelease:     %s\nVersion:     %s", hname, uts.sysname, uts.machine, uts.nodename, uts.release, uts.version); //store all information in a string
		return 1;	//if successful, return 1
	}
}
```

The DESCRIPTION of [gethostname()](http://man7.org/linux/man-pages/man2/gethostname.2.html)

```mathematica
gethostname() returns the null-terminated hostname in the character array name, which has a length of len bytes.  If the null-terminated hostname is too large to fit, then the name is truncated, and no error is returned (but see NOTES below). 
POSIX.1 says that if such truncation occurs, then it is unspecified whether the returned buffer includes a terminating null byte.
```

The `struct utsname` in [sys/utsname.h](http://man7.org/linux/man-pages/man2/uname.2.html)

```c
struct utsname
{
        char sysname[];    /* Operating system name (e.g., "Linux") */
        char nodename[];   /* Name within "some implementation-defined
                              network" */
        char release[];    /* Operating system release (e.g., "2.6.28") */
        char version[];    /* Operating system version */
        char machine[];    /* Hardware identifier */
    #ifdef _GNU_SOURCE
        char domainname[]; /* NIS or YP domain name */
    #endif
};
```



#### file_find

**file_find()** is called when program needs to get the content of the target line in the file

```c
int file_find(int target_line, char file_line[15000])
{
	FILE *fp = fopen("test.txt", "r");	//open test file
	if (!fp)
	{
		return 0;	//if fail to open, return 0
	}
	else
	{
		int position = 0; 	// declare necessary variables
		int line_number = 1;
		int is_quit = 0;	//represent is quit while loop
		int is_print = 1;	//represent is to print

		while(is_quit == 0 || target_line != line_number)	//if not get the line, do looop
		{
			if (is_quit == 1)	//if get the end of line, but not the target line
			{
				is_quit = 0;	//clear is_quit
				line_number++;	//go to next line
				bzero(file_line, 15000);	//clear the string
				position = 0;	//clear position
			}

			char tmp;
			if (fscanf(fp, "%c", &tmp) != EOF)	// if not go to end of file
			{
				if (tmp != '\n') //if not new line
				{
					file_line[position] = tmp;	//add character to tmp string
					position++;
				}
				else
				{
					is_quit = 1;	//if new line, is_quit to 1
				}	
			}
			else
			{
				is_print = 0;	//if target line > total line
				break;
			}
		}

		if (is_print == 1)
		{
			file_line[position] = '\0';	//clear new line character
			return 1;	//if successful, return 1
		}
		else
		{
			return 0;	//if fail, return 0
		}
	}
}
```



#### get_server_cpu_info

**get_server_cpu_info()** is write to print the cpu information of the server

```c
int get_server_cpu_info(char cpu_info[15000])
{
	bzero(cpu_info, 15000);	//clear string
	FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");	//open cpu information file
	if (!cpuinfo)
	{
		return 0;	//if fail to open, return 0
	}
	else
	{
		char *arg = 0;	// declare necessary variables
		size_t size = 0;
		while(getdelim(&arg, &size, 0, cpuinfo) != -1)	//store information in string
		{
			arg[strlen(arg) - 1] = '\0';
			strcat(cpu_info, arg);
		}
		free(arg);	//free memory
		return 1;	//if successful, return 1
	}
	fclose(cpuinfo);	//close the file
}
```



#### get_server_echo_info

**get_server_echo_info()** is write to print network interface of server using **ioctl()**

```c
int get_server_echo_info(char echo_info[15000])
{
	bzero(echo_info, 15000);	// declare necessary variables
	struct ifreq ifr;
	struct ifconf ifc;
	char buf[2048];
	int success = 0;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);	// create a socket 
	if (sock == -1) 
	{
		return 0;	//if fail to create a socket, return 0
	}

	ifc.ifc_len = sizeof(buf);	//get size of buffer
	ifc.ifc_buf = buf;	//get buffer address
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) 
	{
		return 0;	//if fail, return 0
	}

	struct ifreq* it = ifc.ifc_req;			// declare necessary variables
	const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
	char szMac[64];
	int count = 0;
	for (; it != end; ++it) // get interface name and mac address
	{
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) 
		{
			if (! (ifr.ifr_flags & IFF_LOOPBACK)) 
			{
				if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) 
				{
					char echo_info_line[100];
					count ++ ;
					unsigned char * ptr ;
					ptr = (unsigned char  *)&ifr.ifr_ifru.ifru_hwaddr.sa_data[0];
					snprintf(szMac,64,"%02X:%02X:%02X:%02X:%02X:%02X",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5));
					sprintf(echo_info_line, "%d,Interface name : %s , Mac address : %s \n",count,ifr.ifr_name,szMac);
					strcat(echo_info, echo_info_line);
				}
			}
		}
		else
		{
			return 0;	//if fail, return 0
		}
	}
	echo_info[strlen(echo_info) - 1] = '\0'; //clear new line character
	return 1; //if successful, return 1
}
```

The `struct ifreq` 

```c
struct ifreq 
{
	 char ifr_name[IFNAMSIZ]; /* Interface name */
	 union 
     {
	     struct sockaddr ifr_addr;
	     struct sockaddr ifr_dstaddr;
	     struct sockaddr ifr_broadaddr;
	     struct sockaddr ifr_netmask;
	     struct sockaddr ifr_hwaddr;
	     short           ifr_flags;
	     int             ifr_ifindex;
	     int             ifr_metric;
	     int             ifr_mtu;
	     struct ifmap    ifr_map;
	     char            ifr_slave[IFNAMSIZ];
	     char            ifr_newname[IFNAMSIZ];
	     char           *ifr_data;
	 };
};
```

The `struct ifconf` 

```c
struct ifconf 
{
     int                 ifc_len; /* size of buffer */
     union 
     {
         char           *ifc_buf; /* buffer address */
         struct ifreq   *ifc_req; /* array of structures */
     };
 };
```

The DESCRIPTION of [ioctl()](http://man7.org/linux/man-pages/man2/ioctl.2.html)

```mathematica
The ioctl() function manipulates the underlying device parameters of special files.  In particular, many operating characteristics of character special files (e.g., terminals) may be controlled with ioctl() requests.
```



### main function



```c
int main(int argc, char *argv[])
{
	char str[100];	 // declare necessary variables
	int listen_fd, comm_fd;

	struct sockaddr_in servaddr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);	    // create a socket with the appropriate protocol
	if (listen_fd < 0)
	{
		error_socket_open();
	}

	bzero(&servaddr, sizeof(servaddr));	// set all the socket structures with null values

	servaddr.sin_family = AF_INET;	// set appropriate protocol and port number (12108)
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(12108);

	if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)	// Bind a name to a socket
	{
		error_bind();	//if fail to bind, call error_bind() to prompt and exit
	}
	printf("Bind done.\n");	//to prompt bind done

	listen(listen_fd, 10);		// listening for incoming connection
	printf("Waiting for incoming connections...\n");

	int test;
	char sendline[15000];

	comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);	// accept a connection on a socket
	if (comm_fd < 0)
	{
		error_accept();	//if fail to accept, call error_accept() to prompt and exit
	}

	printf("Connect to client.\n");	//to prompt connect successfully

	bzero(sendline, 15000);	//store menu characters to a string
	strcpy(sendline, "\n||==========================================================================================||\n||00000=========================| Welcome to supper server!|===========================00000||\n||>>| Functions:   |                                       | Hint:                |      |<<||\n||<<| -------------| --------------------------------------|----------------------|      |>>||\n||>>| GET TIME     |  get server current time              |  Users should type   |      |<<||\n||>>| GET IP       |  get server ip                        |  corret instructions |      |<<||\n||>>| GET SPACE    |  get server hard disk space           |  OR server retuen    |      |<<||\n||>>| GET MEMORY   |  get server memory (ram + swap)       |  error message       |      |<<||\n||>>| GET SYS      |  get server system information        |----------------------|      |<<||\n||>>| GET ECHO     |  get server network interface address |                             |<<||\n||<<| GET CPU      |  get cpu information                  |          /~                 |>>||\n||>>| -------      |  -------                              |         C oo                |<<||\n||<<| FILE x       |  get content on line x in file        |         _( ^)               |>>||\n||>>| -------------|---------------------------------------|     _ /   ~  _              |<<||\n||<<                                                       _____/           ________     />>||\n||>>|                                                     ~|     xxxxxxxxxxx     |~     /|<<||\n||00000=====================================================       xxxxxxx        =====00000||\n||==========================================================================================||");

	char client_ip[20];
	int is_get_client_ip = get_client_ip(comm_fd, client_ip);	//get client ip
	if (is_get_client_ip == 1)
	{
		strcat(sendline, "\nClient ip: ");
		strcat(sendline, client_ip);
	}

	char server_time_connect[26];
	int is_get_server_time_connect = get_server_time(server_time_connect);	//get server time
	if (is_get_server_time_connect == 1)
	{
		strcat(sendline, "\nTime: ");
		strcat(sendline, server_time_connect);
	}

	printf("Sendline: %s\n", sendline);
	if (write(comm_fd, sendline, strlen(sendline) + 1) < 0)	//write to socket
	{
		error_write();	//if fail to write, call error_write() to prompt and exit
	}

	bzero(str, 100);	// set all the socket structures with null values

	printf("Waiting for command...\n");

	int is_write = 1;	//represent is write or not
	while((read(comm_fd, str, 100)))	//read from socket
	{
		printf("Received: %s\n", str);

		int command_number;
		int is_int = check_int(&command_number, str);	//convert to int and check if int

		bzero(sendline, 15000);

		if (command_number == 0)
		{
			strcpy(sendline, "Invalid command.");	//if received message is 0, store Invalid command in sendline string
		}
		else if (command_number == -1)
		{
			is_write = 0;	//if received message is -1, do not write and break exit the while loop
			break;
		}
		else if (command_number == -2)		//if received message is -2, store server time information in sendline string
		{
			char server_time[26];
			int is_get_server_time = get_server_time(server_time);
			if (is_get_server_time == 1)
			{
				strcpy(sendline, "Server date and time: ");
			 	strcat(sendline, server_time);
			}
			else
			{
				strcpy(sendline, "Error getting server time.");
			}
		}
		else if (command_number == -3)		//if received message is -3, store server ip information in sendline string
		{
			char server_ip[20];
			int is_get_server_ip = get_server_ip(comm_fd, server_ip);
			if (is_get_server_ip == 1)
			{
				strcpy(sendline, "Server ip: ");
			 	strcat(sendline, server_ip);
			}
			else
			{
				strcpy(sendline, "Error getting server ip.");
			}
		}
		else if (command_number == -4)			//if received message is -4, store server disk information in sendline string
		{
			char server_disk_info[15000];
		 	int is_get_server_disk_info = get_server_disk_info(server_disk_info);
			if (is_get_server_disk_info == 1)
			{
				strcpy(sendline, "Server desk space information: \n");
			 	strcat(sendline, server_disk_info);
			}
			else
			{
				strcpy(sendline, "Error getting server desk space information.");
			}
		}
		else if (command_number == -5)			//if received message is -5, store server memory information in sendline string
		{
			char server_memory_info[500];
			int is_get_server_memory_info = get_server_memory_info(server_memory_info);
			if (is_get_server_memory_info == 1)
			{
				strcpy(sendline, "Server memory information(kb): \n");
				strcat(sendline, server_memory_info);
			}
			else
			{
				strcpy(sendline, "Error getting server memory information.");
			}
		}
		else if (command_number == -6)		//if received message is -6, store server system information in sendline string
		{
			char server_sys[500];
			int is_get_server_sys = get_server_system_info(server_sys);
			if (is_get_server_sys == 1)
			{
			strcpy(sendline, "Server system information: \n");
			strcat(sendline, server_sys);
			}
			else
			{
				strcpy(sendline, "Error getting server system information.");
			}
		}
		else if (command_number == -7)			//if received message is -7, store server interface information in sendline string
		{
			char server_echo[15000];
			int is_get_server_echo = get_server_echo_info(server_echo);
			if (is_get_server_echo == 1)
			{
			strcpy(sendline, "Server network interface information: \n");
			strcat(sendline, server_echo);
			}
			else
			{
				strcpy(sendline, "Error getting server network interface information.");
			}
		}
		else if (command_number == -8)		//if received message is -8, store server cpu information in sendline string
		{
			char server_cpu[15000];
			int is_get_server_cpu = get_server_cpu_info(server_cpu);
			if (is_get_server_cpu == 1)
			{
			strcpy(sendline, "Server cpu information: \n");
			strcat(sendline, server_cpu);
			}
			else
			{
				strcpy(sendline, "Error getting server cpu information.");
			}
		}
		else
		{
			char file_line_find[15000];
			int is_file_line_find = file_find(command_number, file_line_find);		//if received message is positive int, store line x in sendline string
			if (is_file_line_find == 1)
			{
				sprintf(sendline, "LINE %d: ", command_number);
				strcat(sendline, file_line_find);
			}
			else
			{
				strcpy(sendline, "Error finding content.");
			}
		}

		if (is_write == 1)
		{
			if (write(comm_fd, sendline, strlen(sendline) + 1) < 0)	// write to the client
			{
				error_write();
			}
			printf("Sendline: %s\n", sendline);
		}
		bzero(str, 100); //clear the string
	}

	close(listen_fd);	//close the socket
	printf("Disconnect.\n");	//prompt to disconnect
}
```



## Implementation 

### GET TIME

```powershell
[Your command]: GET TIME
[Server Message]: Server date and time: Fri Dec  2 10:51:51 2016
[Your command]:
```



### GET IP

```powershell
[Your command]: GET IP
[Server Message]: Server ip: xx.xxx.x.xx
[Your command]:
```



### GET SPACE

```c
Your command]: GET SPACE
[Server Message]: Server desk space information:
Filesystem                     Size      Used Available Use% Mounted on
/dev/mapper/vg_cslinux-lv_root
                             49.09G    16.51G    30.08G  35% /
tmpfs                        31.46G    20.31M    31.44G   0% /dev/shm
/dev/sda1                   476.22M    67.02M   384.21M  15% /boot
dev/mapper/vg_cslinux-lv_home
                            215.94G    42.02G   162.94G  21% /home
[Your command]:
```



### GET MEMORY

```powershell
[Your command]: GET MEMORY
[Server Message]: Server memory information(kb):
             total       used       free     shared    buffers     cached
Mem:      65977548   10074320   55903228     112352     241288    1116800
-/+ buffers/cache:    8716232   57261316
Swap:     31457276    1253008   30204268
[Your command]:
```



### GET SYS

```powershell
Your command]: GET SYS
[Server Message]: Server system information:
Host Name:   cs-linux.nottingham.edu.cn
System:      Linux
Machine:     x86_64
Node Name:   cs-linux.nottingham.edu.cn
Release:     2.6.32-573.3.1.el6.x86_64
Version:     #1 SMP Thu Aug 13 22:55:16 UTC 2015
[Your command]:
```



### GET ECHO

```powershell
Your command]: GET ECHO
[Server Message]: Server network interface information:
1,Interface name : eth0 , Mac address : 00:50:56:B4:D3:43
2,Interface name : docker0 , Mac address : 56:4C:1C:B6:CB:16
[Your command]:
```



### GET CPU

```powershell
[Your command]: GET CPU
[Server Message]: Server cpu information:
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 45
model name	: Intel(R) Xeon(R) CPU E5-2640 v2 @ 2.00GHz
stepping	: 2
microcode	: 1063
cpu MHz		: 2000.000
cache size	: 20480 KB
physical id	: 0
siblings	: 8
core id		: 0
cpu cores	: 8
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts xtopology tsc_reliable nonstop_tsc aperfmperf unfair_spinlock pni pclmulqdq ssse3 cx16 sse4_1 sse4_2 popcnt aes xsave avx hypervisor lahf_lm ida arat xsaveopt pln pts dts
bogomips	: 4000.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 40 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: GenuineIntel
cpu family	: 6
model		: 45
model name	: Intel(R) Xeon(R) CPU E5-2640 v2 @ 2.00GHz
stepping	: 2
microcode	: 1063
cpu MHz		: 2000.000
cache size	: 20480 KB
physical id	: 0
siblings	: 8
core id		: 1
cpu cores	: 8
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts xtopology tsc_reliable nonstop_tsc aperfmperf unfair_spinlock pni pclmulqdq ssse3 cx16 sse4_1 sse4_2 popcnt aes xsave avx hypervisor lahf_lm ida arat xsaveopt pln pts dts
bogomips	: 4000.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 40 bits physical, 48 bits virtual
power management:

processor	: 2
vendor_id	: GenuineIntel
cpu family	: 6
model		: 45
model name	: Intel(R) Xeon(R) CPU E5-2640 v2 @ 2.00GHz
stepping	: 2
microcode	: 1063
cpu MHz		: 2000.000
cache size	: 20480 KB
physical id	: 0
siblings	: 8
core id		: 2
cpu cores	: 8
apicid		: 2
initial apicid	: 2
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts xtopology tsc_reliable nonstop_tsc aperfmperf unfair_spinlock pni pclmulqdq ssse3 cx16 sse4_1 sse4_2 popcnt aes xsave avx hypervisor lahf_lm ida arat xsaveopt pln pts dts
bogomips	: 4000.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 40 bits physical, 48 bits virtual
power management:

processor	: 3
vendor_id	: GenuineIntel
......
......
......
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts xtopology tsc_reliable nonstop_tsc aperfmperf unfair_spinlock pni pclmulqdq ssse3 cx16 sse4_1 sse4_2 popcnt aes xsave avx hypervisor lahf_lm ida arat xsaveopt pln pts dts
bogomips	: 4000.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 40 bits physical, 48 bits virtual
power management:
[Your command]:
```



### FILE X

```powershell
[Your command]: FILE 33
[Server Message]: LINE 33: This article explores ways in which virtual
[Your command]:
```

