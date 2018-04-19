#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
#define PERM IPC_EXCL|IPC_CREAT
int main() {
	int shmid=shmget(IPC_PRIVATE,1024,PERM|0666);
	cout<<shmid<<endl;
	void * addr=shmat(shmid,0,SHM_RND);
	char * op= (char *)addr ;
	cout<<op<<endl;
	for(int i=0;i<1024;i++) {
		op[i]='i'; 
		cout<<i;
	}
	cout<<endl;
	while (true) {
		;
	}
	return 0;
}
