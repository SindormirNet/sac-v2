// SAC Project V2.0 - Copyright (C) 2010 Jorge Gomez Arenas
// This file is part of SAC Project. (http://sac.sindormir.net)
//
// SAC Project is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SAC Project is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SAC Project.  If not, see <http://www.gnu.org/licenses/>.
//
// Contact info: Jorge Gomez Arenas <syvic@sindormir.net>

/* Control de versiones:

  - Version 0.5:      Recepción de datos funcional
  - Version 0.6:      Envio de datos funcional
  - Version 0.7:      Recepción de datos funcional del todo
               :      Este fichero sirve de base para RX y TX
  - Version 0.8:      Corrección de código y eliminación de comentarios
               :      Eliminación de un prompt redundante y añadido flush al principio de la shell
  - Version 0.9:      Añadidas funciones de reset del módulo y prueba fallida de nuevo método de recepción
  - Version 0.9.1:    Añadida función de reset, watchdog y llamadas a wd_alive()
  - Version 0.9.2:    Eliminadas funciones de recibir redundantes. Pruebas de fiabilidad
                      REG_CONTROL no estaba con el bit 2 activado
                      Esta version no funciona correctamente
  - Version 0.9.3b1:  Branch 1. Versión con las modificaciones según la AN de AUREL  
  - Version 0.9.3b1.2 Funciona casi perfectamente la recepción !!!!
  - Version 0.9.3b1.3 Intento de mejora del rendimiento en RX
                      Cambiado el timeout a 50ms. Parece que funciona mejor
                      Función TX mejorada tambien
  - Version 0.9.3b1.4 Intento fallido de depurar código. No usar esta versión
  - Version 0.9.3b1.5 Ordenación de código
  - Version 0.9.3b1.6 Limpieza de funciones en desuso. RX OK
  - Version 0.9.3b1.7 Doble radio_init al arranque parece que hace que la RX vaya mejor. Se deja puesto
                      Varias correciones menores
  - Version 0.9.3b1.8 Ordenación de código. 
                      TX parece que arreglado cogiendo código de SAC 1.0.
                      Volviendo a la rama principal.
  - Version 0.9.4     Añadida linea en send para limpiar irqs antes de salir
  - Version 0.9.5     Función wait irq implementada para RX también
                      Comentadas leds de debug en envio
                      en tx no mira la irq de done si ha fallado la de empty
  - Version 0.9.6     Añadidas de nuevo las llamdas a radio_init al principio de las funciones de envio.
  - Version 0.9.7     Intento implementación funciones de envio y recepción de más de 1 byte
                      Cambiadas llamadas a REG_CONTROL en RX para habilitar el bit de bypass
  - Version 0.9.8b1   Branch 1. Cambio de funciones por las funciones de Cypress (spirf.c)  
                      Esta version funciona parcialmente. los datos se envian y reciben pero no son 100% fiables
  - Version 0.9.8b2   Cambiados chips a 64 bits y cambios en la inicialización
                      Esta versión funciona mucho mejor. Transmite y recibe siempre casi todos los bits 
  - Version 0.9.8b3   Cambiada sensibilidad de los thresholds. Timeouts en funciones de RX y TX
                      Funciona aunque pierde muchos paquetes
  - Version 0.9.8b4   Ídem que la versión anterior pero con paquetes de 64bits. Funciona pero pierde paquetes
  - Version 0.9.8b5   Ídem que el anterior pero cambiando setregs por spiwrites en TX y RX. Pierde paquetes
  - Version 0.9.8b6   Ídem que el anterior pero aumentando velocidad del bus SPI
                      Quitado delay en la función de RX. Añadido timeout en la funcion RX. TX parece funcionar OK
  - Version 0.9.9b1.1 Nueva rama probando cambiando algunas funciones init y orden de RX y TX
                      Esta version funciona MUY BIEN !!! No tan bien :(
  - Version 0.9.9b1.2 Usando las funciones simples de envio de 1 byte del raton acelerométrico
                      Se quitan las funciones del raton acelerométrico que eran un porquería y se cambian varios
                      parámetros de inicialización y envio/recepción. El resultado no es muy bueno
  - Version 0.9.9b1.3 Funciónes de RX y TX reescritas para usar burst. Parece que va mucho mejor
  - Version 0.9.9b1.4 Todo reescrito desde 0 excepto menus
  - Version 0.9.9b1.5 Cambios en la inicialización con respecto al anterior.
                      Implementacion de bit banging en lugar del SPI integrado
  - Version 0.9.9b1.6 Bit banging descartado por malos resultados de timing
                      Varios cambios en la inicialización y en TX y RX. FUNCIONA COJONUDAMENTE EN RX
                      FUNCIONA CASI SIEMPRE EN TX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  - Version 1.0.0.0   Copia exacta de la versión anterior                       
  - Version 1.0.0.1   Modificado Timeout en TX a 100ms
                      Al cabo de un tiempo dejan de recibir pero acaba volviendo. 
                      Algo se debe corromper entre medias
                      Funciona bien justo tras la programación.
                      Funciona bidireccionalmente
  - Version 1.0.0.2   Funciona bastante bien, casi perfecto. Se queda colgado al cabo del tiempo
                      Mejora en la forma de mostrar los datos recibidos
  - Version 1.0.0.3   Intento de arreglo de los bloqueos al cabo del tiempo
                      Cambio de REG_SERDES_CTL a 0x0F. Era 0x0B
  - Version 1.0.0.4   Funciona cojonudamente!!!!!!!!!!!!!!!!!!!!!!!! (Copia del anterior)
  - Version 1.0.0.5   Cambios en la inicialización. Parece que ya no se queda colgado en TX. Funciona MUY BIEN
  - Version 1.0.0.6   Añadido tratamiento de interrupciones
                      Parece que funciona bien la RX ahora. Cambiado comportamiento de la INT
                      Añadido soporte para Device ID en EEPROM
  - Version 1.0.0.7   Montones de cambios. Funciona mucho mejor pero hay que mandar los paquetes dos veces para
                      que lleguen
  - Version 1.0.1     PRIMERA VERSIÓN QUE FUNCIONA INTEGRAMENTE RX/TX CON PAQUETES DE 4 BYTES   
  - Version 1.0.2     Limpieza de código de la versión anterior. Separación de código en varios ficheros
  - Version 1.0.3     Incluye parte del protocolo de envio/recepción de datagramas con verificación de integridad
                      Incluye sistemas de ACK/NACKS para peticion de reenvio de paquetes dañados
  - Version 1.0.4     Mejoras en el envio/recepcion de ACKs. Esta versión va cojonuda en cuanto a timing
  - Version 1.0.5     Optimización de ACK/NACKS. Funciona bien la lectura de RFID
  - Version 1.0.6     ???
  - Version 1.0.7     Esta version va DE PUTA MADRE. Hace una reiniciación de la radio cuando el número de IRQs
                      en TX es superior a 6. Parece que este es el indicador de cuando la TX se cuelga. Añadido
                      papel de plata para aislar interferencias del radiomodem al uC.
                      Cambiada la velocidad del puerto serie a 9600. Esto también puede influir...
                      Además de lo anterior tiene un par de cambios en la inicialización:
                          - No manda su ID al arranque
                          - Cambiado el canal por el 79 (Parece que hay menos tráfico)
                          - Subida la potencia de emisión a 7
                          - Subidos los thresholds para que acepte paquetes con más errores. Parece que es 
                            demasiado  alto. Se reciben muchos paquetes incorrectos
                            
                      Para la siguinte versión:
                          1.- Implementar la comprobación de IRQs en el envio de datagramas
                          2.- Mirar a ver si funciona bien sin la resistencia entre Vcc y GND
                          3.- Dejar los thresholds a por defecto y comprobar si el sistema de acks/nacks empeora

  - Version 1.0.8     Implementada comprobacion de bloqueo en TX para modo de envio de datagramas. Version OK
  - Version 1.0.9     Implementada comprobación de bloqueos en la funcion RadioTransmit. Arreglado fallo en 
                      prepare.
  - Version 1.0.10    Limpieza del código de la versión anterior
  - Version 1.0.11    Ahora los mensajes se mandan por los dos puertos serie.
                      Vuelta al canal 9 para que detecte las tramas la placa de debug
                      Cambio en el timing de los envios ACK/NACK. Pasa de 300ms a 50ms
                      Cambio en el comportamiento de la funcion recibe_datagram
                      Bajado tiempo de "Waiting for response" a 1 seg
                      En RX ya no responde ACK si el tiempo ha expirado
  - Version 1.0.12    Mejora del timing acks
                      Implementación de retries en el envio. Parece que con esto mejora mucho la fiabilidad
                      Tiempos restaurados
                      Esta versión va muy muy bien. La anterior se quedaba colgada en RX
  - Version 1.0.13    Implementación de sistema de mensajes para comunicación con software en PC
  - Version 1.0.14    Añadido control de motores. Cambiados parámetros de retransmisión
  - Version 1.0.15    Mejorado control de motores. Arreglado bug con la lectura/escritura en EEPROM
                      Añadida posibilidad de salir del modo Listen
                      Cambiado firmware para arranque más rápido
  - Version 1.0.16    Creadas librerias de spi y de cywm6935. 
  - Version 1.0.17    Limpieza de código. Solucionados problemas con las librerías.
                      Eliminado código referente al watchdog
                      Cambiada estructura sac_datagram e implementado nuevo protocolo sacp
  - Version 1.0.18    Muchos cambios en el funcionamiento de los ACKS y el protocolo de datagramas
                      En esta version funciona correctamente el sistema de acks y mejora el sistema de rx
                      Ahora la UCC se queda bloqueada en RX
  - Version 1.0.19    Cambios menores e intento de solucion del bloqueo en RX
                      El envio de comandos de motor funciona perfectamente
                      El envio de tags a la ucc funciona perfectamente
                      Añadida soporte para mandar mensajes de remote control (sin probar)
                      Cambiado funcionamiento de menu y limpiadas opciones antiguas
  - Version 1.0.20    Añadido soporte para heartbeats. Mejorado sistema de comunicaciones. Limpieza de codigo
  - Version 1.0.21    ???
  
  
  
  Sistema de mensajes:
  
  i: Mensajes de debug (Ignorados por el programa)
  p: Paquete de datos recibido. Formato [pXXXXXXXXp] siendo X el paquete recibido
  x: Información del protocolo. Formato [xXXXx] siendo X la información del protocolo:
      RXE: RX Error
      TXE: TX Error
      NAS: NACK sent
      NAR: NACK received
      ACS: ACK sent
      ACR: ACK received
      RST: Radio reset caused by TX blocking
      RTO: Response timeout
      MRE: Max numbero of retries expired
  v: Version del firmware. Formato [vX.X.XXv] siendo X la versión
  w: ID. Formato [wXw] siendo X el ID
  
  

  Por hacer:
  
  - Implementar temporizador cuando esté en modo RX para que haga un TD_init si pasa mucho tiempo sin recibir
    ningún paquete.
  - Cada robot, cuando arranque que mande un mensaje notificando que está vivo
  - La UCC, cuando arranque, debe hacer un barrido notificando.

  
  Wish list:
  - Cambio de canal automáticamente en caso de detectar mucho ruido
  - Beacon frames desde la UCC
  - Implementar sistema de comunicación segura mediante puerto serie. Hacer checksum de mensajes 

  
  Mejoras de la placa:
  - Preparar la placa para que una carcasa apantalle al uC
  - Alejar el uC del módulo wireless
  - Orientar las antenas a 45º con respecto al uC
  - Selector de puerto serie Hard/Soft en el mismo DB9 con DPDT. Probar simplemente a duplicar fila pines antes.
  - Filtro en PI a la salida del regulador de 3.3V
  - Pistas del bus SPI no deben ser rectas. Usar herramienta de curvas
  - Condensadores de desacoplo adecuados a la frecuencia del radiomodem
  - Pines de rx y tx invertidos en el rfid: OK
  - Separar conectores de la parte inferior de la placa
  - Separar agujero de inserción inferior derecho
  - Pin IRQ ha cambiado de pin: OK
  - Poner reguladores de tensión tumbados con los condensadores cerámicos justo delante
  
  Recordar:
  - Descubierto un indicador de cuando deja de transmitir. El numero de IRQs que se producen al enviar pasan
    de 5 o 6 a >12  
  - Debe haber un DELAY entre las comprobaciones de la funcion setreg
  - COMPROBAR CADA PEQUEÑO CAMBIO POR ESTÚPIDO QUE PAREZCA. El compilador no va muy fino
  - El watchdog debe ser reinicializado cada medio segundo
  - Alejar el emisor del receptor al menos un metro y medio para evitar interferencias y saturaciones
  - No se pueden poner Serialprintfs por todos lados. Utilizar leds para debug
*/
