#include<iostream>
#include<string>
#include<map>
#include<fstream>
using namespace std;
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
const int keyword=1;
const int op= 2;
const int boundary=3;
const int identifier =4;
const int constant =5;
map<int,map<string, int>>match;

bool check(string s) 
{
	string Keyword[] = { "then","end","repeat","until","read","write","if","else","int","float","return","void","do","while"};
	for (int i = 0; i < ARRAY_SIZE(Keyword); i++)
	{
		if (s == Keyword[i])
			return true;
	}
	return false;

}

void Code(string INPUT_PATH)
{
	ifstream in;
	in.open(INPUT_PATH);
	string s;
	int k = 1;
	char ch = in.get();
	while (ch != EOF)
    {
//        || ch == '{' || ch == '}'
        if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']')
		{
			s = string(1,ch);
			match[k].insert(pair<string, int>(s, boundary));
			k++;
			ch = in.get();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '%')
		{
			s = string(1, ch);
			match[k].insert(pair<string, int>(s, op));
			k++;
			ch = in.get();

		}
		else if (ch == '/')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch != '/')
			{
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}	
			else 
			{
				while (ch!=' ')
				{
					ch = in.get();
				}
			}
		}
		else if (ch == '=')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch != '=')
			{
				match[k].insert(pair<string, int>(s, op));
				k++;
			}
			else if (ch == '=')
			{
				s += ch;
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}
		}
		else if (ch == ':')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=')
			{
				s += ch;
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}
		}
		else if (ch == '>')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=')
			{
				s += ch;
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}
		}
		else if (ch == '!')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=')
			{
				s += ch;
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}
		}
		else if (ch == '<')
		{
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=')
			{
				s += ch;
				match[k].insert(pair<string, int>(s, op));
				k++;
				ch = in.get();
			}
			else if (ch != '=')
			{
				match[k].insert(pair<string, int>(s, op));
				k++;
			}
		}
        else if (ch == '{')
        {
            ch = in.get();
            while (ch != '}')
            {
                ch = in.get();
            }
            ch = in.get();
        }
		else if (isalpha(ch) || ch == '_')
		{
			s = "";
			while (isalpha(ch) || isdigit(ch) || ch == '_') 
			{
				s += ch;
				ch = in.get();
			}
			if (check(s))
			{
				match[k].insert(pair<string, int>(s, keyword));
				k++;
			}
			else
			{
				match[k].insert(pair<string, int>(s, identifier));
				k++;
			}
		}
		else if (isdigit(ch))
		{
			s = "";
			while (isdigit(ch))
			{
				s += ch;
				ch = in.get();
				if (ch == '.')
				{
					s += ch;
					ch = in.get();
					if (isdigit(ch)) 
					{
						while (isdigit(ch)) 
						{
							s += ch;
							ch = in.get();
						}
						match[k].insert(pair<string, int>(s, constant));
						k++;
						break;
					}
				}
				if (!isdigit(ch))
				{
					match[k].insert(pair<string, int>(s, constant));
					k++;
					break;
				}
			}
		}
		else 
		{
			ch = in.get();

		}
		
	}
}
void displayCode(map<int, map<string, int>>match)
{
	ofstream out;
    out.open("sample.lex");
	map<int, map<string, int>>::iterator it;
	for (it = match.begin(); it != match.end(); it++) 
	{
		map<string, int> item = it->second;
		map<string, int> ::iterator it1;
		for (it1 = item.begin(); it1 != item.end(); it1++)
			out << it1->first << "->" << it1->second << endl;	
	}
	out.close();

	ofstream ofile;
	ofile.open("codeTiny.txt");
	for (it = match.begin(); it != match.end(); it++)
	{
		map<string, int> item = it->second;
		map<string, int> ::iterator it1;
		for (it1 = item.begin(); it1 != item.end(); it1++)
			ofile << it1->second << " ";
	}
	ofile.close();

}
//int main()
//{
//	string INPUT_PATH = "SAMPLE.TNY";
//	Code(INPUT_PATH);
//	displayCode(match);

//	return 0;
//}
