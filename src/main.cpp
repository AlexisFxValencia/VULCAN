#include "SceneManager.h"
#include "ContinuousManager.h"
#include "DiscreteManager.h"
#include "DataManager.h"

#include <iostream>

int main() { 
    cout << "Starting neutronics simulator" << endl;
    DataManager dm;
    dm.read("input_files/input.ns");
    while (!dm.keep_window_closed) {
        if (dm.continuous_simulation){     
            cout << "Starting a continuous simulation" << endl;
            ContinuousManager continuous_manager(dm);
            continuous_manager.continuous_main(dm);
            }
        else {
            cout << "Starting a discrete simulation"  << endl;
            DiscreteManager discrete_manager(dm);
            discrete_manager.discrete_main(dm);
        }
    }
    
    
   
    return 0;



};









