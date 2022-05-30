#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
ins(char *name, char *mode)
{
	FILE *file = fopen(name, mode);
	char buf[2048];
	fgets(buf, 2048, stdin);
	while(strcmp(buf, ".\n") != 0)
	{
		fputs(buf, file);
		fgets(buf, 2048, stdin);
	}
	fclose(file);
}

void
addr(char c, char* buf, char* name)
{
	FILE *file;
	FILE *tmp;
	char tmpnm[512];
	tmpnam(tmpnm);
	char buf2[2048];
	int end;
	char str[2048] = {c, '\0'};
	strlcat(str, buf, 2048);
	int line = atoi(str);
	buf = strpbrk(str, "acdp,");
	if(!buf) {
		puts("?");
		return;
	}
	file = fopen(name, "r");
	switch(*buf)
	{
		case 'a':
			tmp = fopen(tmpnm, "a");
			for(int i = 1; i <= line; i ++)
			{
				if(!fgets(buf, 2048, file))
				{
					puts("?");
					fclose(tmp);
					unlink(tmpnm);
					fclose(file);
					return;
				}
				fputs(buf, tmp);
			}
			fclose(tmp);
			ins(tmpnm, "a");
			tmp = fopen(tmpnm, "a");
			while(fgets(buf, 2048, file))
				fputs(buf, tmp);
			fclose(tmp);
			rename(tmpnm, name);
			break;
		case 'c':
			tmp = fopen(tmpnm, "a");
			for(int i = 1; i < line; i ++)
			{
				if(!fgets(buf, 2048, file))
				{
					puts("?");
					fclose(tmp);
					fclose(file);
					unlink(tmpnm);
					return;
				}
				fputs(buf, tmp);
			}
			fclose(tmp);
			ins(tmpnm, "a");
			tmp = fopen(tmpnm, "a");
			fgets(buf, 2048, file);
			while(fgets(buf, 2048, file))
				fputs(buf, tmp);
			fclose(tmp);
			rename(tmpnm, name);
			break;
		case 'd':
			tmp = fopen(tmpnm, "a");
			for(int i = 1; i < line; i ++)
			{
				if(!fgets(buf, 2048, file))
				{
					puts("?");
					fclose(tmp);
					fclose(file);
					unlink(tmpnm);
					return;
				}
				fputs(buf, tmp);
			}
			fgets(buf, 2048, file);
			while(fgets(buf, 2048, file))
				fputs(buf, tmp);
			fclose(tmp);
			rename(tmpnm, name);
			break;
		case 'p':
			for(int i = 1; i <= line; i ++)
				if(!fgets(buf, 2048, file))
				{
					puts("?");
					fclose(file);
					return;
				}
			
			printf("%s", buf);
			break;
		case ',':
			memmove(str,  buf + 1, strlen(str) - (buf - str));
			end = atoi(str);
			buf = strpbrk(str, "cdp");
			if(!buf)
			{
				puts("?");
				fclose(file);
				return;
			}
			switch(*buf)
			{
				case 'c':
					tmp = fopen(tmpnm, "a");
					for(int i = 1; i < line; i ++)
					{
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(tmp);
							fclose(file);
							unlink(tmpnm);
							return;
						}
						fputs(buf, tmp);
					}
					fclose(tmp);
					for(; line <= end; line ++)
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(file);
							unlink(tmpnm);
							return;
						}
					ins(tmpnm, "a");
					tmp = fopen(tmpnm, "a");
					while(fgets(buf, 2048, file))
						fputs(buf, tmp);
					fclose(tmp);
					rename(tmpnm, name);
					break;
				case 'd':
					tmp = fopen(tmpnm, "a");
					for(int i = 1; i < line; i ++)
					{
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(tmp);
							fclose(file);
							unlink(tmpnm);
							return;
						}
						fputs(buf, tmp);
					}
					for(; line <= end; line ++)
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(file);
							fclose(tmp);
							unlink(tmpnm);
							return;
						}
					while(fgets(buf, 2048, file))
						fputs(buf, tmp);
					fclose(tmp);
					rename(tmpnm, name);
					break;
				case 'p':
					for(int i = 1; i < line; i ++)
					{
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(file);
							return;
						}
					}
					for(; line <= end; line ++)
					{
						if(!fgets(buf, 2048, file))
						{
							puts("?");
							fclose(file);
							return;
						}
						printf("%s", buf);
					}
					break;
			}
			break;

	}
	fclose(file);
}

int
main(int argc, char *argv[])
{
	char filename[2048] = "";
	char tmpnm[512];
	FILE *file;
	FILE *tmp;
	char buf[2048];
	tmpnam(tmpnm);
	
	if(argc > 1)
	{
		strlcpy(filename, argv[1], 2048);
		if(access(filename, F_OK) == 0)
		{
			file = fopen(filename, "r");
			tmp = fopen(tmpnm, "a");
			while(fgets(buf, 2048, file))
				fputs(buf, tmp);
			fclose(file);
			fclose(tmp);
		}
		else
		{
			tmp = fopen(tmpnm, "a");
			fprintf(tmp, "");
			fclose(tmp);
		}
	}
	else
	{
		tmp = fopen(tmpnm, "a");
		fprintf(tmp, "");
		fclose(tmp);
	}

	while(1)
	{
		printf("> ");
		char c = getchar();
		fgets(buf, 2048, stdin);
		switch(c)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				addr(c, buf, tmpnm);
				break;
			case 'a':
				ins(tmpnm, "a");
				break;
			case 'c':
				ins(tmpnm, "w");
				break;
			case 'd':
				tmp = fopen(tmpnm, "w");
				fprintf(tmp, "\n");
				fclose(tmp);
				break;
			case 'p':
				tmp = fopen(tmpnm, "r");
				while(fgets(buf, 2048, tmp))
					printf("%s", buf);
				fclose(tmp);
				break;
			case 'q':
				unlink(tmpnm);
				return(0);
				break;
			case 'w':
				if(strlen(buf) > 1)
				{
					memmove(buf, buf + 1, strlen(buf));
					buf[strlen(buf) - 1] = '\0';
				}

				if(argc == 1 && !strlen(filename))
				{
					if(strlen(buf) > 1)
						strlcpy(filename, buf, 2048);
					else
					{
						puts("?");
						break;
					}
				}

				if(strlen(buf) > 1)
				{
					if(access(filename, F_OK) < 0)
						file = fopen(filename, "a");
					else
						file = fopen(filename, "w");
				}
				else
				{
					if(access(filename, F_OK) < 0)
						file = fopen(filename, "a");
					else
						file = fopen(filename, "w");
				}

				tmp = fopen(tmpnm, "r");
				while(fgets(buf, 2048, tmp))
					fputs(buf, file);
				fclose(file);
				fclose(tmp);
				break;
			default:
				printf("?\n");
				break;
		}
	}
}
