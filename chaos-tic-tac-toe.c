#include<stdio.h>

#define RANGE(min, x, max) (!((min) <= (x) && (x) >= (max)))

#define SIZE ((size_t)4)
#define X 'X'
#define O 'O'
#define EMPTY '.'

typedef char Map[SIZE][SIZE];

void  map_print(Map map);
_Bool map_read (Map map);
_Bool map_eval (Map map);

int main(void)
{
	Map map;
	_Bool turn = 0;
	
	for(size_t i = 0; i < SIZE; i += 1)
		memset(map[i], EMPTY, SIZE);
	
	//why not (just a lazy fix if you wonder);
	printf("Seccion name: ");
	getchar();

	while(1)
	{
		printf("\n[[ Player %d ]]\n", turn + 1);
		map_print(map);
		if(!map_read(map))
		{
			printf("\n[[ Try again! ]]\n");
			continue;
		}

		if(!map_eval(map))
		{
			printf("\n[[ Player %d win! ]]\n", turn + 1);
			break;
		}

		turn = !turn;
	}

	return 0;
}

void map_print(Map map)
{
	for(size_t i = 0; i < SIZE; i += 1)
	{
		for(size_t j = 0; j < SIZE; j += 1)
		{
			putchar(map[i][j]);
			putchar(' ');
		}
		putchar('\n');
	}
}

_Bool map_read(Map map)
{
	while ((getchar()) != '\n');

	size_t pos[2];
	signed char c;
	
	printf("Row: ");
	scanf(" %zu", &(pos[0])); pos[0] -= 1; if(!RANGE(0, pos[0], 4)) return 0;

	printf("Column: ");
	scanf(" %zu", &(pos[1])); pos[1] -= 1; if(!RANGE(0, pos[1], 4)) return 0;
	
	while ((getchar()) != '\n');
	
	printf("Symbol (%c, %c): ", X, O);
	if((c = getchar()) == X || c == O)
		if(map[pos[0]][pos[1]] == EMPTY)
			map[pos[0]][pos[1]] = c;
		else
			return 0;

	return 1;
}

_Bool map_eval(Map map)
{
	size_t correct = 0;

	for(size_t i = 0; i < SIZE; i += 1)
	{
		correct = 0;
		for(size_t j = 0; j < SIZE; j += 1)
			if(map[i][0] != EMPTY && map[i][j] == map[i][0]) correct += 1;
		if(correct == SIZE) return 0;

		correct = 0;
		for(size_t j = 0; j < SIZE; j += 1)
			if(map[0][i] != EMPTY && map[j][i] == map[0][i]) correct += 1;
		if(correct == SIZE) return 0;
		
		correct = 0;
		for(size_t j = 0; j < SIZE; j += 1)
			if(map[0][0] != EMPTY && map[j][j] == map[0][0]) correct += 1;
		if(correct == SIZE) return 0;
		
		correct = 0;
		for(size_t j = 0; j < SIZE; j += 1)
			if(map[0][SIZE-1] != EMPTY && map[j][SIZE-(j+1)] == map[0][SIZE-1]) correct += 1;
		if(correct == SIZE) return 0;
	}	

	return 1;
}
