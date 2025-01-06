#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "functions.h"

// logic ham
void printCategoryMenu(){
	printf("***Store Management System Using C***\n\n");
	printf("\t      CATEGORY MENU\n");
	printf("\t=========================\n");
	printf("\t[1] Add Category\n");
	printf("\t[2] Show Category List\n");
	printf("\t[3] Edit A Category\n");
	printf("\t[4] Delete A Category\n");
	printf("\t[5] Search A Category\n");
	printf("\t[6] Sort Categories\n");
	printf("\t[7] Product Management\n");
	printf("\t[0] Exit the program\n");
	printf("\t=========================\n");
}

void exitProgram(){
	printf("=========== Thank you ===========\n");
	printf("=========== See you soon=========\n");
}

void clear(){
    system("cls");
}

int isNumber(char input[]){
    for(int i = 0; i < strlen(input); i++){
        if(!isdigit(input[i])){
        	return 0; 
        }
    }
    return 1; 
}

int checkCategoryId(int input){
    struct Category category[100];
    FILE *file = fopen("CategoryData.dat", "rb");
    if (file == NULL){
        return 1;
    }
    int numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    fclose(file);
    for(int i = 0; i < numberOfCategory; i++){
        if(category[i].categoryId == input){
            return 0; 
        }
    }
    return 1;
}

void saveCategoryToFile(int numberOfCategory, struct Category category[]){
    FILE *file = fopen("CategoryData.dat", "ab");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    int written = fwrite(category, sizeof(struct Category), numberOfCategory, file);
    if(written != numberOfCategory){
        printf("Error writing to file\n");
    }
    fclose(file);
}

void addCategory(int *length, struct Category category[]){
    int numberOfCategory;
    printf("\nEnter the number of categories you want to add: ");
    scanf("%d", &numberOfCategory);
    getchar();
    printf("***Store Management System Using C***\n\n");
    printf("\t      ADD CATEGORY\n");
    for (int i = *length; i < (*length + numberOfCategory); i++){
        printf("\t============================\n");    
        int isValid = 0;
        while(!isValid){
            char buffer[100];
            printf("\tCategory ID: ");
            scanf("%s", buffer);
            getchar();
            if(isNumber(buffer)){
                category[i].categoryId = atoi(buffer);
                if (category[i].categoryId >= 0) {
                    if (checkCategoryId(category[i].categoryId)){
                        isValid = 1;
                    }else{
                        printf("\tError: This ID already exists\n");
                    }
                }else{
                    printf("\tError: Invalid Input\n");
                }
            }else{
                printf("\tError: Invalid Input\n");
            }
        }
        isValid = 0;
        while(!isValid){
            printf("\tCategory Name: ");
            fgets(category[i].categoryName, sizeof(category[i].categoryName), stdin);
            category[i].categoryName[strcspn(category[i].categoryName, "\n")] = '\0';
            if(strlen(category[i].categoryName) > 0 && isValidName(category[i].categoryName)){
                if(checkCategoryName(category[i].categoryName)){
                    isValid = 1;
                }else{
                    printf("\tError: This category name already exists\n");
                }
            }else{
                printf("\tError: Invalid name (letters and spaces only)\n");
            }
        }
        printf("\t============================\n");
    }
    *length += numberOfCategory;
    saveCategoryToFile(numberOfCategory, &category[*length - numberOfCategory]);
    printf("\tAdd Categories Successfully\n\n");
    backOrExit();
}

void loadCategoryFromFile(int numberOfCategory, struct Category category[]){
	FILE *file = fopen("CategoryData.dat", "rb");
	if(file == NULL){
		printf("Error opening file\n");
		return;
	}
	numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    if(numberOfCategory == 0){
        printf("No data found\n");
    }else{
        printf("\nLoaded %d categories from file\n", numberOfCategory);
    }
    printf("+-------------+----------------------------+\n");
    printf("|              ALL CATEGORIES              |\n");
    printf("+-------------+----------------------------+\n");
    printf("| Category ID |           Name             |\n");
    printf("+-------------+----------------------------+\n");
    for(int i = 0; i < numberOfCategory; i++){
        printf("| %-11d | %-26s |\n", category[i].categoryId, category[i].categoryName);
        printf("+-------------+----------------------------+\n");
    }
    printf("\n");
    fclose(file);
}

