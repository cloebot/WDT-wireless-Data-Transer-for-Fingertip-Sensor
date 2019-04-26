#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

void readFile(int fd) {
    char buffer[10];
    int bytes_read;
    int k = 0;
    do {
        char t = 0;
        bytes_read = read(fd, &t, 1);
        if (bytes_read < 0) {
            printf("    read failed!\n", stderr);
        } else if (bytes_read = 0) {
            printf("    No data!\n", stderr);
        } else {
            buffer[k++] = t;
            printf("%c", t);
            if(t == '\n' && t == '\0') {
                printf("%d", atoi(buffer));
                int i;
                for(i=0; i<10; i++)
                    buffer[i]='\0';
                k = 0;
            }
        }
    }
    while (bytes_read != 0);
}

int main (void)
{
  printf("\n +----------------------------------+");
  printf("\n |        Serial Port read          |");
  printf("\n +----------------------------------+");

  // open serial device
  int fd;
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
  perror("\nopen_port: Unable to open /dev/ttyS0 ");
  }
  else
  printf("\nsucceed to open ttyS0 port...");
  fcntl(fd, F_SETFL, 0);
  //Set baudrate to 9600
  struct termios options;
  tcgetattr(fd, &options);
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);

  // Set parity - No Parity (8N1)

  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  //Turn off hardware based flow control (RTS/CTS).
  options.c_cflag &= ~CRTSCTS;

  // Turn on the receiver of the serial port (CREAD)
  options.c_cflag |= CREAD | CLOCAL;

  // // Serial communications with outside devices
  // // NON Cannonical mode is recommended.

  options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                       | INLCR | IGNCR | ICRNL | IXON);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

  options.c_oflag &= ~OPOST;/*No Output Processing*/

  /* Setting Time outs */
  options.c_cc[VMIN]  = 10; /* Read 10 characters */
  options.c_cc[VTIME] = 0;  /* Wait indefinitely   */

  if ( tcsetattr( fd, TCSANOW, &options ) == -1 )
      printf ("\nError with tcsetattr = %s\n", strerror ( errno ) );
  else
      printf ( "%s\n", "tcsetattr succeed" );
      printf("\n  BaudRate = 9600 \n  StopBits = 1 \n  Parity   = none");

  printf("\n\n-> start reading data\n");
  do {
      unsigned char buffer[32];
      ssize_t length = read(fd, &buffer, sizeof(buffer) - 1);
      if (length == -1)
      {
          printf("Error reading from serial port\n");
          break;
      }
      else if (length == 0)
      {
          printf("No more data\n");
          break;
      }
      else
      {
          buffer[length] = '\0';
          printf("%s\n", buffer);
      }
  } while (1);

  // //Write text
  // int n;
  // n = write(fd, "Hello world!\r", 13);
  // if (n < 0)
  //         fputs("write() failed!\n", stderr);

  // n = write(fd, "Printed using the VoCore v1.0\r", 30);
  // if (n < 0)
  //         fputs("write() failed!\n", stderr);

  // n = write(fd, ":)\r", 3);
  // if (n < 0)
  //         fputs("write() failed!\n", stderr);

  //close connection
  close(fd);
  return printf("End\n");
}
