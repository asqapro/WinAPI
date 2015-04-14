#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

string target = "to be or not to be";

class DNA{
    public:
    char genes[18];
    float fitness;
    DNA();
    ~DNA();
    void make_fitness();
    DNA crossover(DNA partner);
    void mutate();
    string get_result();
};

DNA::DNA(){
    for(unsigned int iter = 0; iter < sizeof(genes); iter++){
        genes[iter] = char(rand() % 122 + 97);
    }

}

DNA::~DNA(){

}

void DNA::make_fitness(){ //closeness to target string
    int score = 0;
    for(unsigned int iter = 0; iter < sizeof(genes); iter++){
        if(genes[iter] == target[iter]){
            score++;
        }
    }
    fitness = float(score)/target.length();
}

DNA DNA::crossover(DNA partner){
    DNA child_to_be;

    int gene;

    for(unsigned int iter = 0; iter < sizeof(genes); iter++){
        gene = rand() % 2 + 1;
        if(gene == 1){
            child_to_be.genes[iter] = genes[iter];
        }
        else{
            child_to_be.genes[iter] = partner.genes[iter];
        }
    }


    return child_to_be;
}

void DNA::mutate(){
    float mutation_rate = 0.01;

    for(unsigned int iter = 0; iter < sizeof(genes); iter++){
        if(rand() % 1 + 0 < mutation_rate){
            genes[iter] = char(rand() % 122 + 97);
        }
    }
}

string DNA::get_result(){
    genes[sizeof(genes) + 1] = '\0';
    string str = genes;
    return str;
}

bool operator == (DNA const& v1, DNA const& v2){
    return (v1.genes == v2.genes) && (v1.fitness == v2.fitness);
}

vector<DNA> population;
vector<DNA>::iterator popu;

void setup() {
    for(int iter = 0; iter < 1000; iter++){
        DNA person;
        population.push_back(person);
    }
}

void fit(){
    for(popu = population.begin(); popu != population.end(); popu++){
        DNA item = *popu;
        item.make_fitness();
        *popu = item;
    }
}

vector<DNA> mate_pool;

void make_pool(){
    for(popu = population.begin(); popu != population.end(); popu++){
        DNA item = *popu;
        int n = int(item.fitness * 100);
        for(int iter2 = 0; iter2 < n; iter2++){
            mate_pool.push_back(item);
        }
    }
}

vector<DNA>::iterator popu_copy;

void mate_spawn(){
    for(popu = population.begin(); popu != population.end(); popu++){
        int a = rand() % mate_pool.size() + 1;
        int b = rand() % mate_pool.size() + 1;
        if(a == b){
            while(a == b){
                b = rand() % mate_pool.size() + 1;
            }
        }
        DNA parentA = mate_pool[a];
        DNA parentB = mate_pool[b];
        DNA child;
        child = parentA.crossover(parentB);
        child.mutate();
        if(parentA.fitness < parentB.fitness){
            *popu = child;
        }
        else{
            popu_copy = popu;
            popu = find(population.begin(), population.end(), parentA);
            *popu = child;
            popu = popu_copy;
        }
    }
}

int main()
{
    srand (time(NULL));
    setup();
    int counter = 0;
    while(counter < 150){
        fit();
        make_pool();
        mate_spawn();
        counter++;
    }
    DNA topfit;
    topfit.fitness = 0;
    for(popu = population.begin(); popu != population.end(); popu++){
        DNA item = *popu;
        cout << item.get_result() << endl;
        if(item.fitness > topfit.fitness){
            topfit = item;
        }
    }
    cout << endl << endl << endl;
    cout << topfit.fitness << endl;
    cout << topfit.get_result() << endl;

    return 0;
}
