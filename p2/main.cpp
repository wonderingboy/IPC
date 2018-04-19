#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main(int argc,char* argv[]) {
	int shid=atoi(argv[1]);
	cout<<shid<<endl;
	char *addr=(char*) shmat(shid,0,0);
	for(int i=0;i<1024;i++) {
		cout<<addr[i]<<" ";
	} 
	cout<<endl;
	while(1){
		;
	}	
	return 0;
}
