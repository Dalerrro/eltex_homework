/*
 * example_mutex.c
 */
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/printk.h>

static DEFINE_MUTEX(mymutex);

static int __init example_mutex2_init(void)
{
    int ret;

    pr_info("example_mutex2 init\n");

    ret = mutex_trylock(&mymutex);
    if (ret != 0) {
        pr_info("mutex2 is locked\n");

        if (mutex_is_locked(&mymutex) == 0)
            pr_info("The mutex2 failed to lock!\n");

	//mutex_unlock(&mymutex);
        pr_info("mutex2 is unlocked\n");
    } else
        pr_info("Failed 2 to lock\n");

    return 0;
}

static void __exit example_mutex2_exit(void)
{
    pr_info("example_mutex exit\n");
}

module_init(example_mutex2_init);
module_exit(example_mutex2_exit);

MODULE_DESCRIPTION("Mutex2 example");
MODULE_LICENSE("GPL");
