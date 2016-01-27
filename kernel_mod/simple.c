/*
Brian Scott
COSC 3053-01
"Loading Kernel Modules"
26 Jan 2016
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

// birthday structure
struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

// define list_head object 'birthday_list'
static LIST_HEAD(birthday_list);

// This function is called when the module is loaded
int simple_init(void)
{
   // declare birthday struct pointers
   struct birthday *persons[5];
   struct birthday *ptr;
   int i;
   
   // define 'birthday' internal variables and add to list
   for (i=0;i<5;i++) {
       persons[i] = kmalloc(sizeof(struct birthday), GFP_KERNEL);
       persons[i]->day = 14+i;
       persons[i]->month = 6+i;
       persons[i]->year = 1988+i;
       
       // initialize list member
       INIT_LIST_HEAD(&persons[i]->list);

       // add to end of list
       list_add_tail(&persons[i]->list, &birthday_list);
   }


   printk(KERN_INFO "Loading Module\n");
   
   // traverse list and print to kernel log
   list_for_each_entry(ptr, &birthday_list, list) {
       printk(KERN_INFO "%d.%d.%d\n", ptr->month, ptr->day, ptr->year);
   }
       return 0;
}

// This function is called when the module is removed
void simple_exit(void) {
  struct birthday *ptr, *next;

  printk(KERN_INFO "Removing Module\n");
  
  // print each member and remove it from list
  list_for_each_entry_safe(ptr, next, &birthday_list, list) {
    printk(KERN_INFO "Deleting %d.%d.%d\n", ptr->month, ptr->day, ptr->year);
    list_del(&ptr->list);
    kfree(ptr);
  }
}

// Macros for registering module entry and exit points
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

