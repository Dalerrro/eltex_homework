/*
 my_module.с
 запись времени добавления в ядро модуля и времени удаления.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/timekeeping.h>
#include <linux/time64.h>

#define LOG_FILE "/var/log/my_module.log"

static void log_time(const char *action) {
    struct timespec64 now;
    struct tm tm; 
    struct file *file;
    char buffer[128];
    int len;
    
    ktime_get_real_ts64(&now);
    time64_to_tm(now.tv_sec, 0, &tm); 

    len = snprintf(buffer, sizeof(buffer), 
                   "%s: %04d-%02d-%02d %02d:%02d:%02d\n",
                   action, 
                   tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,  
                   tm.tm_hour, tm.tm_min, tm.tm_sec);  

    file = filp_open("/var/log/my_module.log", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (IS_ERR(file)) {
        printk(KERN_ERR "Failed to open file: %ld\n", PTR_ERR(file));
        return;
    }

    kernel_write(file, buffer, len, &file->f_pos);
    filp_close(file, NULL);
}

static int __init my_module_init(void) {
    pr_info("My module loaded\n");
    log_time("Module loaded");
    return 0;
}

static void __exit my_module_exit(void) {
    pr_info("My module unloaded\n");
    log_time("Module unloaded");
}

module_init(my_module_init);
module_exit(my_module_exit);


MODULE_LICENSE("GPL");