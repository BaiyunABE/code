#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Array {
  int length;
  int capacity;
  int size;
  unsigned char* data;
};

struct Array* create_array(int size, int capacity) {
  struct Array* array = (struct Array*)malloc(sizeof(struct Array));
  array->data = (unsigned char*)malloc(capacity * size);
  array->size = size;
  array->capacity = capacity;
  array->length = 0;
  return array;
}

void insert_array(struct Array* array, const void* data) {
  if (array->length == array->capacity) {
    array->capacity <<= 1;
    void* tmp = (void*)malloc(array->capacity * array->size);
    memcpy(tmp, array->data, array->length * array->size);
    free(array->data);
    array->data = (unsigned char*)tmp;
  }

  memcpy(&array->data[array->length * array->size], data, array->size);
  array->length++;
}

void* find_array(struct Array* array, const int idx) {
  return idx <= array->length ? (void*)&array->data[idx * array->size] : NULL;
}

void* find_if_array(struct Array* array, const void* data, int pred(void*, void*)) {
  struct Array* result = create_array(array->size, 1);
  for (int i = 0; i < array->length; i++) {
    void* target = find_array(array, i);
    if (pred(target, data)) {
      insert_array(result, target);
    }
  }
  return result;
}

void drop_array(struct Array* array) {
  free(array->data);
  free(array);
}

struct CFGProduction {
  struct Array* rhs;
  char lhs;
};

struct CFG {
  struct Array* non_terminals;
  struct Array* terminals;
  struct Array* productions;
  char start_symbol;
};

struct CFG* init_cfg() {
  struct CFG* cfg = (struct CFG*)malloc(sizeof(struct CFG));
  
  char non_terminals[4] = {'S', 'E', 'T', 'F'};
  cfg->non_terminals = create_array(sizeof(char), 4);
  for (int i = 0; i < 4; i++) {
    insert_array(cfg->non_terminals, &non_terminals[i]);
  }
  
  char terminals[7] = {'+', '-', '*', '/', '(', ')', 'n'};
  cfg->terminals = create_array(sizeof(char), 7);
  for (int i = 0; i < 7; i++) {
    insert_array(cfg->terminals, &terminals[i]);
  }

  char productions[9][2][3] = {
    {"S", "E"},
    {"E", "E+T"},
    {"E", "E-T"},
    {"E", "T"},
    {"T", "T*F"},
    {"T", "T/F"},
    {"T", "F"},
    {"F", "(E)"},
    {"F", "n"}
  };
  cfg->productions = create_array(sizeof(struct CFGProduction), 9);
  for (int i = 0; i < 9; i++) {
    struct CFGProduction production;
    production.lhs = productions[i][0][0];
    int len = strlen(productions[i][1]);
    production.rhs = create_array(sizeof(char), len);
    for (int j = 0; j < len; j++) {
      insert_array(production.rhs, &productions[i][1][j]);
    }
    insert_array(cfg->productions, &production);
  }

  cfg->start_symbol = 'S';

  return cfg;
}

int equal_char(void* a, void* b) {
  return *(char*)a == *(char*)b;
}

struct Array* first(struct CFG* cfg, struct Array* s) {
  struct Array* result = create_array(sizeof(char), 1);

  if (s->length == 0) {
    char c = '\0';
    insert_array(result, &c);
    return result;
  }

  char* first_symbol = find_array(s, 0);
  if (find_if_array(cfg->terminals, first_symbol, equal_char)) {
    insert_array(result, first_symbol);
    return result;
  }

  for (int i = 0; i < cfg->productions->length; i++) {
    struct CFGProduction* production = (struct CFGProduction*)find_array(cfg->productions, i);
    if (production->lhs == ) {
      struct Array* new_result = first(cfg, production->rhs->data)
    }
  }
}

int main() {
  struct CFG* cfg = init_cfg();
  return 0;
}


struct LR1Item {
  struct LR1Item* next;
  int productions_n;
  int pos;
  char lookahead;
};

struct LR1ItemSet {
  struct LR1ItemSet* next;
  struct LR1Item* head;
};

struct LR1Item* closure(struct LR1Item** head) {
  // this function will change the list pointed by head.
  int is_changed = 0;

  do {
    is_changed = 0;

    for (struct LR1Item* item = *head; item != NULL; item = item->next) {
      char c = productions[item->productions_n]->rhs[item->pos];

      if (c == '\0' || islower(c)) { // need not closure
        continue;
      }

      char* lookahead = first(&productions[item->productions_n]->rhs[item->pos + 1]); // strcat(s, cur->lookahead);

      for (int i = 0; i < NPRODUCTION) {
        if (productions[i]->lhs != c) {
          continue;
        }

        for (int j = 0; j < NELEMS(lookahead); j++) { // how to storage lookahead? FIRST set?
          int is_existed = 0;

          for (struct LR1Item* old_item = *head; old_item != NULL; old_item = old_item->next) {
            if (old_item->productions_n == i && old_item->pos == 0 && old_item->lookahead == lookahead[j]) {
              is_existed = 1;
              break;
            }
          }

          if (is_existed == 0) {
            struct LR1Item* new_item = (struct LR1Item*)malloc(sizeof(struct LR1Item));
            new_item->productions_n = i;
            new_item->pos = 0;
            new_item->lookahead = lookahead[j];
            new_item->next = *head;
            *head = new_item;
            is_changed = 1;
          }
        }
      }
    }
  } while (is_changed == 1);

  return *head;
}

struct LR1Item* goto(struct LR1Item* item_set, char ) {

  for (;;) {
    ;
  }

  return closure(item_set);
}

struct ActionData {
  union {
    struct {
      int next;
    } shift;
    struct {
      int productions_n;
    } reduce;
  } data;
  char oper;
};

struct ActionData** action;

void init() {
  for (int i = 0; i < NPRODUCTION; i++) {
    fputc(productions[i].lhs, stdout);
    fputs(" -> ", stdout);
    fputs(productions[i].rhs, stdout);
    fputc('\n', stdout);
  }

  struct LR1ItemSet* canonicial_collection = (struct LR1ItemSet*)malloc(sizeof(struct LR1ItemSet));
  canonicial_collection->head = (struct LR1Item*)malloc(sizeof(struct LR1Item));
  canonicial_collection->head->productions_n = 0;
  canonicial_collection->head->pos = 0;
  canonicial_collection->head->lookahead = '$';
  canonicial_collection->head->next = NULL;
  canonicial_collection->next = NULL;

  int flag = 0;

  while (1) {
    ;
  }
}

int main()
{
  init();

  char c;
  while ((c = fgetc(stdin)) != '\n') {
    fputc(c, stdout);
  }

  return EXIT_SUCCESS;
}
