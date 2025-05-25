#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define T 2
#define MIN_CHILDREN (T - 1)
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

    
    typedef enum B_search_result
    {
        MISSING,
        EXISTS
    } B_search_result;

    
    typedef struct B_node
    {
        struct B_node* children[MAX_CHILDREN]; 
        int keys[MAX_KEYS]; 
        int keys_count; 
        int is_leaf; 
        struct B_node* parent; 
    } B_node;


    
    typedef struct B_tree
    {
        B_node* root; 
    } B_tree;


    
    typedef struct B_tree_iterator
    {
        
        B_node* node;
       
        int position;
    } B_tree_iterator;

    typedef void (*split_t)(B_node* node_to_split, int split_at_index);
    typedef void (*insertNotFull_t)(B_node* node, int data);

    
    void Insert(B_tree* tree, int data, split_t split_fn, insertNotFull_t insert_fn);

    
    void Free(B_tree* tree);

    
    B_search_result Search(B_tree* tree, int data);

    
    void insertNotFull(B_node* node, int data);

    
    void split(B_node* parent_of_splited, int split_at_index);

    
    B_tree_iterator IteratorBegin(B_tree* tree);

    
    int Next(B_tree_iterator* iter);

    
    int Key(B_tree_iterator* iter);


    
    extern split_t const* SplitFPtr;
    extern insertNotFull_t const* InsertNotFullPtr;



#ifdef __cplusplus
}
#endif
