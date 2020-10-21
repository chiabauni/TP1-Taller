# Taller de Programación I [75.42] - TP1

---

Nombre: BAUNI Chiara

Padron: 102981

Cuatrimestre: 2C 2020

Link al repositorio: [https://github.com/chiabauni/TP1](https://github.com/chiabauni/TP1)

---

# Indice

1. Presentación del trabajo
    - Introduccion
    - Descripción
2. Especificaciones provistas
    - Cliente
    - Servidor
    - Restricciones
    - Códigos de retorno
3. Modelo propuesto
    - Implementacion
    - Diseño final

---

# Presentación del trabajo

## Introducción

Este trabajo practico consiste en desarrollar dos programas: un cliente y un servidor. El programa emisor deberá leer mensajes por entrada estándar y enviárselos al servidor cifrados. El servidor deberá descifrar los mensajes e imprimirlos por salida estándar.

## Descripción

Para implementar el cifrado del mensaje el usuario ingresando por entrada estándar puede elegir entre 3 tipos de cifrados de clave simétrica: cifrado de Cesar, cifrado de Vigenere y cifrado RC4. 

En este trabajo practico se implementará un programa cliente y uno servidor que se comuniquen a través de sockets TCP encriptando los mensajes con alguna de las opciones mencionadas anteriormente.

---

# Especificaciones provistas

## Cliente

El cliente debe leer por entrada estándar el mensaje a enviar, luego debe encriptar el mensaje, enviarlo y cerrar el socket.

El cliente debe conectarse a un host y un puerto, utilizando el protocolo TCP. La entrada de datos puede ser un archivo cuya ruta es pasada en los argumentos del programa, o la entrada estándar, si no se le pasó ningún argumento.

Una vez conectado, el cliente procesa la entrada de datos leyendo de a chunks de 64 bytes utilizando el stack. Encripta el mensaje según el método y clave pasados en los argumentos del programa y envía el mensaje al servidor. Una vez enviado el mensaje completo se cierra el socket, finalizando con el programa del cliente.

### Formato de linea de comando

El cliente se ejecuta utilizando el siguiente formato:

`./client <server-host> <server-port> --method=<method> --key=<key> [<input file>]`

Donde `<method>` puede ser "cesar",  "vigenere", "rc4" según determine el usuario. Si el argumento `[<input file>]` es incluido será el nombre del archivo de texto, en su defecto se intepretará la entrada estándar.

## Servidor

El servidor debe esperar a la conexión de un cliente, luego recibir el mensaje del cliente, desencriptarlo y cerrar el socket.

Una vez conectado el cliente, recibe el mensaje de a chunks de 64 bytes. Desencripta el mensaje según el método y clave pasados en los argumentos del programa e imprime el mensaje. Una vez imprimido el mensaje completo se cierra el socket, finalizando con el programa del servidor.

### Formato de linea de comando

El server se ejecuta utilizando el siguiente formato:

`./server <server-port> --method=<method> --key=<key>`

Donde `<method>` puede ser "cesar",  "vigenere", "rc4" según determine el usuario. 

## Restricciones

La siguiente es una lista de restricciones técnicas exigidas:

1. El sistema debe desarrollarse en ISO C (C99) / ISO C++11.
2. Está prohibido el uso de variables y funciones globales.
3. Todo socket utilizado en este TP debe ser bloqueante.
4. Las funciones deben ser cortas (idealmente de menos de 10 líneas) y el código claro.
5. El archivo de entrada se debe leer en chunks de 64 Bytes, usando el stack.
6. Los datos que “viajarán” por la red serán solamente en sentido emisor -> receptor (client -> server) y serán ni
más ni menos que el mensaje cifrado.
7. El mensaje plano será recibido por entrada estándar en el cliente, y es la salida esperada por salida estándar
en el servidor. El resto de los flujos estándar se asumirán vacíos.

## Códigos de retorno

Para manejar los errores de manera mas visible, utilicé algunos códigos de retorno.

Los códigos de retorno son los siguientes, para el Client:

1: ARGUMENT_ERROR →No se recibieron los argumentos esperados 

2: INIT_ERROR →No se inicializó correctamente el Client

3: CONNECT_ERROR →No se conecto correctamente con el servidor

4: SEND_ERROR → No se pudo enviar el mensaje

5: UNINIT_ERROR →No se liberaron correctamente los recursos

Para el Server:

1: ARGUMENT_ERROR → No se recibieron los argumentos esperados 

2: INIT_ERROR →No se inicializó correctamente el Server

3: CONNECT_ERROR →No se conectó correctamente con el cliente

4: RECEIVE_ERROR → No se pudo recibir el mensaje

5: UNINIT_ERROR →No se liberaron correctamente los recursos

---

# Modelo propuesto

## Implementación

A la hora de la resolución del trabajo planteado, primero comencé pensando en los TDAs que seria conveniente diseñar, para lograr una solución modula, intentando evitar el acoplamiento entre los distintos TDAs diseñados.

Teniendo en cuenta que se deben generar dos programas, podemos pensar que cliente y servidor podrían ser TDAs. Como ambos implementan sockets podemos pensar que socket puede ser otro TDA implementado por el cliente y el servidor:

- **Cliente**: TDA que se instancia cuando se ejecuta el programa Cliente, y sería el encargado de manejar el flujo de ese programa. Este TDA tendría un socket propio, con el que se conectaría al servidor.
- **Servidor**: TDA que maneja el flujo del programa Servidor, y tiene dos sockets: un socket listener, se encarga de escuchar las conexiones entrantes, y otro socket peer, que sería la referencia al socket aceptado una vez conectado el cliente.
- **Socket**: TDA nos permite encapsular los métodos necesarios para permitir la conexión Cliente-Servidor. Principalmente, el socket se conforma por un file descriptor que lo identifica.

![1](https://github.com/chiabauni/TP1/blob/main/1.png)

Luego de haber codificado estos TDAs, lo siguiente que surgió fue la codificación de los mensajes. Como el método a utilizar depende de la elección del usuario, esto me llevó a pensar que debería haber un TDA Cipher que sea implementado por cada TDA particular del método elegido. Es decir generar 3 TDAs Cesar, Vigenere y RC4.

- **Cesar**: TDA que codifica y decodifica buffers siguiendo el cifrado de Cesar con la clave brindada.
- **Vigenere**: TDA que codifica y decodifica buffers siguiendo el cifrado de Vigenere con la clave brindada.
- **RC4**: TDA que codifica y decodifica buffers siguiendo el cifrado de RC4 con la clave brindada.
- **Cipher**: TDA nos permite encapsular los métodos necesarios para permitir la conexión entre cliente o server con el cifrado deseado.

Finalmente a raíz de algunos comentarios hechos por los profesores decidí implementar el TDA File_encryptor para modular el funcionamiento del socket:

- **File_encryptor**:  TDA nos permite encapsular los métodos necesarios para permitir la conexión entre TDA cliente o server con TDA Cipher. También permite, si se trata del cliente leer un archivo o la entrada estándar según corresponda.

## Modelo final

El diseño final consta de 8 TDAs con responsabilidades claras y un acoplamiento razonable. Los mismos se muestran a continuación:

![2](https://github.com/chiabauni/TP1/blob/main/2.png)
