#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static void sighandler(int sig) {
  if(sig == SIGINT) {
    int fd = open("log.txt", O_APPEND | O_WRONLY);
    write(fd, "Program exited (SIGINT)", 50);
    close(fd);
    exit(0);
  }
  else if(sig == SIGUSR1) {
    printf("Parent PID: %d\n", getppid());
  }
  else {
    printf("Unknown signal %d, how is this being handled?", sig);
    exit(1);
  }
}

int main() {
  setbuf(stdout, NULL);
  if(signal(SIGINT, sighandler) == SIG_ERR)
    printf("Error catching SIGINT\n");
  if(signal(SIGUSR1, sighandler) == SIG_ERR)
    printf("Error catching SIGUSR1\n");
  while(1) {
    printf("PID: %d\n", getpid());
    sleep(1);
  }

}
