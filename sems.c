#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 23

int main(int argc, char *argv[]) {
  int md, val;

  if (argc > 1) {
    if (!strcmp(argv[1], "-c")) {
      if (argv[2]) {
        md = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
        if (md == -1) {
          printf("semaphore already exists\n");
          return 0;
        }
        printf("semaphore created: %d\n", md);
        printf("argv %d\n", atoi(argv[2]));
        semctl(md, 0, SETVAL, atoi(argv[2]));
        val = semctl(md, 0, GETVAL);
        //val = atoi(argv[2]);
        printf("value set: %d\n", val);
      }
      else {
        printf("Missing value argument\n");
      }
    }
    else if (!strcmp(argv[1], "-v")) {
      md = semget(KEY, 1, 0664);
      val = semctl(md, 0, GETVAL);
      printf("semaphore value: %d\n", val);
    }
    else if (!strcmp(argv[1], "-r")) {
      md = semget(KEY, 1, 0664);
      val = semctl(md, 0, IPC_RMID);
      printf("semaphore removed: %d\n", val);
    }
  }
  else {
    printf("Incorrect arguments\n");
  }
  return 0;
}
