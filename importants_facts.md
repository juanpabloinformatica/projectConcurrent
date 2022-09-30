goal.

nos limitaremos a un modo de visualización muy simple gestionado por todas las tarjetas gráficas
desde principios de los años 80 

facts.

- La pantalla es de 80 columnas por 25 líneas: las líneas y columnas se numeran tradicionalmente.
girado desde 0 (por lo tanto, de 0 a 24 para filas y de 0 a 79 para columnas).

- l’adresse de début est 0xB8000

- Cada casilla (de las 80*25) representa un carácter que se muestra en pantalla, 
y está compuesta por 2 bytes (nosotros usamos el tipo
uint8_t para representar un byte en C):

- <img src = "/user/2/pradamej/normal/projectConcurrent/src_de_base/images/Screenshot from 2022-09-26 15-57-34.png" >

- bit 15,  vous devez forcer
le bit 15 à 0.

- <img src = "/user/2/pradamej/normal/projectConcurrent/src_de_base/images/Screenshot from 2022-09-26 15-59-41.png" >

- Para mostrar un carácter en la línea lig y en la columna col de la pantalla, debe escribir en la palabra
de 2 bytes (uint16_t en C) cuya dirección de memoria se puede calcular a partir de la sencilla fórmula
siguiente: 0xB8000 + 2 × (lig × 80 + col).

-  cursor -> todo lo que tienes que hacer es decirle en qué coordenadas debe mostrarlo.

- Al escribir funciones C que necesitan realizar E/S en los puertos, debe usar estos
funciones 

- en esta práctica de laboratorio, el puerto de comando que administra la posición del cursor
es 0x3D4 y el puerto de datos asociado es 0x3D5. La posición del cursor es un número entero de 16 bits

- calculado mediante la siguiente fórmula: pos = col + línea × 80. Esta posición debe enviarse en dos etapas al
tarjeta de video: la secuencia de operaciones a realizar es, por lo tanto, la siguiente:
1. enviar el comando 0x0F en el puerto de comando para indicarle a la tarjeta que vamos a enviar
la parte inferior de la posición del cursor;
2. enviar esta parte inferior al puerto de datos;
3. envíe el comando 0x0E en el puerto de comando para indicar que ahora estamos enviando el
parte superior ;
4. enviar la parte alta de la posición en el puerto de datos