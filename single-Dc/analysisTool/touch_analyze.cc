#include<fstream>
#include<sstream>
#include<cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  ifstream infile(argv[1], ios::in);
  uint64_t cnt = 0;
  uint64_t access_time = 0;
  while (!infile.eof()) {
	string line;
	getline(infile, line);
	stringstream newline(line);
	string term;
	newline >> term;

	if (term == "touch")
	    cnt++;
	else if(term == "#") {
	  string tmp;
	  newline >> tmp;
	  if (tmp == "touch-access")
		access_time++;
	}
  }
  fprintf(stdout, "touch: %u times\n", cnt);
  fprintf(stdout, "access: %lu per time\n", access_time/cnt);
}
