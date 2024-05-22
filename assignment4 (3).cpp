#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//This function has the user enter a valid number of years to simulate growth and then checks to make sure it is a valid integer.
unsigned int check_good_int() {
    string user_str;
    int i;
    cout<<"Enter the number of years to simulate growth: ";
    do {
        cin>> user_str;
        for (i=0; i<user_str.length(); i++) {
            if (user_str.at(i) < '0' || user_str.at(i) > '9') {
                cout <<"Error. Please enter a valid integer: ";
                break;
            }
        }
    } while (i<user_str.length());
    return stoi(user_str);
}

//This function has the user enter a valid tree diameter or height.
double enter_basic_input(string input_wanted) {
  string user_str;
  int i;
  int x;
  cout << "Enter the tree "<<input_wanted<<" (cm): ";
  do {
    cin >> user_str;
    int num_of_decimals = 0;
    for (i = 0; i < user_str.length(); i++) {
      if (user_str.at(i) == '.') {
        num_of_decimals++;
      }
      if (((user_str.at(i) < '0' || user_str.at(i) > '9') && user_str.at(i) != '.') || num_of_decimals > 1) {
        cout << "Error. Please enter a valid "<<input_wanted<<": ";
        break;
      }
    }
  } while (i < user_str.length());
  return stod(user_str);
}


//This has the user enter a valid growth rate
double check_good_double(string growth_rate) {
  string user_str;
  int i;
  int x;
  cout << "Enter the "<<growth_rate<<" growth rate (cm): ";
  do {
    cin >> user_str;
    int num_of_decimals = 0;
    for (i = 0; i < user_str.length(); i++) {
      if (user_str.at(i) == '.') {
        num_of_decimals++;
        } if (((user_str.at(i) < '0' || user_str.at(i) > '9') && user_str.at(i) != '.') || num_of_decimals > 1) {
        cout << "Error. Please enter a valid growth rate: ";
        break;
    }
    }
  } while (i < user_str.length());
  return stod(user_str);
}

//This function checks to see if the entered diameter growth rate is within specified parameters and then reprompts the user to enter a valid one if it is not
double check_growth_rate_diameter (double min, double max) {
    double d_actual = check_good_double("diameter");
    while (cin.fail()||d_actual<min||d_actual>max) {
        cin.clear();
        cin.ignore(1000, '\n');
        d_actual = check_good_double("diameter");
    }
    return d_actual;
}

//This function checks to see if the entered height growth rate is within specified parameters and then reprompts the user to enter a valid one if it is not
double check_growth_rate_height (double min, double max) {
    double h_actual = check_good_double("height");
    while (cin.fail()||h_actual<min||h_actual>max) {
        cout<<"Invalid growth rate for this species. Please enter a valid growth rate: ";
        cin.clear();
        cin.ignore(1000, '\n');
        h_actual= check_good_double("height");
    }
    return h_actual;
}

//This function calls another function and gives it min and maximum values to check if the diameter growth rate falls under and then reprompts them if it doesn't
double growth_rate_d (int species) {
    switch (species) {
        case 1:
        return check_growth_rate_diameter(1.3, 5.1);
        case 2:
        return check_growth_rate_diameter(0.5, 2.5);
        case 3:
        return check_growth_rate_diameter(0,0.499999999999999999999999999);
        default:
        return 0; 
    }
}

//This function calls another function and gives it min and maximum values to check if the height growth rate falls under and then reprompts them if it doesn't
double growth_rate_h (int species) {
    switch (species) {
        case 1:
        return check_growth_rate_height(60,150);
        case 2:
        return check_growth_rate_height(30,90);
        case 3:
        return check_growth_rate_height(0,29.9999999999999999999999999999);
        default:
        return 0;
    }
}

//This function has the user select a valid species type (1-3, from fast to slow)
unsigned int check_species() {
    string user_str;
    int i;
    cout<<"Enter the species (1-fast, 2-medium, 3-slow): ";
    do {
        cin>> user_str;
        for (i=0; i<user_str.length(); i++) {
            if (user_str.at(i) < '1' || user_str.at(i) > '3'||user_str.length()>1) {
                cout <<"Error. Please enter a valid species type: ";
                break;
            }
        }
    } while (i<user_str.length());
    return stoi(user_str);
}

