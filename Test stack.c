#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"


typedef struct Node node;
typedef struct Stack stack;


struct Stack {
  node* top;
  int quant_no;
};

struct Node {
  int dado;
  node* next;
};

node* create_node(int value){
  // Alocando um nó que vai ser o futuro vertice.
  node* n = (node*) calloc(1, sizeof(node));
  // setando os valores da struct no.
  n->dado = value;
  n->next = NULL;

  return n;
}


stack* create_stack(){
  //Alocando a stack.
  stack* sta = (stack*) calloc(1, sizeof(stack));
  sta->top = NULL;
  sta->quant_no = 0;
  return sta;
}

int push(stack* sta, int value){

  node* no = create_node(value);
  if (!sta->quant_no){
    sta->top = no;
  } else {
    no->next = sta->top;
    sta->top = no;
  }
  sta->quant_no ++;
  return sta->top->dado;
}

int pop(stack* sta){

  int vertice = sta->top->dado;

  node* n = sta->top;
  sta->top = sta->top->next;

  free(n);

  return vertice;

}

static FILE* temp_file = NULL;

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

void testFPRINTF(void)
{
   int i1 = 10;

   if (NULL != temp_file) {
      CU_ASSERT(0 == fprintf(temp_file, ""));
      CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
      CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
   }
}

void testFREAD(void)
{
   unsigned char buffer[20];

   if (NULL != temp_file) {
      rewind(temp_file);
      CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));
      CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));
   }
}

void delete_sta(stack* sta){
  free (sta);
}

void testPop(void)
{
  int i, array[15];

  stack* s = create_stack();

  for(i=0 ; i<15 ; i++){
    CU_ASSERT(push(s, i) == i);
  }

  for(i=14 ; i>=0 ; i--){
    CU_ASSERT(pop(s) == i);
  }

  delete_sta(s);

}

int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pSuite, "test of pop()", testPop)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }
   
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();

   testPop();

}
