#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>



struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;	
};
// Create a list of birthday struct
static LIST_HEAD(birthday_list);
/* this function is called when the module is loaded*/

int birthday_init(void){
	printk(KERN_INFO "Loading Module\n");
	
	//Create a new object of birthday
	struct birthday * person;
	person = kmalloc(sizeof(person), GFP_KERNEL);
	person->day = 11;
	person->month = 1;
	person->year = 2000;
	
	//Create 5 objects for strcut
	INIT_LIST_HEAD(&person->list);
	int i;
	for (i = 0; i < 5; i++){
		struct birthday * newPerson;
		newPerson= kmalloc(sizeof(newPerson), GFP_KERNEL);
		newPerson->day = 2 * (i + 1);
		newPerson->month = i + 1;
		newPerson->year = 1990 + i * 2;
		list_add_tail(&newPerson->list, &birthday_list);
	}
	//Moving Inside the list , printing the objects
	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list){
		printk(KERN_INFO "BirthDate : %d/%d/%d\n",ptr->day,ptr->month,ptr->year);
	}
	
	return 0;
}
///* this function is called when the module is removed*/
void birthday_exit(void){
	printk(KERN_INFO "Removing Module");
	struct birthday *ptr, *tmp;
	list_for_each_entry_safe(ptr , tmp , &birthday_list, list){
		list_del(&ptr->list);
		kfree(tmp);

	}
}
/* Macros for registering module entry and exit points.
*/
module_init(birthday_init);
module_exit(birthday_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday M-odule");
MODULE_AUTHOR("SGG");
