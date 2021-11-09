#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>

struct Shortcut {
	char* string;
	int keyCount;
	unsigned short* keys;
};

unsigned short sh1_keys[] = {25, 18}; // P + E
unsigned short sh2_keys[] = {46, 30, 25}; // C + A + P
unsigned short sh3_keys[] = {17, 31, 38}; // W + S + L

int shortcutCount = 3;
struct Shortcut shortcuts[] = {
	{"I passed the Exam!", 2, sh1_keys}, 
	{"Get some cappuccino!", 3, sh2_keys},
	{"Didn't work, installed VM :(", 3, sh3_keys}, 
};

char getChar(int key) {
	switch (key) {
		case 17: return 'W';
		case 18: return 'E';
		case 25: return 'P';
		case 30: return 'A';
		case 31: return 'S';
		case 38: return 'L';
		case 46: return 'C';
	}
	
	return '\0';
}

int main() {
	int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
	if (fd < 0) {
		printf("Open system call failed\n");
		perror("Cause ");
		return -1;
	}
	
	printf("Hello! Here are the available shortcuts:\n");
	for (int i = 0; i < shortcutCount; i++) {
		for (int j = 0; j < shortcuts[i].keyCount; j++) {
			printf("%c", getChar(shortcuts[i].keys[j]));
			if (shortcuts[i].keyCount - j > 1) printf(" + ");
		}
		printf("\n");
	}
	printf("\n");
	
	struct input_event buffer;
	int structSize = sizeof(struct input_event);
	struct Shortcut *current = NULL;
	int index = 0;
	
	while (1) {
		if (read(fd, &buffer, structSize) < structSize) continue;
		if (buffer.type != EV_KEY) continue; // we need only keyboard events
		
		if (buffer.value == 0) { // Key released
			current = NULL; // any released key interrupts shortcut (for simplicity)
			continue;
		}
		
		if (buffer.value == 1) { // key pressed
			if (current == NULL) { // if no shortcut is tracked, find some
				for (int i = 0; i < shortcutCount; i++) {
					if (shortcuts[i].keys[0] == buffer.code) {
						current = &shortcuts[i];
						index = 1;
						break;
					}
				}
			} else { // if some shortcut was tracked, check it
				if (current->keys[index] == buffer.code) {
					index++;
				} else {
					current = NULL;
				}
			}
		}
		
		if (current != NULL && current->keyCount <= index) {
			printf("\n%s\n", current->string);
			current = NULL; // after triggering a shortcut, reset
		} 
	}
	
	return 0;
}