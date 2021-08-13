/* code to track my meals/macros */
#include <food.h>
#include <stdio.h>
#include <string.h>

/* function prototypes */

/* adding food to database */
Food *create_food(const char *, double, double, double, int);
/* print the macros of a food */
void print_food_stats(Food *food);
/* deallocates memory for given food structure */
void destroy_food(Food *food);
/* calculate macros of two foods*/
void initalize_meal(Meal *meal);
/* add food to meal */
int add_food_to_meal(Meal *meal, const char *name, double grams_of_fat,
                     double grams_of_carb, double grams_of_protein,
                     int calories);
/* print meal */
void print_meal(const Meal *meal);
/* deallocate memory for meal */
void destroy_meal(Meal *meal);

Food *create_food(const char *name, double grams_of_fat, double grams_of_carb,
                  double grams_of_protein, int calories) {
  Food *food = malloc(sizeof(Food));

  /* if allocated memory failed */
  if (!food) {
    return NULL;
  }

  if (name) {
    food->name = malloc(strlen(name) + 1); /* dynamically allocated */

    if (food->name && calories >= 0) {
      strcpy(food->name, name);

      food->grams_of_fat = grams_of_fat;
      food->grams_of_carb = grams_of_carb;
      food->grams_of_protein = grams_of_protein;
      food->calories = calories;
    } else {
      return NULL;
    }
  }

  return food;

} /* end of add_food() */

/* given food, print food stats */
void print_food(Food *food) {
  if (food) {
    if (food->name) {
      printf("Food: %s\n", food->name);
      printf("Fat: %lf\n", food->grams_of_fat);
      printf("Carb: %lf\n", food->grams_of_carb);
      printf("Protein: %lf\n", food->grams_of_protein);

      printf("Calories: %d\n", food->calories);
    }
  }
}

/* deallocate memory */
void destroy_food(Food *food) {
  if (food) {
    free(food->name);
    free(food);
  }
}

/* initalize meal */
void initalize_meal(Meal *meal) {
  if (meal) {
    meal->number_of_foods = 0;
    meal->total_calories = 0;
  }
}
int add_food_to_meal(Meal *meal, const char *name, double grams_of_fat,
                     double grams_of_carb, double grams_of_protein,
                     int calories) {
  Food *new_food;

  /* if any input is invalid */
  if (!meal || !name || grams_of_protein < 0 || calories < 0 ||
      grams_of_carb < 0 || grams_of_fat < 0) {
    /* return error */
    return -1;
  }

    /* if list is empty */
  if (meal->head == NULL) {
      create_food(name, grams_of_fat, grams_of_carb, grams_of_protein,calories);
      meal->head = new_food;
  } 
  /* if list is not empty */
  else {
      /* Tom & Jerry Traverse */
      Food *curr = meal->head, *prev = NULL;

        /* sorts by name */
      while (curr && strcmp(name, curr->name)<0){
          prev = curr;
          curr = curr->next;
      }

      /* if food is already in the list */
      if (curr && !strcmp(name,curr->name)){
          /* not really an error, but assume I don't eat same thing twice */
          return -1;
      }else {
          create_food(name,grams_of_fat, grams_of_carb, grams_of_protein,calories);
          if (!curr){
              /* add at end of list */
              prev->next = new_food;
          }else {
              /* insert at beginning of list */
              if (!prev){
                  new_food->next = meal->head;
                  meal->head = new_food;
              }else {
                  /* insert before */
                  prev->next = new_food;
                  new_food->next = curr;
              }
          }
      } /* end of main else */
  }
}

void print_meal(const Meal *meal) {
  int i;
  Food *curr = meal->head;
  if (curr) {
    printf("***** MEAL *****\n");
    printf("Number of Foods: %d\n", meal->number_of_foods);
    printf("Total Calories: %d\n", meal->total_calories);

    while (curr) {
      print_food(curr);

      curr = curr->next;
    }
  }
  fflush(stdout);
}

/* deallocate meal */
void destroy_meal(Meal *meal){
    if (meal){
        Food *curr = meal->head;

        while(curr){
            Food *destroy = curr;

            curr = curr->next;
            /* calls destroy food function to properly deallocate */
            destroy_food(destroy);
        }
        free(meal);

    }
}