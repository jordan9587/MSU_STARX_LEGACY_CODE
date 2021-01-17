#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int open_port(void){
  int fd; // File descriptor for the serial port
  fd = open("/dev/pts/1", O_RDWR | O_NOCTTY | O_NDELAY);
  // "/dev/pts/1" = Name of serial port
  // O_RDWR = Allows read/write access to serial port
  // O_NOCTTY = No terminal will control the process
  // O_NDELAY = Non blocking mode (do not care about the DCD line status)
  if (fd == -1){
    perror("\nopen_port: Unable to open serial port - ");
  }
  else{
    printf("\nPort opened successfully!\n");
  }
  return (fd);
}

void set_port(int fd){
  struct termios options; // Creates the structure
  tcgetattr(fd, &options); // Gets the current attributes

  cfsetispeed(&options,B9600); // Sets read speed to 9600 bps
  cfsetospeed(&options,B9600); // Sets write Speed to 9600 bps

  options.c_cflag &= ~PARENB; // Disables parity
  options.c_cflag &= ~CSTOPB; // Sets the stop bits amount to 1
  options.c_cflag &= ~CSIZE; // Clears the mask for setting the data size
  options.c_cflag |=  CS8; // Set the data bits amount to 8
  options.c_cflag &= ~CRTSCTS; // Disables hardware flow control
  options.c_cflag |=  (CREAD | CLOCAL); // Enables receiver and sets local mode
  options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disables software flow control
  options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Selects raw input mode
  options.c_oflag &= ~OPOST; // Selects raw output mode

  if((tcsetattr(fd, TCSANOW, &options)) != 0){ // Sets the new attributes
    perror("\nset_port: Error in setting attributes - ");
  }
  else{
    printf("\n| Baud rate = 9600 bps | Stop bits = 1 | Parity = None |\n");
  }
}

int write_port(int fd, char *buffer_write, size_t buffer_size){
  int bytes_write = write(fd, buffer_write, buffer_size);
  if (bytes_write < 0){
    fputs("write() of bytes failed!\n", stderr);
  }
  return (bytes_write);
}

int read_port(int fd, char *buffer_read, size_t buffer_size){
  int bytes_read = read(fd, buffer_read, buffer_size);
  return (bytes_read);
}

void close_port(int fd){
  close(fd);
}

int main(){
  int fd, bytes_write = 0, bytes_read = 0;
  char buffer_write[] = "What is your name?:";
  char buffer_read[32];

  fd = open_port(); // Funtion to open serial port
  set_port(fd); // Function to set serial port options
  while(bytes_write < 1){ // Writes until at least 1 byte is transmitted
    bytes_write = write_port(fd, buffer_write, sizeof(buffer_write)); // Function to write to serial port
  }
  while(bytes_read < 1){ // Reads until at least 1 byte is received
    bytes_read = read_port(fd, buffer_read, sizeof(buffer_read)); // Function to read from serial port
  }
  for(int i=0; i<bytes_read; i++){ // Print message received from serial port
    printf("%c",buffer_read[i]);
  }
  close_port(fd); // Function to close serial port
  return 0;
}
