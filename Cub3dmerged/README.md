Estructura del CUB3d
- El proyecto presenta una estructura de ficheros ordenada y sucesiva
- Todos los archivos respetan las reglas de la norminette

Diferentes archivos y sus funciones:
- El archivo main sirve para iniciar el programa, y por donde le pasaremos los argumentos
	por teclado, el fichero mapa "*.cub" y un --save respectivamente.
- Su primera ejecucion es la comprobacion y validacion de los argumentos pasados.
- Asi como validar el mapa y definir todos los parametros que necesita para ejecutar el programa
- Todos esto lo realizara en 6 funciones:

init_paramas: Inicializa todas las vaiables de las estructuras a 0

valid_file:	Se encargara de validar y recoger los parametros de las texturas,
			resolucion y colores del techo y suelo

valid_map:	Se encargara de validar y guardar el mapa que esta situado
			al final del archivo ".cub"

			sourroundingwalls(): 
				Comprueba la existencia de muros y espacios por debajo de los espacios y de las cadenas de numeros
			checkmapbowels(): 
				Comprueba la existencia de espacios y muros delante y detras de las cadenas de numeros y espacios.



save_map:	Su unica fucion es almacenar el mapa en un array bidimensional que luego se recorrera para realizar el raycasting

valid_file2 && valid_map2:	Son continuaciones de valid_file y valid_map para organizar y
							simplificar el contenido de los archivos del programa

Texturas:
	mlx_new_image, mlx_get_data_addr

Funciones auxiliares e inecesario para probar el funcionamiento del programa:
void	drawMap(t_raycaster *rc);
void	print_params(archparams_t	*arch, validmap_t *map);

Compilar cub3d en ubuntu
clang -Wall -Wextra -Werror main.c -lbsd -lmlx -lXext -lX11

Test de mapas:
	https://github.com/joycemacksuele/cub3d_tests
42 GUIDE:
https://harm-smits.github.io/42docs/

BIBLIOGRAFIA:
-Simple untextured raycastSDL
	https://github.com/matroyer/raycaster-sdl
-Minilibx Images Guide
	https://github.com/keuhdall/images_example
-Functions of Minilibx
	https://qst0.github.io/ft_libgfx/man_mlx_new_image.html


valgrind
make compile && valgrind --leak-check=yes ./a.out map.cub

Para liberar toda la memoria locada- liberar las texturas anteriores a la textura que ha generado el error
Liberar line al mostrar error


----PARTE OBLIGATORIA---
Deepthrought - OK
Keys - OK
Flags - OK
Leaks - OK
Norminette
bonus part(makefile rule and modularization)

--------BONUS--------
Crouch,Sprint,Jump
Sombras
Sonidos(mac -> afplay sound.wav &, linux -> aplay sound,wav &)
Skybox
Barra de vida
animaciones
