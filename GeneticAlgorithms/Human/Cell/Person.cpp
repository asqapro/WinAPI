#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

void alive();
void recieve();
void process();
void react();

/*class cell:
    public:
        cell(){

        }
    enum types{
        processor = 1;
        reactor = 2;
        receiver = 3;
    }

*/

vector< vector<int> > brain;

vector< vector<int> > body;

void make_cell(int type, int count, int place){
    vector<int> local_cell;
    local_cell.push_back(type);
    local_cell.push_back(count);
    if(type == 1){
        brain.push_back(local_cell);
    }
    else{
        body.push_back(local_cell);
    }
}

void alive(){

}

void receive(){

}

void process(){

}

void react(){

}

int main()
{
    int retCode = system("World.exe");
    cout << retCode << endl;
    make_cell(1, 1, 1);
    make_cell(2, 1, 2);

    return 0;
}
