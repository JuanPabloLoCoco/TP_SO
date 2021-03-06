#include <shell.h>
#include <stdlib.h>
#include <stdint.h>
#include <plotter.h>
#include <date.h>
#include <echo.h>
#include <time.h>
#include <clear.h>
#include <help.h>
#include <color.h>
#include <tpTwoTests.h>

uint64_t _int80(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

char command [COMMAND_MAX_LENGTH];
char args[COMMANDS_MAX_ARGS+1];
int functionArgs[MAX_QUADRATIC_INTS];
int width = 0;
int height = 0;

void shell()
{
	setUpShell();
	int command;
	printPrompt();
	while(command = getCommands())
	{
		if(command >= COMMANDS_QUANTITY)
		{
			printf("command not found\n");
		}
		else
		{
			switch(command)
			{
				case TIME:
					time();
					break;
				case DATE:
					date();
					break;
				case CLEAR:
					clear();
					setUpShell();
					break;
				case HELP:
					help();
					break;
				case ECHO:
					echo(args);
					break;
				case LINEAR:
					functionScreen(0,functionArgs[0],functionArgs[1]);
					break;
				case QUADRATIC:
					functionScreen(functionArgs[0],functionArgs[1],functionArgs[2]);
					break;
				case COLOR:
					color(functionArgs[0],functionArgs[1],functionArgs[2]);
					break;
				case TEST:
					test(functionArgs[0]);
					break;
				case TP_TWO_TEST:
					testsTpTwo(functionArgs[0]);
					break;
			}
		}
		printPrompt();
	}
}

/*set up the pointer to the las line*/
void setUpShell()
{
	width = (int)_int80(11, 0, 0, 0, 0, 0);
	height = (int)_int80(11, 1, 0, 0, 0, 0);
	_int80(12, 0, height - 1 * CHAR_HEIGHT, 0, 0, 0);
}

/*prints the prompt*/
void printPrompt()
{
	printf("$>");
}

/*read the input and returns a value corresponding to the
** command read.
*/
int getCommands()
{
	int c;
	int i = 0;
	while((c = getchar()) != '\n' && (i == 0 || c != ' '))
	{
		if(c != '\b')
			putchar(c);
		if(i != 0 || c != ' ')
		{
		 	if(c == '\b')
			{
		 		if(i > 0)
				{
		 			i--;
				}
		 	}
		 	else
			{
		 		command[i] = c;
				i++;
			}
		}
	}
	putchar(c);
	if(c == ' ')
	{
		if(readArgs(args) == 1)
		{
			return getCommands();
		}
	}
	else
	{
		args[0] = 0;
	}
	if(i < COMMAND_MAX_LENGTH)
	{
		command[i] = 0;
		int argsLength = strlen(args);
		if(strcmp(command, "time") && argsLength == 0)
		{
			return TIME;
		}
		else if (strcmp(command, "date") && argsLength == 0)
		{
			return DATE;
		}
		else if (strcmp(command, "clear") && argsLength == 0)
		{
			return CLEAR;
		}
		else if (strcmp(command, "help") && argsLength == 0)
		{
			return HELP;
		}
		else if(strcmp(command, "echo"))
		{
			return ECHO;
		}
		else if(strcmp(command, "linear"))
		{
			if(getInts(MAX_LINEAR_INTS) != MAX_LINEAR_INTS)
			{
			 	return COMMANDS_QUANTITY;
			}
			return LINEAR;
		}
		else if(strcmp(command, "quadratic"))
		{
			if(getInts(MAX_QUADRATIC_INTS) != MAX_QUADRATIC_INTS)
			{
				return COMMANDS_QUANTITY;
			}
			return QUADRATIC;
		}
		else if(strcmp(command, "color"))
		{
			if(getInts(MAX_COLOR_INTS) != MAX_COLOR_INTS || !valid(0,255,MAX_COLOR_INTS))
			{
				return COMMANDS_QUANTITY;
			}
			return COLOR;
		}
		else if(strcmp(command, "test"))
		{
			if(getInts(ID_INTS) != ID_INTS || !valid(0,3,ID_INTS))
			{
				return COMMANDS_QUANTITY;
			}
			return TEST;
		}
		else if(strcmp(command, "tpTwoTests"))
		{
			return TP_TWO_TEST;
		}
	}
	return COMMANDS_QUANTITY;
}

/*reads from the input until enter and returns 0 if could be read
** 1 if there were more backspaces than typed chars
*/
int readArgs(char * args)
{
	int c;
	int i = 0;
	while((c = getchar())!='\n')
	{
		if(c != '\b')
		{
			putchar(c);
			if(i < COMMANDS_MAX_ARGS)
			{
		 		args[i] = c;
				i++;
			}
		}
		else if(i > 0 && i < COMMANDS_MAX_ARGS)
		{
		 		i--;
		}
		else
		{
			return 1;
		}
	}
	putchar(c);
	args[i] = 0;
	return 0;
}

/*stores the numbers of the argument read in an integer vector
** and returns how many ints were given
*/
int getInts(int totalArgs)
{
	int i;
	int j = 0;
	int sign = 0;
	for(i = 0; args[i]; i++)
	{
		if(args[i] != ' ' && !isNum(args[i]))
		{
			if(args[i] == '-')
			{
				sign = 1;
			}
			else
			{
				return MAX_QUADRATIC_INTS + 1;
			}
		}
		else if(isNum(args[i]))
		{
			if(j < totalArgs)
			{
				functionArgs[j] = (sign == 1)? -getNumber(args, &i) : getNumber(args, &i);
				j++;
			}
			else
			{
				return MAX_QUADRATIC_INTS + 1;
			}
		}
	}
	return j;
}

/*turns the string starting in args at the position pos
** into its corresponding integer value
*/
int getNumber(char* args, int* pos)
{
	int num = 0;
	while(isNum(args[*pos]))
	{
		num = num * 10 + (args[*pos] - 48);
		(*pos)++;
	}
	(*pos)--;
	return num;
}

/*set the screen to plot a function and then plots it
** when q is pressed clears the screen and returns to
** shell screen mode.
*/
void functionScreen(int a, int b, int c)
{
	clear();
	printf("Presione q para salir.\n");
	drawFunction(a,b,c);
	int l;
	while((l = getchar()) != 'q');
	clear();
	setUpShell();
}

/*returns 1 if all of the integer numbers read in the
** argument are between from and to, returns 0 if not
*/
int valid(int from,int to,int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(functionArgs[i] < from || functionArgs[i] > to)
			return 0;
	}
	return 1;
}

