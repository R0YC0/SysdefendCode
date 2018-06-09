#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
void bufStuff(char letter);
int words_recognition(char buffer[], unsigned buffLen);

void bufStuff(char letter)
{
	int i = 0;
	static char buffer[24] = { 0 };
	//memset(buffer, '\0', sizeof(buffer));
	//strncpy(buffer,strncat(buffer++,letter,1),sizeof(buffer)/sizeof(char));
	memcpy(buffer, (buffer + 1), sizeof(buffer) / sizeof(char));
	buffer[22] = letter;


	if (words_recognition(buffer, sizeof(buffer) / sizeof(char)) == 1)
		printf("word detected\n");


}

int words_recognition(char* buffer, unsigned buffLen)
{
	int i = 0, j = 0;
	char command[] = "cat";
	for (i = 0; i < buffLen; i++)
	{
		if (buffer[i] == command[j])
		{
			if (j == strlen(command))
				return 1;  //evil command
			j++;
		}
		else if (j != 0)   //try search the word again, from the start
			j = 0;
	}

	return 0;

}

int main()
{
	int i = 0;
	for (i = 0; i<23; i++)
	{
		bufStuff('b');
	}
	bufStuff('c');
	bufStuff('a');
	bufStuff('t');
	bufStuff('f');
	bufStuff('q');
	getchar();
	return 0;
}
