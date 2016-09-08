#include<fstream>
#include<sstream>
using namespace std;

int main()
{
    ifstream infile("metadata", ios::in);
    ofstream outfile("brief", ios::out);

    while(!infile.eof())
    {
	string line;
	getline(infile, line);
	stringstream newline(line);

	string term;
	newline >> term;

	if(term.find('d') != string::npos)
	    outfile<<"d\t";
	else
	    outfile<<"f\t";
	newline >> term;
	newline >> term;
	newline >> term;
	newline >> term;
	outfile << term << "\t";
	newline >> term;
	newline >> term;
	newline >> term;
	outfile << term << "\n";
    }
}
