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

char str_number[25];

void error_socket_open()	//send error message when fail to open the socket and exit with code 1
{
	printf("Error on opening socket.\n");
	exit(1);
}

void error_bind()	//send error message when fail to bind and exit with code 2
{
	printf("Error on binding.\n");
	exit(2);
}

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

int check_int(int *value, char *argument)
{
	int sign = 1;
	if (argument[0] == '-')
	{
		char nega[strlen(argument)];
		int i;
		for (i = 0; i < strlen(argument); i++)
		{
			nega[i] = argument[i + 1];
		}
		nega[strlen(argument)] = '\0';
		strcpy(argument, nega);
		sign = -1;
	}
	char *endptr;
	long v = strtol(argument, &endptr, 10) * sign;
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
			return 1; 	//return 1 to say sucessfully in converting to a number
		}
	}
}

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
			char disk_name_space[100];
			
			if (sprintf(disk_oneline, "\n%-25s" + 1, device) > 25) //store disk name
			{
				sprintf(disk_name_space, "\n%-25s", "");
				strcat(disk_oneline, disk_name_space);
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
