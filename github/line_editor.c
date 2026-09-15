#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char *lines[MAX_LINES];
int lineCount = 0;

/* Function to insert a line */
void insertLine(int position, char text[])
{
    if (lineCount >= MAX_LINES)
    {
        printf("Error: Document is full.\n");
        return;
    }

    if (position < 1 || position > lineCount + 1)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Shift lines downward */
    for (int i = lineCount; i >= position; i--)
    {
        lines[i] = lines[i - 1];
    }

    /* Allocate memory for new line */
    lines[position - 1] = malloc(strlen(text) + 1);

    if (lines[position - 1] == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    strcpy(lines[position - 1], text);

    lineCount++;

    printf("Line inserted successfully.\n");
}

/* Function to delete a line */
void deleteLine(int position)
{
    if (lineCount == 0)
    {
        printf("Error: Document is empty.\n");
        return;
    }

    if (position < 1 || position > lineCount)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Free memory of deleted line */
    free(lines[position - 1]);

    /* Shift remaining lines upward */
    for (int i = position - 1; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lineCount--;

    printf("Line deleted successfully.\n");
}

/* Function to display the document */
void displayDocument()
{
    if (lineCount == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}

/* Function to free all memory */
void freeDocument()
{
    for (int i = 0; i < lineCount; i++)
    {
        free(lines[i]);
    }
}

/* Main function */
int main()
{
    int choice;
    int position;
    char text[MAX_LENGTH];

    printf("=================================\n");
    printf("       SIMPLE LINE EDITOR\n");
    printf("=================================\n");

    while (1)
    {
        printf("\nCommands:\n");
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Display document\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // Remove newline

        switch (choice)
        {
            case 1:
                printf("Enter line number (1-%d): ", lineCount + 1);
                scanf("%d", &position);
                getchar();

                printf("Enter text: ");
                fgets(text, MAX_LENGTH, stdin);

                /* Remove newline from fgets */
                text[strcspn(text, "\n")] = '\0';

                insertLine(position, text);
                break;

            case 2:
                printf("Enter line number to delete: ");
                scanf("%d", &position);
                getchar();

                deleteLine(position);
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                freeDocument();
                printf("Exiting editor...\n");
                return 0;

            default:
                printf("Error: Invalid choice.\n");
        }
    }

    return 0;
}