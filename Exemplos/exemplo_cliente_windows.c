#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 6000
#define MAX_MSG 100

int main(int argc, char *argv[]) {
  
  int sd, rc, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry; 
       
  /* check command line args */
  if(argc<3) {
    printf("usage : %s <Server> <data1> ... <dataN> \n", argv[0]);
    exit(1);
  }

  WSAStartup(MAKEWORD(2,1),&wsaData);

  lpHostEntry = gethostbyname(argv[1]);
  if (lpHostEntry == NULL)
  {
       printf("gethostbyname()");
       exit(1);
  }
  /* socket creation */
  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    printf("%s: cannot open socket \n",argv[0]);
    exit(1);
  }

  /* bind any port */
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);
  
  remoteServAddr.sin_family = AF_INET;
  remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
										// ^ Server's address
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);	// Port number from command line

  /* send data */
  for(i=1;i<argc;i++) {
    rc = sendto(sd, argv[i], strlen(argv[i])+1, 0, 
		(LPSOCKADDR) &remoteServAddr, 
		sizeof(struct sockaddr));
    if(rc<0) {
      printf("%s: cannot send data %d \n",argv[0],i-1);
      closesocket(sd);
      exit(1);
    }
  }
  closesocket(sd);
  return 1;

}

