#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <winsock2.h>
#include <windows.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif



#define MAX 100
#define PORT 8080
#define SA struct sockaddr


#include "RSA.h"

//global variable declarations
int p,q;
long int n,phifunction,server_publickey,server_n;
struct keys keyed;

//function declarations
void generate();
void func(int);


int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;


	//generate the private and public keys:
	generate();
	printf("\n\n");
	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}

void generate(){
   while(1){
        //Takes input if the numbers are prime else asks again for input
        printf("Enter the first prime number\n");
        scanf("%d",&p);
        fflush(stdin);
        printf("Enter the second prime number\n");
        scanf("%d", &q);
        fflush(stdin);
        int is_prime_p,is_prime_q;
        is_prime_p = check_prime(p);
        is_prime_q = check_prime(q);
        // printf("%d %d", is_prime_p,is_prime_q);
        if( is_prime_p && is_prime_q){
            break;
        }
        else{
            printf("Enter the pair of prime numbers\n");
        }

    }
    phifunction = (long int)((p-1)*(q-1));
    n = (long int)(p * q);

    keyed = generate_keys(phifunction);
    printf("Public Key: %li\n",keyed.e);
    printf("Private Key: %li\n",keyed.d);
    printf("Modulo: %li\n",n);

}

void func(int sockfd)
{
    char buff[MAX];
	long int tosend[MAX];
    int i1,i2;

	//send public key and n to server

	write(sockfd, &n, sizeof(n));
	read(sockfd, &server_n, sizeof(server_n));

	//receive the public key and n from server
	write(sockfd, &keyed.e, sizeof(keyed.e));
	read(sockfd, &server_publickey, sizeof(server_publickey));

	printf("Modulo of Server: %li\n",server_n);
	printf("Public Key oif Server: %li\n",server_publickey);

    for (;;) {
        bzero(buff, sizeof(buff));
        printf("\n\tTo Server : ");
        i1 = 0;
        gets(buff);

		for(i2=0;i2<strlen(buff);i2++){
			// printf("%c",buff[i2]);
			tosend[i2] = encrypt((long int)buff[i2],server_publickey,server_n);
		}

		//sending encrypted data in integer format
        write(sockfd, &tosend, sizeof(tosend));

		//clearing the values of buff and tosend
        bzero(buff, sizeof(buff));
		bzero(tosend, sizeof(tosend));

		//reading the sent data by server in integer format
        read(sockfd, &tosend, sizeof(tosend));
		
		//decrypting the data from integer format to string format and storing in buff

		// i1 = (sizeof(tosend)/sizeof(int));
		int i = 0;

		// while(tosend[++i]!='\0'){
		// 	printf("\n\n\n----%li----\n\n",tosend[i-1]);
		// 	}

		printf("\n\n--------------------------------------------------------\nValue before decryption: \n");
		while(tosend[i]!=0){
			printf("%d,",tosend[i]);
			buff[i] = decrypt(tosend[i],keyed.d,n);
			i++;
		}
		// for(i2=0;i2<i1;i2++){
		// 	printf("%d,",tosend[i2]);
		// 	buff[i2] = decrypt(tosend[i2],keyed.d,n);
		// } 
		printf("\n-----------------------------------------------------------------\n");

		//printing the data
        printf("\nFrom Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("\n----Client Exit...----\n");
            break;
        }
    }
}
