#include <bits/stdc++.h>
#include "lexicalanalyzer.cpp"

void Program();
void declaration();
int dataType();
void identifier_list();
void statement_list();
int statement();
int assign_stat();
void expr();
void simple_expr();
void eprime();
void term();
void seprime();
int relop();
void factor();
void tprime();
int mulop();
int addop();
int decision_stat();
void dprime();
int looping_stat();


void Program()
{
	if(strcmp(token.c_str(),"main") == 0)
	{
		getToken("Program");
		if(strcmp(token.c_str(),"(") == 0)
		{
			getToken("Program");
			if(strcmp(token.c_str(),")") == 0)
			{
				getToken("Program");
				if(strcmp(token.c_str(),"{") == 0)
				{
					getToken("Program");
					declaration();
					statement_list();
					if(strcmp(token.c_str(),"}") == 0)
					{
						printf("Parse complete\n");
						exit(0);
					}
					else
					{
						printf("Error atB\n");
						exit(1);
					}
				}
				else
				{
					printf("Error at\n");
					exit(1);
				}
			}
			else
			{
				printf("Error at\n");
				exit(1);
			}
		}
		else
		{
			printf("Error at\n");
			exit(1);
		}

	}
	else
	{
		printf("Error at\n");
		exit(1);
	}

}

void declaration()
{
	int incoming=dataType();
	if(incoming == 1)
	{
		identifier_list();
		if(strcmp(token.c_str(),";") == 0)
		{
			getToken("declaration");
			declaration();
		}
		else
		{
			printf("Error at\n");
			exit(1);
		}
	}
	else
		return;		
}
int dataType()
{
	if(strcmp(token.c_str(),"int") == 0 || strcmp(token.c_str(),"char") == 0)
	{
		getToken("datatype");
		return 1;
	}
	else
		return 0;
}

void identifier_list()
{
	if(strcmp(token.c_str(),"id") == 0)
	{
		getToken("identifier_list");
		if(strcmp(token.c_str(),",") == 0)
		{
			getToken("identifier_list");
			identifier_list();
		}
		else if (strcmp(token.c_str(),"[") == 0)
		{
			getToken("identifier_list");
			if (strcmp(token.c_str(),"num") == 0)
			{
				getToken("identifier_list");
				if (strcmp(token.c_str(),"]") == 0)
				{
					getToken("identifier_list");
					if(strcmp(token.c_str(),",") == 0)
					{
						getToken("identifier_list");
						identifier_list();
					}
					else
						return;
				}
			}
		}
		else
			return;
	}
	else
	{
		printf("Error at in id");
		exit(1);
	}
}

void statement_list()
{
	int incoming=statement();
	if(incoming == 1)
		statement_list();
	else
		return;
}

int statement()
{
	int incoming = assign_stat();
	if(incoming == 0)
	{
		if(strcmp(token.c_str(),"}") != 0)
		{
			incoming=decision_stat();
			if(!incoming)
				incoming=looping_stat();
		}
	}
	else
	{
		if(strcmp(token.c_str(),";") == 0)
		{
				getToken("statement");
				return 1;
		}
		else
		{
			printf("Error ati\n");
			exit(1);	
		}
	}
	return incoming;
}

int decision_stat()
{
	if(strcmp(token.c_str(),"if") == 0)
	{
		getToken("decision_stat");
		if(strcmp(token.c_str(),"(") == 0)
		{
			getToken("decision_stat");
			expr();
			if(strcmp(token.c_str(),")") == 0)
			{
				getToken("decision_stat");
				if(strcmp(token.c_str(),"{") == 0)
				{
					getToken("decision_stat");
					statement_list();
					if(strcmp(token.c_str(),"}") == 0)
					{
						getToken("decision_stat");
						dprime();
						return 1;
					}
					else
					{
						printf("Error at }\n");
						exit(1);
					}
				}
				else
				{
					printf("Error at {\n");
					exit(1);
				}
			}
			else
			{
				printf("Error at )\n");
				exit(1);
			}
		}
		else
		{
			printf("Error at (\n");
			exit(1);
		}
	}
	else
		return 0;
}

