/* food structures */

#if !defined(FOOD_H)
#define FOOD_H

/* 1 gram of protein = 4 calories */
#define CALORIES_PER_GRAM_PROTEIN 4
/* 1 gram of fat = 9 calories */
#define CALORIES_PER_GRAM_FAT 9
/* 1 gram of carb = 4 calories */
#define CALORIES_PER_GRAM_CARB 4

/* maximum number of meals I would be eating */
#define MAX_MEALS 6

/* structure for food */
typedef struct food{
    char *name; /* dynamically allocated */
    double grams_of_fat, grams_of_carb, grams_of_protein;

    /* calories should be all grams added together */
    int calories;

    /* linked-list */
    struct food *next;
    /* design fat, carb, protein structures and have calories == that */
} Food;

/* structure for meal, which includes food */
typedef struct meal {
    Food *head;
    int number_of_foods;
    int total_calories;
} Meal;

#endif