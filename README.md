[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=12050773&assignment_repo_type=AssignmentRepo)
# PiXelPerFect

![Logo del Proyecto](https://i.imgur.com/9I7uA5T.png)

## Descripción del Proyecto

Breve descripción del proyecto y sus características principales.

## Requisitos

Lista de requisitos de hardware y software necesarios para utilizar el proyecto.

## Guía de Instalación

Instrucciones detalladas sobre cómo instalar el proyecto, incluyendo dependencias y configuraciones necesarias.
Instalacion de OpenCV 4.8.0

OpenCV Releases: https://opencv.org/releases/

1. Clonar este repositorio. 
2. Descargar la liberia OpenCV version 4.8.0 de la pagina de OpenCV
3. Descomprimir la carpeta OpenCV dentro del disco C:
   
Configurar variables de entorno del sistema:
4. En windows buscar editar las variables de entorno del sistema e ingresar a variables de entorno.
5. En variables de usuario ingresar a PATH y crear una nueva ruta hacia la carpeta opencv C:\tools\opencv\build\x64\vc16\bin
   
   PATH            | C:\tools\opencv\build\x64\vc16\bin
   
6. En variables del sistema crear las siguientes nuevas variables:
     
  OPENCV_DIR            | C:\tools\opencv\build\x64\vc16\lib
  OPENCV_INCLUDE_PATHS  | C:\tools\opencv\build\include
  OPENCV_LINK_LIBS      | opencv_world460
  OPENCV_LINK_PATHS     | C:\tools\opencv\build\x64\vc16\lib
  OPENCV_PATH           | C:\tools\opencv

7. Descargar visual studio 2022, se usara el compilador de visual studio, y cambiar la arquitectura a amd64.

Configuracion de CMAKELIST:

  cmake_minimum_required(VERSION 3.25)
  project(test) // <-------- Nombre del proyecto

  set(CMAKE_CXX_STANDARD 23) 

  set(ENV{OPENCV_DIR} "C:/tools/opencv/build") // <---------- Ruta de acceso a el directorio de opencv

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

  find_package(OpenCV REQUIRED) 
  include_directories(${OpenCV_INCLUDE_DIRS})

  add_executable(test main.cpp) // <--------------Cambia dependiendo del proyecto

  set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

  target_link_libraries(test ${OpenCV_LIBS}) // <------------ Modificar el nombre del proyecto


## Instrucciones o Reglas de Uso

## Licencia de Uso

[LICENCIA](https://github.com/CS1103/proyecto-final-pf-2023-02-sec2-grupo1/blob/main/LICENSE)


## Diagramas

### Diagrama de Casos de Uso

![Diagrama de Casos de Uso](https://i.imgur.com/KW1gTUp.png)
![Diagrama de Casos de Uso](https://miro.medium.com/v2/resize:fit:1400/1*RxT4yZtXFkQ47Fe7huHe_w.png)

## Link de Video de Presentación

Enlace a un video de presentación o demostración del proyecto si está disponible.

## Autores

| Código | Nombre                            |
|--------|-----------------------------------|
| Autor 1| Estefano Mauricio Zarate Manosalva |
| Autor 2| Esteban Jose Sulca Infante        |
| Autor 3| Natalia Falla Valdez              |
| Autor 4| Ary Fernando Sanchez Cerna        |
| Autor 5| Jose Guerrero Ernesto Cueva       |
| Autor 6| Carlo Stefano Torres Gabrielli    |


## Bibliografía

<span style="font-family: 'Times New Roman', Times, serif;">Dong, C., Loy, C. C., He, K., & Tang, X. (2015). Image Super-Resolution Using Deep Convolutional Networks. Computer Science > Computer Vision and Pattern Recognition. arXiv:1501.00092 [cs.CV].</span>

<span style="font-family: 'Times New Roman', Times, serif;">De, A. M. D. (2021, October 6). Implementación de redes neuronales convolucionales en Field-Programmable Logic Arrays. https://riunet.upv.es/handle/10251/173839?show=full</span>

<span style="font-family: 'Times New Roman', Times, serif;">SRCNN-Based Enhanced Imaging for low frequency radar. (2018, August 1). IEEE Conference Publication | IEEE Xplore. https://ieeexplore.ieee.org/abstract/document/8597817</span>

<span style="font-family: 'Times New Roman', Times, serif;">Intelligent systems and computer technology. (n.d.). Google Books. https://books.google.com.pe/books?hl=en&lr=&id=gK4SEAAAQBAJ&oi=fnd&pg=PA3&dq=srcnn&ots=6uK4S5JIVn&sig=m7RmiqsJEhHwrYJkE-Ar0aoPmdc&redir_esc=y#v=onepage&q=srcnn&f=false</span>

---

