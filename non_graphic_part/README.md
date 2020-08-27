Estructura del CUB3d
- El proyecto presenta una estructura de ficheros ordenada y sucesiva
- Todos los archivos respetan las reglas de la norminette

Diferentes archivos y sus funciones:
- EL archivo main sirve para iniciar el programa, y por donde le pasaremos los argumentos
por teclado, el fichero mapa "*.cub" y un --save respectivamente.
- Su primera ejecucion es la comprobacion y validacion de los argumentos pasados.
- Asi como validar el mapa y definir todos los parametros que necesita para ejecutar el programa
- Todos esto lo realizara en 6 funciones:

init_paramas: Inicializa todas las vaiables de las estructuras a 0

valid_file:	Se encargara de validar y recoger los parametros de las texturas,
			resolucion y colores del techo y suelo

valid_map:	Se encargara de validar y guardar el mapa que esta situado
			al final del archivo ".cub"

save_map:	Su unica fucion es almacenar el mapa en un array bidimensional que luego se 				recorrera para realizar el raycasting

valid_file2 && valid_map2:	Son continuaciones de valid_file y valid_map para organizar y
							simplificar el contenido de los archivos del programa
							