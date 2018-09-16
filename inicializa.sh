#! /bin/sh
# Script de inicialización de librerías y extensiones para Inform 6.
# Versión: 2.0 (2018/09/16)

# Rutas:
fichero_librerias="/usr/share/inform/6.31/module"
fichero_extensiones="/usr/share/inform/6.31/include"
fichero_sintaxis_gtksourceview="/usr/share/gtksourceview-3.0/language-specs"
fichero_paquetes_atom="$HOME/.atom/packages"

sudo true

# Resaltado de sintaxis para GtkSourceView:
echo -n "Copiando archivo de resaltado de sintaxis para GtkSourceView..."
sudo cp inform6.lang $fichero_sintaxis_gtksourceview
echo " hecho."

# Definición de la gramática de Inform 6 para Atom:
echo -n "Copiando archivos de gramática para Atom..."
if [ -d $fichero_paquetes_atom]; then
	if [ -d $fichero_paquetes_atom/language-inform6]; then
		sudo rm -r $fichero_paquetes_atom/language-inform6
	fi
	sudo cp language-inform6 $fichero_paquetes_atom/language-inform6
fi
echo " hecho."

# Librerías Inform 6 e INFSP 6:
echo -n "Copiando archivos de las librerías Inform 6 e INFSP 6..."
if [ -d $fichero_librerias ]; then
	sudo rm -r $fichero_librerias
fi
sudo mkdir $fichero_librerias
sudo cp InformLibrary/*.h $fichero_librerias/
sudo cp INFSP6/*.h $fichero_librerias/
cp InformLibrary/README README_temp
echo " " >> README_temp
cat INFSP6/README >> README_temp
sudo mv README_temp $fichero_librerias/README
echo " hecho."

# Librería GWindows (DA-Gwindows v1.2):
echo -n "Copiando archivos de la librería GWindows (DA-Gwindows v1.2)..."
if [ -d $fichero_extensiones/gwindows ]; then
	sudo rm -r $fichero_extensiones/gwindows
fi
sudo mkdir $fichero_extensiones/gwindows
sudo cp DaGWindows/* $fichero_extensiones/gwindows/
# Extensión de barra de estado para GWindows:
sudo cp Extensions/gstatusX.h $fichero_extensiones/gwindows/
echo " hecho."

# Librería Vorple para Inform 6:
echo -n "Copiando archivos de la librería Vorple para Inform 6..."
if [ -d $fichero_extensiones/vorple ]; then
	sudo rm -r $fichero_extensiones/vorple
fi
sudo mkdir $fichero_extensiones/vorple
sudo cp Vorple6/*.h $fichero_extensiones/vorple/
sudo cp Vorple6/JustEnoughGlulx.h $fichero_extensiones/vorple/
echo " hecho."

# Otras extensiones:
echo -n "Copiando archivos de otras extensiones..."
if [ -d fichero_extensiones/other ]; then
	sudo rm -r $fichero_extensiones/other
fi
sudo mkdir $fichero_extensiones/other
sudo cp Extensions/*.h $fichero_extensiones/other/
sudo ln -s $fichero_extensiones/other/dainunek.h $fichero_extensiones/other/Dainunek.h
sudo ln -s $fichero_extensiones/other/damusix.h $fichero_extensiones/other/Damusix.h
sudo ln -s $directorio_extensiones/other/infglk.h $directorio_extensiones/other/InfGlk.h
echo " hecho."
echo " "

echo $fichero_librerias
sudo ls --color=auto $fichero_librerias
echo " "

echo $fichero_extensiones
sudo ls --color=auto $fichero_extensiones
echo " "

echo $fichero_extensiones/gwindows
sudo ls --color=auto $fichero_extensiones/gwindows/
echo " "

echo $fichero_extensiones/vorple
sudo ls --color=auto $fichero_extensiones/vorple/
echo " "

echo $fichero_extensiones/other
sudo ls --color=auto $fichero_extensiones/other/
echo " "

#sudo -k
