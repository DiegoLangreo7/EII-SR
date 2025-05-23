class Viajes {
    constructor() {
        this.error = false;
        this.ubicacionesActivadas = {}; 
        this.menuVisible = false;
        this.marcadorActual = null; 
        this.mapaGeoposicionado = null; 
        this.intervaloServidor = null;

        this.ubicaciones = [
            { lat: 43.35497125680212, lng: -5.851532044963847, temp: 12.5, humedad: 75, nombre: "Escuela de Ingeniería Informática" },
            { lat: 43.36351679083699, lng: -5.850723348870346, temp: 14.0, humedad: 80, nombre: "Calle Uría" },
            { lat: 43.36327622737893, lng: -5.885647315358318, temp: 13.2, humedad: 85, nombre: "Las Campas" },
            { lat: 43.30796703415945, lng: -5.696012358783663, temp: 15.8, humedad: 70, nombre: "La Felguera" }
        ];
    }

    generateDynamicMap() {
        const section = document.querySelector("section");
        section.innerHTML = ""; 
        section.insertAdjacentHTML("beforeend", "<h3>Mapa de ubicaciones</h3>");

        const mapaDiv = document.createElement("div");
        mapaDiv.id = "mapa"; 
        mapaDiv.style.height = "500px"; 
        section.appendChild(mapaDiv);

        const centro = this.ubicaciones[0]; 
        if (!this.mapaGeoposicionado) {
            this.mapaGeoposicionado = new google.maps.Map(mapaDiv, {
                zoom: 13,
                center: centro,
                mapTypeId: google.maps.MapTypeId.ROADMAP
            });
        } else {
            this.mapaGeoposicionado.setCenter(centro);
        }

        let menu = document.querySelector("#menuMapa");
        if (!menu) {
            menu = document.createElement("div");
            menu.id = "menuMapa"; 
            menu.style.display = "none"; 
            menu.innerHTML = `
                <p id="infoUbicacion">Has pinchado sobre una ubicación</p>
                <button id="toggleUbicacion">Encender</button>
                <div id="interruptor" class="interruptor apagado"></div>
                <div id="datosAmbientales" style="display:none;"></div>
            `;
            section.appendChild(menu);
        }

        this.ubicaciones.forEach((ubicacion, index) => {
            const marcador = new google.maps.Marker({
                position: ubicacion,
                map: this.mapaGeoposicionado,
                title: `Ubicación ${index + 1}`
            });

            google.maps.event.addListener(marcador, 'click', () => {
                if (this.menuVisible && this.marcadorActual !== marcador) {
                    this.ocultarMenu();
                }

                menu.style.display = "block";
                this.marcadorActual = marcador; 
                this.menuVisible = true; 

                const key = `${ubicacion.lat},${ubicacion.lng}`;

                const infoUbicacion = document.getElementById("infoUbicacion");
                infoUbicacion.textContent = `
                    Has pinchado sobre la ubicación: 
                    ${ubicacion.nombre} 
                    (Latitud: ${ubicacion.lat.toFixed(4)}, Longitud: ${ubicacion.lng.toFixed(4)})
                `;

                const estado = this.ubicacionesActivadas[key] || false;
                this.updateButtonAndSwitch(estado);

                document.getElementById("toggleUbicacion").onclick = () => {
                    const newState = !this.ubicacionesActivadas[key];
                    this.ubicacionesActivadas[key] = newState;
                    this.updateButtonAndSwitch(newState);

                    if (index === 0) {
                        this.buclePeticionServidor(newState);
                    } else {
                        this.mostrarDatosAmbientales(ubicacion, newState);
                    }
                };
            });
        });

        google.maps.event.addListener(this.mapaGeoposicionado, 'click', () => {
            if (this.menuVisible) {
                this.ocultarMenu(); 
            }
        });
    }

    ocultarMenu() {
        const menu = document.querySelector("#menuMapa");
        if (menu) {
            menu.style.display = "none"; 
        }
        this.menuVisible = false; 
        this.marcadorActual = null; 

        const datosAmbientales = document.getElementById("datosAmbientales");
        if (datosAmbientales) {
            datosAmbientales.style.display = "none";
            datosAmbientales.textContent = "";
        }
    }

    updateButtonAndSwitch(estado) {
        const boton = document.getElementById("toggleUbicacion");
        const interruptor = document.getElementById("interruptor");

        if (estado) {
            boton.textContent = "Apagar";
            interruptor.classList.add("encendido");
            interruptor.classList.remove("apagado");
        } else {
            boton.textContent = "Encender";
            interruptor.classList.add("apagado");
            interruptor.classList.remove("encendido");
        }
    }

    buclePeticionServidor(estado) {
        const url = estado ? "http://192.168.61.145/index?encender" : "http://192.168.61.145/index?apagar";
        if (estado) {
            this.intervaloServidor = setInterval(() => {
                fetch(url)
                    .then(response => response.text())
                    .then(data => {
                        const datosAmbientales = document.getElementById("datosAmbientales");
                        datosAmbientales.style.display = "block";
                        datosAmbientales.innerHTML = data;

                        const tempMatch = data.match(/Temperature:\s*(\d+(\.\d+)?)ºC/); 
                        if (tempMatch) {
                            const temperatura = parseFloat(tempMatch[1]);  
                            console.log(temperatura);  

                            if (temperatura > 25) {  
                                alert("¡ALERTA! La temperatura ha superado los 25°C."); 
                            }
                        }

                    })
                    .catch(err => console.error("Error al obtener datos del servidor:", err));
            }, 3000); 
        } else {
            clearInterval(this.intervaloServidor);
            this.intervaloServidor = null;

            fetch(url)
            .then(response => console.log(`Petición enviada: ${url}`))
            .catch(err => console.error("Error al enviar la petición:", err));

            const datosAmbientales = document.getElementById("datosAmbientales");
            datosAmbientales.style.display = "none";
            datosAmbientales.textContent = "";
        }
    }

    mostrarDatosAmbientales(ubicacion, estado) {
        const datosAmbientales = document.getElementById("datosAmbientales");
        if (estado) {
            datosAmbientales.style.display = "block";
            datosAmbientales.textContent = `Temperatura: ${ubicacion.temp}°C, Humedad: ${ubicacion.humedad}%`;
        } else {
            datosAmbientales.style.display = "none";
            datosAmbientales.textContent = "";
        }
    }
}

var geolocalizacion = new Viajes();
