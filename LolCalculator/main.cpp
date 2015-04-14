#include "championClasses.h"
#include "itemClasses.h"
#include "curlFunctionsHeader.h"

using namespace std;

string map;

istream& GotoLine(istream& file, unsigned int num){
    file.seekg(ios::beg);
    for(unsigned int i=0; i < num; ++i){
        file.ignore(10,'\n'); //each data line should not exceed 10 characters
    }
    return file;
}

int searchStringArray(string toSearch[], string searchFor, int size)
{
    for(int iter = 0; iter < size; iter++)
    {
        if(toSearch[iter] == searchFor)
        {
            return iter;
        }
    }
    return -1;
}

int searchCharArray(char toSearch[], char searchFor, int size)
{
    for(int iter = 0; iter < size; iter++)
    {
        char check = toSearch[iter];
        if(check == searchFor)
        {
            return iter;
        }
    }
    return -1;
}

string champs[123] = {"Aatrox", "Ahri", "Akali","Alistar","Amumu","Anivia","Annie","Ashe","Azir","Blitzcrank","Brand","Braum","Caitlyn","Cassiopeia",
                        "ChoGath","Corki","Darius","Diana","Dr. Mundo","Draven","Elise","Evelynn","Ezreal","Fiddlesticks","Fiora","Fizz","Galio",
                        "Gangplank","Garen","Gnar","Gragas","Graves","Hecarim","Heimerdinger","Irelia","Janna","Jarvan IV","Jax","Jayce","Jinx",
                        "Kalista","Karma","Karthus","Kassadin","Katarina","Kayle","Kennen","Kha\'Zix","KogMaw","LeBlanc","Lee Sin","Leona","Lissandra",
                        "Lucian","Lulu","Lux","Malphite","Malzahar","Maokai","Master Yi","Miss Fortune","Mordekaiser","Morgana","Nami","Nasus",
                        "Nautilus","Nidalee","Nocturne","Nunu","Olaf","Orianna","Pantheon","Poppy","Quinn","Rammus","Rek\'Sai","Renekton","Rengar",
                        "Riven","Rumble","Ryze","Sejuani","Shaco","Shen","Shyvana","Singed","Sion","Sivir","Skarner","Sona","Soraka","Swain",
                        "Syndra","Talon","Taric","Teemo","Thresh","Tristana","Trundle","Tryndamere","Twisted Fate","Twitch","Udyr","Urgot","Varus",
                        "Vayne","Veigar","Vel\'Koz","Vi","Viktor","Vladimir","Volibear","Warwick","Wukong","Xerath","Xin Zhao","Yasuo","Yorick","Zac",
                        "Zed","Ziggs","Zilean","Zyra"};

