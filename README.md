# DCA0445-PROCESSAMENTO-DIGITAL-DE-IMAGENS

# Atenção !!
__Todos os exercícios de processamento de imagem apresentados a seguir foi utilizando a biblioteca de processamento__
__de imagem chamada__ _**OpenCV**_.  

A versão do OpenCV utilizada é a  4.1.1.
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
A resposta desse Exercício se encontra na pasta [labeling][labeling/]. 
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
Em C++, vá até a pasta [C++](labeling/C++), entre na pasta build e execute os seguintes comandos:  
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
