/*---------------------------
 * os_list_head.c
 *  Created on: Jul 5, 2017
 *      Author: Bailin Rui
 *          ���ߣ��ǰ���
 *---------------------------
 *list_head is used in all kinds of kernel struct.
 *for example: semaphore,device etc.
 *
 *
 *
 *---------------------------
 */


#include "c_share.h"

#include <linux/list.h>
#include <linux/gfp.h>
#include <linux/slab.h>

struct list_node_entry{
	struct list_head node;
	void *entry;
}list_node_entry_t;
/**************************************************/
void *os_ini_list_node(void);
void *os_ini_list_node(void)
{
	struct list_node_entry *node;
	node=kmalloc(sizeof(struct list_node_entry),GFP_ATOMIC);
	INIT_LIST_HEAD(&node->node);
	node->entry=NULL;
	return(node);
}
/**************************************************/
void os_insert_list_node(void *last,void *item,void *next);
void os_insert_list_node(void *last,void *item,void *next)
{
	struct list_node_entry *l,*t,*n;
	l=(struct list_node_entry *)last;
	t=(struct list_node_entry *)item;
	n=(struct list_node_entry *)next;
	__list_add(&l->node,&t->node,&n->node);
}
/**************************************************/
/*if next is head,then item is put to the tail of list*/
void os_before_list_node(void *item,void *next);
void os_before_list_node(void *item,void *next)
{
	struct list_node_entry *t,*n;
	struct list_head *l;
	t=(struct list_node_entry *)item;
	n=(struct list_node_entry *)next;
	l=n->node.prev;
	__list_add(l,&t->node,&n->node);
}
/**************************************************/
void os_after_list_node(void *last,void *item);
void os_after_list_node(void *last,void *item)
{
	struct list_node_entry *l,*t;
	struct list_head *n;
	l=(struct list_node_entry *)last;
	t=(struct list_node_entry *)item;
	n=l->node.next;
	__list_add(&l->node,&t->node,n);
}
/**************************************************/
void os_del_list_node(void *item);
void os_del_list_node(void *item)
{
	struct list_node_entry *t;
	t=(struct list_node_entry *)item;
	list_del(&t->node);
}
/**************************************************/
void *os_get_next_node(void *last);
void *os_get_next_node(void *last)
{
	struct list_node_entry *t,*l;
	struct list_head	*q;
	l=(struct list_node_entry *)last;
	q=l->node.next;
	t=container_of(q,struct list_node_entry,node);
	return(t);
}
/**************************************************/
void *os_get_last_node(void *next);
void *os_get_last_node(void *next)
{
	struct list_node_entry *t,*n;
	struct list_head	*q;
	n=(struct list_node_entry *)next;
	q=n->node.prev;
	t=container_of(q,struct list_node_entry,node);
	return(t);
}
/**************************************************/
void *os_get_node_entry(void *item);
void *os_get_node_entry(void *item)
{
	struct list_node_entry *t;
	t=(struct list_node_entry *)item;
	return(t->entry);
}
/**************************************************/
void os_set_node_entry(void *item,void *entry);
void os_set_node_entry(void *item,void *entry)
{
	struct list_node_entry *t;
	t=(struct list_node_entry *)item;
	t->entry=entry;
}

/**************************************************/
int os_is_list_empty(void *list_head);
int os_is_list_empty(void *list_head)
{
	int ret;
	struct list_node_entry *q_head;
	q_head=(struct list_node_entry *)list_head;
	ret=list_empty(&q_head->node);
	return(ret);
}

/**************************************************/
void os_distroy_list_node(void *node);
void os_distroy_list_node(void *node)
{
	kfree(node);
}
/* end of os_list_head.c */
