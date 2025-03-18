#ifndef RB_TREE_H
#define RB_TREE_H

typedef enum color {
  RED,
  BLACK,
} color;

typedef struct rb_tree {
  int key;
  struct rb_tree *parent;
  struct rb_tree *left;
  struct rb_tree *right;
  color c;
} rb_tree;

void insert(rb_tree **root, int key);
void delete(rb_tree **root, rb_tree *node);
rb_tree *search(rb_tree *root, int key);

#endif
