#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Khai bao cau truc
struct Category {
    int categoryId;
    char categoryName[20];
};

struct Product {
    int productId; 
    int categoryId;
    char productName[20];
    int quantity;
    float price;
};

