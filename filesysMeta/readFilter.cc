#include<fstream>
#include<sstream>
#include<vector>
#include<cstdlib>
using namespace std;

const unsigned int testUp = 1000;

vector<string> fileSet;

int main(int argc, char* argv[])
{
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
	    outfile << "mkdir "<< term << '\n';
	}
	else if(!term.compare("f")){
	    string size;
	    newline >> size;
	    newline >> term;
	    fileSet.push_back(term);
	    outfile << "write " << term << " " << size << '\n';
	}
    }

    for(int i = 0 ; i < testUp ; i++)
    {
	unsigned int index = rand()%fileSet.size();
	outfile<<"read "<< fileSet[index] << '\n';
    }

    infile.close();
    outfile.close();
}
