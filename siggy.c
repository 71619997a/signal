#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

static char intmsg[50] = "Program exited (SIGINT)\n";

static void sighandler(int sig) {
  if(sig == SIGINT) {
    int fd = open("log.txt", O_APPEND | O_WRONLY);
    write(fd, intmsg, strlen(intmsg));  // kept breaking w/o exact num
    close(fd);
    exit(0);
    return;
  }
  else if(sig == SIGUSR1) {
    printf("Parent PID: %d\n", getppid());
    return;
  }
  else {
    printf("Unknown signal %d, how is this being handled?", sig);
    exit(1);
    return;
  }
}

int main() {
  if(signal(SIGINT, sighandler) == SIG_ERR)
    printf("Error catching SIGINT\n");
  if(signal(SIGUSR1, sighandler) == SIG_ERR)
    printf("Error catching SIGUSR1\n");
  while(1) {
    printf("PID: %d\n", getpid());
    sleep(1);
  }

}
