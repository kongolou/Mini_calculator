#include <iostream>

namespace Mini_calculator
{
	using std::cin;
	using std::cout;

	constexpr char NUM = 'n';
	constexpr char QUIT = 'q';
	constexpr char CALC = ';';

	struct Token
	{
		char kind = NUM;
		double value = 0.0;
	};

	Token get_token()
	{
		char kind;
		cin >> kind;
		switch (kind)
		{
		case QUIT:
		case CALC:
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
			return Token{ kind,0.0 };
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			cin.unget();
			double value;
			cin >> value;
			return Token{ NUM,value };
		}
		default:
		{
			cout << "Bad input. Please try again.\n";
			return Token{ QUIT,0.0 };
		}

		}
	}

	Token tkn_buf;

	double expression();
	double primary()
	{
		tkn_buf.kind = NUM;
		for (double temp = 0.0; tkn_buf.kind != QUIT;)
		{
			switch (tkn_buf.kind)
			{
			case NUM:
				temp = tkn_buf.value; // 穿透
			case ')':
				tkn_buf = get_token();
				break;
			case '(':
				return expression();
			default:
				return temp;
			}
		}
		return 0.0;
	}
	double term()
	{
		for (double temp = primary(); tkn_buf.kind != QUIT;)
		{
			switch (tkn_buf.kind)
			{
			case '*':
				temp *= primary();
				break;
			case '/':
			{
				double x = primary();
				if (fabs(x) > 1e-15) // 浮点数比较
				{
					temp /= x;
				}
				else
				{
					cout << "Can't be divided by zero!";
					tkn_buf.kind = QUIT;
				}
				break;
			}
			default:
				return temp;
			}
		}
		return 0.0;
	}
	double expression()
	{
		for (double temp = term(); tkn_buf.kind != QUIT;)
		{
			switch (tkn_buf.kind)
			{
			case '+':
				temp += term();
				break;
			case '-':
				temp -= term();
				break;
			default:
				return temp;
			}
		}
		return 0.0;
	}

	void calculate()
	{
		cout
			<< "Mini_calculator v1.0 by Louis Sheng\n"
			<< "Inspired by Bjarne Stroustrup.\n"
			<< "\n[Grammar]\n\n"
			<< "Expression:\n"
			<< "\tTerm\n"
			<< "\tExpression\"+\"Term\n"
			<< "\tExpression\"-\"Term\n"
			<< "Term:\n"
			<< "\tPrimary\n"
			<< "\tTerm\"*\"Primary\n"
			<< "\tTerm\"/\"Primary\n"
			<< "Primary:\n"
			<< "\tnumber\n"
			<< "\t\"(\"Expression\")\"\n"
			<< "Quit:\n\t"
			<< QUIT
			<< "\nCalculate:\n\t"
			<< CALC
			<< "\n\n[Example]\n\n"
			<< ">2-(-3/5);\n"
			<< "=2.6\n"
			<< "\n[Test]\n";
		for (double result = 0.0; tkn_buf.kind != QUIT;)
		{
			cout << "\n>";
			result = expression();
			if (tkn_buf.kind == CALC) // 注意等号
			{
				cout << "=" << result;
			}
		}
	}
}

int main()
{
	Mini_calculator::calculate();
	return 0;
}