#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define T 2
#define MIN_CHILDREN (T - 1)
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

    /*
    Результат поиска ключа в дереве:
    MISSING - такого ключа в дереве нет.
    EXISTS - ключ в дереве присутсвует.
    */
    typedef enum B_search_result
    {
        MISSING,
        EXISTS
    } B_search_result;

    /*
    Узел дерева, как для внутренних узлов, так и для листьев.
    */
    typedef struct B_node
    {
        struct B_node* children[MAX_CHILDREN]; // массив указателей на дочерние узлы
        int keys[MAX_KEYS]; // массив ключей, содежащихся в этом узле
        int keys_count; // текущее кол-во ключей, содержащихся в узле (т.е. в массиве keys)
        int is_leaf; // лист - узел дерева, у которого нет ни одного дочернего узла.
        struct B_node* parent; // указатель на родителя, или NULL для корня дерева
    } B_node;


    /*
    Основная структура, для работы с одним экземпляром дерева
    */
    typedef struct B_tree
    {
        B_node* root; // Указатель на корневой узел дерева
    } B_tree;


    /*
    Структура данных для одного экземпляра итератора по дереву
    */
    typedef struct B_tree_iterator
    {
        // Указатель на узел, на который сейчас указывает итератор
        B_node* node;
        // Номер ключа внутри узла, на котором сейчас стоит итератор
        int position;
    } B_tree_iterator;

    typedef void (*split_t)(B_node* node_to_split, int split_at_index);
    typedef void (*insertNotFull_t)(B_node* node, int data);

    /*
    Добавить ключ в дерево.
     Если ключ уже существует - ничего не делать
    B_tree tree = {};
    Insert(&tree, 1);
    Insert(&tree, 1);
    Insert(&tree, 2);
    */
    void Insert(B_tree* tree, int data, split_t split_fn, insertNotFull_t insert_fn);

    // Освободить выделенную под дерево память.
    void Free(B_tree* tree);

    /*
    Проверить, есть ли в дереве tree ключ data
    Пример:
    B_tree tree = {};
    Insert(&tree, 7);
    Search(&tree, 7); ---> EXISTS
    Search(&tree, 5); ---> MISSING
    */
    B_search_result Search(B_tree* tree, int data);

    // Добавляет в узел не полностью заполненный узел node  ключ data
    // см. https://neerc.ifmo.ru/wiki/index.php?title=B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
    void insertNotFull(B_node* node, int data);

    // Получает на вход незаполненный узел parent_of_splited,
    // у которого есть полностью заполненный дочерний узел по индексу split_at_index.
    // Разбивает полностью этот полностью заполненный дочерний узел на два.
    // см. https://neerc.ifmo.ru/wiki/index.php?title=B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
    void split(B_node* parent_of_splited, int split_at_index);

    // Создать новый итератор по дереву
    B_tree_iterator IteratorBegin(B_tree* tree);

    // Передвинуться на следующий элемент при итерировании дерева
    // Возвращает 1 если итератор еще "жив" и можно получать значение через Key
    // Возвращает 0, если итерирование окончено, все узлы были посещены, значение через Key уже не получить
    int Next(B_tree_iterator* iter);

    // Получить ключ, на который сейчас указывает итератор
    int Key(B_tree_iterator* iter);

    /*
    Пример использования итератора:
    B_tree_iterator iter = IteratorBegin(&tree);
    while (int has_element = Next(&iter))
    {
        printf("%d", Key(&iter));
    }
    */


    /*
    №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
    №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
    №№№№№№№№№                ВНИМАНИЕ!!              №№№№№№№№№
    №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
    №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
    Для интроспекции решения необходиммо вызывать внутри вашего исходного файла функции:
    - split
    - insertNotFull
    объявленные выше, особым образом, а именно по указателям:
    (*SplitFPtr)(node, 1)
    (*InsertNotFullPtr)(node, 1)
    Пример:
    У вас есть где-то в исходом коде вызов:

      insertNotFull(node->children[key_ind], data);

    При отправке в систему проверки, вам нужно заменить его на
      (*InsertNotFullPtr)(node->children[key_ind], data);
    */
    extern split_t const* SplitFPtr;
    extern insertNotFull_t const* InsertNotFullPtr;



#ifdef __cplusplus
}
#endif