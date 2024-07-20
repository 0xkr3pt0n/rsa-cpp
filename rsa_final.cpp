#include <iostream>
#include <string>
#include <math.h>

class encryption
{
private:
	double p, q; // p and q are two prime numbers used in generating public/private keys
public:
	// class methods prototypes
	encryption(double, double); // default constructor of the class
	double gcd (double a, double b); // function to retuen gcd of two numbers
	double calculate_n(); // function to find n which is p*q
	double calculate_fi(); // function to find fi of n 
	double calculate_e(); // function to find e in encrypt equation
	double calculate_d(); // function to find d in decrypt equation
	void display_keys(); // function to display public and private keys
	double encrypt(double message); // encryption function
	double decrypt(double cipher); // decryption function
};
// class methods decleration
encryption::encryption(double p, double q)
{
	this -> p = p;
	this -> q = q;
}
double encryption::gcd(double a, double b)
{
	if (a==b)
		return a;
	if (a>b)
		gcd(a-b, b);
	if (a<b)
		gcd(a, b-a);
}
double encryption::calculate_n()
{
	return p*q;
}
double encryption::calculate_fi()
{
	return ((p-1)*(q-1));
}
double encryption::calculate_e()
{
	double temp = calculate_fi(); // temprory variable to hold the value of fi of(n) 
	double e = 2;
	for(int i=0; i<temp; i++)
	{
		if(e>1 && e<temp && gcd(calculate_fi(),e)==1)
			return e;
		else
			e++;
	}
}
double encryption::calculate_d()
{
	// temprory variables for storing fi of(n) and e
	double temp1 = calculate_fi();
	double temp2 = calculate_e();
	for (int i=0; i<100; i++)
	{
		double t1 = temp2*i;
		double t2 = fmod(t1, temp1);
		if (t2 == 1)
		{
			return i;
			break;
		}
	}
	
}

void encryption::display_keys()
{
	double t1 = calculate_e();
	double t2 = calculate_n();
	double t3 = calculate_d();
	std::cout<<"encryption key ("<<t1<<","<<t2<<") \n";
	std::cout<<"decryption key ("<<t3<<","<<t2<<")\n";
}
double encryption::encrypt(double message)
{
	double t1 = calculate_e();
	double t2 = calculate_n();
	double c_temp = pow(message,t1);
	double cipher = fmod(c_temp, t2);
	return cipher;

}

double encryption::decrypt(double cipher)
{
	double t2 = calculate_n();
	double t3 = calculate_d();
	double p_temp = pow(cipher, t3);
	double plain = fmod(p_temp, t2);
	return plain;
}

// main function for testing class capabillties
int main()
{
	encryption rsa(3, 11);
	rsa.display_keys();
	//std::cout<<rsa.encrypt(29);
	std::cout<<rsa.decrypt(2);
	
	return 0;
}