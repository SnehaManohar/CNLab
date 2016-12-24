#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int soc, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr;

    /*  socket creates an endpoint for communication and returns a file descriptor */
    /*soc is our socket descriptor for later use returns -1 if we have a error
	int socket(int domain,int type,nt protocol)*/
	soc = socket(PF_INET, SOCK_STREAM, 0);//protocol family

    /*
     * sockaddr_in is used for ip manipulation
     * we define the port and IP for the connection.
     */
    addr.sin_family = AF_INET;//address family
    addr.sin_port = htons(7891);//htons() function converts the unsigned sort integer hostshort from host byte order to network byte order
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");//LINE I GO WRONG

    /*  keep trying to esatablish connection with server */
    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server");
    printf("\nEnter file name: ");
    scanf("%s", fname);
    /*  send the filename to the server */
    send(soc, fname, sizeof(fname), 0);

    printf("\nRecieved response\n");
    /*  keep printing any data received from the server */
    while ((n = recv(soc, buffer, sizeof(buffer), 0)) > 0)
        printf("%s", buffer);

    return 0;
}
