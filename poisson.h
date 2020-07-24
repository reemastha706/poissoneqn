#pragma once

class Voltage{
    protected:
    int nx;
    int ny;
    float Vup_;
    float Vdown_;
    float step_size_;
    float **V;
    float **source;
    float **R;

    public:
    Voltage(int nx1, int ny1, float step_size,float Vup, float Vdown);
    void voltage_initialization();
    float norm();
    void calculate_voltage();
    void freeVoltage(float **variable,float nx,float ny);

    ~Voltage();
};

class Electricfield : public Voltage{
    private:
    float **Ex;
    float **Ey;
    float **Ex_prime;
    float **Ey_prime;
    float **E;

    public:
    Electricfield(int nx1,int ny1,float step_size,float Vup, float Vdown);
    void Electricfield_initialization();
    void calculate_electricfield();
    void freeElectricfield(float **variable,float nx,float ny);

    ~Electricfield();  

};

