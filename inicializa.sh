#! /bin/sh
# Script de inicializaciónn de librerías y extensiones para Inform 6.
# Versión: 2.0 (2018/09/16)

# Rutas:
directorio_librerias="/usr/share/inform/6.31/module"
directorio_extensiones="/usr/share/inform/6.31/include"
directorio_sintaxis_gtksourceview="/usr/share/gtksourceview-3.0/language-specs"
directorio_paquetes_atom=$HOME"/.atom/packages"

sudo true

# Resaltado de sintaxis para GtkSourceView:
echo -n "Copiando archivo de resaltado de sintaxis para GtkSourceView..."
sudo cp inform6.lang $directorio_sintaxis_gtksourceview
echo " hecho."

# Definición parcial de la gramática de Inform 6 para Atom:
echo -n "Copiando archivos de gramática para Atom..."
if [ -d $directorio_paquetes_atom]; then
	if [ -d $directorio_paquetes_atom/language-inform6]; then
		sudo rm -r $directorio_paquetes_atom/language-inform6
	fi
	sudo cp language-inform6 $directorio_paquetes_atom/language-inform6
fi
echo " hecho."

# Librerías Inform 6 e INFSP 6:
echo -n "Copiando archivos de las librerías Inform 6 e INFSP 6..."
if [ -d $directorio_librerias ]; then
	sudo rm -r $directorio_librerias
fi
sudo mkdir $directorio_librerias
sudo cp InformLibrary/*.h $directorio_librerias/
sudo cp INFSP6/*.h $directorio_librerias/
cp InformLibrary/README README_temp
echo " " >> README_temp
cat INFSP6/README >> README_temp
sudo mv README_temp $directorio_librerias/README
echo " hecho."

# Librería GWindows (DA-Gwindows v1.2):
echo -n "Copiando archivos de la librería GWindows (DA-Gwindows v1.2)..."
if [ -d $directorio_extensiones/gwindows ]; then
	sudo rm -r $directorio_extensiones/gwindows
fi
sudo mkdir $directorio_extensiones/gwindows
sudo cp DaGWindows/* $directorio_extensiones/gwindows/
# Extensión de barra de estado para GWindows:
sudo cp Extensions/gstatusX.h $directorio_extensiones/gwindows/
echo " hecho."

# Librería Vorple para Inform 6:
echo -n "Copiando archivos de la librería Vorple para Inform 6..."
if [ -d $directorio_extensiones/vorple ]; then
	sudo rm -r $directorio_extensiones/vorple
fi
sudo mkdir $directorio_extensiones/vorple
sudo cp Vorple6/*.h $directorio_extensiones/vorple/
sudo cp Vorple6/JustEnoughGlulx/JustEnoughGlulx.h $directorio_extensiones/vorple/
echo " hecho."

# Otras extensiones:
echo -n "Copiando archivos de otras extensiones..."
if [ -d $directorio_extensiones/other ]; then
	sudo rm -r $directorio_extensiones/other
fi
sudo mkdir $directorio_extensiones/other
sudo cp Extensions/*.h $directorio_extensiones/other/
sudo ln -s $directorio_extensiones/other/dainunek.h $directorio_extensiones/other/Dainunek.h
sudo ln -s $directorio_extensiones/other/damusix.h $directorio_extensiones/other/Damusix.h
sudo ln -s $directorio_extensiones/other/infglk.h $directorio_extensiones/other/InfGlk.h
echo " hecho."
echo " "

# Script de compilación:
if [ -f ../compila.sh ]; then
	rm ../compila.sh
fi
cp compila.sh ../

echo $directorio_librerias
sudo ls --color=auto $directorio_librerias
echo " "

echo $directorio_extensiones
sudo ls --color=auto $directorio_extensiones
echo " "

echo $directorio_extensiones/gwindows
sudo ls --color=auto $directorio_extensiones/gwindows/
echo " "

echo $directorio_extensiones/vorple
sudo ls --color=auto $directorio_extensiones/vorple/
echo " "

echo $directorio_extensiones/other
sudo ls --color=auto $directorio_extensiones/other/
echo " "

#sudo -k
