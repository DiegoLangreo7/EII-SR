//DIEGO GARCIA GONZALEZ UO294255

d1 = 2.1;  // Altura de los cilindros
fn = 50;   // Resolución de los cilindros
d_suelo = [47, 15, 3]; // Dimensiones del suelo
d_pared = [47, 3, 23]; // Dimensiones de la pared

ojosFinal();

// FIGURA -----------------------------------------------------------
module ojosFinal() {
    difference() {
        base();
        ojos();
        surcoParedArriba();
        surcoParedAbajo();
        surcoBujero();
        surcoSuelo();
    }  
}

// SUELO -----------------------------------------------------------
module suelo() {
    translate([23.5, 7.5, 1.5])
        cube(d_suelo, true); 
}

// PARED -----------------------------------------------------------
module pared() {
    translate([23.5, 13.5, 11.5])
        cube(d_pared, true);
}

// BASE -----------------------------------------------------------
module base() {
    suelo();
    pared();
}

// OJO -----------------------------------------------------------
module ojo() {
    translate([10.4, 13.5, 13])
        sphere(r = 8.2, $fn = fn);
}

// OJOS -----------------------------------------------------------
module ojos() {
    ojo();
    translate([47, 0, 0]) {
        mirror([-1, 0, 0]) {
            ojo();
        }
    }
}

// SURCO PARED ARRIBA -----------------------------------------------------------
module surcoParedArriba() {
    hull() {
        rotate([90, 0, 0]) {
            translate([18, 21.5, -13]) {
                surcoArriba();
            }
        }
        rotate([90, 0, 0]) {
            translate([29, 21.5, -13]) {
                surcoArriba();
            }
        }
    }
}

// SURCO PARED ABAJO -----------------------------------------------------------
module surcoParedAbajo() {
    hull() {
        rotate([90, 0, 0]) {
            translate([18.3, 6, -13]) {
                surcoMedio();
            }
        }
        rotate([90, 0, 0]) {
            translate([28.7, 6, -13]) {
                surcoMedio();
            }
        }
    }
}

// SURCO SUELO -----------------------------------------------------------
module surcoSuelo() {
    hull() {
        translate([10, 7.5, 0]) {
            surcoAbajoPunta();
        }
        translate([40, 7.5, 0]) {
            surcoAbajoPunta();
        }
        translate([23.5, 7.5, 0]) {
            surcoAbajoMedio();
        }
    }
}

// SURCO BUJERO -----------------------------------------------------------
module surcoBujero() {
    translate([23.5, 7.5, 0]) {
        cylinder(h = d1, d = 7.5, $fn = fn, center = true);
    }
}

// SURCO ARRIBA -----------------------------------------------------------
module surcoArriba() {
    cylinder(h = d1, d = 2.5, $fn = fn, center = true);
}

// SURCO MEDIO -----------------------------------------------------------
module surcoMedio() {
    cylinder(h = d1, d = 4.5, $fn = fn, center = true);
}

// SURCO ABAJO PUNTA -----------------------------------------------------------
module surcoAbajoPunta() {
    cylinder(h = d1, d = 5, $fn = fn, center = true);
}

// SURCO ABAJO MEDIO -----------------------------------------------------------
module surcoAbajoMedio() {
    cylinder(h = d1, d = 6, $fn = fn, center = true);
}
