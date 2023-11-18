#include "filesystem.c"

void printMenu() {
    printf("\n==== Mini File System ====\n");
    printf("1. Create File\n");
    printf("2. Delete File\n");
    printf("3. Read File\n");
    printf("4. Write to File\n");
    printf("5. Rewrite File\n");
    printf("6. Exit\n");
    printf("==========================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char filename[MAX_FILENAME_LEN];
    char filepath[MAX_PATH];
    char data[BLOCK_SIZE];
    int size;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", filename);
                printf("Enter file path: ");
                scanf("%s", filepath);
                printf("Enter file size: ");
                scanf("%d", &size);
                createFile(filename, filepath, size);
                break;

            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", filename);
                printf("Enter file path: ");
                scanf("%s", filepath);
                deleteFile(filename, filepath);
                break;

            case 3:
                printf("Enter file name to read: ");
                scanf("%s", filename);
                printf("Enter file path: ");
                scanf("%s", filepath);
                readFile(filename, filepath);
                break;

            case 4:
                printf("Enter file name to write: ");
                scanf("%s", filename);
                printf("Enter file path: ");
                scanf("%s", filepath);
                printf("Enter data to write: ");
                scanf("%s", data);
                writeFile(filename, filepath, data);
                break;

            case 5:
                printf("Enter file name to rewrite: ");
                scanf("%s", filename);
                printf("Enter file path: ");
                scanf("%s", filepath);
                printf("Enter data to rewrite: ");
                scanf("%s", data);
                rewriteFile(filename, filepath, data);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
