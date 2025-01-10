#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTES 100
#define NOTE_LENGTH 256

typedef struct {
    int day;
    int month;
    int year;
    char note[NOTE_LENGTH];
} Note;

Note notes[MAX_NOTES];
int noteCount = 0;

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

int getDayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int h = day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    h = h % 7;
    return (h + 5) % 7;  // Adjusting to make 0=Sunday, 1=Monday, ..., 6=Saturday
}

void printCalendar(int month, int year) {
    printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    int days = getDaysInMonth(month, year);
    int startDay = getDayOfWeek(1, month, year);  // No need to cast anymore
    for (int i = 0; i < startDay; i++) {
        printf("     ");
    }
    for (int day = 1; day <= days; day++) {
        printf("%5d", day);
        if ((day + startDay) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void addNote() {
    if (noteCount >= MAX_NOTES) {
        printf("Note limit reached. Cannot add more notes.\n");
        return;
    }
    printf("Enter date (dd mm yyyy): ");
    int day, month, year;
    scanf("%d %d %d", &day, &month, &year);
    printf("Enter note: ");
    getchar();  // Consume newline character left by scanf
    fgets(notes[noteCount].note, NOTE_LENGTH, stdin);
    notes[noteCount].day = day;
    notes[noteCount].month = month;
    notes[noteCount].year = year;
    noteCount++;
    printf("Note added successfully.\n");
}

void viewNotes(int day, int month, int year) {
    printf("Notes for %02d-%02d-%04d:\n", day, month, year);
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].day == day && notes[i].month == month && notes[i].year == year) {
            printf("- %s", notes[i].note);
        }
    }
}

int main()
 {
  int choice; 
  while (1) 
  {
   printf("\nCalendar Menu:\n");
    printf("1. Find out the day\n"); 
	printf("2. Print all the days of the month\n"); 
	printf("3. Add note\n"); 
	printf("4. View notes\n"); 
	printf("5. Exit\n");
	 printf("Enter your choice: "); 
	 scanf("%d", &choice);
	  switch (choice)
	   {
	    case 1: 
		{ int day, month, year; 
		printf("Enter date (dd mm yyyy): "); 
		scanf("%d %d %d", &day, &month, &year); 
		printf("The day is: %s\n", getDayOfWeek(day, month, year)); 
		break;
		 }
		  case 2:
		   { 
		   int month, year;
		    printf("Enter month and year (mm yyyy): "); 
			scanf("%d %d", &month, &year);
			 printCalendar(month, year); 
			 break;
			  } 
			  case 3: 
			  addNote();
			   break;
			    case 4:
				 { 
				 int day, month, year;
				  printf("Enter date (dd mm yyyy): "); 
				  scanf("%d %d %d", &day, &month, &year); 
				  viewNotes(day, month, year); 
				  break;
				   } 
				   case 5:
				    exit(0); 
					default: 
					printf("Invalid choice. Please try again.\n"); 
					} 
				}
			}
