#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PRODUCTS 100
void delete_product(void);
void add_product(void);
void search_product(void);
void display_menu(void);

struct Product {
    char barcode_num[14];
    char product_name[100];
    float price;
    int stock;
};

struct Product products[MAX_PRODUCTS];
int num_products = 0;

void add_product() {
    char barcode_num[14], product_name[100];
    float price;
    int stock;

    
    printf("Enter the barcode of the product : ");
    scanf("%s", barcode_num);
    printf("Enter the name of the product : ");
    scanf("%s", product_name);
    printf("Enter the price of the product : ");
    scanf("%f", &price);
    printf("Enter the stock of the product : ");
    scanf("%d", &stock);


    struct Product new_product;
    strcpy(new_product.barcode_num, barcode_num);
    strcpy(new_product.product_name, product_name);
    new_product.price = price;
    new_product.stock = stock;

    products[num_products++] = new_product;

 
    FILE* file = fopen("products.txt", "a");
    fprintf(file, "%s;%s;%.2f;%d\n", barcode_num, product_name, price, stock);
    fclose(file);
    printf("Product is adding.....Please wait...\n");
    sleep(1.5);
    printf("Product added successfully.\n");
}

void search_product() {
    char barcode_num[14];
    printf("Enter the barcode of the product to search : ");
    scanf("%s", barcode_num);
    printf("Product is searching...Please wait..\n");
    sleep(1.5);
    
    for (int i = 0; i < num_products; i++) {
        if (strcmp(barcode_num, products[i].barcode_num) == 0) {
            printf("Product found: %s, %.2f TL, %d in stock.\n", products[i].product_name, products[i].price, products[i].stock);
            return;
        }
    }
    printf("Product not found.\n");
}


void delete_product() {
    char barcode_num[14];
    printf("Enter the barcode of the product to delete : ");
    scanf("%s", barcode_num);

    for (int i = 0; i < num_products; i++) {
        if (strcmp(barcode_num, products[i].barcode_num) == 0) {
            
            for (int j = i; j < num_products - 1; j++) {
                products[j] = products[j + 1];
            }
            num_products--;

            
            FILE* file = fopen("products.txt", "w");
            for (int i = 0; i < num_products; i++) {
                fprintf(file, "%s;%s;%.2f;%d\n", products[i].barcode_num, products[i].product_name, products[i].price, products[i].stock);
            }
            fclose(file);
            printf("Product is being deleted......Please wait...\n");
            sleep(2);
            printf("Product deleted successfully.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void display_menu() {
    printf("\nWelcome to the product management system.\n");
    printf("***MENU***\n");
    printf("1. Add a product\n");
    printf("2. Search for a product\n");
    printf("3. Delete a product\n");
    printf("4. Exit\n");
    printf("Please select an option : ");
}
int main() {
    
    FILE* file = fopen("products.txt", "r");
    if (file) {
        char line[200];
        while (fgets(line, sizeof(line), file)) {
            char barcode_num[14], product_name[100], stock_str[10], price_str[10];
            int stock;
            float price;
            sscanf(line, "%[^;];%[^;];%[^;];%[^;]\n", barcode_num, product_name, price_str, stock_str);
            price = atof(price_str);
            stock = atoi(stock_str);
            
            struct Product product;
            strcpy(product.barcode_num, barcode_num);
            strcpy(product.product_name, product_name);
            product.price = price;
            product.stock = stock;
            
            products[num_products++] = product;
        }
        fclose(file);
    }
    while(1){
        int choice;
        
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_product();
                break;
            case 2:
                search_product();
                break;
            case 3:
                delete_product();
                break;
            case 4:
                printf("Exiting....!\n");
                sleep(1.5);
                printf("BYE BYE \n");
                return 1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
}
