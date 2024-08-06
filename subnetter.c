#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ul unsigned long
#define ull unsigned long long

//Parse the IP Address given, return an integer
//Takes a pointer to ip addr char array


void usage(){
	printf("\nUsage: subnetter <ip address> <netmask>");
}

int parser (uint32_t *addr, char *ipaddr)
{	
	//Pointer to the start memory location for the ipaddr char array
	const char *p = ipaddr;

	//Pointer that will be used to track the memory location of the last numerical value in the char array
	char *endp;

	
	//strtoul() will iterate over the char array until the first non-numerical character
	//more precisely - the first character it cannot parse based on the base parameter (last)
	//the last position is set to the value (&) of the endp pointer variable
	//In subsequent octets, we set the p pointer to the endp pointer's value +1, meaning next char, so after dot. Also checking if it's not a dot in which case we return error.

	unsigned long a = strtoul(p, &endp, 10);
	if (*endp != '.') return -1;
	unsigned long b = strtoul(p = endp+1, &endp, 10);
	if (*endp != '.') return -1;
	unsigned long c = strtoul(p = endp+1, &endp, 10);
	if (*endp != '.') return -1;
	unsigned long d = strtoul(p = endp+1, &endp, 10);

	//Combine it using bitwise magic
	*addr = (uint32_t) ((a << 24) | (b << 16) | (c << 8) | d);

	//Return 0 for success!

	return 0;
}


void todotquad(unsigned int ip, char * start_ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    sprintf(start_ip, "\n%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);

}
	

int main (int argc, char* argv[])
{
	uint32_t ip_dec;
	uint32_t net_dec;

	char * mask =(char*)(sizeof(char)*32);

	printf("\nThis is %s",argv[0]); 
	printf("\nArguments passed: %i\n", argc-1);
	if (argc == 3){

		char* IP = argv[1];
		char* Netmask = argv[2];

		printf("\nIP Address: %s", IP);
		printf("\nNetMask: %s\n", Netmask);	

		int r = parser(&ip_dec, IP);

		if (r == -1){
		       	printf("\n Error Parsing IP Address");
			return 1;
		}

		int rn = parser(&net_dec, Netmask);

		if (rn == -1){
			printf("\n Error Parsing Netmask");
			return 1;
		}
		if (ip_dec > net_dec){
			printf("\nError: arguments possibly in wrong order. Double check?");
			usage();
			return 1;
		}	

		printf("\nDecimal IP: %u", ip_dec);
		printf("\nDecimal Netmask: %u\n", net_dec);
		
		if (r == 0 && rn == 0){

			//Bitwise AND on given IP and Subnet and print result
		
			uint32_t bitw_and = (ip_dec & net_dec);
			printf("\nDecimal Network Starting Address: %u\n",bitw_and);

			//Allocate new char array to hold dot quad formatted start ip

			char * start_ip = malloc(16 * sizeof(char));
			todotquad(bitw_and+1, start_ip);

			//We do NOT dereference the array when passing it to printf as a C-string!!!!
			printf("\nStarting address is: %s", start_ip);

			//Bitwise OR between First IP and Bitwise-NOT network mask
			uint32_t bitw_or = (bitw_and | ~net_dec);
			char * end_ip = malloc(16 * sizeof(char));
			printf("\nDecimal Network Last Address: %u\n",bitw_or);
			todotquad(bitw_or, end_ip);
			printf("\nLast Address is: %s", end_ip);

			//Finally, we print usable hosts:
			printf("\nUsable Hosts: %u", bitw_or-bitw_and);
		
		}
	}
	else {
		printf("\nError: Too many/Too Few arguments\n");
		usage();
		return 1;
	}
	return 0;
}
