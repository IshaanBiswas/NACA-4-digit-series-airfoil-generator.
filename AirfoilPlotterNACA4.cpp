#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double chord1(double x, double p, double m){
    return (m/pow(p,2))*(2*p*x - pow(x,2));
}

double chord2(double x, double p, double m){
    return (m/pow(1-p,2))*((1-2*p)+2*p*x-pow(x,2));
}

double thickness(double x, double t, double c){
    return (t/0.2)*(0.2969*sqrt(x/c) - 0.1260*x/c - 0.3516*pow(x/c,2) + 0.2543*pow(x/c,3) - 0.1015 *pow(x/c,4));
}

int main(){
    int DIGIT, n;
    double c, m, p, x, y, t, xfoil, yfoil, O;

    ofstream CSV("NACA4dig.csv");
    
    cout<<"Enter the Digits of your NACA 4 digit airfoil";
    cin >> DIGIT;
    cout <<"Enter the chord length of your airfoil. ";
    cin >> c;
    cout << " How many points do you want to generate:";
    cin >> n;

    m = ((DIGIT/1000)/100.00)*c;
    p = ((DIGIT % 1000)/100)/10.0*c;
    t = ((DIGIT % 100)/100.0)*c;
    
    for (int i=0; i<= n; i++){
        if(i<=(n/2)){
            x = i * (2*c/n);
            if ( x <= p){
                y = chord1(x, p, m);
                O = atan((chord1(x+0.0001, p, m)-chord1(x, p, m))/0.0001);
            }else{
                y = chord2(x, p, m);
                O = atan((chord2(x+0.0001, p, m)-chord2(x, p, m))/0.0001);
            }
            
            xfoil = x - thickness(x,t,c)*sin(O);
            yfoil = y + thickness(x,t,c)*cos(O);
            
        }else if(i>(n/2) && i<(n+1)/2 ){
            xfoil = c;
            yfoil = 0;
        }else{
            x = c- (i-(n/2))*(2*c/n);
            if ( x <= p){
                y = chord1(x, p, m);
                O = atan((chord1(x+0.0001, p, m)-chord1(x, p, m))/0.0001);
            }else{
                y = chord2(x, p, m);
                O = atan((chord2(x+0.0001, p, m)-chord2(x, p, m))/0.0001);
            }
            xfoil = x + thickness(x,t,c)*sin(O);
            yfoil = y - thickness(x,t,c)*cos(O);
        }
        CSV << xfoil<<','<<yfoil<<endl;
    }
    CSV.close();
    cout<<"file generated";
    return 0;
}