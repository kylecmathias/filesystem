#include "filesystem.h"

int createFile(const char *filename, const char *filepath, int size) {
    char fullFilePath[MAX_PATH];
    int attributes = GetFileAttributes(fullFilePath) != INVALID_FILE_ATTRIBUTES;

    if (attributes) {
        printf("Error: File '%s' already exists in the specified directory.\n", filename);
        return -1;
    }

    if (strstr(filename, ".") == NULL) {
        printf("Error: File extension missing in '%s'.\n", filename);
        return -1;
    }

    snprintf(fullFilePath, sizeof(fullFilePath), "%s\\%s", filepath, filename);

    if (GetFileAttributes(fullFilePath) != INVALID_FILE_ATTRIBUTES) {
        printf("Error: File '%s' already exists in the specified directory.\n", filename);
        return -1;
    }

    HANDLE fileHandle = CreateFile(
        fullFilePath,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to create file '%s'. Error code: %lu\n", filename, GetLastError());
        return -1;
    }

    CloseHandle(fileHandle);

    printf("File '%s' created and edited successfully.\n", filename);

    return 0;
}

int deleteFile(const char *filename, const char *filepath) {
    if (filepath[strlen(filepath) - 1] != '\\') {
        char fullDirectoryPath[MAX_PATH];
        snprintf(fullDirectoryPath, sizeof(fullDirectoryPath), "%s\\", filepath);
        filepath = fullDirectoryPath;
    }

    char fullFilePath[MAX_PATH];
    snprintf(fullFilePath, sizeof(fullFilePath), "%s%s", filepath, filename);

    if (DeleteFile(fullFilePath)) {
        printf("File '%s' deleted successfully.\n", filename);
        return 0;
    } else {
        printf("Error: Unable to delete file '%s'. Error code: %lu\n", filename, GetLastError());
        return -1;
    }
}

void readFile(const char *filename, const char *directory) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "%s\\%s", directory, filename);

    HANDLE fileHandle = CreateFile(
        filepath,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle != INVALID_HANDLE_VALUE) {
        char buffer[BLOCK_SIZE];
        DWORD bytesRead;

        while (ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
            printf("%.*s", (int)bytesRead, buffer);
        }

        CloseHandle(fileHandle);
        printf("\nFile read successfully.\n");
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}

void writeFile(const char *filename, const char *directory, const char *data) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "%s\\%s", directory, filename);

    HANDLE fileHandle = CreateFile(
        filepath,
        FILE_APPEND_DATA, 
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,  
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle != INVALID_HANDLE_VALUE) {
        DWORD bytesWritten;
        if (WriteFile(fileHandle, data, strlen(data), &bytesWritten, NULL)) {
            CloseHandle(fileHandle);
            printf("Data appended to file successfully.\n");
        } else {
            printf("Error: Unable to append data to file.\n");
            CloseHandle(fileHandle);
        }
    } else {
        printf("Error: Unable to open file for appending.\n");
    }
}


void rewriteFile(const char *filename, const char *directory, const char *data) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "%s\\%s", directory, filename);

    HANDLE fileHandle = CreateFile(
        filepath,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle != INVALID_HANDLE_VALUE) {
        DWORD bytesWritten;
        if (WriteFile(fileHandle, data, strlen(data), &bytesWritten, NULL)) {
            CloseHandle(fileHandle);
            printf("Data written to file successfully.\n");
        } else {
            printf("Error: Unable to write data to file.\n");
            CloseHandle(fileHandle);
        }
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

