#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
#define PERM IPC_EXCL|IPC_CREAT
int main() {
	int shmid=shmget(IPC_PRIVATE,1024,PERM);
	cout<<shmid<<endl;
	void * addr=shmat(shmid,0,0);
	char * op= (char *)addr ;
	for(int i=0;i<1024;i++)
		op[i]=i%255; 
	return 0;
}
