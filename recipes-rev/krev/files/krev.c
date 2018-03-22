
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/time.h>
#include <linux/types.h>

#if 0
static int rev_open(struct inode *inode, struct file *filp) { return 0; }
static int rev_close(struct inode *inode, struct file *filp) { return 0; }
static long rev_unlocked_ioctl(struct file *filp, unsigned int arg,
                               unsigned long cmd) {
  switch (cmd) {
  default:
    printk("REV driver receive Wrong IOCTL command = 0x%lx\n", cmd);
    return -EFAULT;
  }
  return 0;
}

static struct file_operations rev_fops = {
    .owner = THIS_MODULE,
    .open = rev_open,
    .release = rev_close,
    .unlocked_ioctl = rev_unlocked_ioctl,
};
#endif

static void rev_parse_args(char *str, u8 *argc, char **argv, int max_arg) {
  char *ps = str;
  char *token;
  const char delimiters[] = " \t\n";

  while ((token = strsep(&ps, delimiters)) != NULL) {
#if 0
    printk("[%s]\n", token);
#endif
    argv[*argc] = token;
    (*argc)++;
  }
}

int proc_rev_status(struct seq_file *sf, void *v) {
  int idx;
  for (idx = 0; idx < 3; idx++) {
    seq_printf(sf, "status(%d):\n", idx);
  }
  return 0;
}

static int do_something(void *kvm, u32 len) {
  void *x;
  if (!kvm || !len)
    return -1;

  for (x = kvm; x < (kvm + len); x += PAGE_SIZE) {
    memset(x, 0xff, 0x10);
  }
  return 0;
}

u32 *vm;
u32 *km;

int proc_rev_control(struct file *file, const char __user *buffer, size_t count,
                     loff_t *ppos) {
  char *str;
  u8 argc = 0;
  char *argv[5];
#if 0
  u8 i;
#endif
  u32 sz;

  str = kzalloc(count + 1, GFP_KERNEL);
  if (!str)
    return -ENOMEM;

  if (copy_from_user(str, buffer, count))
    return -EFAULT;

  rev_parse_args(str, &argc, argv, 5);

#if 0
  for (i = 0; i < argc; i++) {
    printk("argv[%d]=%s\n", i, argv[i]);
  }
#endif

  if (argc >= 2) {
    if (!strcmp(argv[0], "kmalloc")) {
      sz = (int)simple_strtol(argv[1], NULL, 10);
      km = kmalloc(sz, GFP_KERNEL);
      do_something(km, sz);
      if (!km)
        printk("kmalloc of %u bytes FAILED!\n", sz);
      else {
        printk("kmalloc'd %u bytes (%u Kb, %u MB) @ 0x%08x\n",
               sz, sz / 1024, sz / (1024 * 1024), (u32)km);
      }
    } else if (!strcmp(argv[0], "vmalloc")) {
      sz = (int)simple_strtol(argv[1], NULL, 10);
      vm = vmalloc(sz);
      do_something(vm, sz);
      if (!vm)
        printk("vmalloc of %u bytes FAILED!\n", sz);
      else {
        printk("vmalloc'd %u bytes (%u Kb, %u MB) @ 0x%08x\n",
               sz, sz / 1024, sz / (1024 * 1024), (u32)vm);
      }
    } else if (!strcmp(argv[0], "kfree")) {
      if (!km)
        printk("km = 0!\n");
      else {
        kfree(km);
        printk("kfree'd\n");
      }
    } else if (!strcmp(argv[0], "vfree")) {
      if (!vm)
        printk("vm = 0!\n");
      else {
        vfree(vm);
        printk("vfree'd\n");
      }
    }
  } else {
    printk("unknown command");
  }

  kfree(str);
  return count;
}

int proc_rev_help(struct seq_file *sf, void *v) {
  seq_printf(sf, "Usage:\n");
  seq_printf(sf, "  echo \"kmalloc <bytes>\" > /proc/krev-control\n");
  seq_printf(sf, "  echo \"vmalloc <bytes>\" > /proc/krev-control\n");
  seq_printf(sf, "  echo \"kfree\" > /proc/krev-control\n");
  seq_printf(sf, "  echo \"vfree\" > /proc/krev-control\n");
  return 0;
}

int proc_rev_help_open(struct inode *inode, struct file *file) {
  return single_open(file, proc_rev_help, PDE_DATA(inode));
}

int proc_rev_status_open(struct inode *inode, struct file *file) {
  return single_open(file, proc_rev_status, PDE_DATA(inode));
}

struct file_operations proc_rev_help_fops = {
    .owner = THIS_MODULE,
    .open = proc_rev_help_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = seq_release,
};

struct file_operations proc_rev_control_fops = {
    .owner = THIS_MODULE,
    .read = seq_read,
    .llseek = seq_lseek,
    .write = proc_rev_control,
};

struct file_operations proc_rev_status_fops = {
    .owner = THIS_MODULE,
    .open = proc_rev_status_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = seq_release,
};

static int __init krev_init(void) {
  int err = -1;

  printk("Init: %s (%s-%s) \n", "krev", __DATE__, __TIME__);

  if (proc_create("krev-help", S_IFREG | S_IRUGO | S_IWUSR, NULL,
                  &proc_rev_help_fops) == NULL) {
    printk("proc create entry error\n");
  } else if (proc_create("krev-control", S_IFREG | S_IRUGO | S_IWUSR, NULL,
                         &proc_rev_control_fops) == NULL) {
    printk("proc create entry error\n");
  } else if (proc_create("krev-status", S_IFREG | S_IRUGO | S_IWUSR, NULL,
                         &proc_rev_status_fops) == NULL) {
    printk("proc create entry error\n");
  } else
    err = 0;
  return err;
}

static void __exit krev_exit(void) {
  printk("Exit: %s\n", "krev");
  remove_proc_entry("krev-help", NULL);
  remove_proc_entry("krev-control", NULL);
  remove_proc_entry("krev-status", NULL);
}

module_init(krev_init);
module_exit(krev_exit);

MODULE_AUTHOR("REV");
MODULE_DESCRIPTION("rev kmod");
MODULE_LICENSE("GPL");
