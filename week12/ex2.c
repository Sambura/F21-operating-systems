#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>

const char* STATES_MAP[] = {"RELEASED", "PRESSED", "REPEATED"};

int main() {
	int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
	if (fd < 0) {
		printf("Open system call failed\n");
		perror("Cause ");
		return -1;
	}
	
	struct input_event buffer;
	int structSize = sizeof(struct input_event);
	
	while (1) {
		if (read(fd, &buffer, structSize) < structSize) continue;
		if (buffer.type != EV_KEY) continue; // we need only keyboard events
		
		const char* state = STATES_MAP[buffer.value];
		
		printf("\n%s 0x%X (%d)\n", state, buffer.code, buffer.code);
	}
	
	return 0;
}