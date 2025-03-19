#include "splaythree.h"

void _change_parent(Node *aim, Node *parent) {

  aim->parent = parent->parent;
  if (aim->parent != NULL) {
    if (aim->parent->left == parent) {
      aim->parent->left = aim;
    } else if (aim->parent->right == parent) {
      aim->parent->right = aim;
    }
  }
  parent->parent = aim;
}

void _rotate(Node *aim) {
  Node *parent = aim->parent;

  if (parent->left == aim) {

    Node *keep_right = aim->right;
    aim->right = parent;
    parent->left = keep_right;

  } else if (parent->right == aim) {

    Node *keep_left = aim->left;
    aim->left = parent;
    parent->right = keep_left;
  }

  _change_parent(aim, parent);
}

// mode 0 - left, mode 1 - right
void _zigzig(Node *aim) {
  Node *parent = aim->parent;

  _rotate(parent);
  _rotate(aim);
}

void _zigzag(Node *aim) {
  _rotate(aim);
  _rotate(aim);
}

Node *_splay(Node *aim, Node *stPar) {

  while (aim->parent != NULL) {

    // if it doesn`t have grandpa
    if (aim->parent->parent == NULL) {
      _rotate(aim);
    } else {
      Node *parent = aim->parent;
      Node *grandparent = aim->parent->parent;

      if (((parent->left == aim) && (grandparent->left == parent)) ||
          ((parent->right == aim) && (grandparent->right == parent))) {
        _zigzig(aim);
      } else {
        _zigzag(aim);
      }
    }
  }

  return aim;
}

Node *insert(Node *root, int value) {
  Node *current = root;

  Node *new_element = malloc(sizeof(Node));
  new_element->value = value;

  if (current == NULL) {
    return NULL;
  }

  while (1) {
    // what do with equal elements?

    if (current->value == value) {
      return root;
    }

    // left
    if (current->value > value) {
      if (current->left == NULL) {
        current->left = new_element;
        new_element->parent = current;
        break;
      } else {
        current = current->left;
      }
    }

    // right
    if (current->value < value) {
      if (current->right == NULL) {
        current->right = new_element;
        new_element->parent = current;
        break;
      } else {
        current = current->right;
      }
    }
  }

  return _splay(new_element, NULL);
}

Node *search(Node *root, int value) {

  if (root == NULL) {
    return NULL;
  }

  Node *current = root;
  Node *lastcur = root;

  while (current != NULL) {
    if (current->value == value) {
      break;
    }

    lastcur = current;
    if (current->value > value)
      current = current->left;
    else if (current->value < value)
      current = current->right;
  }

  if (current == NULL) {

    return _splay(lastcur, root->parent);
  }

  return _splay(current, root->parent);
}

Node *erase(Node *root, int value) {

  if (root == NULL)
    return NULL;

  root = search(root, value);

  _set_parent(root->left, NULL);
  _set_parent(root->right, NULL);

  Node *old = root;
  root = _merge(root->left, root->right);

  free(old);

  return root;
}

void _set_parent(Node *child, Node *parent) {
  if (child != NULL) {
    child->parent = parent;
  }
}

Node *_merge(Node *left, Node *right) {

  if (right == NULL) {
    return left;
  }
  if (left == NULL) {
    return right;
  }
  right = search(right, left->value);

  right->left = left;
  left->parent = right;

  return right;
}