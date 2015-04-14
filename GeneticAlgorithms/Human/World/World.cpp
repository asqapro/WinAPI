#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

void stimulus(int scenario){
    ofstream world_data;
    world_data.open ("world_data.txt");
    world_data << scenario << "\n";
    world_data.close();
}

int main(){
    return 0;
}
