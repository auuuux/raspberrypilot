#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

//char *portname = "/dev/ttyS0";
char *portname = "/dev/ttyAMA0";

static int serial_fd_read;
//static int serial_fd_write;

// opens and configures the serial port, returns its file descriptor, stores its file descriptor
int32_t serial_open(void) {
	// open the port
	serial_fd_read = open (portname, O_RDWR| O_NOCTTY | O_SYNC);
	if (serial_fd_read < 0)
	{
		perror("While opening read serial port ");
		return -1;
	}
	//serial_fd_write = open (portname,  O_WRONLY| O_NOCTTY | O_SYNC);
	//if (serial_fd_write < 0)
	//{
	//	perror("While opening write serial port ");
	//	return -1;
	//}


	struct termios options;
	tcgetattr(serial_fd_read, &options);
	cfsetispeed(&options,B57600);
	cfsetospeed(&options,B57600);
	options.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR | ICRNL;
	options.c_oflag = 0;
	tcflush(serial_fd_read, TCIFLUSH);
	tcsetattr(serial_fd_read,TCSANOW, &options);
	return serial_fd_read;
}

int32_t serial_write(uint8_t *buf, uint32_t len) {
	return write(serial_fd_write,buf,len);
}