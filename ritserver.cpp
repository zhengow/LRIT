#include "ritserver.h"

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<fstream>

#define PORT 3389
#define LISTEN_NUM 5

using namespace std;

void GetPrice(float* res){
	int random = rand()%10;
	ifstream inFile;
	string filename("RTMPrice_2.csv");
	
	inFile.open(filename);
	for(int i=0;i<600;i++){
		inFile >> res[i];
	}
	return;
}

int main(){
	
	float price[600];
	GetPrice(price);

	//create server's socket
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if( -1 == socketServer){
		cout << "Socket create error";
		return 0;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("172.17.0.6");
 	
	//bind address to server's socket	
	int bRes = bind(socketServer, (const struct sockaddr*)&server_addr, sizeof(server_addr));	
	if(-1 == bRes){
		cout << "Bind error";
		return 0;
	}	
	
	//begin listening
	if(-1 == listen(socketServer, LISTEN_NUM)){
		cout << "Listen error";
		return 0;
	}

	char buf[1024];
	
	while(1){
		cout << "Working" << std::endl;
		int socketClient = accept(socketServer, NULL, NULL);
		if( -1 == socketClient){
			cout << "Connection error";
			return 0;
		}
		else{
			cout << "Connection success" << std::endl;
		}
		
		/*int sRes = send(socketClient, "Welcome", 7, 0);

		if( -1 == sRes){
			cout << "Send error";
			shutdown(socketClient,SHUT_RDWR);
			return 0;
		}
		*/
		
		int cur = 0;
		char buf[4];
		while(cur<100){
			memcpy(buf,&price[cur],4);
			int sRes = send(socketClient, buf, 4, 0);
			cout << "Now is" << cur << endl;
			if( -1 == sRes){
				cout << "Send error";
				shutdown(socketClient,SHUT_RDWR);
				return 0;
			}
			else
				cout << "Send Success" << endl;
				
		
			cur++;
		}

	
		
		
		while(1)
		{
			cout << "Stop" <<endl;
			sleep(5);
		}
		
		shutdown(socketClient,SHUT_RDWR);
		
	}	
	return 0;


}
