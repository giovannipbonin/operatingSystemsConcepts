#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>


void dfs_task(struct task_struct *headTask)
{
    if (headTask == NULL) return;
    printk(KERN_INFO "Name: %s State: %d PID: %d\n", headTask->comm, headTask->state, headTask->pid);
    struct list_head *list;
    struct task_struct *new_task;
    list_for_each(list, &headTask->children)
    {
        new_task = list_entry(list, struct task_struct, sibling);
        dfs_task(new_task);
    }
}


int psDfs_init(void)
{
    dfs_task(&init_task);
    return 0;
}

void psDfs_exit(void)
{
}

module_init(psDfs_init);
module_exit(psDfs_exit);


