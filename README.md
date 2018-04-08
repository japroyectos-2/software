# EC3882 - Laboratorio de Proyectos 2. Sección 1.
# Estación Meteorológica (SOFTWARE).

#### Autores: 
#### Jeckson Jaimes. 12-10446.
#### Anna Cafaro. 12-10997.
#### Profesor: Novel Certad.

En este repositorio se encuentran los algoritmos utilizados para el desarrollo de la interfaz gráfica y la conmunicación serial entre el demoqe, los sensores y el computador. Este apartado tiene como finalidad el desarrollo de un interfaz completa donde se aprecie la unión y funcionamiento de todos los sensores que integrarán la estación meteorológica.

## Lenguajes de programación utilizados.

* Matlab. [**Codes**](https://github.com/japroyectos-2/software/tree/master/Matlab).
* CodeWarrior. [**Codes**]().
* Processing. [**Codes**](https://github.com/japroyectos-2/software/tree/master/Processing/Interfaz).

### Matlab.

En este lenguaje de programación, se hizo una primera "interfaz" en la que se recogían una serie de datos recibidos del demoqe y luego estos eran impresos por pantalla, no era útil ya que no era información en tiempo real, por lo que se decidió seguir trabajando en Processing.

### CodeWarrior.

En este lenguaje de programación, se programa todo el funcionamiento del microcontrolador que se está utilizando, en este se recibe el valor de la señal adquirida por el bloque de adquisición y se realiza la conversión analógico-digital, luego esta señal es procesada y codificada con el protocolo de información que se desea utilizar para luego ser enviado por vía puerto serial hacia Processing donde se hará la interpretación de la señal para posteriormente ser mostrada en la interfaz.

Para mayor información sobre la documentación del algoritmo utilizado, [**click aquí**](https://github.com/japroyectos-2/software/wiki/CodeWarrior)

### Processing.

En este lenguaje de programación, se espera crear la totalidad de la interfaz gráfica final donde se mostrará en ella la unión y funcionamiento de los sensores a utilizar en la estación meteorológica, así como las características de estos.

Para mayor información sobre la documentación del algoritmo utilizado, [**click aquí**](https://github.com/japroyectos-2/software/wiki/Processing)

Agradecimiento al Prof. Novel Certad y al preparador Said Alvarado por los conocimientos impartidos y la buena disposición para la realización de este proyecto, así como a los compañeros que ayudaron en los avances de este.
