#include <bits/stdc++.h>
using namespace std;

string token;
fstream tokenList;

struct SymbolTable
{
	int id, numargs, size, lineno;
	char lexname[50], type[10], scope[10], rettype[10];
	char **arglist;
};

void tokenizer()
{
	char lastKeyword[10];
	SymbolTable st[100];
	for(int i = 0; i < 100; i++)
		st[i].id = -1;
	int line = 1, key_flag = 0, lid = 0;
	char c;
	char keywords[][10] = {{"char"}, {"int"}, {"if"}, {"else"}, {"while"}, {"include"},{"main"},{"for"}};
	FILE *fo = fopen("q.c", "r");
	FILE *fw = fopen("token.txt", "w");		
	while((c = getc(fo)) != EOF)
	{
		if(c == '\n')
		{
			line++;
		}
		else if(isalpha(c))
		{
			char s[100];
			int i = 0;
			do
			{
				s[i++] = c;
				c = getc(fo);
			}
			while(isalnum(c));
			s[i] = '\0';
			fseek(fo, -1, SEEK_CUR);
			key_flag = 0;
			for(i = 0; i < 8; i++)
			{
				if(!strcmp(s, keywords[i]))
				{
					key_flag = 1;
					putc('<', fw);
					fputs(s, fw);
					putc('>', fw);putc('\n', fw);
					strcpy(lastKeyword, s);
				}
			}
			if(!key_flag)
			{
				int isFuncFlag = 0, isArrFlag = 0;
				char sta[10];
				if(c == '[')
				{	
					fseek(fo, 1, SEEK_CUR);
					i = 0;
					c = getc(fo);
					do
					{
						sta[i++] = c;
						c = getc(fo);		
					}
					while(isdigit(c));
						sta[i] = '\0';
					fseek(fo, -strlen(sta)-2, SEEK_CUR);
					isArrFlag = 1;
				}
				else if(c == '(')
					isFuncFlag = 1;
				int no = 7;
				for(i = 0; i < strlen(s); i++)
					no = no*13 + s[i];
				no %= 100;
				if(st[no].id == -1)
				{
					lid++;
					st[no].id = lid;
					strcpy(st[no].lexname, s);
					if(!isFuncFlag)
					{
						strcpy(st[no].type, lastKeyword);
						strcpy(st[no].rettype, "null");
					}
					else
					{
						strcpy(st[no].type, "fn");
						strcpy(st[no].rettype, lastKeyword);
					}
					st[no].size = 0;
					if(isArrFlag)
						st[no].size = atoi(sta);
					int scope_flag = 0;
					for(int check = 0; check < 100; check++)
						if(!strcmp(st[check].lexname, "main"))
						{
							strcpy(st[no].scope, "local");
							scope_flag = 1;
						}
					if(scope_flag == 0)
						strcpy(st[no].scope, "global");
					st[no].numargs = 0;
					st[no].lineno = line;
					st[no].arglist = new char *[10];
					
				}
				putc('<', fw);
				fputs("id", fw);
				putc('>', fw);putc('\n', fw);
			}
		}
		else if(isdigit(c))
		{
			char s[100];
			int i = 0;
			do
			{
				s[i++] = c;
				c = getc(fo);
			}
			while(isdigit(c));
				s[i] = '\0';
			putc('<', fw);
			fputs("num", fw);
			putc('>', fw);putc('\n', fw);
			fseek(fo, -1, SEEK_CUR);
		}
		else if(c != ' ' && c != '\t')
		{	
			if(c == '\'' || c == '\"')
			{	
				c = getc(fo);				
				putc('<', fw);
				while(c != '\'' && c != '\"')
				{
					putc(c, fw);
					c = getc(fo);
				}
				putc('>', fw);putc('\n', fw);											
			}
			else if(c == '+')
			{
				c = getc(fo);
				if(c == '+')
				{
					putc('<', fw);
					fputs("inc", fw);
					putc('>', fw);putc('\n', fw);
				}
				else
				{
					fseek(fo, -2, SEEK_CUR);
					c = getc(fo);
					putc('<', fw);
					putc(c, fw);
					putc('>', fw);putc('\n', fw);
				}
			}
			else
			{
				putc('<', fw);
				putc(c, fw);
				putc('>', fw);putc('\n', fw);
			}
		}
	}
	fclose(fw);
	fclose(fo);
	tokenList.open("token.txt");
}

string getToken(string function)
{
	if(getline(tokenList,token))
	{
		const char* start=token.c_str();
		const char* end=start+token.size();
		token=string(start+1,end-1);
		cout<<function<<" : "<<token<<"\n";
		return token;
	}
	else
		printf("Error\n");
}