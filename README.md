# DCA0445-PROCESSAMENTO-DIGITAL-DE-IMAGENS

# Atenção !!
__Todos os exercícios de processamento de imagem apresentados a seguir foi utilizando a biblioteca de processamento__
__de imagem chamada__ _**OpenCV**_.  

A versão do OpenCV utilizada é a  4.1.1.  
A versão do python utilizada é a  3.7.4
Versões anteriores pode haver problemas na compilação ou execução dos scrips python!!! 

## Exercício Regions  
A resposta desse exercício se encontra na pasta [regions](regions/).  
O problema foi resolvido tanto em python quando em C++.  

Para testar a solução em python  vá até a pasta [Python](regions/Python) e execute o seguinte comando:  
```zsh
$ python regions.py photos/biel.png # ou qualquer outra imagem

```

```zsh
$ python swap_regions.py.py photos/biel.png # ou qualquer outra imagem

```

Em C++, vá até a pasta [C++](regions/C++),escolha qual exercício deseja executar , entre na pasta build e execute os seguintes comandos:

```zsh 
    cmake ..
    make
```
caso esteja testando o [regions](regions/C++/regions)  
```zsh
    ./regions photos/biel.png # ou qualquer outra imagem
```
Ou, caso esteja testando o [swap regions](regions/C++/swap_regions)
```zsh
    ./swapRegions photos/biel.png # ou qualquer outra imagem
```

## Exercício Labeling  
A resposta desse Exercício se encontra na pasta [labeling](labeling/). 
O problema foi resolvido tanto em python quando em C++.  

Para testar a solução em python  vá até a pasta [Python](labeling/Python) e execute o seguinte comando: 
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
Em C++, vá até a pasta [C++](labeling/C++) e execute os seguintes comandos:  
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
## Exercício histogram
A resposta desse Exercício se encontra na pasta [histogram](histogram/). 
O problema foi resolvido tanto em python quando em C++.  


__OBS:__ para executar esse exemplo, alem do opencv  você terá que instalar o libVLC. 

Para testar a solução em python  vá até a pasta [Python](histogram/Python) e execute o seguinte comando: 
```zsh
$ python equalize.py. # pressione "e" para sair do programa
```

```zsh
$ python motion_detector.py. # pressione "e" para sair do programa
 # não se mexa !! 
 # baby shark doo doo doo 
```

Em C++, vá até a pasta [C++](histogram/C++) e execute os seguintes comandos:  
```zsh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./equalize # pressione "e" para sair do programa
# ou 
$ ./motionDetector # pressione "e" para sair do programa
 # não se mexa !!
 # baby shark doo doo doo 
```


## Exercício spatial Filters

A resposta desse Exercício se encontra na pasta [spatialFilters](spatialFilters/). O problema foi resolvido em python versão 3.7.4

Para testar a solução em python vá até a pasta [Python](spatialFilters/Python/) e execute o seguinte comando:

```zsh

$ python laplgauss.py 

```

```zsh 

$ python tilt_shift.py
# a imagem será salva em data/tiltShift_blend2.jpg
``` 

```zsh
# vídeo muito lento porem ao terminar o tilt shift, você pode verificar o seu resultado
# em data/Toy_Story_tilted.avi
$ python tilt_shift_video.py 
```