void createChamp(int champNumber, string summonerName)
{
    ifstream championData("championData.txt");
    if(!championData.is_open()){
        cout << "Error, file not found" << endl;
    }
    else{
        GotoLine(championData, champNumber*18);
        float champStats[18];
        for(int it = 0; it < 18; it++) //loop through input file
        {
            string line;
            getline(championData, line);
            champStats[it] = atof(line.c_str());
        }
        int champType = 1;  //0: no resource, 1: mana, 2: energy, 3: health, 4: fury, 5: ferocity, 6: rage, 7: heat
        switch(champNumber)
        {
            case 0: //Aatrox
                champType = 3;
            case 2: //Akali
                champType = 2;
            case 18: //Dr. Mundo
                champType = 3;
            case 28: //Garen
                champType = 0;
            case 29: //Gnar
                champType = 6;
            case 44: //Katarina
                champType = 0;
            case 46: //Kennen
                champType = 2;
            case 50: //Lee Sin
                champType = 2;
            case 61: //Mordekaiser
                champType = 3;
            case 75: //Rek'Sai
                champType = 4;
            case 76: //Renekton
                champType = 4;
            case 77: //Rengar
                champType = 5;
            case 78: //Riven
                champType = 0;
            case 79: //Rumble
                champType = 7;
            case 83: //Shen
                champType = 2;
            case 84: //Shyvana
                champType = 4;
            case 99: //Tryndamere
                champType = 4;
            case 110: //Vladimir
                champType = 3;
            case 116: //Yasuo
                champType = 0;
            case 118: //Zac
                champType = 3;
            case 119: //Zed
                champType = 2;
        }
        if(champType == 0)
        {
            champion champ (champStats, "Cooldown", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 1)
        {
            champion champ (champStats, "Mana", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 2)
        {
            champion champ (champStats, "Energy", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 3)
        {
            champion champ (champStats, "Health", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 4)
        {
            champion champ (champStats, "Fury", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 5)
        {
            champion champ (champStats, "Ferocity", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 6)
        {
            champion champ (champStats, "Rage", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
        else if(champType == 7)
        {
            champion champ (champStats, "Heat", champs[champNumber], summonerName);
            champList.push_back(champ);
        }
    }
}

vector<string> stringSplit(string toSplit, char tokens[], int size)
{
    vector<string> splitString;
    int stringStart = 0;
    for(unsigned int iter = 0; iter < toSplit.size(); iter++)
    {
        char currChar = toSplit[iter];
        if(iter == toSplit.size()-1 && stringStart != -1 && searchCharArray(tokens, currChar, size) == -1)
        {
            splitString.push_back(toSplit.substr(stringStart));
        }
        if(searchCharArray(tokens, currChar, size) != -1)
        {
            if(stringStart != -1)
            {
                splitString.push_back(toSplit.substr(stringStart, iter-stringStart));
                stringStart = -1;
                iter--;
            }
            else
            {
                stringStart = iter+1;
            }
        }
    }
    return splitString;
}

void testMatchup(champion champ1, champion champ2)
{
    double trueADChamp1 = champ1.calcADDealt(champ2);
    double trueADChamp2 = champ2.calcADDealt(champ1);
    cout << "Each autoattack by " << champ1.summonerName << " will deal " << trueADChamp1 << " damage." << endl;
    cout << "Each autoattack by " << champ2.summonerName << " will deal " << trueADChamp2 << " damage." << endl;
    double deathTimeChamp1 = champ1.health / (champ2.AS * trueADChamp2);
    int deathAmountChamp1 = ceil(champ1.health / trueADChamp2);
    cout << "It will take " << deathAmountChamp1 << " attacks from " << champ2.summonerName << " for " << champ1.summonerName << " to die." << endl;
    cout << "It will take " << deathTimeChamp1 << " seconds for " << champ1.summonerName << " to die." << endl;
    cout << endl;
    double deathTimeChamp2 = champ2.health / (champ1.AS * trueADChamp2);
    int deathAmountChamp2 = ceil(champ2.health / trueADChamp2);
    cout << "It will take " << deathAmountChamp2 << " attacks from " << champ1.summonerName << " for " << champ2.summonerName << " to die." << endl;
    cout << "It will take " << deathTimeChamp2 << " seconds for " << champ2.summonerName << " to die." << endl;
}

int main()
{
    CURL* curlObj;
    curl_global_init(CURL_GLOBAL_ALL);
    curlObj = curl_easy_init();
    curl_easy_setopt(curlObj, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curlObj, CURLOPT_URL, "https://na.api.pvp.net/api/lol/na/v1.4/summoner/by-name/RiotSchmick?api_key=732bcfd6-2dbb-4507-ab0f-560b7d79eead");
    curl_easy_setopt(curlObj, CURLOPT_WRITEFUNCTION, &writeCallback);

    //curl_easy_perform(curlObj);

    char tokens[] = {'{', '}', ':', ','};
    vector<string> gameStats = stringSplit(curlData, tokens, 4);
    for(unsigned int iter = 0; iter < gameStats.size(); iter++)
    {
        cout << gameStats[iter] << endl;
    }

    cout << "What map are you playing on? ";
    getline(cin, map);

    string champName = " ";
    string summonerName = " ";
    cout << "Enter each champion in your game, one per line" << endl;
    while(champName != "" && summonerName != "")
    {
        cout << "Enter the summoner's name: ";
        getline(cin, summonerName);
        if(summonerName == "")
        {
            break;
        }
        cout << "Enter their champion: ";
        getline(cin, champName);
        int champNum = searchStringArray(champs, champName, 123);
        if(champNum == -1)
        {
            cout << "That is not a champion recognized by this calculator." << endl;
            continue;
        }
        createChamp(champNum, summonerName);
    }
    cout << endl << endl;
    string command;
    while(command != "quit")
    {
        cout << "Enter a command: ";
        getline(cin, command);

        char tokens[] = {' '};
        vector<string> brokenDown = stringSplit(command, tokens, 1);

        vector<champion> matchupList;
        if(find(brokenDown.begin(), brokenDown.end(), "matchup") != brokenDown.end())
        {
            for(unsigned int iter = 0; iter < champList.size(); iter++)
            {
                if(champList[iter].summonerName == brokenDown[1] || champList[iter].summonerName == brokenDown[2])
                {
                    matchupList.push_back(champList[iter]);
                }
            }
            testMatchup(matchupList[0], matchupList[1]);
        }
    }
    Sleep(100000);
    curl_easy_cleanup(curlObj);
    curl_global_cleanup();
    return 0;
}

/*CHAMPION LIST
1. Aatrox
2. Ahri
3. Akali
4. Alistar
5. Amumu
6. Anivia
7. Annie
8. Ashe
9. Azir
10. Blitzcrank
11. Brand
12. Braum
13. Caitlyn
14. Cassiopeia
15. ChoGath
16. Corki
17. Darius
18. Diana
19. DrMundo
20. Draven
21. Elise
22. Evelynn
23. Ezreal
24. Fiddlesticks
25. Fiora
26. Fizz
27. Galio
28. Gangplank
29. Garen
30. Gnar
31. Gragas
32. Graves
33. Hecarim
34. Heimerdinger
35. Irelia
36. Janna
37. JarvanIV
38. Jax
39. Jayce
40. Jinx
41. Kalista
42. Karma
43. Karthus
44. Kassadin
45. Katarina
46. Kayle
47. Kennen
48. KhaZix
49. KogMaw
50. LeBlanc
51. LeeSin
52. Leona
53. Lissandra
54. Lucian
55. Lulu
56. Lux
57. Malphite
58. Malzahar
59. Maokai
60. MasterYi
61. MissFortune
62. Mordekaiser
63. Morgana
64. Nami
65. Nasus
66. Nautilus
67. Nidalee
68. Nocturne
69. Nunu
70. Olaf
71. Orianna
72. Pantheon
73. Poppy
74. Quinn
75. Rammus
76. Rek'Sai
77. Renekton
78. Rengar
79. Riven
80. Rumble
81. Ryze
82. Sejuani
83. Shaco
84. Shen
85. Shyvana
86. Singed
87. Sion
88. Sivir
89. Skarner
90. Sona
91. Soraka
92. Swain
93. Syndra
94. Talon
95. Taric
96. Teemo
97. Thresh
98. Tristana
99. Trundle
100. Tryndamere
101. TwistedFate
102. Twitch
103. Udyr
104. Urgot
105. Varus
106. Vayne
107. Veigar
108. Vel'Koz
109. Vi
110. Viktor
111. Vladimir
112. Volibear
113. Warwick
114. Wukong
115. Xerath
116. XinZhao
117. Yasuo
118. Yorick
119. Zac
120. Zed
121. Ziggs
122. Zilean
123. Zyra
END CHAMP LIST*/
