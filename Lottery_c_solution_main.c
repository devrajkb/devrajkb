#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

/* INPUT example
Archana, 1,35,5,7,9,11,13
Dev, 13,5,42,33,65,16,49


*/


#define MAX_NUMBER_PLAYERS   10
#define MAX_NAME_LENGTH      50
#define LOTTERY_NUMBERS      7
#define ADDITIONAL_NUMBERS   4
#define MAX_NUMBER           100
#define MAX_ENTRY_LINE       250


typedef struct lottery {
	char name[MAX_NAME_LENGTH];
	unsigned int numbers[LOTTERY_NUMBERS];
	unsigned int right;
	unsigned int additional_numbers;
} lottery_t;

lottery_t g_lottery_lines[MAX_NUMBER_PLAYERS];
unsigned int g_number_lottery_players = 0;

unsigned int g_corret_line[LOTTERY_NUMBERS];
unsigned int g_corret_line_count = 0;
unsigned int g_additional_numbers[ADDITIONAL_NUMBERS];
unsigned int g_additional_numbers_count = 0;


void print_lottery_lines()
{
	for (unsigned int i = 0; i < g_number_lottery_players; i++) {
		printf("%s, %u, %u, %u, %u, %u, %u, %u \n", 
			g_lottery_lines[i].name,
			g_lottery_lines[i].numbers[0],
			g_lottery_lines[i].numbers[1],
			g_lottery_lines[i].numbers[2],
			g_lottery_lines[i].numbers[3],
			g_lottery_lines[i].numbers[4],
			g_lottery_lines[i].numbers[5],
			g_lottery_lines[i].numbers[6]);
	}

}

void sort_ascending_order(unsigned int* elements, unsigned int number_of_elements)
{
	unsigned int swap, i,j;

	for (i = 0; i < number_of_elements - 1; i++)
	{
		for (j = 0; j < number_of_elements - i - 1; j++)
		{
			if (elements[j] > elements[j + 1]) /* For decreasing order use '<' instead of '>' */
			{
				swap = elements[j];
				elements[j] = elements[j + 1];
				elements[j + 1] = swap;
			}
		}
	}
}

void sort_lottery_lines()
{
	for (unsigned int i = 0; i < g_number_lottery_players; i++) {
		sort_ascending_order(g_lottery_lines[i].numbers, LOTTERY_NUMBERS);
	}
}
void convert_input_to_workable_format(char* lottery_line, unsigned int index)
{
	unsigned int counter = 0;
	char* pch = strtok(lottery_line, " ,.-");
	while (pch != NULL)
	{
		//printf("%s\n", pch);
		if (counter == 0) {
			strcpy(g_lottery_lines[index].name, pch);
		}
		else {
			g_lottery_lines[index].numbers[counter - 1] = atoi(pch);
		}
		counter++;
		pch = strtok(NULL, " ,.-");
	}
}

void read_lottery_lines(void)
{
	char lottery_line[MAX_ENTRY_LINE];
	printf("Enter lottery lines, enter empty line to END entering : ");

	do {
		gets(lottery_line);
		if (strlen(lottery_line)) {
			//puts(lottery_line);
			convert_input_to_workable_format(lottery_line, g_number_lottery_players);
			g_number_lottery_players++;
		}
	} while (strlen(lottery_line));
	//printf("Reading done \n");
	//print_lottery_lines();
}

bool number_exists(unsigned int* elements, unsigned int number_of_elements, unsigned int number)
{
	for (unsigned int i = 0; i < number_of_elements; i++) {
		if (elements[i] == number) {
			return true;
		}
	}

	return false;
}

unsigned int get_random_number(unsigned int lower, unsigned int upper) 
{
		unsigned int num = (rand() %
			(upper - lower + 1)) + lower;
		//printf("%d ", num);
		return num;
}
void correct_line_generate(void)
{
	//unsigned int i;
	unsigned int lower = 1;
	unsigned int upper = MAX_NUMBER;
	srand(time(0));

	do {
		unsigned int number = get_random_number(lower, upper);
		if (!number_exists(g_corret_line, g_corret_line_count, number) && 
			!number_exists(g_additional_numbers, g_additional_numbers_count, number)) {
			g_corret_line[g_corret_line_count++] = number;
		}
	} while (g_corret_line_count < LOTTERY_NUMBERS);

	do {
		unsigned int number = get_random_number(lower, upper);
		if (!number_exists(g_corret_line, g_corret_line_count, number) &&
			!number_exists(g_additional_numbers, g_additional_numbers_count, number)) {
			g_additional_numbers[g_additional_numbers_count++] = number;
		}
	} while (g_additional_numbers_count < ADDITIONAL_NUMBERS);

}

void print_correct_additional_line()
{
	printf("Correct row %u, %u, %u, %u, %u, %u, %u \n%u, %u, %u, %u\n",
		g_corret_line[0],
		g_corret_line[1],
		g_corret_line[2],
		g_corret_line[3],
		g_corret_line[4],
		g_corret_line[5],
		g_corret_line[6],
		g_additional_numbers[0],
		g_additional_numbers[1],
		g_additional_numbers[2],
		g_additional_numbers[3]);

}
void sort_data(void)
{
	sort_ascending_order(g_corret_line, g_corret_line_count);
	sort_ascending_order(g_additional_numbers, g_additional_numbers_count);
	sort_lottery_lines();

	//printf("Sorted lottery lines \n");
	//print_lottery_lines();
	//print_correct_additional_line();

}
void correct_data(void)
{
	for (unsigned int player = 0; player < g_number_lottery_players; player++) {
		unsigned int right = 0;
		unsigned int additional_number = 0;
		for (unsigned int i = 0; i < LOTTERY_NUMBERS; i++) {
			if (number_exists(g_lottery_lines[player].numbers, LOTTERY_NUMBERS, g_corret_line[i])) {
				right++;
			}
		}
		for (unsigned int i = 0; i < ADDITIONAL_NUMBERS; i++) {
			if (number_exists(g_lottery_lines[player].numbers, LOTTERY_NUMBERS, g_additional_numbers[i])) {
				additional_number++;
			}
		}
		g_lottery_lines[player].right = right;
		g_lottery_lines[player].additional_numbers = additional_number;
	}
}
void print_data(void)
{
	print_correct_additional_line();
	for (unsigned int i = 0; i < g_number_lottery_players; i++) {
		unsigned int right = 0;
		unsigned int additional_number = 0;
		printf("%s, %u, %u, %u, %u, %u, %u, %u",
			g_lottery_lines[i].name,
			g_lottery_lines[i].numbers[0],
			g_lottery_lines[i].numbers[1],
			g_lottery_lines[i].numbers[2],
			g_lottery_lines[i].numbers[3],
			g_lottery_lines[i].numbers[4],
			g_lottery_lines[i].numbers[5],
			g_lottery_lines[i].numbers[6]);
		if (g_lottery_lines[i].right) {
			printf(" %u right,", g_lottery_lines[i].right);
		}
		else {
			printf(" zero right,");
		}

		if (g_lottery_lines[i].additional_numbers) {
			printf(" %u\nadditional number \n,", g_lottery_lines[i].additional_numbers);
		}
		else {
			printf(" zero\nadditional number \n,");
		}
	}

}
void store_data(void){
}

int main(void)
{
    read_lottery_lines();
	correct_line_generate();
	sort_data();
	correct_data();
	print_data();
	store_data();

}