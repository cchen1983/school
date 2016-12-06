#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 6052

#define MAX_DN 256

#ifndef readline
/**
 *  *  * readline() - read an entire line from a file descriptor until a newline.
 *   *   * functions returns the number of characters read but not including the
 *    *    * null character.
 *     *    **/
int readline(int fd, char *str, int maxlen)
{
  int n;           /* no. of chars */
  int readcount;   /* no. characters read */
  char c;

  for (n = 1; n < maxlen; n++) {
    /* read 1 character at a time */
    readcount = read(fd, &c, 1); /* store result in readcount */
    if (readcount == 1) /* 1 char read? */
    {
      *str = c;      /* copy character to buffer */
      str++;         /* increment buffer index */
      if (c == '\n') /* is it a newline character? */
         break;      /* then exit for loop */
    }
    else if (readcount == 0) /* no character read? */
    {
      if (n == 1)   /* no character read? */
        return (0); /* then return 0 */
      else
        break;      /* else simply exit loop */
    }
    else
      return (-1); /* error in read() */
  }
  *str=0;       /* null-terminate the buffer */
  return (n);   /* return number of characters read */
} /* readline() */
#endif
extern int readline(int fd, char *buf, int max);
