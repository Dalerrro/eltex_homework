#obj-m += sleep.o
#obj-m += example_rwlock.o
#obj-m += completions.o
#obj-m += example_mutex.o

#obj-m += example_tasklet.o
obj-m += example_sched.o

PWD := $(CURDIR)
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
