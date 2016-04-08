// Evan Grissino
// 04/06/2016
// PID object class

class PID {
    private:
        int P, I, D;
        int Integrator, Derivator;
        int Integrator_max, Integrator_min;
        double P_val, I_val, D_val;
    
    public:
        double set_point, error, PID_const;
    
    PID(double set, double init) {
        P = 2;
        I = 1;
        D = 0;
        
        Derivator = 0;
        Integrator = 0;
        Integrator_max = 100;
        Integrator_min = -100;
        PID_const = 0.1;
        
        P_val = 0;
        I_val = 0;
        D_val = 0;
        
        set_point = set;
        error = init - set;
    };
    
    double update(double current) {
        error = set_point - current;
        P_val = P * error;
        D_val = D * (error - Derivator);
        Derivator = error;
        
        Integrator = Integrator + error;
        if (Integrator > Integrator_max) {
            Integrator = Integrator_max;
        }
        else {
            if (Integrator < Integrator_min) {
                Integrator = Integrator_min;
            };
        };
        
        I_val = Integrator * I;
            
        return (P_val + I_val + D_val) * PID_const;
    };  
};