void editCategory(int *numberOfCategory, struct Category category[]){
	loadCategoryFromFile(*numberOfCategory, category);
	FILE *file = fopen("CategoryData.dat", "rb+");
	if(file == NULL){
		printf("Error opening file\n");
		return;
	}
	*numberOfCategory = fread(category, sizeof(struct Category), 100, file);
	printf("\n\t***Store Management System Using C***\n\n");
	printf("\t           EDIT CATEGORY\n");
	printf("\t===================================\n");
	printf("\t+---------------------------------+\n");
	int position;
	validateIdInput(&position);
	int findIndex = -1;
	for(int i = 0; i < *numberOfCategory; i++){
		if(category[i].categoryId == position){
			findIndex = i;
			break;
		}
	}
	if(findIndex == -1){
		printf("\tError: This ID doesn't exist\n");
	}else{
		printf("\t+---------------------------------+\n");
		printf("\tCategory ID: %d\n", category[findIndex].categoryId);
		printf("\tCategory Name: %s\n", category[findIndex].categoryName);
		printf("\t+---------------------------------+\n");
		printf("\tInput New Category Name: ");
		fgets(category[findIndex].categoryName, sizeof(category[findIndex].categoryName), stdin);
		category[findIndex].categoryName[strcspn(category[findIndex].categoryName, "\n")] = '\0';
		fseek(file, findIndex * sizeof(struct Category), SEEK_SET);
		fwrite(&category[findIndex], sizeof(struct Category), 1, file);
		printf("\tEditing Success\n");
	}
	fclose(file);
	backOrExit();
	clear();
}

void validateNameInput(char input[]){
    int isValid = 0;
    while(!isValid){
        printf("\tEnter the Category Name: ");
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = '\0';
        if (isValidName(input)) {
            isValid = 1;
        }else{
            printf("\tError: Invalid Input\n");
        }
    }
}

int checkCategoryName(char name[]){
    struct Category category[100];
    FILE *file = fopen("CategoryData.dat", "rb");
    if (file == NULL){
        return 1; 
    }
    int numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    fclose(file);
    for(int i = 0; i < numberOfCategory; i++){
        if(strcmp(category[i].categoryName, name) == 0){
        	return 0; 
        }
    }
    return 1;
}

void deleteCategory(int *numberOfCategory, struct Category category[]){
	FILE *file = fopen("CategoryData.dat", "rb+");
	if(file == NULL){
		printf("Error opening file\n");
		return;
	}
	*numberOfCategory = fread(category, sizeof(struct Category), 100, file);
	fclose(file);
	printf("\n***Store Management System Using C***\n\n");
	printf("\t     DELETE CATEGORY\n");
	printf("\t=========================\n");
	printf("\t+-----------------------+\n");
	int position;
	validateIdInput(&position);
	int findIndex = -1;
	for(int i = 0; i < *numberOfCategory; i++){
		if(category[i].categoryId == position){
			findIndex = i;
			break;
		}
	}
	if(findIndex == -1){
		printf("\tError: This ID doesn't exist\n");
	}else{
		printf("\t+-----------------------+\n");
		printf("\tCategory ID: %d\n", category[findIndex].categoryId);
		printf("\tCategory Name: %s\n", category[findIndex].categoryName);
		printf("\t+-----------------------+\n");
		char select;
		printf("\tDelete This Category? (Y/N): ");
		scanf("%c", &select);
		getchar();
		if(select == 'y' || select == 'Y'){
			for(int i = findIndex; i < *numberOfCategory - 1; i++){
				category[i] = category[i + 1];
			}
			(*numberOfCategory)--;
   			file = fopen("CategoryData.dat", "wb");
    		if (file == NULL) {
       			printf("Error opening file\n");
        		return;
        	}
    		fwrite(category, sizeof(struct Category), *numberOfCategory, file);
    		printf("\tDelete Success\n");
   			printf("\t=========================\n");
    		fclose(file);
		}else if(select == 'n' || select == 'N'){
			return;
		}	
	}
	backOrExit();
	clear();
}

