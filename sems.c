#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 0

int main(int argc, char *argv[]) {
  int md, val;
  md = semget(KEY, 4, IPC_CREAT | 0666);
  if (!strcmp(argv[1], "-c")) {
    if (argv[2]) {
      if (md) {
        printf("Semaphore created: %d\n", md);
        printf("argv %s\n", *argv[2]);
        semctl(md, 0, SETVAL, *argv[2]);
        val = semctl(md, 0, GETVAL);
        printf("value set: %d\n", val);
      }
      else {

      }
    }
    else {
      printf("Missing value argument\n");
    }
  }
  else if (!strcmp(argv[1], "-v")) {
    val = semctl(md, 0, GETVAL);
    printf("semaphore value: %d\n", val);
  }
  else if (!strcmp(argv[1], "-r")) {

  }
  return 0;
}
