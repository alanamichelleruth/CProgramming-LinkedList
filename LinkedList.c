/*
 * NAME: Alana Ruth
 *
 * Interactive program dealing with linked lists. Each node contains a string of
 * length at most 10, a positive integer, and a pointer to the next node of the
 * list.
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* define the maximum length of the command to be 4 */
#define MAXCOM 4
/* define the maximum length of a string in the linked list to be 10 */
#define MAXSTR 10
/* define the boolean values */
#define TRUE 1
#define FALSE 0


/* define the linked list node */
typedef struct node{
  char *word;
  int value;
  struct node * next;
}node_type;


/* function prototypes */
void ins(node_type **h, char str[MAXSTR]);
void sort(node_type *h);
int isSorted(node_type *h);
void del(node_type **h, char str[MAXSTR]);
void fde(node_type **h, int val);
void pst(node_type *h);
void prl(node_type *h);
void pcr(node_type *h, int v1, int v2);
void ppr(node_type *h, char str[MAXSTR]);
int isPrefix(char *pre, char *str);
void psu(node_type *h, char str[MAXSTR]);
int isSuffix(char *suff, char *str);


int main(int argc, char **argv){

  node_type *head;
  /* head initially points to NULL */
  head = NULL;

  /* prompt user to enter a command and store that command in command */
  char command[MAXCOM];
  printf("Please enter a command: "); fflush(stdout);
  scanf("%s", command);

  /* local variables to store the parameters to the commands, if applicable */
  char word[MAXSTR];
  int num1, num2;

  /* loop iterates while the command is not "end" */
  while (strcmp(command, "end") != 0){
    /* check for each command and call the appropriate function */

    if (strcmp(command, "ins") == 0){
      scanf("%s", word);
      ins(&head, word);
    }

    if (strcmp(command, "del") == 0){
      scanf("%s", word);
      del(&head, word);
    }

    if (strcmp(command, "fde") == 0){
      scanf("%d", &num1);
      fde(&head, num1);
    }

    if (strcmp(command, "pst") == 0){
      pst(head);
    }

    if (strcmp(command, "prl") == 0){
      prl(head);
    }

    if (strcmp(command, "pcr") == 0){
      scanf("%d %d", &num1, &num2);
      pcr(head, num1, num2);
    }

    if (strcmp(command, "ppr") == 0){
      scanf("%s", word);
      ppr(head, word);
    }

    if (strcmp(command, "psu") == 0){
      scanf("%s", word);
      psu(head, word);
    }

    printf("Please enter another command: "); fflush(stdout);
    scanf("%s", command);

  }
  /* return 0 at end of main */
  return 0;
}


void ins(node_type **h, char str[MAXSTR]){

  /* if malloc returns NULL, print an error message and stop */
  node_type *newNode;
  if ((newNode = (node_type *)malloc(sizeof(node_type))) == NULL){
    printf("Node allocation failed. \n"); fflush(stdout);
    exit(1);
  }

  /* if head is NULL, insert the newNode at the head and exit the function(return) */
  if (*h == NULL){
    newNode->word = malloc(sizeof(char)*10);
    strcpy(newNode->word, str);
    newNode->value = 1;
    newNode->next = NULL;

    (*h) = newNode;

    return;
  }

  /* temp node to run through the linked list */
  node_type *temp = *h;
  int shouldIns = TRUE;

  /* iterates through all nodes in the linked list */
  while (temp != NULL){
    /* if there is a word in the linked list equal to the new word */
    if (strcmp(temp->word, str) == 0){
      temp->value++;
      shouldIns = FALSE;
    }
    temp = temp->next;
  }

  /* trial node to run through the linked list again */
  node_type *trial = *h;
  while (trial->next != NULL){
    trial = trial->next;
  }

  /* inserts the new node at the end of the linked list */
  if (shouldIns){
    newNode->word = malloc(sizeof(char)*10);
    strcpy(newNode->word, str);
    newNode->value = 1;
    newNode->next = NULL;

    trial->next = newNode;
  }

  /* sorts the linked list in decending order of values */
  while (!isSorted(*h)){
    sort(*h);
  }
}

void sort(node_type *h){

  /* local variables to assist with switching the words and values in the nodes */
  node_type *current = h;
  char *tempWord = malloc(sizeof(char)*10);
  int tempValue;

  /* iterates through the linked list until the next node is NULL */
  while ((current)->next != NULL){

    /* if the next node's value is greater than the current node's value */
    if ((current)->next->value > (current)->value){
      strcpy(tempWord, (current)->word);
      strcpy((current)->word, (current)->next->word);
     strcpy((current)->next->word, tempWord);

      /* swap the words and the values in current and current->next */
      tempValue = (current)->value;
      (current)->value = (current)->next->value;
      (current)->next->value = tempValue;
    }
    current = (current)->next;
  }

  /* frees the memory */
  free(tempWord);
}

