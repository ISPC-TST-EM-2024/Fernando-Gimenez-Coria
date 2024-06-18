![logo](../rsc/visuales/LOGO.png)    

# **Guía resumen manual de referencia** 
# Manual de Referencia de la Familia de Microcontroladores PIC de Rango Medio

## 1. Introducción

- **Objetivo del Manual:** Presenta el propósito y la estructura del documento.
- **Descripción General:** Información básica sobre la familia de microcontroladores PIC de rango medio.
- **Convenciones:** Explicación de términos y notaciones utilizados a lo largo del manual.  

## 2. Oscilador

- **Tipos de Osciladores:** Cristal, resonadores cerámicos, oscilador RC externo e interno.
- **Configuración:** Cómo configurar los diferentes tipos de osciladores.
- **Modos de Operación:** Efectos del modo de suspensión y reinicio en el oscilador.  

## 3. Reset

- **Tipos de Reinicio:** Power-on Reset (POR), Brown-out Reset (BOR), reinicio por watchdog.
- **Registros de Estado:** Registros y bits de control relacionados con los eventos de reinicio.
- **Consejos de Diseño:** Mejores prácticas para manejar los reinicios.  

## 4. Arquitectura

- **Esquema del Ciclo de Instrucción:** Detalles del ciclo de reloj y ejecución de instrucciones.
- **Flujo de Instrucciones:** Descripción del flujo de datos e instrucciones.
- **Entradas y Salidas:** Configuración y uso de los pines de E/S.  

## 5. CPU y ALU

- **Unidad Central de Procesamiento:** Descripción de la CPU, registros de uso general y registros especiales.
- **Unidad Lógica Aritmética (ALU):** Operaciones soportadas por la ALU y su funcionamiento.
- **Registros Clave:** STATUS, OPTION_REG y otros registros importantes.  

## 6. Organización de Memoria

- **Memoria de Programa:** Mapeo y uso de la memoria de programa.
- **Memoria de Datos:** Organización de la memoria de datos, incluyendo bancos y registros especiales.
- **Consejos de Diseño:** Buenas prácticas para la gestión de la memoria.  

## 7. EEPROM de Datos

- **Operaciones Básicas:** Lectura y escritura en la EEPROM.
- **Registros de Control:** Detalles de los registros utilizados para acceder a la EEPROM.
- **Protección Contra Escrituras Espurias:** Mecanismos para proteger la memoria EEPROM.  

## 8. Interrupciones

- **Sistema de Interrupciones:** Estructura y funcionamiento del sistema de interrupciones.
- **Registros de Control:** Cómo configurar y manejar las interrupciones.
- **Latencia de Interrupciones:** Tiempos y consideraciones para el manejo de interrupciones.  

## 9. Puertos de E/S

- **Descripción de Puertos:** Detalles de los puertos (PORTA, PORTB, etc.) y su configuración.
- **Registros TRIS:** Cómo usar los registros TRIS para configurar los pines como entrada o salida.
- **Consejos de Diseño:** Mejores prácticas para el uso de puertos de E/S.  

## 10. Puerto Esclavo Paralelo (PSP)

- **Funcionamiento del PSP:** Descripción y uso del puerto esclavo paralelo.
- **Registros de Control:** Configuración y manejo del PSP.
- **Operación en Modo de Suspensión:** Consideraciones para el uso del PSP en modo de suspensión.  

## 11. Timer0

- **Descripción del Timer0:** Funcionamiento y configuración del Timer0.
- **Prescaler:** Uso del prescaler con el Timer0.
- **Reloj Externo:** Configuración para el uso de un reloj externo con el Timer0.  

## 12. Timer1

- **Modos de Operación:** Detalles de los modos sincronizado y asincrónico del Timer1.
- **Oscilador del Timer1:** Uso y configuración del oscilador interno del Timer1.
- **Consejos de Diseño:** Buenas prácticas para la configuración del Timer1.  

## 13. Timer2

- **Descripción del Timer2:** Funcionamiento y configuración del Timer2.
- **Prescaler y Postscaler:** Cómo usar y configurar el prescaler y postscaler del Timer2.  

## 14. Comparar/Capturar/PWM (CCP)

- **Modos de Captura y Comparación:** Funcionamiento y configuración de los modos CCP.
- **Modulación por Ancho de Pulso (PWM):** Uso del PWM y configuración del CCP para generar señales PWM.
- **Consejos de Diseño:** Buenas prácticas para el uso de los módulos CCP.  

## 15. Puerto Serial Sincrónico (SSP)

- **Modo SPI:** Configuración y uso del puerto serial sincrónico en modo SPI.
- **Modo I2C:** Configuración y uso del SSP en modo I2C.
- **Registros de Control:** Detalles de los registros asociados con el SSP.  

## 16. Puerto Serial Básico Sincrónico (BSSP)

- **Modos de Operación:** Descripción y configuración de los modos SPI e I2C básicos.
- **Inicialización y Configuración:** Cómo inicializar y configurar el BSSP.
- **Consejos de Diseño:** Buenas prácticas para el uso del BSSP.  

## 17. Puerto Serial Maestro Sincrónico (MSSP)

- **Modos SPI e I2C Avanzados:** Detalles avanzados de la operación en modos SPI e I2C.
- **Registros y Configuración:** Cómo manejar los registros y configurar el MSSP.
- **Consejos de Conexión:** Consideraciones para la conexión y uso del MSSP.  

## 18. USART

