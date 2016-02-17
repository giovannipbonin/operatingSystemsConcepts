#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/kernel.h>

static LIST_HEAD(birthday_list);

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
        struct birthday *person0;
        struct birthday *person1;
        struct birthday *person2;
        struct birthday *person3;
        struct birthday *person4;
        struct birthday *ptr;
        printk(KERN_INFO "Loading Module\n");

        person0 = kmalloc(sizeof(*person0), GFP_KERNEL);
        person0->day = 1;
        person0->month = 8;
        person0->year = 1995;
        INIT_LIST_HEAD(&person0->list);
        list_add_tail(&person0->list, &birthday_list);

        person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
        person1->day = 2;
        person1->month = 8;
        person1->year = 1995;
        INIT_LIST_HEAD(&person1->list);
        list_add_tail(&person1->list, &birthday_list);


        person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
        person2->day = 4;
        person2->month = 8;
        person2->year = 1995;
        INIT_LIST_HEAD(&person2->list);
        list_add_tail(&person2->list, &birthday_list);


        person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
        person3->day = 3;
        person3->month = 8;
        person3->year = 1995;
        INIT_LIST_HEAD(&person3->list);
        list_add_tail(&person3->list, &birthday_list);


        person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
        person4->day = 5;
        person4->month = 8;
        person4->year = 1995;
        INIT_LIST_HEAD(&person4->list);
        list_add_tail(&person4->list, &birthday_list);


        list_for_each_entry(ptr, &birthday_list, list)
        {
           printk(KERN_INFO "Current day is: %d\nCurrent month is: %d\nCurrent year is: %d\n\n", ptr->day, ptr->month, ptr->year);
        }
        return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	struct birthday *ptr, *next;
	printk(KERN_INFO "Removing Module\n");
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

