# Exercício  K-means
O problema foi resolvido em C++  

Para testar a solução, vá até a pasta [C++](C++) e execute os seguintes comandos:  

```zsh
cd C++ 

mkdir build

cd build 

cmake .. 

make

./kmeans_test -help # provável output
# --rounds <r>:	recebe o número de execuçoes do k-means
# --help:	mostra o help na tela
# --clusters <c>:	 recebe o número de médias do k-means

./kmeans_test -r 1 -i ../../pictures/morroDoCareca.jpg -c 25

convert -delay 20 -loop 0 *.jpg mygif.gif  
```

### gif gerado pelo k-means 
![morro do careca gif](pictures/morroDoCareca.gif)

Foi utilizado 25 fotos