- **Generador de Tasa de Baudios:** Configuración del generador de baudios para comunicación serial.
- **Modos Asíncronos y Síncronos:** Uso del USART en modos de operación asíncronos y síncronos.
- **Registros de Control:** Configuración y uso de los registros relacionados con el USART.  

## 19. Referencia de Voltaje

- **Configuración de Referencia de Voltaje:** Ajuste y precisión de la referencia de voltaje.
- **Operación en Modo de Suspensión:** Efectos del modo de suspensión en la referencia de voltaje.
- **Reinicios y Consideraciones:** Cómo manejar la referencia de voltaje durante reinicios.  

## 20. Comparador

- **Configuración y Operación del Comparador:** Uso del comparador en aplicaciones analógicas.
- **Registros y Ajustes:** Configuración de registros para el comparador.
- **Consejos de Conexión:** Buenas prácticas para la conexión del comparador.  

## 21. Convertidor A/D de 8 bits

- **Requisitos de Adquisición:** Parámetros y tiempos necesarios para una correcta adquisición de datos.
- **Selección de Reloj de Conversión:** Cómo elegir y configurar el reloj para el convertidor A/D.
- **Pines Analógicos y Operación de Conversión:** Configuración de pines y proceso de conversión A/D.  

## 22. Convertidor A/D Básico de 8 bits

- **Operación Básica:** Funcionamiento simple del convertidor A/D de 8 bits.
- **Configuración y Uso:** Cómo configurar y utilizar el convertidor A/D básico.  

## 23. Convertidor A/D de 10 bits

- **Descripción y Funcionamiento:** Detalles y precisión del convertidor A/D de 10 bits.
- **Configuración de Pines y Registros:** Ajustes necesarios para el uso del convertidor A/D de 10 bits.
- **Requisitos de Adquisición:** Parámetros necesarios para una adquisición precisa.  

## 24. A/D de Pendiente (SLOPE)

- **Proceso de Conversión:** Cómo funciona el convertidor A/D de pendiente.
- **Módulos Analógicos Relacionados:** Uso y configuración de módulos relacionados con el A/D de pendiente.
Calibración y Diseño: Parámetros de calibración y buenas prácticas de diseño.  

## 25. LCD

- **Registro de Control:** Configuración y manejo del registro de control del LCD.
- **Sincronización y Operación:** Sincronización y uso del módulo LCD.
- **Configuración y Conexión:** Cómo configurar y conectar el LCD al microcontrolador.  

## 26. Modulación de Ancho de Pulso (PWM)

- **Principios de PWM:** Descripción básica de la modulación por ancho de pulso.
- **Configuración del Módulo PWM:** Cómo configurar y usar el módulo PWM en el PIC.
- **Aplicaciones Típicas:** Ejemplos de uso de PWM en control de motores y otros dispositivos.  

## 27. Módulo de Comparación

- **Configuración del Comparador:** Detalles sobre cómo configurar el módulo de comparación.
- **Operación y Ajustes:** Uso práctico y ajustes del comparador.
- **Aplicaciones Prácticas:** Ejemplos de aplicaciones del módulo de comparación en circuitos.  

## 28. Módulo de Captura

- **Principios de Operación:** Cómo funciona el módulo de captura.
- **Configuración y Uso:** Ajustes necesarios para usar el módulo de captura.
- **Ejemplos de Aplicaciones:** Aplicaciones típicas del módulo de captura en mediciones de tiempo y eventos.
## 29. Módulo de Temporización (Timer)

- **Descripción General:** Explicación de los módulos de temporización disponibles.
- **Configuración y Uso:** Cómo configurar y usar los diferentes temporizadores.
- **Aplicaciones Típicas:** Ejemplos de uso de temporizadores en aplicaciones de control de tiempo.  

## 30. Módulo de Comunicación Serial (SCI)

- **Introducción al SCI:** Descripción del módulo de comunicación serial.
- **Configuración y Operación:** Ajustes necesarios para la comunicación serial.
- **Ejemplos Prácticos:** Aplicaciones comunes del módulo SCI en comunicación de datos.  

## 31. Módulo de Comunicación Síncrona (SPI)

- **Principios de SPI:** Explicación básica del protocolo de comunicación SPI.
- **Configuración del Módulo SPI:** Cómo configurar y usar el módulo SPI en el PIC.
- **Aplicaciones del SPI:** Ejemplos de uso de SPI en comunicación con otros dispositivos.  

## 32. Módulo de Comunicación I2C

- **Introducción al I2C:** Descripción del protocolo de comunicación I2C.
- **Configuración y Operación del Módulo I2C:** Cómo configurar y usar el módulo I2C.
- **Ejemplos de Aplicaciones:** Uso de I2C en la comunicación entre múltiples dispositivos.  

## 33. Módulo de Comunicación UART

- **Principios del UART:** Descripción del protocolo UART.
- **Configuración y Uso del UART:** Ajustes necesarios para usar el UART en el PIC.
- **Aplicaciones Típicas:** Ejemplos de uso del UART en comunicación de datos.  

## 34. Configuración de Pines

- **Mapeo de Pines:** Descripción de cómo mapear y configurar los pines del microcontrolador.
- **Registros de Control:** Ajustes necesarios en los registros para configurar los pines.
- **Ejemplos de Aplicaciones:** Configuración de pines en aplicaciones prácticas.  

## 35. Prácticas de Diseño y Programación

- **Mejores Prácticas:** Consejos generales para el diseño y programación de aplicaciones con microcontroladores PIC.
- **Optimización del Código:** Técnicas para optimizar el código ensamblador.
- **Depuración y Pruebas:** Métodos para la depuración y pruebas de aplicaciones.
