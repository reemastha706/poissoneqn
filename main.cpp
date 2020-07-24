#include "poisson.cpp"

int main(){
    int nx1,ny1;
    float step_size;
    float Vup, Vdown;
    int num;
    cout << "....................Poisson's Equation Solver.......................\n";
    cout << "\n\n\n";
    cout <<"Enter the length grid of the box\n";
    cin >> nx1;
    cout << "Enter the width grid of the box\n";
    cin >> ny1;
    cout <<"Stepsize:\n";
    cout << "1 : extra fine \n ";
    cout << "2 :  fine \n";
    cout << "3 : normal \n";
    cin >> num;
    switch(num){
        case 1:
            step_size = 0.01;
            break;
        case 2:
            step_size = 0.5;
            break;
        case 3:
            step_size = 1.0;
            break;

    }
    cout  << "Your image is of grid lines" << nx1  <<"x" << ny1<<"............"<<endl;
    cout <<"High potential \n";
    cin >> Vup;
    cout <<"Low Potential \n";
    cin >> Vdown;
    cout <<"Loading....."<<endl;
    Electricfield e(nx1,ny1,step_size,Vup,Vdown);
    e.calculate_electricfield();
    cout <<"Your output is ready."<<endl;

    

}