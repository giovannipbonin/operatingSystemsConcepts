#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>


int ps_init(void)
{
    struct task_struct *task;
    for_each_process(task)
    {
        printk(KERN_INFO "Name: %s State: %d PID: %d\n", task->comm, task->state, task->pid);
    }
    return 0;
}

void ps_exit(void)
{
}

module_init(ps_init);
module_exit(ps_exit);


