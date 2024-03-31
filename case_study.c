#include <stdio.h>
#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS_TO_ADD 10
char item_names[MAX_ITEMS][MAX_NAME_LENGTH];
float item_prices[MAX_ITEMS];
int item_quantities[MAX_ITEMS];
int numItems = 0;
int compareNames(const char *name1, const char *name2) {
    int i = 0;
    while (name1[i] != '\0' && name2[i] != '\0') {
        if (name1[i] != name2[i]) {
            return 0;
        }
        i++;
    }
    return name1[i] == '\0' && name2[i] == '\0';
}
void addProducts() {
    if (numItems >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }
    if (numItems + MAX_PRODUCTS_TO_ADD > MAX_ITEMS) {
        printf("Cannot add more than %d products at once.\n", MAX_PRODUCTS_TO_ADD);
        return;
    }
    int numProducts;
    printf("Enter the number of products to add (maximum %d): ", MAX_PRODUCTS_TO_ADD);
    scanf("%d", &numProducts);
    if (numProducts <= 0 || numProducts > MAX_PRODUCTS_TO_ADD) {
        printf("Invalid number of products.\n");
        return;
    }
    for (int i = 0; i < numProducts; i++) {
        printf("Enter product details for product %d:\n", numItems + 1);
        printf("Name: ");
        scanf("%s", item_names[numItems]);
        printf("Price (in Rs): ");
        scanf("%f", &item_prices[numItems]);
        printf("Quantity: ");
        scanf("%d", &item_quantities[numItems]);
        numItems++;
    }
    printf("Products added successfully.\n");
}
void generateBill() {
    char itemName[MAX_NAME_LENGTH];
    int quantityNeeded;
    float total = 0.0;
    float tax = 0.0; // Initialize tax
    int found = 0;
    printf("Enter the number of different products to buy: ");
    scanf("%d", &quantityNeeded);
    printf("\n-------------------BILL-------------------\n");
    printf("%-20s %-10s %-10s\n", "Item", "Price", "Quantity");
    printf("------------------------------------------\n");
    for (int i = 0; i < quantityNeeded; i++) {
        printf("Enter the product you need: ");
        scanf("%s", itemName);
                found = 0;
        for (int j = 0; j < numItems; j++) {
            if (compareNames(itemName, item_names[j])) {
                found = 1;
                int quantityToBuy;
                printf("Enter quantity of %s: ", itemName);
                scanf("%d", &quantityToBuy);
                if (item_quantities[j] >= quantityToBuy) {
                    printf("%-20s %-10.2f %-10d\n", item_names[j], item_prices[j], quantityToBuy);
                    total += item_prices[j] * quantityToBuy;
                    item_quantities[j] -= quantityToBuy;
                } else {
                    printf("Insufficient quantity available for %s.\n", itemName);
                    break;
                }
            }
        }

        if (!found) {
            printf("Product %s not available.\n", itemName);
        }
    }

    // Calculate tax (9% of the total)
    tax = total * 0.09;
    total += tax; // Add tax to the total

    printf("------------------------------------------\n");
    printf("Subtotal: Rs%.2f\n", total - tax); // Display subtotal before tax
    printf("Tax (9%%): Rs%.2f\n", tax); // Display tax amount
    printf("Total: Rs%.2f\n", total);
}

int main() {
    int choice;
    do {
        printf("\nWelcome to Smart Bazaar!\n");
        printf("1. Customer\n");
        printf("2. Shop Owner\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateBill();
                break;
            case 2:
                addProducts();
                break;
            case 3:
                printf("Exiting...\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (1); // Infinite loop until choice 3 is selected

    return 0;
}