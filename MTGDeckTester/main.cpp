#include <iostream>
#include <sstream>

using namespace std;

class card{
    public:
    string type;
    string name;
    int power;
    int toughness;
    string effect;
    string mana_type_returned;
    int mana_amount_returned_black;
    int mana_amount_returned_white;
    int mana_amount_returned_green;
    int mana_amount_returned_blue;
    int mana_amount_returned_red;
    bool enter_tapped;
    int mana_cost_black;
    int mana_cost_white;
    int mana_cost_green;
    int mana_cost_blue;
    int mana_cost_red;
    int mana_cost_colorless;
    int mana_cost_converted;
};

card Deck[60];

int main()
{
    int deck_index = 0;
    while(deck_index < 60){
        card next_card;
        cout << "Enter the name of the next card in your deck: ";
        getline(cin, next_card.name);
        cout << "Enter the card type: ";
        getline(cin, next_card.type);
        if(next_card.type.find("creature") != string::npos && next_card.type.find("enchantment") == string::npos){
            cout << "Enter the power of the card: ";
            cin >> next_card.power;
            cout << "Enter the toughness of the card: ";
            cin >> next_card.toughness;
        }
        else if(next_card.type.find("sorcery") != string::npos){
            cout << "Enter the effect of the card: ";
            getline(cin, next_card.effect);
        }
        else if(next_card.type.find("instant") != string::npos){
            cout << "Enter the effect of the card: ";
            getline(cin, next_card.effect);
        }
        else if(next_card.type.find("land") != string::npos){
            cout << "Enter the mana type returned by the card (enter multicolored as \"color1, color2\"): ";
            getline(cin, next_card.mana_type_returned);
            cout << "Enter the mana amount returned by this card (enter as \"color: amount, color: amount\"): ";
            string temp = "";
            getline(cin, temp);
            unsigned black = temp.find("black");
            unsigned white = temp.find("white");
            unsigned green = temp.find("green");
            unsigned blue = temp.find("blue");
            unsigned red = temp.find("red");
            if(black != string::npos){
                string black_temp = temp.substr(black+8, temp.find(",", black)); //the +8 comes from the size of the string "black" + the size of the string ": "
                stringstream black_convert(temp);
                black_convert >> next_card.mana_amount_returned_black;
            }
            if(white != string::npos){
                string white_temp = temp.substr(white+8, temp.find(",", white)); //the +8 comes from the size of the string "white" + the size of the string ": "
                stringstream white_convert(temp);
                white_convert >> next_card.mana_amount_returned_white;
            }
            if(green != string::npos){
                string green_temp = temp.substr(green+8, temp.find(",", green)); //the +8 comes from the size of the string "green" + the size of the string ": "
                stringstream green_convert(temp);
                green_convert >> next_card.mana_amount_returned_green;
            }
            if(blue != string::npos){
                string blue_temp = temp.substr(blue+7, temp.find(",", blue)); //the +7 comes from the size of the string "blue" + the size of the string ": "
                stringstream blue_convert(temp);
                blue_convert >> next_card.mana_amount_returned_blue;
            }
            if(red != string::npos){
                string red_temp = temp.substr(red+6, temp.find(",", red)); //the +6 comes from the size of the string "red" + the size of the string ": "
                stringstream red_convert(temp);
                red_convert >> next_card.mana_amount_returned_red;
            }
            cout << "Does this card come into play tapped? (y/n) ";
            if(cin.get() == 'y'){
                next_card.enter_tapped = true;
            }
            else if(cin.get() == 'n'){
                next_card.enter_tapped = false;
            }
        }
        else if(next_card.type.find("enchantment") != string::npos){
            cout << "Enter the effect of the card: ";
            getline(cin, next_card.effect);
        }
        else if(next_card.type.find("artifact") != string::npos){
            cout << "Enter the effect of the card: ";
            getline(cin, next_card.effect);
        }
        if(next_card.type.find("land") == string::npos){
            cout << "Enter the black mana cost of the card: ";
            cin >> next_card.mana_cost_black;
            cout << "Enter the white mana cost of the card: ";
            cin >> next_card.mana_cost_white;
            cout << "Enter the green mana cost of the card: ";
            cin >> next_card.mana_cost_green;
            cout << "Enter the blue mana cost of the card: ";
            cin >> next_card.mana_cost_blue;
            cout << "Enter the red mana cost of the card: ";
            cin >> next_card.mana_cost_red;
            cout << "Enter the colorless mana cost of the card: ";
            cin >> next_card.mana_cost_colorless;
            next_card.mana_cost_converted = next_card.mana_cost_black + next_card.mana_cost_white +
                                            next_card.mana_cost_green + next_card.mana_cost_blue +
                                            next_card.mana_cost_red + next_card.mana_cost_colorless;
            cout << "Converted mana cost: " << next_card.mana_cost_converted << endl;
        }
        Deck[deck_index] = next_card;
        deck_index++;
        cin.clear(); cin.sync();
    }
    return 0;
}
