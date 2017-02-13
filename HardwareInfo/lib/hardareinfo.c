#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "hardwareinfo.h"

/** detecting whether base is starts with str
 */
bool startsWith (char* base, char* str)
{
    return (strstr(base, str) - base) == 0;
}

/** detecting whether base is ends with str
 */
bool endsWith (char* base, char* str)
{
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

/**
* Check if a file exist using stat() function
* return 1 if the file exist otherwise return 0
*/
int fileExist(const char* filename){
	struct stat buffer;
	int exist = stat(filename,&buffer);
	if(exist == 0)
	    return 1;
	else // -1
	    return 0;
}

/** reading file and return value from it
 * This function allocates memory for the returned string.
 * The caller must call free() to prevent memory leaks.
 * */
char* ReadProcEntry(char *filename)
{
	FILE *proc_file = fopen(filename,"r");
	char proc_contents[20];
	char *real_proc_contents = NULL;
	char c;
	int i = 0;

	if(proc_file)
	{
		while ((c = fgetc(proc_file)) != EOF && i < sizeof(proc_contents) - 2)
		{
			if (c == '\n')
			{
				i--;
				break;
			}
			proc_contents[i] = c;
			i++;
		}
		proc_contents[i+1] = '\0';
		real_proc_contents = malloc(strlen(proc_contents) + 1);
		if (real_proc_contents)
			strcpy(real_proc_contents, proc_contents);

		fclose(proc_file);
	}
	else
		puts("[HARDWAREINFO] Can not open this proc entry!\n");

	return real_proc_contents;
}

char *_getVideoResolutions()
{
	char *videoresolutions = NULL;
	if(fileExist("/proc/stb/video/videomode_choices"))
	{
		videoresolutions = ReadProcEntry("/proc/stb/video/videomode_choices");
		return videoresolutions;
	}
	free(videoresolutions);
	return strdup("unavailable");
}

