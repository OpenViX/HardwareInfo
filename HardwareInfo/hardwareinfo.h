#ifndef __HARDWAREINFO_H__
#define __HARDWAREINFO_H__

bool startsWith (char* base, char* str);
bool endsWith (char* base, char* str);
int fileExist(const char* filename);

/* The caller is always responsible for calling free() on the returned
 * string from all the functions that follow. */

char *ReadProcEntry(char *filename);

char *_getVideoResolutions();

#endif
