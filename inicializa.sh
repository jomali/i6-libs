#! /bin/sh
# Script de inicializaciónn de librerías y extensiones para Inform 6.
# Versión: 3.0 (2018/09/18)

# Versión de la librería Inform:
inform_version="611"
# Rutas:
directorio_librerias="/usr/share/inform6/library"
directorio_extensiones="/usr/share/inform6/extensions"
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
sudo cp Inform6/library$inform_version/*.h $directorio_librerias/
sudo ln -s $directorio_librerias/english.h $directorio_librerias/English.h
sudo ln -s $directorio_librerias/grammar.h $directorio_librerias/Grammar.h
sudo ln -s $directorio_librerias/parser.h $directorio_librerias/Parser.h
sudo ln -s $directorio_librerias/verblib.h $directorio_librerias/Verblib.h
sudo ln -s $directorio_librerias/verblib.h $directorio_librerias/VerbLib.h
sudo cp INFSP6/*.h $directorio_librerias/
sudo ln -s $directorio_librerias/infspr.h $directorio_librerias/INFSPR.h
sudo ln -s $directorio_librerias/spanish.h $directorio_librerias/Spanish.h
sudo ln -s $directorio_librerias/spanishg.h $directorio_librerias/SpanishG.h
cp Inform6/library$inform_version/README README_temp
echo " " >> README_temp
cat INFSP6/README >> README_temp
sudo mv README_temp $directorio_librerias/README
echo " hecho."

# Otras extensiones:
echo -n "Copiando archivos de extensiones generales..."
if [ -d $directorio_extensiones ]; then
	sudo rm -r $directorio_extensiones
fi
sudo mkdir $directorio_extensiones
sudo cp Extensions/*.h $directorio_extensiones/
sudo ln -s $directorio_extensiones/dainunek.h $directorio_extensiones/Dainunek.h
sudo ln -s $directorio_extensiones/damusix.h $directorio_extensiones/Damusix.h
sudo ln -s $directorio_extensiones/infglk.h $directorio_extensiones/InfGlk.h
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

#sudo -k
