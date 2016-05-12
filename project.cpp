#include<iostream>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;		//includes very commonly used syntax in C++ like cin, cout, map etc

//Make a normal probability density function
double pdf(double x, double mean, double sigma)		//Use double for everyday use. We can also use long double for higher accuracy.
{
	static const double Pi = 3.14159265; 
	return exp( -1 * (x) * (x) / (2)) / (sqrt(2 * Pi));		//returns the value of N(0,1)
}

//Make a cummulative normal distribution function
double cdf(double x, double arg1, double arg2, double(*pPDF)(double,double,double), double y) 	//since pdf contains three double arguments
{
	double sum = 0;
	double ninf = -1000000; 	// Negative infinity, we can put any number which is as close to negative infinity with respect to normal distribution function
	double n = 10000000; 		// More number of smaller section(dx) we take, the result comes out to be more precise. However, it will also increase the compilation time.

	for (double i = 1; i < n-1; i++) 	//for all smaller buckets we add the pdf to calculate the cdf
		sum += pPDF( x + i*(x-ninf)/n ,arg1,arg2);

	y = return ((x - ninf) / n) * ((pPDF(x,arg1,arg2) + pPDF(ninf,arg1,arg2))/2 + sum);		//returns the value of cumulative probability distribution function by adding all the pdf of the smaller pdf values
	return y;
}

int main()
{
	string value[1];
	ofstream textfile("Book1.txt",std::ios_base::app); 	//It helps to create another new line in the file without deleting the previous calculated output from the file
	
	double x, mean, sigma;
	cout << "x, mean, sigma: "; 	//asks the user for inputs
	cin >> x >> mean >> sigma; 		//take input for the x, means and sigma values

	cout << "PDF of x is: " << pdf(x,mean,sigma) << endl;
	cout << "CDF of x is: " << cdf(x,mean,sigma,pdf) << endl; // Note we added a pointer to your pdf function
	
	if(textfile.is_open()) 		//use of if statement so that the output is printed only when the file is open
	{
		getline(cin,value[0]);
		textfile<<"The value of cdf at " << x << ": " << cdf(x,mean,sigma,pdf) <<endl;
	}
	textfile.close(); 		//close the text file after every use
	std::cin.get();			//helps the output screen to stay for sometime until we enter anything else			
	return 0;
}

