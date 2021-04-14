#include <linux/module.h>
#include "link_list.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nachum Barcohen <nachum.barcohen@gmail.com>");

static int __init md_init(void) {
    printk("+ module link_list started!\n");
    return 0;
}

static void __exit md_exit(void) {
    printk("+ module link_list unloaded!\n");
}

extern proto_db_element* proto_db_create(void) {
    proto_db_element* head = (proto_db_element*)kmalloc(sizeof(proto_db_element), GFP_KERNEL);
    head->next = NULL;
    head->proc_hdr_func = NULL;
    head->proto_name = NULL;
    head->proto_hex_code = 0;
    return head;
}
EXPORT_SYMBOL(proto_db_create);

extern void proto_db_purge(proto_db_element* head) {
    proto_db_element* current_element = head;
    while(current_element) {
        current_element = current_element->next;
        kfree(head);
        head = current_element;
    }
}
EXPORT_SYMBOL(proto_db_purge);

extern bool proto_db_add(proto_db_element* head, char* name, u_short hex, void (*func_ptr)(struct sk_buff*)) {
    proto_db_element* current_element = head;
    while(current_element->next) {
        current_element = current_element->next;
    }
    current_element->next = (proto_db_element*)kmalloc(sizeof(proto_db_element), GFP_KERNEL);
    if(!current_element->next) {
        return false;
    }
    current_element = current_element->next;
    current_element->proto_name = (char*)kmalloc(sizeof(char)*4, GFP_KERNEL);
    current_element->proto_name = name;
    current_element->proto_hex_code = hex;
    current_element->proc_hdr_func = *func_ptr;
    current_element->next = NULL;
    return true;
}
EXPORT_SYMBOL(proto_db_add);

extern bool proto_db_del(proto_db_element* head, int type, void* param) {
    proto_db_element* current_element = head->next;
    proto_db_element* previous = head;
    bool flag = 0;
    while(current_element) {
        //0 - search for name
        //1 - search for hex code
        switch(type) {
            case 0:
                if(*(current_element->proto_name) == *((char*)param)) {
                    flag = 1;
                }
                break;
            case 1:
                if(current_element->proto_hex_code == *((u_short*)param)) {
                    flag = 1;
                }
                break;
            default:
            return false;
        }
        
        if(flag) {
            previous->next = current_element->next;
            kfree(current_element);
            return true;
        }
        previous->next = current_element;
        current_element =  current_element->next;
        
    }
    return false;
}
EXPORT_SYMBOL(proto_db_del);

extern proto_db_element* proto_db_find(proto_db_element* head, int type, void* param) {
    proto_db_element* current_element = head->next;
    while(current_element) {
        //0 - search for name
        //1 - search for hex code
        switch(type) {
            case 0:
                if(*(current_element->proto_name) == *((char*)param)) {
                   return current_element;
                }
                break;
            case 1:
                if(current_element->proto_hex_code == *((u_short*)param)) {
                    return current_element;
                }
                break;
            default:
            return NULL;
        }
        current_element = current_element->next;
    }
    
    return NULL;
}
EXPORT_SYMBOL(proto_db_find);

module_init(md_init);
module_exit(md_exit);
