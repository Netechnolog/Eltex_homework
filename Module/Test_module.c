#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>

static struct file_operations;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};

static int major = 0;
static rwlock_t lock;
static char string[15] = "Hello!\0";

ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off)
{
    size_t rc;
    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string, 15);
    read_unlock(&lock);

    return rc;
}

ssize_t test_write(struct file *fd, char __user *buff, size_t size, loff_t *off)
{
    size_t rc = 0;
    if(size > 15)
    {
        return -EINVAL;
    }

    write_lock(&lock);
    rc = simple_write_to_buffer(string, 15, off, buff, size);
    write_unlock(&lock);

    return rc;
}

int init_module(void)
{
    int retval = 0;
    pr_info("Test module loaded\n");
    rwlock_init(&lock);
    major = register_chrdev(major, "test", &fops);
    if(major < 0)
    {
        pr_info("Major = %d\n", major);
    }
    return 0;
}


void cleanup_module(void)
{
    unregister_chrdev(major, "test");
    pr_info("Test module unloaded\n");
}


MODULE_LICENSE("GPL");

