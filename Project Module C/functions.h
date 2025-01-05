#include "datatypes.h"
//khai bao nguyen mau ham
void printCategoryMenu();
void selectMenu();
void exitProgram();
void clear();
void backOrExit();
int isNumber(char input[]);
int isValidName(char input[]);
void validateIdInput(int *input);
int checkCategoryId(int input);
void addCategory(int *length, struct Category category[]);
void saveCategoryToFile(int numberOfCategory, struct Category category[]);
void loadCategoryFromFile(int numberOfCategory, struct Category category[]);
void editCategory(int *numberOfCategory, struct Category category[]);
void validateNameInput(char input[]);
int checkCategoryName(char name[]);
void deleteCategory(int *numberOfCategory, struct Category category[]);
void searchCategory(int *numberOfCategory, struct Category category[]);
void sortCategory(int numberOfCategory, struct Category category[]);
void sortCategoryById(int *numberOfCategory, struct Category category[]);
void sortCategoryByName(int *numberOfCategory, struct Category category[]);
int readCategoryFromFile(struct Category category[]);
void displayCategory(int numberOfCategory, struct Category category[]);
void printProductMenu();
void addProduct(int *length, struct Product product[]);
int checkProductId(int input);
void saveProductToFile(int numberOfProduct, struct Product product[]);
void loadProductFromFile(int numberOfProduct, struct Product product[]);
void displayProduct(int numberOfProduct, struct Product product[]);
void deleteProduct(int *numberOfProduct, struct Product product[]);
void searchProduct(int *numberOfProduct, struct Product product[]);
void sortProduct(int numberOfProduct, struct Product product[]);
void sortProductByPriceAsc(int numberOfProduct, struct Product product[]);
void sortProductByPriceDesc(int numberOfProduct, struct Product product[]);
void editProduct(int *numberOfProduct, struct Product product[]);

