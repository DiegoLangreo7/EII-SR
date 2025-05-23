//DIEGO GARCIA GONZALEZ UO294255

bracket(); 
fn_cylinder = 25;
fn_cylinder_2 = 19;

// FIGURA FINAL --------------------------------------

module bracket() {
    parDeTapasCirculares();
    parDeTapasCuadradas();
    
}

// PAREJA DE TAPAS CIRCULARES  ------------------------
module parDeTapasCirculares(){
    tapaCircularConAgujeros();
//    translate([-45, -14.2, 0]) {
//        mirror([1, 0, 0]) {
//            tapaCircularConAgujeros();
//        }
//    }
}

// PAREJA DE TAPAS CUADRADAS  ------------------------
module parDeTapasCuadradas(){
    tapaCuadradaConAgujeros();
//    translate([-45, -14.2, 0]) {
//        mirror([1, 0, 0]) {
//            tapaCuadradaConAgujeros();/
//        }
//    }
}
    

module tapaCuadradaConAgujeros() {
    difference() {
        tapaCuadrada();
        rotate([90, 0, 0]) { 
            translate([-13.8, 8.2, -3.5]) {
                cylinder(h = 4, r = 1, $fn = fn_cylinder);
            }
        }
        rotate([90, 0, 0]) { 
            translate([-26.3, 8.2, -3.5]) {
                cylinder(h = 4, r = 1, $fn = fn_cylinder);
            }
        }
    }
}

module tapaCuadrada() {
    translate([-29.75, 0, 0])
        cube([25.5, 3, 12.7]);
}

module tapaCircularConAgujeros() {
    difference() {
        tapaCircular();
        rotate([0, 90, 0]) { 
            translate([-3, 22.25, -7.3]) {
                cylinder(h = 4, r = 1, $fn = fn_cylinder);
            }
        }
        rotate([0, 90, 0]) { 
            translate([-3, 9.7, -7.3]) {
                cylinder(h = 4, r = 1, $fn = fn_cylinder);
            }
        }
    }
}

module tapaCircular() {
    translate([-7.25, 0, 0]) {
        cube([3, 20, 12.7]);
    }
    translate([-7.25, 0, 0]) {
        cube([3, 25.4, 7]);
    }
    rotate([0, 90, 0]) { 
        translate([-7.75, 20.5, -7.25]) {
            cylinder(h = 3, r = 5, $fn = fn_cylinder_2);
        }
    }
}


