/** @file listy.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN 50

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct node_t
{
    char *word;
    int duplicate;
    struct node_t *next;
} node_t;

typedef struct node_q3
{
    char *portname;
    char *portshort; 
    char *portcity; 
    char *portcountry; 
    struct node_q3 *next;
} node_q3;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(char *val,int duplicate);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *);
node_t *add_inorder2(node_t *, node_t *);
node_t *add_inorder3(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);

node_q3 *new_node_q3(char *val, char *val2, char *val3,char *val4);
node_q3 *add_end_q3(node_q3 *, node_q3 *);
node_q3 *peek_front_q3(node_q3 *);
node_q3 *remove_front_q3(node_q3 *);

void apply(node_t *, void (*fn)(node_t *, void *), void *arg);

#endif
