#include <iostream>
using namespace std;

//This function checks to see if the user has entered a good positive integer and reprompts the user until they have before sending a valid entry to main
int good_input(int input_to_check) { 
    while (cin.fail()||input_to_check <0) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invalid entry. Please enter a positive integer"<<endl;
        cin>>input_to_check;
}
    int checked_input = input_to_check;
    return checked_input;
}

//This function calculates the pulse pressure (pp) by subtracting the diastolic pulse pressure from the systolic pulse pressure before returning the pp to main
int cal_pulsepressure(int sp, int dp) {
    int pp = sp-dp;
    return pp;
}

//This function checks if the pulse prssure (PP) is more than 80 or not (high or normal) before printing a message to the user telling them whether their PP is normal or high along with their PP
void pulsepressurestatus (int pulsep) {
    if (pulsep > 80) {
        cout << "Your pulse pressure is high: " << pulsep <<" mmHG" <<endl;
    } else {
        cout <<"Your pulse pressure is normal: " <<pulsep <<" mmHG" <<endl;
    }
}

//This function calculates mean arterial pressure (MAP) by dividing pulse pressure by 3 and then adding diastolic pressure. The function then prints out the user's MAP.
double map (double pp, double dp) {
    double mean_pressure =  (float) 1/3*pp+dp;
    cout << "Your mean arterial pressure is: " <<mean_pressure<< " mmHG"<<endl;
    return mean_pressure;
}

//This function prints out a message to the user telling them whether or not their mean arterial pressure (map) is within acceptable limits or if they should seek medical assistance (map <60)
void meanpressure_status (double map) {
    if (map < 60) {
        cout << "You should seek medical assistance" <<endl;
    } else {
        cout <<"Your mean arterial pressure is within acceptable limits" <<endl;
    }
}

/* This is the main function that initally takes the user's syatolic and disatolic pressure before calling the good_input function to see 
the inputs are valid positve integers. Then, the main function calls other functions such as ones calculating the pulse pressure and mean arterial pressure
along with their associated check threshold and print message functions.*/

int main() {
int sp {0};
int dp {0};
cout<<"Enter systolic pressure"<<endl;
cin>>sp;
sp = good_input(sp);
cout<<"Enter diastolic pressure"<<endl;
cin>>dp;
dp = good_input(dp);
double pulsepressure = cal_pulsepressure(sp, dp);
pulsepressurestatus(pulsepressure);
double mean_pressure = map(pulsepressure, dp);
meanpressure_status(mean_pressure);
}