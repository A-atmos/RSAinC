#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <math.h>
#define MAX 100
#define PORT 8080
#define SA struct sockaddr

#include "RSA.h"


int p,q;
long int n,phifunction,client_publickey,client_n;
struct keys keyed;

//function Decalrations

void generate();
void func(int);

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	//Generate the keys
	generate();
	printf("\n\n");

	// socket create and verification
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");



	printf("\n\n");
	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
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


// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	long int tosend[MAX];
	int i1,i2;

	// //receive the public key and n from client
	read(sockfd, &client_n, sizeof(client_n));
	// write(sockfd, n, sizeof(n));
	write(sockfd, &n, sizeof(n));
	//send public key and n to client
	read(sockfd, &client_publickey, sizeof(client_publickey));
	write(sockfd, &keyed.e, sizeof(keyed.e));

	printf("Modulo of Client: %li\n",client_n);
	printf("Public Key oif Client: %li\n",client_publickey);

	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);
		bzero(tosend, sizeof(tosend));

		// read the message from client and copy it in tosend
		read(sockfd, &tosend, sizeof(tosend));

		//decrypting the data from integer format to string format and storing in buff

		i1 = (sizeof(tosend)/sizeof(int));

		for(i2=0;i2<i1;i2++){
			buff[i2] = decrypt(tosend[i2],keyed.d,n);
		} 


		// print buffer which contains the client contents
		printf("\nFrom client: %s\n\t To client :", buff);
		bzero(buff, MAX);
		bzero(tosend, sizeof(tosend));
		i1 = 0;
		// copy server message in the buffer
		// printf("Here");
		fflush(stdin);
		gets(buff);
		fflush(stdin);
		// printf("%d",i1);
		// printf("%s",buff);
		i2=0;
		for(i2=0;i2<strlen(buff);i2++){
			tosend[i2] = encrypt((long int)buff[i2],client_publickey,client_n);
		}

		// and send that tosend to client
		write(sockfd, &tosend, sizeof(tosend));


		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("\n----Server Exit...----\n");
			break;
		}
	}
}