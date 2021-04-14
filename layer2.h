typedef void (*proc_func_ptr)(struct sk_buff*);
extern void proc_l2(struct sk_buff* skb);
extern bool l2_add_l3_proto(char* name, u_short hex, proc_func_ptr func);
extern bool l2_del_l3_proto(int type, void* param);