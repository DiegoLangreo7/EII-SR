//DIEGO GARCIA GONZALEZ UO294255

tabla();

// FIGURA FINAL 
module tabla() {
    difference() {
        plataformaMasEspejo();
        tuercasBujeroCostado();
    }
}

// LAS DOS PARTES DE LA PLATAFORMA
module plataformaMasEspejo() {
    // PLATAFORMA ORIGINAL
    plataformaFinal();
    
    // ESPEJO
    espejo();
}

// PLATAFORMA CON TODO ------------------------------------
module plataformaFinal() {
    // BORDE IZQUIERDO
    hull() {
        translate([5, 27, 1.5])
            cylinder(h = 3, d = 8, center = true);
        translate([-22.1, 27.1, 1.5])
            cylinder(h = 3, d = 8, center = true);
    }
    
    // BORDE DERECHO
    hull() {
        translate([5, -27, 1.5])
            cylinder(h = 3, d = 8, center = true);
        translate([-22.12, -27.2, 1.5])
            cylinder(h = 3, d = 8, center = true);
    }
    
    // PLATAFORMA
    difference() {
        plataformaConMonturas();
        bahia();
        agujeros();
        tuercas();
        cajoneras();
    }
}

// PLATAFORMA BASE -----------------------------------------
module plataformaBase() {
    translate([-26, -28, 0]) {
        cube([31, 56, 3]);
    }
}

// PLATAFORMA CON MONTURAS ---------------------------------
module plataformaConMonturas() {
    plataformaBase();
    monturasD4();
    mirror([0, 1, 0]) {
        monturasD4();
    }
}

// LOS AGUJEROS QUE SON 4-----------------------------------
module agujeroD4() {
    translate([-19.5, -14.2, 1]) {
        cylinder(h = 20, r = 1.7, center = true, $fn = 200);
    }
}

// AGUJEROS DEL LADO NATURAL -------------------------------
module agujeros() {
    agujeroD4();
    
    mirror([1, 0, 0]) {
        translate([39, 28.5, 1]) {
            agujeroD4();
        }
    }
}

// LAS 4 MONTURAS DE ARRIBA---------------------------------
module monturasD4() {
    translate([-26, 11.51, 0]) {
        cube([16, 8.5, 9]);
    }
}

// HUECO CON FORMA DE TUERCA -------------------------------
module tuerca() {
    rotate([0, 0, 30]) { 
        translate([-24, -2.7, 8]) {
            cylinder(h = 3, r = 3.15, $fn = 6);
        } 
    }
}

// PAREJA DE TUERCAS ---------------------------------------
module tuercas() {
    tuerca();
    mirror([0, 1, 0]) {
        tuerca();
    }
}

// CAJONERA DE LA MONTURA
module cajonera() {
    translate([-25.5, -20, 3]) {
        cube([12.5, 8.5, 3]);
    }
}

// PAREJA DE CAJONERAS ---------------------------------------
module cajoneras() {
    cajonera();
    mirror([0, 1, 0]) {
        cajonera();
    }
}

// BAHIA DE BARCOS -------------------------------------------
module bahia() {
    translate([-33, -11.5, -1]) {
        cube([20, 23, 4.1]);
    }
}

// LA TUERCA DEL COSTADO ---------------------------------------
module tuercaBujeroCostado() {
    rotate([0, 0, 90]) {
        translate([44, -5.5, -7]) {
            tuerca();
        }
    }
    
    translate([39.4, 38.7, 1]) {
        agujeroD4();
    }
}

// PAREJA DE TUERCAS DEL COSTADO -------------------------------
module tuercasBujeroCostado() {
    tuercaBujeroCostado();
    translate([10,0,0]) {
        mirror([1, 0, 0]) {
            tuercaBujeroCostado();
        }
    }
}


// ESPEJO ----------------------------------------------------
module espejo() {
    translate([10, 0, 0]) {
        mirror([1, 0, 0]) {
            plataformaFinal();
        }
    }
}