void searchCategory(int *numberOfCategory, struct Category category[]){
    FILE *file = fopen("CategoryData.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    *numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    fclose(file);
    printf("\t          SEARCH CATEGORY\n");
    printf("\t===================================\n");
    char categoryName[100];
    validateNameInput(categoryName);
    int findIndex = -1;
    for(int i = 0; i < *numberOfCategory; i++){
    	if(strstr(category[i].categoryName, categoryName) != NULL){
        	findIndex = i;
    	}
	}
    if(findIndex == -1){
        printf("\tError: This Category Name doesn't exist\n");
    }else{
    	printf("\n");
   	 	printf("+-------------+----------------------------+\n");
    	printf("| Category ID |           Name             |\n");
    	printf("+-------------+----------------------------+\n");
        printf("| %-11d | %-26s |\n", category[findIndex].categoryId, category[findIndex].categoryName);
        printf("+-------------+----------------------------+\n");
    }
    backOrExit();
    clear();
}

void sortCategory(int numberOfCategory, struct Category category[]){
	FILE *file = fopen("CategoryData.dat", "rb");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    fclose(file);
    if(numberOfCategory > 0){
    	printf("\t         SORT CATEGORY\n");
    	printf("\t+------------------------------+\n");
    	printf("\t[1] Sort by ID\n");
        printf("\t[2] Sort by Name\n");
        printf("\t+------------------------------+\n");
        printf("\tChoose sorting method: ");
        int choice;
        scanf("%d", &choice);
        getchar();
        if(choice == 1){
            sortCategoryById(&numberOfCategory, category);
        }else if(choice == 2){
            sortCategoryByName(&numberOfCategory, category);
        }else{
            printf("Invalid choice\n");
            return;
        }
    	displayCategory(numberOfCategory, category);
    	backOrExit();
    }else{
        printf("No categories found.\n");
    }
}

void displayCategory(int numberOfCategory, struct Category category[]){
    printf("+-------------+----------------------------+\n");
    printf("|              ALL CATEGORIES              |\n");
    printf("+-------------+----------------------------+\n");
    printf("| Category ID |           Name             |\n");
    printf("+-------------+----------------------------+\n");
    for(int i = 0; i < numberOfCategory; i++){
        printf("| %-11d | %-26s |\n", category[i].categoryId, category[i].categoryName);
        printf("+-------------+----------------------------+\n");
    }
    printf("\n");
}

void sortCategoryById(int *numberOfCategory, struct Category category[]){
    int n = *numberOfCategory;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(category[j].categoryId > category[j + 1].categoryId){
                struct Category temp = category[j];
                category[j] = category[j + 1];
                category[j + 1] = temp;
            }
        }
    }
}

void sortCategoryByName(int *numberOfCategory, struct Category category[]){
    int n = *numberOfCategory;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(strcmp(category[j].categoryName, category[j + 1].categoryName) > 0){
                struct Category temp = category[j];
                category[j] = category[j + 1];
                category[j + 1] = temp;
            }
        }
    }
}

