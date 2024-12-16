#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} User;

FILE* open_file(char* filename,char* type){
    FILE* file=fopen(filename,type);
    if(!file){
        printf("Error opening file");
       return 0;
    }
    return file;
}

void create_user() {
    FILE* file = open_file("users.txt", "a");
    
    User user;
    printf("Enter ID: ");
    scanf("%d", &user.id);
    getchar(); 
    printf("Enter Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0'; 
    printf("Enter Age: ");
    scanf("%d", &user.age);
    fprintf(file, "%d %s %d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added\n");
}

void read_users() {
    User user;
    FILE* file = open_file("users.txt", "r");
  
    printf("| ID | Name                 | Age |\n");
    while (fscanf(file, "%d %49s %d", &user.id, user.name, &user.age) != EOF) {
        printf("| %2d | %-20s | %3d |\n", user.id, user.name, user.age);
    }
    fclose(file);
}

void update_user() {
    FILE* file = open_file("users.txt", "r");
    
    FILE* temp = open_file("temp.txt", "w");
    // if (!temp) {
    //     fclose(file);
    //     printf("Error creating file\n");
    //     return;
    // }
    int id, found = 0;
    User user;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    while (fscanf(file, "%d %49s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            printf("Enter new ID: ");
            scanf("%d", &user.id);
            getchar(); 
            printf("Enter new Name: ");
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = '\0'; 
            printf("Enter new Age: ");
            scanf("%d", &user.age);
            found = 1;
        }
        fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
    }
    fclose(file);
    fclose(temp);
    remove("users.txt");
    rename("temp.txt", "users.txt");
    if (!found) printf("User not found\n");
    else printf("User updated successfully\n");
}

void delete_user() {
    FILE* file = open_file("users.txt", "r");
   
    FILE* temp = open_file("temp.txt", "w");
    // if (!temp) {
    //     fclose(file);
    //     printf("Error creating file\n");
    //     return;
    // }
    int id, found = 0;
    User user;
    printf("Enter ID : ");
    scanf("%d", &id);
    while (fscanf(file, "%d %49s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id != id) {
            fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove("users.txt");
    rename("temp.txt", "users.txt");
    if (!found) printf("User not found\n");
    else printf("User deleted successfully\n");
}

int main() {
    int choice;
    int counter=3;
    while (counter>0) {
        printf("\n1. Create User\n2. Read Users\n3. Update User\n4. Delete User\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1: create_user(); break;
            case 2: read_users(); break;
            case 3: update_user(); break;
            case 4: delete_user(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice\n",--counter);
        }
    }
}