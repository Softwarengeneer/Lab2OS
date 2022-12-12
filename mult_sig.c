#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/pci.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("A simple module of getting MULTIPROCESS_SIGNAL structure");
MODULE_AUTHOR("Nikita Kuznetsov");
MODULE_VERSION("1.0");

struct dentry *kmod_root;
struct dentry *debugfs_file_kmod;
struct dentry *pid_task_struct;
struct debugfs_blob_wrapper pid_wrapper;
struct task_struct *ts1;
struct multiprocess_signal_info *msi;
struct user_message *u_msg;

char data[PAGE_SIZE];
char str[100];

int data_len = 0;

pid_t pid = 1;


struct multiprocess_signal_info {
    int nr_threads;
    unsigned int flags;
    unsigned int sigHandlers[_NSIG];
};

struct user_message {
    struct multiprocess_signal_info u_msi;
};

ssize_t file_write_operation(struct file *f, const char *buffer, size_t len, loff_t *off) {
    return len;
}
ssize_t file_read_operation(struct file *f, char *buffer,
                            size_t len, loff_t *off) {
    pr_info("Start read_mult");
    sprintf(str, "Threads in current process (nr_threads): %d \n", u_msg->u_msi.nr_threads);
    sprintf(str, "Signal action handlers (sa_handler): \n");
    sprintf(str, "Flags of signals (flags): %d\n", u_msg->u_msi.flags);
    return len;
}

struct file_operations fops = {
        .write = file_write_operation,
        .read = file_read_operation,
};

int __init ms_init(void) {
    int i = 0;
    printk(KERN_INFO "kmod: module loading.\n");
    kmod_root = debugfs_create_dir("lab2_OS_2", NULL);
    ts1 = get_pid_task(find_get_pid(pid), PIDTYPE_PID);

    msi = vmalloc(sizeof(struct multiprocess_signal_info));
    msi->nr_threads = ts1->signal->nr_threads;
    msi->flags = ts1->signal->flags;
    for (i = 0; i < _NSIG; i++) {
        msi->sigHandlers[i] = (uintptr_t) ts1->sighand->action[i].sa.sa_handler;
    }

    printk(KERN_INFO "Threads in current process (nr_threads): %d\n", msi->nr_threads);
    printk(KERN_INFO "Signal action handlers (sa_handler): \n");
    for (i = 0; i < _NSIG; i++)
        printk(KERN_INFO "%d - 0x%08X\n", i, (unsigned int) msi->sigHandlers[i]);
    printk(KERN_INFO "Flags of signals (flags): %d\n", msi->flags);

    i = 0;


    pid_wrapper.data = (void *) u_msg;
    pid_wrapper.size = sizeof(struct user_message);
    pid_task_struct = debugfs_create_blob("init", 0644, kmod_root, &pid_wrapper);
    debugfs_file_kmod = debugfs_create_file("structure", 0644,
                                            kmod_root, &u_msg,
                                            &fops);
    if (pid_task_struct == NULL) return 1;

    printk(KERN_INFO
    "kmod: data size is %ld.\n", pid_wrapper.size);

    return 0;
}

void __exit ms_exit(void) {
    vfree(msi);
    vfree(u_msg);

    debugfs_remove_recursive(kmod_root);
    printk(KERN_INFO "kmod: module unloaded\n");
}

module_init(ms_init);
module_exit(ms_exit);