int readCategoryFromFile(struct Category category[]){
    FILE *file = fopen("CategoryData.dat", "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    int numberOfCategory = fread(category, sizeof(struct Category), 100, file);
    fclose(file);
    return numberOfCategory;
}

void backOrExit(){
	char select;
	printf("\tBack(b) or Exit(0): ");
	scanf("%c", &select);
	getchar();
	if(select == '0'){
		clear();
		exitProgram();
		exit(0);
	}else if(select == 'b'){
		clear();
		return;
	}else{
		printf("\tInvalid selection\n");
		backOrExit();
	}
}

int isValidName(char input[]){
    int hasNoSpace = 0;
    for(int i = 0; i < strlen(input); i++){
        if(!isspace(input[i])){
            hasNoSpace = 1;
            break;
        }
    }
    if(!hasNoSpace) return 0;
    for(int i = 0; i < strlen(input); i++){
        if(!isalpha(input[i]) && input[i] != ' '){
            return 0;
        }
    }
    return 1;
}

void validateIdInput(int *input){
    char buffer[100];
    int isValid = 0;
    while(!isValid){
        printf("\tEnter the ID: ");
        scanf("%s", buffer);
        getchar();
        if(isNumber(buffer)){
            *input = atoi(buffer);
            if (*input >= 0){
                isValid = 1;
            }else{
                printf("\tError: Invalid Input\n");
            }
        }else{
            printf("\tError: Invalid Input\n");
        }
    }
}

void printProductMenu(){
	printf("***Store Management System Using C***\n\n");
	printf("\t      PRODUCT MENU\n");
	printf("\t=========================\n");
	printf("\t[1] Add Product\n");
	printf("\t[2] Show Product List\n");
	printf("\t[3] Edit A Product\n");
	printf("\t[4] Delete A Product\n");
	printf("\t[5] Search A Product\n");
	printf("\t[6] Sort Products\n");
	printf("\t[0] Exit the program\n");
	printf("\t=========================\n");	
}

void addProduct(int *length, struct Product product[]){
    int numberOfProduct;
    printf("\nEnter the number of products you want to add: ");
    scanf("%d", &numberOfProduct);
    getchar();
    printf("\n***Store Management System Using C***\n\n");
    printf("\t      ADD PRODUCT\n");
    for(int i = *length; i < (*length + numberOfProduct); i++){
        printf("\t============================\n");
        int isValid = 0;
        while(!isValid){
            printf("\tProduct ID: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if(isNumber(buffer)){
                int tempId = atoi(buffer);
                if (tempId > 0 && checkProductId(tempId)){
                    product[i].productId = tempId;
                    isValid = 1;
                }else{
                    printf("\tError: Invalid ID or ID already exists\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        isValid = 0;
        while(!isValid){
            printf("\tCategory ID: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if(isNumber(buffer)){
                int tempId = atoi(buffer);
                if(tempId > 0 && !checkCategoryId(tempId)){
                    product[i].categoryId = tempId;
                    isValid = 1;
                }else{
                    printf("\tError: Invalid ID or category doesn't exist\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        printf("\tProduct Name: ");
        fgets(product[i].productName, sizeof(product[i].productName), stdin);
        product[i].productName[strcspn(product[i].productName, "\n")] = '\0';
        isValid = 0;
        while (!isValid) {
            printf("\tQuantity: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if(isNumber(buffer)){
                int tempQty = atoi(buffer);
                if (tempQty >= 0) {
                    product[i].quantity = tempQty;
                    isValid = 1;
                }else{
                    printf("\tError: Quantity cannot be negative\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        isValid = 0;
        while(!isValid){
            printf("\tPrice: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            float tempPrice;
            if(sscanf(buffer, "%f", &tempPrice) == 1){
                if(tempPrice >= 0){
                    product[i].price = tempPrice;
                    isValid = 1;
                }else{
                    printf("\tError: Price cannot be negative\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        printf("\t============================\n");
    } 
    *length += numberOfProduct;
    saveProductToFile(numberOfProduct, &product[*length - numberOfProduct]);
    printf("\tAdd Products Successfully\n\n");
    backOrExit();
}

void saveProductToFile(int numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "ab");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    int written = fwrite(product, sizeof(struct Product), numberOfProduct, file);
    if(written != numberOfProduct){
        printf("\tError writing to file\n");
    }
    fclose(file);
}

void loadProductFromFile(int numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "rb");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    if(numberOfProduct == 0){
        printf("\tNo data found...\n");
    }else{
        printf("\n\tLoaded %d products from file\n", numberOfProduct);
    }
    displayProduct(numberOfProduct, product);
    fclose(file);
}

void displayProduct(int numberOfProduct, struct Product product[]){
    printf("+----------+------------+------------------+----------+------------+\n");
    printf("|                         ALL PRODUCTS                             |\n");
    printf("+----------+------------+------------------+----------+------------+\n");
    printf("| Prod. ID | Categ. ID  |       Name       | Quantity |   Price    |\n");
    printf("+----------+------------+------------------+----------+------------+\n");
    for(int i = 0; i < numberOfProduct; i++){
        printf("| %-8d | %-10d | %-16s | %-8d | %10.1f |\n", 
            product[i].productId, 
            product[i].categoryId,
            product[i].productName,
            product[i].quantity,
            product[i].price);
        printf("+----------+------------+------------------+----------+------------+\n");
    }
    printf("\n");
}

void deleteProduct(int *numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "rb+");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    *numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    fclose(file);
    printf("\n***Store Management System Using C***\n\n");
    printf("\t     DELETE PRODUCT\n");
    printf("\t=========================\n");
    int productId;
    printf("\tEnter Product ID to delete: ");
    scanf("%d", &productId);
    getchar();
    int findIndex = -1;
    for(int i = 0; i < *numberOfProduct; i++){
        if(product[i].productId == productId){
            findIndex = i;
            break;
        }
    }
    if(findIndex == -1){
        printf("\tError: Product ID not found\n");
    }else{
        printf("\tProduct Details:\n");
        printf("\t+-----------------------+\n");
        printf("\tProduct ID: %d\n", product[findIndex].productId);
        printf("\tProduct Name: %s\n", product[findIndex].productName);
        printf("\t+-----------------------+\n");
        char confirm;
        printf("\tAre you sure you want to delete this product? (Y/N): ");
        scanf("%c", &confirm);
        getchar();
        if(confirm == 'Y' || confirm == 'y'){
            for(int i = findIndex; i < *numberOfProduct - 1; i++){
                product[i] = product[i + 1];
            }
            (*numberOfProduct)--;
            file = fopen("ProductData.dat", "wb");
            if(file == NULL){
                printf("\tError opening file\n");
                return;
            }
            fwrite(product, sizeof(struct Product), *numberOfProduct, file);
            fclose(file);
            printf("\t=========================\n");
            printf("\tProduct deleted successfully!\n");
        }
    }
    backOrExit();
}

void searchProduct(int *numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "rb");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    *numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    fclose(file);
    printf("\n***Store Management System Using C***\n\n");
    printf("\t     SEARCH PRODUCT\n");
    printf("\t=========================\n");
    printf("\t[1] Search by ID\n");
    printf("\t[2] Search by Name\n");
    printf("\t+-----------------------+\n");
    printf("\tEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    getchar();
    if(choice == 1){
        int productId;
        printf("\tEnter Product ID: ");
        scanf("%d", &productId);
        int found = 0;
        for(int i = 0; i < *numberOfProduct; i++){
            if(product[i].productId == productId){
                printf("\n\tProduct Found:\n");
    			printf("+----------+------------+------------------+----------+------------+\n");
   				printf("| Prod. ID | Categ. ID  |       Name       | Quantity |   Price    |\n");
    			printf("+----------+------------+------------------+----------+------------+\n");
                printf("| %-8d | %-10d | %-16s | %-8d | %10.1f |\n",
                    product[i].productId,
                    product[i].categoryId,
                    product[i].productName,
                    product[i].quantity,
                    product[i].price);
                printf("+----------+------------+------------------+----------+------------+\n");
                found = 1;
                break;
            }
        }
        if(!found) printf("\tProduct not found!\n");
    }
    else if(choice == 2){
        char searchName[100];
        printf("\tEnter Product Name: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';
        int found = 0;
        printf("\n\tSearch Results:\n");
        printf("+----------+------------+------------------+----------+------------+\n");
   		printf("| Prod. ID | Categ. ID  |       Name       | Quantity |   Price    |\n");
    	printf("+----------+------------+------------------+----------+------------+\n");
        for(int i = 0; i < *numberOfProduct; i++){
            if(strstr(product[i].productName, searchName) != NULL){
                printf("| %-8d | %-10d | %-16s | %-8d | %10.1f |\n",
                    product[i].productId,
                    product[i].categoryId,
                    product[i].productName,
                    product[i].quantity,
                    product[i].price);
                printf("+----------+------------+------------------+----------+---------+\n");
                found = 1;
            }
        }
        if(!found) printf("\tNo products found\n");
    }
    backOrExit();
}

int checkProductId(int input){
    struct Product product[100];
    FILE *file = fopen("ProductData.dat", "rb");
    if (file == NULL){
        return 1;
    }
    int numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    fclose(file);
    for(int i = 0; i < numberOfProduct; i++){
        if(product[i].productId == input){
            return 0; 
        }
    }
    return 1; 
}

void sortProduct(int numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "rb");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    fclose(file);
    if(numberOfProduct > 0){
    	printf("\t         SORT PRODUCT\n");
    	printf("\t=========================\n");
        printf("\t[1] Sort by Price Ascending\n");
        printf("\t[2] Sort by Price Descending\n");
        printf("\t+-----------------------+\n");
        printf("\tChoose sorting method: ");
        int choice;
        scanf("%d", &choice);
        getchar();
        printf("\t+-----------------------+\n");
        switch(choice){
            case 1:
                sortProductByPriceAsc(numberOfProduct, product);
                break;
            case 2:
                sortProductByPriceDesc(numberOfProduct, product);
                break;
            default:
                printf("\tInvalid choice!\n");
                return;
        }
        displayProduct(numberOfProduct, product);
    }else{
        printf("\tNo products found.\n");
    }
    backOrExit();
}

void sortProductByPriceDesc(int numberOfProduct, struct Product product[]){
    for (int i = 0; i < numberOfProduct - 1; i++){
        for (int j = 0; j < numberOfProduct - i - 1; j++){
            if (product[j].price < product[j + 1].price){
                struct Product temp = product[j];
                product[j] = product[j + 1];
                product[j + 1] = temp;
            }
        }
    }
}

void sortProductByPriceAsc(int numberOfProduct, struct Product product[]){
    for(int i = 0; i < numberOfProduct - 1; i++){
        for(int j = 0; j < numberOfProduct - i - 1; j++){
            if(product[j].price > product[j + 1].price){
                struct Product temp = product[j];
                product[j] = product[j + 1];
                product[j + 1] = temp;
            }
        }
    }
}

void editProduct(int *numberOfProduct, struct Product product[]){
    FILE *file = fopen("ProductData.dat", "rb+");
    if(file == NULL){
        printf("\tError opening file\n");
        return;
    }
    *numberOfProduct = fread(product, sizeof(struct Product), 100, file);
    printf("\n***Store Management System Using C***\n\n");
    printf("\t           EDIT PRODUCT\n");
    printf("\t===================================\n");
    int productId;
    printf("\tEnter Product ID to edit: ");
    scanf("%d", &productId);
    getchar();
    int findIndex = -1;
    for(int i = 0; i < *numberOfProduct; i++){
        if(product[i].productId == productId){
            findIndex = i;
            break;
        }
    }
    if(findIndex == -1){
        printf("\tError: Product ID not found\n");
    }else{
        printf("\tCurrent Product Details:\n");
        printf("\tProduct ID: %d\n", product[findIndex].productId);
        printf("\tCategory ID: %d\n", product[findIndex].categoryId);
        printf("\tProduct Name: %s\n", product[findIndex].productName);
        printf("\tQuantity: %d\n", product[findIndex].quantity);
        printf("\tPrice: %.2f\n", product[findIndex].price);
        printf("\n\tEnter new details:\n");
        int isValid = 0;
        while(!isValid){
            printf("\tNew Category ID: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if(isNumber(buffer)){
                int tempId = atoi(buffer);
                if (tempId > 0 && !checkCategoryId(tempId)){
                    product[findIndex].categoryId = tempId;
                    isValid = 1;
                }else{
                    printf("\tError: Invalid ID or category doesn't exist\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        printf("\tNew Product Name: ");
        fgets(product[findIndex].productName, sizeof(product[findIndex].productName), stdin);
        product[findIndex].productName[strcspn(product[findIndex].productName, "\n")] = '\0';
        isValid = 0;
        while(!isValid){
            printf("\tNew Quantity: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            if(isNumber(buffer)){
                int tempQty = atoi(buffer);
                if(tempQty >= 0){
                    product[findIndex].quantity = tempQty;
                    isValid = 1;
                }else{
                    printf("\tError: Quantity cannot be negative\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        isValid = 0;
        while(!isValid){
            printf("\tNew Price: ");
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            float tempPrice;
            if(sscanf(buffer, "%f", &tempPrice) == 1){
                if(tempPrice >= 0){
                    product[findIndex].price = tempPrice;
                    isValid = 1;
                }else{
                    printf("\tError: Price cannot be negative\n");
                }
            }else{
                printf("\tError: Invalid input\n");
            }
        }
        fseek(file, findIndex * sizeof(struct Product), SEEK_SET);
        fwrite(&product[findIndex], sizeof(struct Product), 1, file);
        printf("\n\tProduct updated successfully!\n");
    }
    fclose(file);
    backOrExit();
}

