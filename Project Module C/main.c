#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int choice;
	int select;
	struct Category category[100];
	struct Product product[100];
	int numberOfCategory = 0;
	int numberOfProduct = 0;
	int length = 0;
	do{
		clear();
		printCategoryMenu();
		printf("\tEnter your choice: ");
		scanf("%d", &choice);
		getchar();
		switch(choice){
			case 1: // Add Category
				clear();
				addCategory(&length, category);
				break;
			case 2: // Show Category List
				clear();
				numberOfCategory = readCategoryFromFile(category);
				displayCategory(numberOfCategory, category);
				backOrExit();
				break;
			case 3: // Edit A Category
				clear();
				editCategory(&numberOfCategory, category);
				break;
			case 4: // Delete A Category
				clear();
				deleteCategory(&numberOfCategory, category);
				break;
			case 5: // Search A Category
				clear();
				searchCategory(&numberOfCategory, category);
				break;
			case 6: // Sort Category
				clear();
				sortCategory(numberOfCategory, category);
				break;
			case 7: // Product Management
				clear();
				do{
					printProductMenu();
					printf("\tEnter your select: ");
					scanf("%d", &select);
					getchar();
					switch(select){
						case 1: // Add Product
							clear();
							addProduct(&length, product);
							break;
						case 2: // Show Product List
							clear();
							loadProductFromFile(numberOfProduct, product);
							backOrExit();
							break;
						case 3: // Edit A Product
							clear();
							editProduct(&numberOfProduct, product);
							break;
						case 4: // Delete A Product
							clear();
							deleteProduct(&numberOfProduct, product);
							break;
						case 5: // Search A Product
							clear();
							searchProduct(&numberOfProduct, product);
							break;
						case 6: // Sort Products
							clear();
							sortProduct(&numberOfProduct, product);
							break;
						case 0: // Exit
							clear();
							break;
						default:
							printf("Error: Your choice is invalid\n");
							backOrExit();
					}
				}while(select != 0);
				break;
			case 0: // Exit 
				clear();
				exitProgram();
				break;
			default:
				printf("Error: Your choice is invalid\n");
				backOrExit();
		}
	}while(choice != 0);
	return 0;
}

