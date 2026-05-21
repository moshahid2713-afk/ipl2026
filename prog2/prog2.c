#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure Definition
typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function to store records in ASCII format
void storeRecords(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    Student s;

    for (int i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        // Store in ASCII format
        fprintf(fp, "%d %s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

// Function to create array of seek positions
int createSeekPositions(const char *filename, long positions[]) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return 0;
    }

    int count = 0;
    char ch;

    // First record starts at position 0
    positions[count++] = ftell(fp);

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            positions[count++] = ftell(fp);
        }
    }

    fclose(fp);

    return count - 1; // Last position after EOF not needed
}

// Function to display record from given position
void displayRecord(const char *filename, long pos) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    Student s;

    fseek(fp, pos, SEEK_SET);

    fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks);

    printf("\nRecord Found:\n");
    printf("ID    : %d\n", s.id);
    printf("Name  : %s\n", s.name);
    printf("Marks : %.2f\n", s.marks);

    fclose(fp);
}

int main() {
    const char *filename = "students.txt";

    int n;

    long positions[MAX];

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Store records
    storeRecords(filename, n);

    // Create seek positions
    int total = createSeekPositions(filename, positions);

    printf("\nSeek Positions:\n");
    for (int i = 0; i < total; i++) {
        printf("Record %d starts at position %ld\n", i + 1, positions[i]);
    }

    int rec;

    printf("\nEnter record number to display: ");
    scanf("%d", &rec);

    if (rec >= 1 && rec <= total) {
        displayRecord(filename, positions[rec - 1]);
    } else {
        printf("Invalid record number!\n");
    }

    return 0;
}
