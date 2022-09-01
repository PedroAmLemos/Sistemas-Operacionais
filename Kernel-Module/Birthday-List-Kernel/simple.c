#include <linux/list.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void){
    printk(KERN_INFO "Carregando Modulo\n");

    struct birthday *person;

    int i = 0;
    for(i = 0; i < 5; i++){
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i;
        person->month = 2 + i;
        person->year = 1995 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list){
        printk(KERN_INFO "dia: %d mes: %d ano: %d", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

void simple_exit(void) {
    struct birthday *ptr, *next;

    list_for_each_entry_safe(ptr, next, &birthday_list, list){
        list_del(&ptr->list);
        kfree(ptr);
    }

    printk(KERN_INFO "Removendo Modulo\n");

}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

