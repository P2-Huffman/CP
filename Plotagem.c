#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _tree Tree;
typedef struct _queue Queue;

Tree* creat_tree();
Queue* creat_queue();

Tree* insert_tree(Tree *root, int element, int *cust);
Queue* insert_queue(Queue *head, int element, int *cust);

int search_tree(Tree *root, int element);
int search_queue(Queue *head, int element);

void plot(int cust_Tree[],int cust_Queue[], char *title);

int main()
{
    srand(time(NULL));
    int array[30000], cust_tree[30000], cust_queue[30000], *cust;
    Tree *root = creat_tree();
    Queue *head = creat_queue();
    char k[100];
    int a, b, c;
    cust = (int*) malloc(sizeof(int));

    scanf("%[^\n]s", k);
    getchar();
    for(a = 0; a < 30000; a++)
    {
        b = rand()%100000;
        //printf("%d %d\n", a, b);
        (*cust) = 0;
        root = insert_tree(root, b, cust);
        cust_tree[a] = (*cust);
        (*cust) = 0;
        head = insert_queue(head, b, cust);
        cust_queue[a] = (*cust);
        array[a] = b;
    }
    plot(cust_tree, cust_queue, k);
    for(a = 0; a < 30000; a++)
    {
        b = rand()%30000;
        cust_tree[a] = search_tree(root, array[b]);
        cust_queue[a] = search_queue(head, array[b]);
        printf("%d %d\n", cust_queue[a], cust_tree[a]);

    }
    scanf("%[^\n]s", k);
    getchar();
    plot(cust_tree, cust_queue, k);

    //test_tree(root);
    //test_queue(head);
    return 0;
}

struct _tree
{
    int node;
    Tree *left;
    Tree *right;
};
struct _queue
{
    int element;
    Queue *next;
};
Tree* creat_tree()
{
    return NULL;
}
Queue* creat_queue()
{
    return NULL;
}
Tree* creat_node(int element)
{
    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->node = element;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
Queue *creat_element(int element)
{
    Queue *new_element = (Queue*) malloc(sizeof(Queue));
    new_element->element = element;
    new_element->next = NULL;

    return new_element;
}
Tree* insert_tree(Tree *root, int element, int *cust)
{
    if(root == NULL)
        return creat_node(element);
    (*cust)++;

    if(root->node < element)
        root->right = insert_tree(root->right, element, cust);
    else
        root->left = insert_tree(root->left, element, cust);
    return root;
}
Queue* insert_queue(Queue *head, int element, int *cust)
{
    if(head == NULL)
    {
        head = creat_element(element);
        return head;
    }
    (*cust)++;
    Queue *aux = head;
    while(aux->next != NULL)
    {
        (*cust)++;
        aux = aux->next;
    }
    aux->next = creat_element(element);

    return head;
}
int search_tree(Tree *root, int element)
{
    int cust = 0;
    while(root->node != element)
    {
        if(root == NULL)
            return -1;
        if(root->node > element)
            root = root->left;
        else
            root = root->right;
        cust++;
    }
    return cust;
}
int search_queue(Queue *head, int element)
{
    int cust = 0;
    if(head == NULL)
        return -1;
    while(head->element != element)
    {
        head = head->next;
        cust++;
    }
    return cust;
}
void test_tree(Tree *root)
{
    if(root == NULL)
        return ;
    printf("|%d|", root->node);
    test_tree(root->left);
    test_tree(root->right);
}
void test_queue(Queue *head)
{
    while(head != NULL)
    {
        printf("%d ", head->element);
        head = head->next;
    }
}
void test_cust(int custo[])
{
    int a;
    for(a = 0; a < 30000; a++)
    {
        printf("%d\n", custo[a]);
    }
}
void plot(int cust_Tree[],int cust_Queue[], char *title)
{
    int a, b, c;
    FILE *dataplot = fopen(title, "wb");
    fprintf(dataplot, "%s", "pdf(\"TREE vs QUEUE.pdf\")\n");
    fprintf(dataplot, "x<-c(%d", 0);
    for(a = 300; a <= 30000; a+=300)
    {
        fprintf(dataplot, ", %d", a);
    }
    fprintf(dataplot, ")%c", '\n');

    fprintf(dataplot, "y<-c(%d", cust_Tree[0]);
    for(a = 300; a <= 30000; a+=300)
    {
        fprintf(dataplot, ", %d", cust_Tree[a-1]);
    }
    fprintf(dataplot, ")%c", '\n');

    fprintf(dataplot, "z<-c(%d", cust_Queue[0]);
    for(a = 300; a <= 30000; a+=300)
    {
        fprintf(dataplot, ", %d", cust_Queue[a-1]);
    }
    printf("buia");
    fprintf(dataplot, ")%c", '\n');

    fprintf(dataplot, "%s", "par(mfrow=c(2, 1))\n");
    fprintf(dataplot, "%s", "plot(x, y, ylab = \"Cust\", xlab = \"Nº of elements\", main = \"Tree\")\n");
    fprintf(dataplot, "%s", "lines(x,y)\n");
    fprintf(dataplot, "%s", "plot(x, z, ylab = \"Cust\", xlab = \"Nº of elements\", main = \"Queue\")\n");
    fprintf(dataplot, "%s", "lines(x,z)\n");

    fprintf(dataplot, "%s", "dev.off()\n");

    fclose(title);

}
