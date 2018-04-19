#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
#define PERM IPC_CREAT
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
// initialize 
int set_semvalue(int sem_id){
	union semun sem_union;
	sem_union.val=1;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        return 0;
    }
    return 1;
}	
// substract one occupy release
static int semaphore_p(int sem_id) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;//P()
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sem_b, 1) == -1)
    {
        return 0;
    }
    return 1;
}
// add one release source
static int semaphore_v(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;//V()
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sem_b, 1) == -1)
    {
        return 0;
    }
    return 1;
}
// delete sem
static void del_semvalue(int sem_id)
{
    union semun sem_union;
 
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
    }
}


int main() {
	int shmid=shmget(IPC_PRIVATE,1024,PERM|0666);
	if(-1==shmid){
		cout<<"fail to allocate shm"<<endl;
		return 0;
	}
	int semid=semget((key_t)3524,1,0666|PERM);
	if (-1==semid) {
		cout<<"fail to allocate sem"<<endl;
		return 0;
	}
	cout<<"shmid: "<<shmid<<endl; 
	cout<<"semid: "<<semid<<endl;
	void * addr=shmat(shmid,0,SHM_RND);
	char * op= (char *)addr ;
	if(-1== set_semvalue(semid)) {
		cout<<"fail to initialize signal"<<endl;
		return 0;
	}
	while(1) {
		semaphore_p(semid);
		op[1]='h';
		op[1]=op[1]+1;
		semaphore_v(semid);
	}
	return 0;
}
