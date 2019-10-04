# Exercício Labeling  
O problema foi resolvido tanto em python quando em C++.  

Para testar a solução em python  vá até a pasta [Python](Python) e execute o seguinte comando: 
```zsh
$ python labeling.py images/bolhas.png
# Provável output
counting objects_and_holes
all objects 21 
objects with hole 8 
objects with no hole 13
just counting objects
objects 32
```
Em C++, vá até a pasta [C++](C++) e execute os seguintes comandos:  
```zsh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./labeling ../images/bolhas.png
#Provável output
counting objects and holes

all Objects: 21
Objects with holes: 8
Objects with not holes: 13


just counting objects: 

all Objects: 32

```