// void prodcons() {
// 	_int80(18,200);//sleep
//
// 	_int80(30, "prodConsRead", readMutex); //createMutex
// 	_int80(30, "prodConsWrite", writeMutex); //createMutex
// 	_int80(30, "prodConsModify", modifyQueueMutex); //createMutex
//
// 	_int80(27, &readMutex);//initSemaphore
// 	_int80(27, &writeMutex);//initSemaphore
// 	_int80(9);
//
// 	producer();
// 	consumer();
// }
//
// void producer(){
//
//     int i = 0;
//
//     _int80(32, writeMutex, writeMutex);//lockMutex
//     int maxProduced = 50;
//     while (i < maxProduced){
//         while (queueSize >= MAX_PRODUCT_QUEUE_SIZE){
//             _int80(26, writeMutex);//waitSemaphore
//         }
//
//         //addToProductQueue
//         _int80(32, modifyQueueMutex, modifyQueueMutex);//lockMutex
//         if(queueSize == MAX_PRODUCT_QUEUE_SIZE){
//         	printf("No puede agregar");
//         	return;
//         }
//         int index = (queueIndex + queueSize) % MAX_PRODUCT_QUEUE_SIZE;
//         queue[index] = i;
// //        printf("prod %d\n",i);
//         _int80(25, &readMutex);
//     }
//     _int80(25, writeMutex, writeMutex);
// //    printf("liberado: %d, index: %d\n",queueSize,queueIndex);
// }
//
// void consumer(){
//
//     _int80(32, readMutex, readMutex);//lockMutex
//     while (1){
//         while (queueSize <= 0){
//             _int80(26, readMutex);//waitSemaphore
//         }
//
//         //removeFromProductQueue();
//         _int80(32, modifyQueueMutex, modifyQueueMutex);//lockMutex
//         if(queueSize == 0){
//         	printf("No puede quitar");
//         	return;
//         }
//         queueIndex = (queueIndex + 1) % MAX_PRODUCT_QUEUE_SIZE;
//         queueSize--;
// //        printf("prod %d\n",i);
//         _int80(33, modifyQueueMutex);//unlock
//         _int80(25, writeMutex, writeMutex);//signalSemaphore
//
//     }
//     _int80(25, readMutex, readMutex);//signalSemaphore
// 	}
