//DIEGO GARCIA GONZALEZ UO294255
 
$fn_esfera_pequena = 25; // Resolución para esferas pequeñas
$fn_bola_principal = 50; // Resolución para la bola principal
$fn_dedo = 30; // Resolución para los dedos
$radio_dedo = 5; // Radio de los dedos

module pies() {
    bolaPrincipal();
    dedoDelMedio();
    dedoIzquierda();
    dedoDerecha();
    pelotaMedio();
    pelotaIzquierda();
    pelotaDerecha();
    pelotaAtras();
}

// BOLA PRINCIPAL ----------------------------------------------------------
module bolaPrincipal() {
    difference() {
        translate([0, 0, 5])
            sphere(r = 25, $fn = $fn_bola_principal);
        translate([0, 0, -25])
            cube([500, 500, 51], true);
        
        translate([14.7, -20, -26])
            cube([20, 50, 52]);
        
        translate([-14, -40, 15])
            cube([35, 50, 30]);
        
        translate([-20, -6, 15])
            cube([7, 4, 15]);
    }
}

// DEDO DEL MEDIO -----------------------------------------------------
module dedoDelMedio() {
    difference() {
        translate([-6, -30, 0]) {
            rotate([90, 0, -10]) {
                cylinder(h = 25, r = $radio_dedo, center = true, $fn = $fn_dedo); 
            }
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 50, 20]);
        }
    }
}

// DEDO IZQUIERDA -----------------------------------------------------
module dedoIzquierda() {
    difference() {
        translate([-25, -20, 0]) {
            rotate([90, 0, -26]) {
                cylinder(h = 24.3, r = $radio_dedo, center = true, $fn = $fn_dedo);  
            }
        }
        
        translate([-50, -59, -19.5]) {
            cube([90, 90, 20]);
        }
    }
}

// DEDO DERECHA ---------------------------------------------------------
module dedoDerecha() {
    difference() {
        translate([12, -25, 0]) {
            rotate([90, 0, 24]) {
                cylinder(h = 25, r = $radio_dedo, center = true, $fn = $fn_dedo); 
            }
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 50, 20]);
        }
    }
}

// PELOTA MEDIO ------------------------------------------
module pelotaMedio() {
    difference() {
        translate([-6.5, -37, 0]) {
            sphere(r = 8, $fn = $fn_esfera_pequena);
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 1000, 20]);
        }
    }
}

// PELOTA IZQUIERDA -----------------------------------------
module pelotaIzquierda() {
    difference() {
        translate([-28.5, -27, 0]) {
            sphere(r = 7, $fn = $fn_esfera_pequena);
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 1000, 20]);
        }
    }
}

// PELOTA DERECHA --------------------------------------------
module pelotaDerecha() {
    difference() {
        translate([17.6, -35, 0]) {
            sphere(r = 9, $fn = $fn_esfera_pequena);
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 1000, 20]);
        }
    }
}

// PELOTA ATRAS  -----------------------------------------
module pelotaAtras() {
    difference() {
        translate([1, 33, 0]) {
            sphere(r = 15, $fn = $fn_bola_principal);
        }
        
        translate([-40, -59, -19.5]) {
            cube([70, 1000, 20]);
        }
    }
}


