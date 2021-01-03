#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char buff[80];
	fprintf(stdout, "<HTML>");
 	fprintf(stdout, "<BODY bgcolor=#FFDD00>");
 	fprintf(stdout, "<CENTER><TABLE>");
 	
	while (fgets(buff,80,stdin))
	{ 
		char *p = strchr(buff, '\n');
		if (p) 
			*p='\0';
		fprintf(stdout, "<TR>");
		fprintf(stdout, "<TD>");
		fprintf(stdout, "<H1>");
		fprintf(stdout, "%s", buff);
		fprintf(stdout, "</H1>");
		fprintf(stdout, "</TD>");
		fprintf(stdout, "</TR>");
	}

	fprintf(stdout, "</TABLE></CENTER");
	fprintf(stdout, "</BODY>");
	fprintf(stdout, "</HTML>");
	
	return 0;
} 
