#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <joystick_pi.h>

int main(int argc, char *argv[])
{
	
	int leftStick;
	int rightStick;
	int nunchukStick_x;
	int nunchukStick_y;
	int fwdSpeed;
	int bwdSpeed;
	int speed;	
	int fd, rc;
	int done = 0;

	struct js_event jse;

	fd = open_joystick();
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}

	while (!done) {
		rc = read_joystick_event(&jse);
		usleep(100);
		if (rc == 1) {
			//printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n", jse.time, jse.value, jse.type, jse.number);
		
			// Left stick position
			if( jse.number == 1 && jse.type == 2) 
				leftStick = jse.value;
				
			// Right stick position
			if( jse.number == 3 && jse.type == 2) 
				rightStick = jse.value;	
					
			// ? = 32767 / 128
					
			int leftSpeed = (leftStick * -1) / 128;
			int rightSpeed = (rightStick * -1) / 128;
			printf(" LeftSpeed %d, RightSpeed %d \n", leftSpeed, rightSpeed);
		}
	}
}