/* returns a boolean to know whether or not to sort */
int isSorted(node_type *h){

  int isSorted = TRUE;
  node_type *current = h;

  while (current->next != NULL){
    /* if there is an instance where the next value is greater than the current, */
    /* then it needs to be sorted. */
    if(current->next->value > current->value){
      isSorted = FALSE;
    }
    current = current->next;
  }
  return isSorted;
}

void del(node_type **h, char str[MAXSTR]){

  node_type *temp = *h;

  /* if the head is NULL, do nothing */
  if (temp == NULL)
    return;

  /* checks if any nodes have the same word as str */
  while (temp != NULL){
    if (strcmp(temp->word, str) == 0){
      /* subtract one from value of the node if the word is the same as str */
      temp->value--;
    }
    temp = temp->next;
  }

  /* sort the list */
  while (!isSorted(*h)){
    sort(*h);
  }

  node_type *current = *h;
  node_type *prev = NULL;

  while(current->next != NULL){
    prev = current;
    current = current->next;
  }

  /* if the last node in the list, current, has value 0, delete the node */
  if(current->value == 0){
    /* because current is being deleted, make sure the previous node points to the correct next node */
    if (prev != NULL){
      prev->next = current->next;
    }
    /* else-- when the node is the first node */
    else{
      /* head gets NULL */
      (*h) = current->next;
    }
    /* frees the memory */
    free(current);
    return;
  }
}

void fde(node_type **h, int val){

  node_type *current = *h;

  /* if the list is empty or val is 0, do nothing */
  if (current == NULL || val == 0)
    return;

  while (current != NULL){
    if (current->value <= val){
      current->value = 1;
    }
    current = current->next;
  }

   while(!isSorted(*h)){
     sort(*h);
   }

   /* by this point, all the nodes with values <= val will have value 1 and be at the end of the list */

   node_type *trial = *h;
   while (trial != NULL){
     /* find all the nodes who have value 1, AKA all those who should get deleted */
     if(trial->value == 1){
       del(h, trial->word);
     }
     else{
       trial = trial->next;
     }
   }
}

void pst(node_type *h){

  /* if the list is empty */
  if (h == NULL){
    printf("The list is empty.\n"); fflush(stdout);
    return;
  }

  /* local variables to hold the statistics */
  int numNodes = 0;
  int maxCount = h->value;
  int minCount;
  int sum = 0;
  float avg = 0.0;

  /* initialize the statistics correctly while iterating through the list */
  while (h != NULL){
    numNodes++;
    minCount = h->value;
    sum = sum + h->value;

    h = h->next;
  }

  /* compute the avg with a float variable */
  avg = sum/(double)numNodes;

  /* print the results to the console */
  printf("No. of nodes: %d\n", numNodes); fflush(stdout);
  printf("Max. count: %d\n", maxCount); fflush(stdout);
  printf("Min. count: %d\n", minCount); fflush(stdout);
  printf("Avg. count: %.2f\n", avg); fflush(stdout);
}

void prl(node_type *h){
  /* if the list is empty */
  if (h == NULL){
    printf("The list is empty.\n"); fflush(stdout);
    return;
  }
  /* print each node's word and value on a line by itself */
  else{
    while (h != NULL){
      printf("%s\t%d\n", h->word, h->value); fflush(stdout);
      h = h->next;
    }
  }
}

void pcr(node_type *h, int v1, int v2){

  /* if the list is empty */
  if (h == NULL){
    printf("The list is empty.\n"); fflush(stdout);
    return;
  }

  /* iterate through the list */
  while (h != NULL){
    /* if the value of the node is between v1 and v2, print the node's word and value */
    if (h->value >= v1 && h->value <= v2){
      printf("%s\t%d\n", h->word, h->value); fflush(stdout);
    }
    h = h->next;
  }
}

void ppr(node_type *h, char str[MAXSTR]){

  /* if the list is empty */
  if (h == NULL){
    printf("The list is empty.\n"); fflush(stdout);
    return;
  }

  while (h != NULL){
    /* if str is a prefix of the current node's word, print the node's word and value */
   if (isPrefix(str, h->word)){
      printf("%s\t%d\n", h->word, h->value); fflush(stdout);
    }
    h = h->next;
  }
}

/* returns TRUE if the pre is a prefix of str, FALSE otherwise */
int isPrefix(char *pre, char *str){

  if (strncmp(pre, str, strlen(pre)) == 0)
    return TRUE;
  else
    return FALSE;
}

void psu(node_type *h, char str[MAXSTR]){

  /* if the list is empty */
  if (h == NULL){
    printf("The list is empty.\n"); fflush(stdout);
  }

  while (h != NULL){
    /* if str is a suffix of the current node's word, print the node's word and value */
    if (isSuffix(str, h->word)){
      printf("%s\t%d\n", h->word, h->value); fflush(stdout);
    }
    h = h->next;
  }
}

/* returns TRUE if the suff is a suffix of str, FALSE otherwise */
int isSuffix(char *suff, char *str){
  if (strcmp(str + (strlen(str)-strlen(suff)), suff) == 0)
    return TRUE;
  else
    return FALSE;
}
