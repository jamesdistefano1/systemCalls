#include <mycp.h>

int main(int argc, char *argv[]){
  // this will fail the program unless it is called with exactly two files
  if ((argv[0] == NULL) || (argv[1] == NULL) || (argv[2] == NULL) || (argv[3] != NULL)){
    printf("failed");
    return 0;
  }

  int fd1;
  int fd2;
  char buf[BUFFSIZE];
  int isOk1;
  int isOk2;
  int n;
  // copies errno so that it can be made into a string
  int errnum;

  char* toDelete;

  // access returns 0 if the file can be accessed, fails otherwise and runs
  //    the code in the if statement
  isOk1 = access(argv[1], F_OK);
  errnum = errno;
  if (isOk1 != 0){
    printf("Unable to access first file.  Value of errno: %d\n ", errno);
    printf("The error message is : %s\n",  strerror(errnum));
    perror("Message from perror");
  }


  // open, read, and write return a negative number if they fail, which will
  //    cause the if statements to execute
  fd1 = open(argv[1], O_RDWR);
  errnum = errno;
  if (fd1 < 0){
    printf("Unable to open first file.  Value of errno: %d\n ", errno);
    printf("The error message is : %s\n",  strerror(errnum));
    perror("Message from perror");
  }

  isOk2 = access(argv[2], F_OK);
  if (isOk2 == 0){
    int choice;
    printf("are you sure you want to overwrite this file? type 1 for yes, 2 for no   \n");
    scanf("%d", &choice);
    printf("%d", choice);
    switch(choice){
      case 1:
        fd2 = open(argv[2], O_RDWR);
        errnum = errno;
        if (fd2 < 0){
          printf("Unable to open second file.  Value of errno: %d\n ", errno);
          printf("The error message is : %s\n",  strerror(errnum));
          perror("Message from perror");
        }
        break;
      case 2:
        printf("got it.  exiting program now \n");
        return 0;
      }
    }
    else {
      fd2 = open(argv[2], O_RDWR | O_CREAT);
      errnum = errno;
      if (fd2 < 0){
        printf("Unable to open second file.  Value of errno: %d\n ", errno);
        printf("The error message is : %s\n",  strerror(errnum));
        perror("Message from perror");
      }
    }

  n = read(fd1, buf, BUFFSIZE);
  errnum = errno;
  if (n < 0){
    printf("Unable to read first file.  Value of errno: %d\n ", errno);
    printf("The error message is : %s\n",  strerror(errnum));
    perror("Message from perror");
  }

  write(fd2, buf, n);
  errnum = errno;
  if (n < 0){
    printf("Unable to write into second file.  Value of errno: %d\n ", errno);
    printf("The error message is : %s\n",  strerror(errnum));
    perror("Message from perror");
  }

  // closes the files back up so they cannot be accessed
  close(fd1);
  close(fd2);
}
