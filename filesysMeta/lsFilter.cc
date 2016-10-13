#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
using namespace std;

const unsigned int testUp = 100;

vector<string> directory;

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    ifstream infile(argv[1], ios::in);
    ofstream outfile(argv[2], ios::out);

    while(!infile.eof()){
	string line;
	getline(infile, line);
	stringstream newline(line);

	string term;
	newline >> term;

	if(!term.compare("d")){
	    newline >> term;
	    newline >> term;
	    directory.push_back(term);
	    outfile << "mkdir "<< term << '\n';
	}
	else if(!term.compare("f")){
	    string size;
	    newline >> size;
	    newline >> term;
	    outfile << "write " << term << " " << size << '\n';
	}
    }

    for(int i = 0 ; i < testUp ; i++)
    {
	unsigned int index = rand()%directory.size();
	outfile << "ls " << directory[index] << '\n';
    }

    infile.close();
    outfile.close();
}
