#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  int pid1, pid2;
  int count1 = 0, count2 = 0;

  // Child 1: 1 ticket
  pid1 = fork();
  if(pid1 == 0){
    settickets(1);
    for(int i = 0; i < 500000; i++) count1++;
    printf(1, "child1 (1 ticket): done\n");
    exit();
  }

  // Child 2: 3 tickets
  pid2 = fork();
  if(pid2 == 0){
    settickets(3);
    for(int i = 0; i < 500000; i++) count2++;
    printf(1, "child2 (3 tickets): done\n");
    exit();
  }

  wait();
  wait();
  printf(1, "lotterytest: done\n");
  exit();
}