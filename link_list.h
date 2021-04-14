#include <linux/netdevice.h>
typedef void (*cb_func_ptr)(struct sk_buff*);

typedef struct proto_db {
    struct proto_db* next;
    cb_func_ptr proc_hdr_func;
    char* proto_name;
    u_short proto_hex_code;
} proto_db_element;

extern proto_db_element* proto_db_create(void);
extern bool proto_db_add(proto_db_element* head, char* name, u_short hex, void (*func_ptr)(struct sk_buff*));
extern bool proto_db_del(proto_db_element* head, int type, void* param);
extern proto_db_element* proto_db_find(proto_db_element* head, int type, void* param);
extern void proto_db_purge(proto_db_element* head);
