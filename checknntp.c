
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

#include <errno.h>

#define DEFAULT_ALARMSEC 20

int main(int argc, char *argv[]) {

  int in_fd;
  int out_fd;

  int retval;

  char hostname[120];

  long int retcode;
  
  long int version[3];

  char status[20];
  
  char posting_str[10];

  FILE *fp;
  size_t len;
  char *line;

  ssize_t bytes_written;

  long int timeout_interval;

  timeout_interval = argc>1 ? strtol(argv[1],NULL,10) : DEFAULT_ALARMSEC;
  
  in_fd = 6;
  out_fd = 7;

  fp = fdopen(in_fd, "r");
  if (fp == NULL) {
    perror("fdopen");
    return -1;
  }

  len = 0;
  line = NULL;

  alarm(timeout_interval);
  
  while ((retval = getline(&line,&len,fp)) != -1) {

    if (len <= 0) {
      continue;
    }

    if (!strncmp(line, "205 Bye!", 8)) {
      printf("SUCCESS");
      return 0;
    }
    
    retval = sscanf(line, "%ld %[^ ] InterNetNews NNRP server INN %ld.%ld.%ld %[^ ] (posting %[^)])", &retcode, hostname, version+0, version+1, version+2, status, posting_str);

    if (retval == 7 && retcode == 200) {

      bytes_written = write(out_fd, "QUIT\r\n", 6);
      if  (bytes_written != 6) {
	perror("write");
	return -1;
      }
      
    }
    
  }
    
  printf("FAIL");
  
  return -1;
  
}
