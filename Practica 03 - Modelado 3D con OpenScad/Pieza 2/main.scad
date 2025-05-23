//DIEGO GARCIA GONZALEZ UO294255

use <pies.scad>;  
use <ojos.scad>;  
use <plataforma.scad>;  
use <brackets.scad>;  


translate([0, -20, 45]) {
    rotate([270,0,270]) { 
        bracket();
    }
}

translate([60, -20, 45]) {
    rotate([270,0,270]) { 
        mirror([0,0,1]){
            bracket();
        }
    }
}

translate([25, 0, 60]) {
    rotate([0, 180, 180]) {
        tabla();
    }
}
translate([55, -15, 80]) {
    rotate([0, 0, 180]) {
        ojosFinal();
    }
}
pies();
translate([61, 0, 0]) {
        mirror([1, 0, 0]) {
            pies(); 
        }
    }
 