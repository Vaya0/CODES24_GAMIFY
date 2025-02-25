
#include <iostream>
#include <fstream>
#include <cstring>  
#include <sstream>
#include <Windows.h>
#include <thread>
#pragma warning(disable : 4996)


class FileManager {
private:
    static constexpr int MAX_FILES = 100; 
    char  filenames[MAX_FILES][255] = {}; 
    int numFiles = 0;

public:
    void createFile(const char* filename);

    int findFile(const char* filename);

    void readFile(const char* filename);

    void writeFile(const char* filename);

    void deleteFile(const char* filename);
l
    void interface1();
};

void FileManager::createFile(const char* filename) {
    if (numFiles < MAX_FILES) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to create file: " << filename << std::endl;
        }
        else {
            file.close();
            strcpy_s(filenames[numFiles++], 255, filename);
            std::cout << "File '" << filename << "' created successfully." << std::endl;
        }
    }
    else {
        std::cerr << "Maximum number of files reached." << std::endl;
    }
}

int FileManager::findFile(const char* filename) {
    for (int i = 0; i < numFiles; ++i) {
        if (std::strcmp(filenames[i], filename) == 0) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

size_t getFileSize(std::ifstream& f) {
    size_t currentPos = f.tellg();
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();

    f.seekg(currentPos);
    return size;
}

void FileManager::readFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary); 
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    size_t fileSize = getFileSize(file);

    char* buffer = new char[fileSize];
    file.read(buffer, fileSize);
    file.close();

    std::cout << "Content of '" << filename << "':\n";
    std::cout.write(buffer, fileSize);

    delete[] buffer;
}

void FileManager::writeFile(const char* filename) {
    std::ofstream file(filename, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    else {
        std::cout << "Enter content to write (write the word 'DONE' if you have finished):\n";
        std::string line;
        while (true) {
            std::getline(std::cin, line);
            if (line == "DONE") {
                break;  
            }
            file << line << std::endl; 
        }
        file.close();
        std::cout << "Content written to file '" << filename << "' successfully." << std::endl;
    }
}

void FileManager::deleteFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File '" << filename << "' does not exist." << std::endl;
        return;
    }
    file.close();
    remove(filename);
    int index = findFile(filename);
    if (index != -1) {
        for (int i = index; i < numFiles - 1; ++i) {
            strcpy_s(filenames[i], 255, filenames[i + 1]);
        }
        numFiles--;
        std::cout << "File '" << filename << "' deleted successfully." << std::endl;
    }
    else {
        std::cerr << "Error deleting file: " << filename << std::endl;
    }
}


DWORD WINAPI SecondConsoleThread(LPVOID lpParam) {
    AllocConsole();

    SetConsoleTitle(L"Second Console");
 
    getchar();
    
    return 0;
}

    void FileManager::interface1() {

    HANDLE hThread = CreateThread(NULL, 0, SecondConsoleThread, NULL, 0, NULL);

    CloseHandle(hThread);

    getchar();

    AllocConsole();
    AttachConsole(ATTACH_PARENT_PROCESS);

    FILE* stdout_file = stdout;
    FILE* stdin_file = stdin;
    FILE* file1;
    FILE* file2;
    freopen_s(&file1, "CONOUT$", "w", stdout_file);
    freopen_s(&file2, "CONIN$", "r", stdin_file); 
   
    printf("~Choose an operation:\n");
    printf("1. Create a file\n");
    printf("2. Read a file\n");
    printf("3. Write to a file\n");
    printf("4. Delete a file\n");
    printf("5. Exit\n");

    int choice;
    while (1) {
        std::cin >> choice;
        switch (choice) {
        case 1: {
            std::cout << "Enter filename to create: ";
            char filename[256];
            std::cin >> filename;
            createFile(filename);
            break;
        }
        case 2: {
            std::cout << "Enter filename to read: ";
            char filename[256];
            std::cin >> filename;
            readFile(filename);
            break;
        }
        case 3: {
            std::cout << "Enter filename to write to: ";
            char filename[256];
            std::cin >> filename;
            writeFile(filename);
            break;
        }
        case 4: {
            std::cout << "Enter filename to delete: ";
            char filename[256];
            std::cin >> filename;
            deleteFile(filename);
            break;
        }
        case 5: {
            freopen_s(&stdout_file, "CONOUT$", "w", file1);
            freopen_s(&stdin_file, "CONIN$", "r", file2); 
            return ;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
       
    }
    
    return;
}



int main() {
    
    std::cout << "THIS IS MAIN" << std::endl;
   
    HANDLE hOriginalStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOriginalStdin = GetStdHandle(STD_INPUT_HANDLE);

    FileManager fileManager;
    FreeConsole();
    fileManager.interface1(); 
    
    SetStdHandle(STD_OUTPUT_HANDLE, hOriginalStdout);
    SetStdHandle(STD_INPUT_HANDLE, hOriginalStdin);

    return 0;
}
