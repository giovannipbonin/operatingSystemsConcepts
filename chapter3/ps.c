#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <stdio.h>

struct task_struct *task;

int ps_init()
{
    int i = 0;
    for_each_process(task)
    {
        printf("%d\n", i);
        i++;
    }
}


