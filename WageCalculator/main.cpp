#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    float wage;

    map<string, float> typeTimes;
    typeTimes["seconds"] = 2.777777777777778e-4;
    typeTimes["minutes"] = 0.0166666666666667;
    typeTimes["hours"] = 1.0;
    typeTimes["days"] = 24.0;
    typeTimes["weeks"] = 168.0;
    typeTimes["years"] = 61320.0;

    string timeType;
    float intTimeType;
    float time;

    while(true){
        cout << "Enter hourly wage: $";
        cin >> wage;

        cin.clear();
        cin.sync();

        cout << "Seconds, minutes, hours, days, weeks, or years? ";
        cin >> timeType;

        intTimeType = typeTimes[timeType];

        cout << "Enter time remaining: ";
        cin >> time;

        cin.clear();
        cin.sync();

        cout << "Profit: $" << (time * intTimeType) * wage << endl;
    }
    return 0;
}
