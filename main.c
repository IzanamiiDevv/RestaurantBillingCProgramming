#include <stdio.h>
#include <stdlib.h>
#define MAX_FOOD 10

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
void printMenu(Food* food_data);
int s_viaCategory(const void* a, const void* b);

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

    qsort(foodData, MAX_FOOD, sizeof(Food), s_viaCategory);
    printMenu(foodData);

    
    float appetizers[] = {30.0, 15.0, 99.0};
    float mainCourses[] = {180.0, 130.0, 80.0};
    float desserts[] = {80.0, 60.0, 50.0};

    float totalBill = 0.0;
    int choice;

    int selectedItems[10];
    int itemCount = 0;

    while (1) {
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice >= 1 && choice <= 9) {
            selectedItems[itemCount++] = choice;
            switch (choice) {
                case 1:
                    totalBill += appetizers[0];
                    break;
                case 2:
                    totalBill += appetizers[1];
                    break;
                case 3:
                    totalBill += appetizers[2];
                    break;
                case 4:
                    totalBill += mainCourses[0];
                    break;
                case 5:
                    totalBill += mainCourses[1];
                    break;
                case 6:
                    totalBill += mainCourses[2];
                    break;
                case 7:
                    totalBill += desserts[0];
                    break;
                case 8:
                    totalBill += desserts[1];
                    break;
                case 9:
                    totalBill += desserts[2];
                    break;
            }
        } else {
            printf("Invalid choice. Please select a valid item.\n");
        }
    }

    printf("-------------------------");
    printf("\nReceipt:\n");
    for (int i = 0; i < itemCount; i++) {
        choice = selectedItems[i];
        switch (choice) {
            case 1:
                printf("Sinigang Soup:\t P%.2f\n", appetizers[0]);
                break;
            case 2:
                printf("Lumpia:\t\t P%.2f\n", appetizers[1]);
                break;
            case 3:
                printf("Ceasar Salad:\t P%.2f\n", appetizers[2]);
                break;
            case 4:
                printf("Chicken Adobo:\t P%.2f\n", mainCourses[0]);
                break;
            case 5:
                printf("Beef Steak:\t P%.2f\n", mainCourses[1]);
                break;
            case 6:
                printf("Pancit:\t\t P%.2f\n", mainCourses[2]);
                break;
            case 7:
                printf("Halo-Halo:\t P%.2f\n", desserts[0]);
                break;
            case 8:
                printf("Leche Flan:\t P%.2f\n", desserts[1]);
                break;
            case 9:
                printf("Ube Ice Cream:\t P%.2f\n", desserts[2]);
                break;
        }
    }

    printf("-------------------------");
    printf("\nTotal Bill:\t P%.2f\n", totalBill);
    printf("-------------------------");
    
    float payment;
    printf("\nEnter the amount you are paying: P");
    scanf("%f", &payment);

    if (payment < totalBill) {
        printf("\nPayment is less than the total bill. Please pay the full amount.\n");
    } else {
        float change = payment - totalBill;
        printf("\nThank you for your payment. Your change is P%.2f\n", change);
    }

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

void printMenu(Food* food_data) {
    unsigned char a_count = 0;
    unsigned char mc_count = 0;
    unsigned char dess_count = 0;
    unsigned char *a_indexes = NULL;
    unsigned char *mc_indexes = NULL;
    unsigned char *dess_indexes = NULL;

    for(unsigned char i = 0; i < MAX_FOOD; i++)
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