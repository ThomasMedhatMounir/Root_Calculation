// this program calculate roots of any polynomial equation
// header files needed
#include<iostream>
#include<cmath>
#include<string.h>
#include<cstdlib>
#pragma warning (disable : 4996 )  // for strtok
using namespace std;

double EP = 0.00000001;   // epsilon is percision

float horner(int* coefficient, int n, float x)          // horner method to find the value of F(x) at at any x
{
	float result = 0;  // Initialize result
	//  to Evaluate value of polynomial using Horner's method
	// n is power of polynomial
	for (int i = 0; i < n; i++)
	{
		result = (result + coefficient[i]) * x;
	}
	result = result + coefficient[n];
	return result;      // F(x)
}//end of horner function


inline float f(float x, int eq[], int n)    //inline function as to decrease debugging time.
{
	double y = 0;   // y=f(x)
	int i = 0;     // counter
		while (n >= 0)  // n is power
		{
			y += eq[i] * pow(x, n); // to get the value of f(X) ex : y=f(x)= 3(2)^1+2(2)^0
			i++;
			n--;
		}
		return y;
} // end of f function


double bisection(float a, float b, int eq[], int n)    //BISECTION METHOD OF ROOT FINDING
{
	double c = (a + b) / 2, c_before = 0, y;
	do
	{
		y = f(c, eq, n);
		if (y > 0)
		{
			a = c;    c_before = c;
		}
		else if (y < 0)
		{
			b = c;    c_before = c;
		}
		else if (y == 0)
			break;
		c = (a + b) / 2;
	}
	while (fabs(c - c_before) >= pow(10, -6)); // condition to exit while loop when the percentage of difference between the output & exact value less than 0.00000001%

	return c;
}// end of bisection function


void print_roots(int eq[], int n, int a, int b)  // to print the roots of polynomial function
{
	int i = 0;
	float root[10];       // can calculate and get output to roots up to 10 root for same equation
	for (int j = a; j <= b; j++)

		/*j++ counter : if input intervals are for example [-5,5],the program find roots between each unit
		( roots between -5 and -4 , -4 and -3 and so on till 5), to avoid finding only one root in
		the same interval and  if two roots are found in the same unit we can increase precision by
		DECREASING increment value , but will slow debugging time in an obvious effect */
	{
		float y1, y2;
		y1 = f(j, eq, n);
		y2 = f(j + 1, eq, n);

		if (y1 == 0)

		{
			root[i] = j; i++;
		}


		else if (y1 > 0 && y2 < 0)

		{
			root[i] = bisection(j, j + 1, eq, n);    i++;
		}

		else if (y1 < 0 && y2 >0)

		{
			root[i] = bisection(j + 1, j, eq, n);   i++;
		}

	} // end for
	if (i > 0)
	{
		cout << "\nRoot(s) of equation :-\n\n";
		for (int count = 0; count < i; count++)
		{
			cout << "Root " << count + 1 << " = " << root[count] << endl << endl;
		}
		// to check roots
		for (int count = 0; count < i; count++)
		{
			cout << "Check of Bisection method \n value of F( " << root[count] << " ) = " << (float)(int)horner(eq, n, root[count]) << endl << endl;
		}
	} // end if
	else
	{
		cout << "No Roots for this polynomial Equation." << endl << endl;
	}
} // end of print_roots function


// main function

