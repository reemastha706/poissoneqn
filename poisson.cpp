#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<vector> 
#include "poisson.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

using namespace std;

Voltage::Voltage(int nx1, int ny1, float step_size,float Vup, float Vdown){
    nx = nx1;
    ny = ny1;
    step_size_= step_size;
    Vup_ = Vup;
    Vdown_ = Vdown;
}

void Voltage::freeVoltage(float **variable, float nx, float ny){
    for(int i = 0;i<nx;i++){
        delete[] variable[i];
    }
    delete[] variable;
}

void Voltage::voltage_initialization(){    
    V = new float*[nx];
    source = new float*[nx];
    R = new float*[nx];
    for(int i = 0;i<nx;i++)
    {
        V[i] = new float[ny]();
        source[i] = new float[ny]();
        R[i] = new float[ny];
    }

    for(int j = 30;j<ny-30;j++){
        source[(nx/2) - 10][j] = Vup_;
        source[(nx/2) + 10][j] = Vdown_;
    }

}

float Voltage::norm(){   //L2-norm 
    float sum = 0.0;
    for(int i = 0;i<nx;i++)
    {
        for(int j = 0;j<ny;j++)
        {
            sum += pow(R[i][j],2);
        }
    }
    return sqrt(sum);
}

void Voltage::calculate_voltage(){
    voltage_initialization();   //creating a matrix V and initilizing with Dirchilet's boundary condition
    float tolerance = pow(10,-6);
    bool done = true;
    int itr = 0;
    float pi = 3.14;
    float t = cos(pi/nx) + cos(pi/ny);
    float omega = (8 - sqrt(64 - 16*pow(t,2)))/(pow(t,2));  //relaxation parameter
    while(done == true){
        float r = 0.0;
        for(int i = 1;i<nx-1;i++){
            for(int j = 1;j<ny-1;j++)
            {
                float vv = (V[i-1][j] + V[i+1][j] + V[i][j-1] + V[i][j+1] + pow(step_size_,2) * source[i][j])/4.0; 
                R[i][j] = vv - V[i][j];     //correction for SOR
                V[i][j] = V[i][j] + omega* R[i][j];   
            }
        }
        if(norm() >= tolerance){
            itr++;
        }
        else{done = false;}
    }
    
}


Voltage::~Voltage(){}


Electricfield::Electricfield(int nx1,int ny1,float step_size,float Vup, float Vdown):Voltage(nx1,ny1,step_size,Vup,Vdown){
}

void Electricfield::freeElectricfield(float **variable, float nx, float ny){
for(int i = 0;i<nx;i++){
    delete[] variable[i];
}
delete[] variable;
}  

void Electricfield::Electricfield_initialization(){
    Ex = new float*[nx-1];
    Ey = new float*[nx-1];
    Ex_prime = new float*[nx-2];
    Ey_prime = new float*[nx-2];
    

    for(int i = 0;i<nx-1;i++)
    {
        Ex[i] = new float[ny-1];
        Ey[i] = new float[ny-1];
    }  
    for(int i = 0;i<nx-2;i++)
    {
        Ex_prime[i] = new float[ny-2];
        Ey_prime[i] = new float[ny-2];
    
    }    
}
    
void Electricfield::calculate_electricfield(){
    calculate_voltage();
    Electricfield_initialization();
    vector<float> E((nx-2) * (ny-2));
    vector<float> Vnew(nx * ny);

    for(int i = 0;i<nx;i++)
    {
        for(int j = 0;j<ny;j++){
            Vnew.at(ny * i + j) = V[i][j];
        }
    }
    for(int i = 0;i<nx-1;i++)
    {
        for(int j = 0;j<ny-1;j++)
        {
            Ex[i][j] = - (V[i+1][j] - V[i][j])/step_size_;
            Ey[i][j] = - (V[i][j+1] - V[i][j])/step_size_;
        }
    }

        
    for(int i = 0;i<nx-2;i++)
    {
        for(int j = 0;j<ny-2;j++)
        {
            Ex_prime[i][j] = (0.5)*(Ex[i][j] + Ex[i][j+1]);
            Ey_prime[i][j] = (0.5)*(Ey[i][j] + Ey[i+1][j]);
            E.at((ny-2) * i + j) = sqrt(pow(Ex_prime[i][j],2) + pow(Ey_prime[i][j],2));

        }
    }
    const float* ztr = &(Vnew[0]);
    PyObject* mat;
    /*plt::title("Voltage Potential");
    plt::imshow(ztr,nx,ny,1,{},&mat);
    plt::colorbar(mat);
    plt::save("Voltage.png");*/
    
    const float* z = &(E[0]);
    plt::title("Electricfield Intenity");
    plt::imshow(z,nx-2,ny-2,1,{}, &mat);
    plt::colorbar(mat);
    plt::save("Electricfield.png");
    Py_DECREF(mat);
    //delete ztr;
    freeVoltage(V,nx,ny);
    freeVoltage(source,nx,ny);
    freeVoltage(R,nx,ny);
    freeElectricfield(Ex,nx-1,ny-1);
    freeElectricfield(Ey,nx-1,ny-1);
    freeElectricfield(Ex_prime,nx-2,ny-2);
    freeElectricfield(Ey_prime,nx-2,ny-2);


}


Electricfield::~Electricfield(){};



