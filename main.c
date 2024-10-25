#include <stdio.h>
#include <stdlib.h>

enum Food_Type {
    Appetizer,
    MainCourse,
    Dessert
};

typedef struct {
    enum Food_Type food_t;
    const char* name;
    float price;
} Food;

Food addFood(enum Food_Type food_t, const char* name, float price);
void printMenu(Food* food_data, unsigned char* length);
int s_viaCategory(const void* a, const void* b);
void getUserFoods(int** buff, int* len_buff, Food* food_data, unsigned char* food_len);
void printnReceipt(int* items, int* item_len, Food* foods, float* ttl_bill);
void getPayment(float* total_bill);

#define MAX_FOOD 9
int main() {
    Food foodData[MAX_FOOD];

    foodData[0] = addFood(Appetizer, "Sinigang", 30.0);
    foodData[1] = addFood(Appetizer, "Lumpia", 15.0);
    foodData[2] = addFood(Appetizer, "Ceasar Salad", 99.0);

    foodData[3] = addFood(MainCourse, "Adobong Chicken", 180.0);
    foodData[4] = addFood(MainCourse, "Beef na Stik", 130.0);
    foodData[5] = addFood(MainCourse, "Pancit", 80.0);

    foodData[6] = addFood(Dessert, "Halo Halo", 80.0);
    foodData[7] = addFood(Dessert, "Leche Flan", 60.0);
    foodData[8] = addFood(Dessert, "Ube Ice Cream", 50.0);

    unsigned char food_length = sizeof(foodData) / sizeof(Food);
    qsort(foodData, food_length, sizeof(Food), s_viaCategory);
    printMenu(foodData, &food_length);

    int *selectedItems = NULL;
    unsigned int s_item_length = 0;

    float total_bill;

    getUserFoods(&selectedItems, &s_item_length, foodData, &food_length);
    printnReceipt(selectedItems, &s_item_length, foodData, &total_bill);
    getPayment(&total_bill);

    free(selectedItems);
    return 0;
}

Food addFood(enum Food_Type food_t, const char* name, float price) {
    Food buffer;
    buffer.food_t = food_t;
    buffer.name = name;
    buffer.price = price;

    return buffer;
}

int s_viaCategory(const void* a, const void* b) {
    return ((*(Food*)a).food_t - (*(Food*)b).food_t);
}

void printMenu(Food* food_data, unsigned char* length) {
    unsigned char a_count = 0;
    unsigned char mc_count = 0;
    unsigned char dess_count = 0;
    unsigned char *a_indexes = NULL;
    unsigned char *mc_indexes = NULL;
    unsigned char *dess_indexes = NULL;

    for(unsigned char i = 0; i < *length; i++)
        switch (food_data[i].food_t) {
        case Appetizer:
            a_count += 1;
            a_indexes = realloc(a_indexes, sizeof(unsigned char) * a_count);
            a_indexes[a_count - 1] = i;
            break;
        case MainCourse:
            mc_count += 1;
            mc_indexes = realloc(mc_indexes, sizeof(unsigned char) * mc_count);
            mc_indexes[mc_count - 1] = i;
            break;
        case Dessert:
            dess_count += 1;
            dess_indexes = realloc(dess_indexes, sizeof(unsigned char) * dess_count);
            dess_indexes[dess_count - 1] = i;
            break;
        }

    printf("Gonzales and Toreta's Restaurant Menu:\n");
    
    if(a_count != 0) {
        printf("Appetizer:\n");
        for(unsigned char i = 0; i < a_count; i++)
            printf("\t%i.%s, price: %.2f\n",
            (i + 1),food_data[a_indexes[i]].name, food_data[a_indexes[i]].price);
    }

    if(mc_count != 0) {
        printf("Main Courses:\n");
        for(unsigned char i = 0; i < mc_count; i++)
        printf("\t%i.%s, price: %.2f\n",
            (i + 4),food_data[mc_indexes[i]].name, food_data[mc_indexes[i]].price);
    }

    if(dess_count != 0) {
        printf("Desserts:\n");
        for(unsigned char i = 0; i < dess_count; i++)
        printf("\t%i.%s, price: %.2f\n",
            (i + 7),food_data[dess_indexes[i]].name, food_data[dess_indexes[i]].price);
    }

    free(a_indexes);
    free(mc_indexes);
    free(dess_indexes);

    printf("\nSelect items by entering their id:\n");
}

void getUserFoods(int** buff, int* len_buff, Food* food_data, unsigned char* food_len) {
    unsigned char choice;
    unsigned int count_s = 0;

    while (1) {
        printf("Select [1-9] 0 to exit: ");
        if (scanf("%hhu", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0)
            break;
        
        if (choice >= 1 && choice <= *food_len) {
            int* temp = realloc(*buff, sizeof(int) * (count_s + 1));
            *buff = temp;
            (*buff)[count_s] = choice - 1;
            count_s++;
        } else {
            printf("Invalid choice. Please select a valid item.\n");
        }
    }

    *len_buff = count_s;
}

void printnReceipt(int* items, int* item_len, Food* foods, float* ttl_bill) {
    printf("-------------------------");
    printf("\nReceipt:\n");
    float total;
    for(unsigned int i = 0; i < (*item_len); i++) {
        printf("%s:\t P%.2f\n", foods[items[i]].name, foods[items[i]].price);
        total += foods[items[i]].price;
    }

    printf("Total Bill: %.2f\n", total);
    printf("-------------------------");
    (*ttl_bill) = total;
}

void getPayment(float* total_bill) {
    float payment;
    printf("\nEnter the amount you are paying: P");
    scanf("%f", &payment);
    if (payment < (*total_bill)) {
        printf("\nPayment is less than the total bill. Please pay the full amount.\n");
    } else {
        float change = payment - (*total_bill);
        printf("\nThank you for your payment. Your change is P%.2f\n", change);
    }
}