int main() {

	// some decleration
	const int stringsize = 1000;       //  size for string input
	char st[stringsize];              // the string which will store the polynomial equation input by user
	char* s1;                        // for dynamic array which will be a copy of st polynomial equation
	char* ptr;                      // for tokenization and extract coefficient
	char* search;                  // for tokenization and extract coefficient
	char* eqptr;                  // pointer of st polynomial equation
	int* coefficient = NULL;     //  dymanic array where coefficient will be stored
	int counter = 0;            //  counter for printing coefficient
	int count = 0;             // counter  to extract coefficient
	int errors = 0;           // counter of errors
	int n = 0;               // power of polynomial equation
	float a = 0.0;          // start point of domain
	float b = 0.0;         // end point of domain


	// introdunction to user
	cout << "\n\t\t\tThis Program for calculating the root of any Polynomial equation . \n\t\t\t F( x ) = anx^n + an-1x^n-1 + an-2x^n-2 + ... + a1x + a0 = 0 \n";
	cout << "\nPRECAUTIONS TO AVOID ERRORS :- \n 1)start your function with space \n 2)Minus Sign must not have a blank with coefficient i.e. -7 not - 7\n3) All Letters must be lowercase\n 4) ALL terms of the Polynomial must be entered even zero coefficient one \n EXAMPLE :  (space)4x^4 -3x^3 + 0x^2 -1x^1 + 0 \n\n";




	// to let the user input the polynomial equation
	cout << "Enter the Polynomial Equation  F(X) = ";

	cin.getline(st, stringsize, '\n');  // to get the polynomial as string
	cout << endl << endl;

	// copy of st in s1
	s1 = new char[stringsize];  // dynamic array

	strcpy(s1, st);    // to copy polynomial in st in s1


					   // check for errors codes
	eqptr = st;   // pointer of st

	// to check that the user did not enter polynomial eqution on the form   (space)4x^4 -3x^3 + 2x^2 -1x^1 -10


		// to check that there is space at start of the polynomial equation
	if (eqptr[0] != ' ')
	{
		cout << "ERROR : No Space entered at start of the polynomial equation \n \n";
		errors++;
	}

	// to check that user did not enter spaces bewteen negative sign and coefficient
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] == '-')
		{
			if (eqptr[i + 1] == ' ')
			{
				errors++;
				cout << "ERROR: there is Space between negative sign and coefficient\n";
				cout << "No Space should be between negative sign and coefficient \n\n";
				break;
			}
		}
	}

	// to check that there is space before and after positive sign
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] == '+')
		{
			if (eqptr[i - 1] == ' ' && eqptr[i + 1] == ' ')
			{
				break;
			}
			else
			{
				errors++;
				cout << "ERROR : There is no space before and after the + sign \n\n";
			}
		}
	}

	// to check that user did not input a sign and then nothing more
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] == '+' || eqptr[i] == '-')
		{
			if (eqptr[i + 1] == '\0')
			{
				errors++;
				cout << "ERROR : There is a sign with nothing after it as example 4x^4 -3x^3 + 2x^2 -1x^1 +  \n\n";
				break;
			}
		}
	}

	// to check that user did not enter for example (1x1) insted of (1x^1)
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] == 'x')
		{
			if (eqptr[i] == 'x' && eqptr[i + 1] == '^')
			{

			}
			else
			{
				cout << "ERROR: Polynomial equation contain x without power sign example x1\n\n";
				errors++;

			}
		}
	}

	// to check that user did not  enter for example (1x^+) or (=)
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] == '^' && eqptr[i + 1] == ' ')
		{
			errors++;
			cout << "ERROR : Polynomial equation entered contain for example x^+ \n\n";
		}
		else if (eqptr[i] == '=')
		{
			errors++;
			cout << "ERROR : Polynomial equation entered contain = \n\n";
		}

	}

	// to check that user did not enter for example (x^2) instead of (1x^2)
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if ((eqptr[i] == 'x' && eqptr[i - 1] == ' ') || (eqptr[i] == 'x' && eqptr[i - 1] == '-'))
		{
			errors++;
			cout<< "ERROR : Polynomial equation entered contain for example + x^2 no coefficient is entered  \n\n";
		}
	}


	// to check that user did not enter any letter except (x)
	for (int i = 1; i < strlen(eqptr); i++)
	{
		if (eqptr[i] >= 'a' && eqptr[i] <= 'z')
		{
			if (eqptr[i] - 'x' != 0)
			{
				errors++;
				cout << "ERROR: Polynomial equation should be in one variable which is x \n\n";
				break;
			}
		}
	}


		//  NO ERROR CODE
		if(errors == 0)
		{
			// extract the coeficients
			ptr = strtok(st, " +");     // to token the polynomial equation in st

			while (ptr)
			{
				search = strstr(ptr, "x^");           // Returns a pointer to the first occurrence of x^ in pt
				ptr = strtok(NULL, " +");
				counter++;                 // counter count number of terms of the polynomial equations
			}

			// to identify the degree of function

			n = counter - 1;              // degree = number of terms - 1
			cout << "The Polynomial equation degree = " << n << endl << endl;   // to print the degree of polynomial equation


			// find coefficient

			coefficient = new int[counter];    // dynamic array to store coefficient

			ptr = strtok(s1, " +");          // to token the polynomial equation in st

			while (ptr)
			{

				long coeff;
				if (*ptr == 'x')
				{
					coeff = 1;
				}
				else if (*ptr == NULL)
				{
					coeff = 0;
				}
				else
				{
					char* endptr;
					coeff = strtol(ptr, &endptr, 10);       // strtol interprets the contents of a string as an integral number of the specified base and return its value as a long int.
				}
				coefficient[count] = coeff;
				ptr = strtok(NULL, " +");
				count++;
			}
			cout << "Cofficient are : \t" << endl << endl;

			// to print the coefficient
			for (int i = 0; i < counter; i++)
			{
				cout << coefficient[i] << " \t ";
			}
			cout << endl << endl;

			// to let user enter domain of function

			cout << "Enter the domain : \n ";

			cout << "\nPRECAUTIONS TO AVOID ERRORS :- \n 1)Enter the start point then end point (smaller number then larger number)\n\n\n";

			cout << "Start Point (a) = ";
			cin >> a;

			cout << endl;

			cout << "End Point (b) = ";
			cin >> b;

			cout << endl << endl;

			print_roots(coefficient, n, a, b); // void function to print

			delete[]coefficient;  // close dynamic array
			delete[]s1;          //  close dynamic array

		}//end if
		else
		{
			cout << "ERROR ERROR THERE IS AN ERROR THAT NEED TO BE FIXED \n\n";
		}
		cout << "\n\t\t\t\t\tEND OF PROGRAM\n\n\n\n";
		return 0;
}// end main