int looping_stat()
{
	if(strcmp(token.c_str(),"while") == 0)
	{
		getToken("looping_stat");
		if(strcmp(token.c_str(),"(") == 0)
		{
			getToken("looping_stat");
			expr();
			if(strcmp(token.c_str(),")") == 0)
			{
				getToken("looping_stat");
				if(strcmp(token.c_str(),"{") == 0)
				{
					getToken("looping_stat");
					statement_list();
					if(strcmp(token.c_str(),"}") == 0)
					{
						getToken("looping_stat");
						return 1;
					}
					else
					{
						printf("Error } expected\n");
						exit(1);
					}
				}
				else
				{
					printf("Error { expected\n");
					exit(1);
				}
			}
			else
			{
				printf("Error ) expected\n");
				exit(1);
			}
		}
		else
		{
			printf("Error ( expected\n");
			exit(1);
		}
	}
	
	else if(strcmp(token.c_str(),"for") == 0)
	{
		getToken("looping_stat");
		if(strcmp(token.c_str(),"(") == 0)
		{
			getToken("looping_stat");
			assign_stat();
			if(strcmp(token.c_str(),";") == 0)
			{
				getToken("looping_stat");
				expr();
				if(strcmp(token.c_str(),";") == 0)
				{
					getToken("looping_stat");
					assign_stat();
					if(strcmp(token.c_str(),")") == 0)
					{
						getToken("looping_stat");
						if(strcmp(token.c_str(),"{") == 0)
						{
							getToken("looping_stat");
							statement_list();
							if(strcmp(token.c_str(),"}") == 0)
							{
								getToken("looping_stat");
								return 1;
							}
							else
							{
								printf("} expected\n");
								exit(1);
							}
						}
						else
						{
							printf("{ expected\n");
							exit(1);
						}
					}
					else
					{
						printf(") expected\n");
						exit(1);	
					}
				}
				else
				{
					printf("Error at ;\n");
					exit(1);	
				}
			}
			else
			{
				printf("Error at ;\n");
				exit(1);	
			}
		}
		else
		{
			printf("( expected\n");
			exit(1);
		}
	}
	else
	{
		printf("while/for error\n");
		exit(1);

	}
}

void dprime()
{
	if(strcmp(token.c_str(),"else") == 0)
	{
		getToken("dprime");
		if(strcmp(token.c_str(),"{") == 0)
		{
			getToken("dprime");
			statement_list();
			if(strcmp(token.c_str(),"}") == 0)
			{
				getToken("dprime");
			}
			else
			{
				printf("Error at dprime }\n");
				exit(1);
			}
		}
		else
		{
			printf("Error at dprime {\n");
			exit(1);
		}
	}
	else
		return;
}
int assign_stat()
{
	if(strcmp(token.c_str(),"id") == 0)
	{
		getToken("assign_stat");
		if(strcmp(token.c_str(),"=") == 0)
		{
			getToken("assign_stat");
			expr();
		}
		else
		{
			printf("Error at in = assign\n");
			exit(1);
		}
	}
	else
		return 0;
}

void expr()
{
	simple_expr();
	eprime();
}

void simple_expr()
{
	term();
	seprime();
}
void eprime()
{
	int incoming= relop();
	if(incoming == 1)
		simple_expr();		
	else
		return;
}
void seprime()
{
	int incoming = addop();
	if(incoming == 1)
	{
		term();
		seprime();
	}
	else
		return;
}

int addop()
{
	if( strcmp(token.c_str(),"+") == 0 || strcmp(token.c_str(),"-") == 0)
	{
		getToken("addop");
		return 1;
	}
	else
		return 0;
}

void term()
{
	factor();
	tprime();
}

void factor()
{
	if(strcmp(token.c_str(),"id") == 0 || strcmp(token.c_str(),"num") == 0)
		getToken("factor");
	else
	{
		printf("Error at in factor\n");
		exit(1);
	}
}

void tprime()
{
	int incoming = mulop();
	if(incoming == 1)
	{
		factor();
		tprime();
	}
	else
		return;
}

int mulop()
{
	if(strcmp(token.c_str(),"*") == 0 || strcmp(token.c_str(),"%") == 0 || strcmp(token.c_str(),"/") == 0)
	{
		getToken("mulop");
		return 1;
	}
	else
		return 0;
}

int relop()
{
	if(strcmp(token.c_str(),"=") == 0)
	{
		getToken("relop");
		if(strcmp(token.c_str(),"=") == 0)
			return 1;
		else
			return 0;
	}
	if(strcmp(token.c_str(),"!") == 0)
	{
		getToken("relop");
		if(strcmp(token.c_str(),"=") == 0)
			return 1;
		else
			return 0;
	}
	if(strcmp(token.c_str(),">") == 0)
	{
		getToken("relop");
		if(strcmp(token.c_str(),"=") == 0)
		{
			getToken("relop");
			return 1;
		}
		else if(strcmp(token.c_str(),"id") == 0)
			return 1;
		else if(strcmp(token.c_str(),"num") == 0)
			return 1;
		else
			return 0;
	}
	if(strcmp(token.c_str(),"<") == 0)
	{
		getToken("relop");
		if(strcmp(token.c_str(),"=") == 0)
		{
			getToken("relop");
			return 1;
		}
		else if(strcmp(token.c_str(),"id") == 0)
		{
			return 1;
		}
		else if(strcmp(token.c_str(),"num") == 0)
		{
			return 1;
		}
		else
			return 0;
	}
}

int main()
{
	tokenizer();
	getToken("main");
	Program();
	printf("Parse successful\n");
	return 0;
}
