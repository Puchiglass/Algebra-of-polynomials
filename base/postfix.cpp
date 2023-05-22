#include "postfix.h"
#include "stack.h"
#include <iostream>

int TPostfix::prior(string a)
{
	if (a == "dx" || a == "dy" || a == "dz" || a == "Ix" || a == "Iy" || a == "Iz" || a == "*_" || a == "/_")
		return 3;
	if (a == "+_" || a == "-_")
		return 2;
	if (a == "(_" || a == ")_")
		return 1;
	return 0;
}

string TPostfix::to_postfix()
{
	sc.set_size(infix.size());
	sd.set_size(infix.size());
	char tmp;
	string con;
	for (int i = 0; i < infix.size(); i++)\
	{
		con.clear();
		tmp = infix[i];
		if ((tmp == 'd' || tmp == 'I') && ((infix[i + 1] == 'x') || (infix[i + 1] == 'y') || (infix[i + 1] == 'z')))
		{
			con += tmp;
			con += infix[i + 1];
			i++;
		}
		else
		{
			con += tmp;
			con += '_';
			if (prior(con) == 0)
			{
				postfix += tmp;
				continue;
			}
		}
		if ((prior(con) == 2) || (prior(con) == 3))
		{
			if (postfix.size() != 0)
				if (postfix[postfix.size() - 1] != '|')
					postfix += "|";
			if (sc.is_empty() == true)
				sc.add(con);
			else
			{
				if (prior(con) > prior(sc.info_top()))
				{
					sc.add(con);
				}
				else
				{
					while (prior(con) <= prior(sc.info_top()))
					{
						postfix += sc.get_top();
						postfix += "|";
						if (sc.is_empty() == true)
							break;
					}
					sc.add(con);
				}
			}
		}
		else
			if (tmp == '(')
				sc.add(con);
			else
				if (tmp == ')')
				{
					postfix += "|";
					while (sc.info_top() != "(_")
					{
						postfix += sc.get_top();
						postfix += "|";

					}
					sc.get_top();
				}

	}
	if (tmp != ')')
		postfix += "|";
	while (sc.is_empty() != true)
	{
		postfix += sc.get_top();
		postfix += "|";
	}

	return postfix;
}

Polynom TPostfix::calculate(Table** tab)
{
	Polynom a, b;
	string con;
	double k;
	for (int i = 0; i < postfix.size() - 1; i++)
	{
		con.clear();
		while (postfix[i] != '|')
		{
			con += postfix[i];
			i++;
		}
		if (con == "+_")
		{
			a = sd.get_top(); b = sd.get_top();
			sd.add(a + b);
			continue;
		}
		if (con == "-_")
		{
			a = sd.get_top();
			if (sd.is_empty() == true)
					sd.add(a *= -1);
			else
			{
				b = sd.get_top();
				sd.add(b - a);
			}
			continue;
		}
		if (con == "*_")
		{
			a = sd.get_top(); b = sd.get_top();
			sd.add(a * b);
			continue;
		}
//		if (con == "/_")
//		{
//			a = sd.get_top(); b = sd.get_top();
////			sd.add(b / a);
//			continue;
//		}
		if (con == "dx" || con == "dy" || con == "dz")
		{
			a = sd.get_top();
			sd.add(a.derivative(con[1]));
			continue;

		}
		if (con == "Ix" || con == "Iy" || con == "Iz")
		{
			a = sd.get_top();
			sd.add(a.integral(con[1]));
			continue;
		}
		if (con[0] > 47 && con[0] < 58)
		{
			Polynom v(con);
			sd.add(v);
		}
		else
		{
			a = *tab[4]->find(con)->poly;/////////////////////////////////
			sd.add(a);
		}
	}
	a = sd.get_top();
	if (sd.is_empty() != true)
	{
		throw 0;
	}
	return a;
}







