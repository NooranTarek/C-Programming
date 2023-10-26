#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define maximumWords 50

struct Word {
    char text[100];
    int length;
};

void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printWithCursor(char* text, int cursorPos, int row, int col) {
    gotoxy(col, row);
    for (int i = 0; i < strlen(text); i++) {
        if (i == cursorPos) {
            printf("_");
        }
        printf("%c", text[i]);
    }
    if (cursorPos == strlen(text)) {
        printf(" ");
    }
}

//void clearBuffer() {
//    int ch;
//    while ((ch = getchar()) != '\n' && ch != EOF);
//}

int main() {
    struct Word words[maximumWords];
    int numWords = 0;
    int choice = 0;
    int cursorX = 0;
    char character;
    int currentWord = -1; // To track which word is being edited

    while (1) {
        system("cls");
        gotoxy(0, 0);
        printf("1. Enter a word\n");
        gotoxy(0, 1);
        printf("2. Edit a word delete char \n");
        gotoxy(0, 2);
        printf("3. see what you wrote\n");
        printf("Choose what you want to do from 1 to 3: ");

        choice = getch(); // Get the character representing the key

        if (choice == '1') {
            if (numWords < maximumWords) {
                gotoxy(0, 7);
                printf("Write what you want: ");
                scanf(" %[^\n]", words[numWords].text);
                words[numWords].length = strlen(words[numWords].text);
                printf("Word added successfully: %s\n", words[numWords].text); // Print the word immediately
                numWords++;
                getch();
            } else {
                gotoxy(0, 7);
                printf("Maximum number of words reached!\n");
                getch();
            }
        } else if (choice == '2') {
            if (numWords > 0) {
                int wordNum;
                gotoxy(0, 10);
                printf("Enter the word number to edit (1-%d): ", numWords);
                scanf("%d", &wordNum);

                if (wordNum >= 1 && wordNum <= numWords) {
                    currentWord = wordNum - 1;
                    int cursorPos = words[currentWord].length;
                    gotoxy(0, 12);
                    printf("Editing Word: ");
                    printWithCursor(words[currentWord].text, cursorPos, 12, 15);
                    while (1) {
                        character = getch();
                        if (character == 13) { // Enter key
                            break;
                        } else if (character == 27) { // Esc key to exit edit mode
                            break;
                        } else if (character == 8) { // Backspace key
                            if (cursorPos > 0) {
                                cursorPos--;
                                for (int i = cursorPos; i < words[currentWord].length; i++) {
                                    words[currentWord].text[i] = words[currentWord].text[i + 1];
                                }
                                words[currentWord].length--;
                            }
                        } else if (character == 77 && cursorPos < words[currentWord].length) { // Right arrow key
                            cursorPos++;
                        } else if (character == 75 && cursorPos > 0) { // Left arrow key
                            cursorPos--;
                        } else {
                            // Insert other characters
                            if (words[currentWord].length < sizeof(words[currentWord].text) - 1) {
                                for (int i = words[currentWord].length; i > cursorPos; i--) {
                                    words[currentWord].text[i] = words[currentWord].text[i - 1];
                                }
                                words[currentWord].text[cursorPos] = character;
                                cursorPos++;
                                words[currentWord].length++;
                            }
                        }
                        gotoxy(0, 14);
                        printf("Editing Word: ");
                        printWithCursor(words[currentWord].text, cursorPos, 14, 15);
                    }
                    printf("\nWord edited successfully!\n");
                    currentWord = -1; // Reset currentWord
                    getch();
                } else {
                    gotoxy(0, 12);
                    printf("Invalid word number!\n");
                    getch();
                }
            } else {
                gotoxy(0, 10);
                printf("No words to edit!\n");
                getch();
            }
        } else if (choice == '3') {
            gotoxy(0, 10);
            if (numWords > 0) {
                for (int i = 0; i < numWords; i++) {
                    printf("%d. %s\n", i + 1, words[i].text);
                }
            } else {
                printf("No words entered yet.\n");
            }
            getch();
        }
         else {
            gotoxy(0, 10);
            printf("Invalid choice. Please try again!\n");
            getch();
        }
    }

    return 0;
}
