
#include <iostream>

using namespace std;

class Quinn
{
public:
	Quinn();
	~Quinn();

	int name = 0;


private:
};

Quinn::Quinn()
{
}

Quinn::~Quinn()
{
}



int main()
{
    
	Quinn q;
	q.name = 12;

	int newm = 1222;


	printf("name is: %p", &newm);
	
}
