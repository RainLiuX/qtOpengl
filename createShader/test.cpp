#include <fstream> 
#include <iostream>
#include <string>

int main()
{
	using namespace std;
	string text;
	ifstream file("fragshader.frag");
	string temp;
	while(getline(file, temp))
	{
		text += temp + "\n";
	}
	cout<<text<<endl;
}