//This function has calculate the cry weight of the tree and returns it to main
double c_dry_weight (double diameter, double height ) {
    double green_weight=0;
    if (diameter <28) {
        green_weight = 0.0577*pow(diameter, 2) * height;
    } else {
        green_weight = 0.0346*pow(diameter, 2) * height;
    } 
    double dry_weight = (green_weight*0.725)*1.2;
    return dry_weight;
}

//This function calculates the amount of strored carbon from the dry weight and then returns it to main
double carbon_s(double dry_weight) {
    double carbon_stored = (0.5*dry_weight)/1000;
    return carbon_stored;
}

//This function calculates the carbon absorbed from the stored carbon and returns it to main
double carbon_abs(double carbon_s, double height) {
        double carbon_absorbed = 3.67*carbon_s;
    return carbon_absorbed;
}

//This function outputs the the amount of carbon absorbed per year and then returns the total amount of carbon absorbed over the extra years
double other_years_carbon (double height, double diameter, double h_growth, double d_growth, int num_years, double carbon_absorbed) {
    int i;
    double x= 0;
    for (i=0; i<num_years; i++) {
        height = height+h_growth;
        diameter = diameter+d_growth;
        double new_carbon =carbon_abs(carbon_s(c_dry_weight(diameter, height)), height)-carbon_absorbed;
        carbon_absorbed= carbon_abs(carbon_s(c_dry_weight(diameter, height)), height);
        x += new_carbon;
        if (height >=30.48) {
             cout<<"Year "<<(i+1)<<": The total CO2 absorbed this year is: "<<new_carbon<<" kg"<<endl;
        } else {
            cout<<"Year "<<(i+1)<<": The tree is too small to absorb much CO2 yet"<<endl;
        }

 }
 return x;
}

//This function prints out the current stats about the tree without taking the simulated years into acccount
void first_print(double dry_weight, double carbon_stored, double carbon_absorbed, double height) {
    cout<<'\n'<<"To Date: "<<endl;
    cout<<"The current dry weight is: "<<dry_weight<<" kg"<<endl;
    cout<<"The total carbon stored is: "<<carbon_stored<<" kg"<<endl;
    if (height >=30.48) {
             cout<<"The total CO2 absorbed is: "<<carbon_absorbed<<" kg"<<endl<<endl;
        } else {
            cout<<"The tree is too small to absorb much CO2 yet"<<endl<<endl;;
        }

}

//This function prints out the end stats about the tree after taking into account the simulatd years
void endprint(double height, double diameter, double h_growth, double d_growth, int num_years, double total_carbon) {
    int i;
    double n_height = height;
    double n_diameter = diameter;
    for (i=0; i<num_years; i++) {
        n_height = n_height+h_growth;
        n_diameter = n_diameter+d_growth;
    } 
    cout<<'\n'<<"Over an additional "<<num_years<<" years,"<<endl;
    cout<<"The diameter will grow: "<<n_diameter-diameter<<" cm"<<endl;
    cout<<"The height will grow: "<<n_height-height<<" cm"<<endl;
    if (n_height >=30.48) {
            cout<<"The total extra CO2 absorbed will be: "<<total_carbon<<" kg"<<endl;
        } else {
            cout<<"The tree is still too small to absorb much CO2 yet"<<endl;
        }
}

//This function calls other functions so that the whole program works. Basically, it is a central hub to call other functions
int main () {
    int species = check_species();
    double diameter = enter_basic_input("diameter");
    double diameter_growth = growth_rate_d(species);
    double height = enter_basic_input("height");
    double height_growth = growth_rate_h(species);
    int num_years = check_good_int();
    double dry_weight = c_dry_weight(diameter, height);
    double carbon_stored = carbon_s(dry_weight);
    double carbon_absorbed = carbon_abs(carbon_stored, height);
    first_print(dry_weight, carbon_stored, carbon_absorbed, height);
    double total_carbon = other_years_carbon(height, diameter, height_growth, diameter_growth, num_years, carbon_absorbed);
    endprint(height, diameter, height_growth, diameter_growth, num_years, total_carbon);
}