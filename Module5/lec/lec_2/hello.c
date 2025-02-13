#include <stdio.h>

struct file_operations fops = {
	.read = device_read,
	.release = device_release
};

int main(void)
{
	printf("hello");
	return 0;
}
