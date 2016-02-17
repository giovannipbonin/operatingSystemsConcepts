#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/kernel.h>

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
        printk(KERN_INFO "Loading Module\n");
        static LIST_HEAD(birthday_list);

        struct birthday *person0;
        person = kmalloc(sizeof(*person0), GFP_KERNEL);
        person0->day = 1;
        person0->month = 8;
        person0->year = 1995;
        INIT_LIST_HEAD(&person0->list);
        list_add_tail(&person0->list, &birthday_list);

        struct birthday *person1;
        person = kmalloc(sizeof(*person1), GFP_KERNEL);
        person1->day = 2;
        person1->month = 8;
        person1->year = 1995;
        INIT_LIST_HEAD(&person1->list);
        list_add_tail(&person1->list, &birthday_list);


        struct birthday *person2;
        person = kmalloc(sizeof(*person2), GFP_KERNEL);
        person2->day = 4;
        person2->month = 8;
        person2->year = 1995;
        INIT_LIST_HEAD(&person2->list);
        list_add_tail(&person2->list, &birthday_list);


        struct birthday *person3;
        person = kmalloc(sizeof(*person3), GFP_KERNEL);
        person3->day = 3;
        person3->month = 8;
        person3->year = 1995;
        INIT_LIST_HEAD(&person3->list);
        list_add_tail(&person3->list, &birthday_list);


        struct birthday *person4;
        person = kmalloc(sizeof(*person4), GFP_KERNEL);
        person4->day = 5;
        person4->month = 8;
        person4->year = 1995;
        INIT_LIST_HEAD(&person4->list);
        list_add_tail(&person4->list, &birthday_list);

        struct birthday *ptr;

        list_for_each_entry(ptr, &birthday_list, list)
        {
           printk(KERN_INFO, "Current day is: %s\n", ptr->day);
        }
        return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

