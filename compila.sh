#! /bin/sh

#===============================================================================
# Script para compilar y ejecutar relatos interactivos programados en Inform 6.
# Herramientas utilizadas:
#	<>	inform:			Compilador Inform 6
#	<>	bresc:			Blorb resource compiler (sólo en Glulx)
#	<>	gargoyle-free:	Intérprete multi-plataforma
#-------------------------------------------------------------------------------

bresc_location=~/data/bin
zcode_interpreter=gargoyle-free;
glulx_interpreter=gargoyle-free;

inform_path=,/usr/share/inform6/library/,/usr/share/inform6/extensions/,/usr/share/inform6/extensions/gwindows/,/usr/share/inform6/extensions/vorple/

#-------------------------------------------------------------------------------

if [ "$1" != "" ]; then gameFile=$1;
else
	echo -n "Introduce el nombre del archivo (sin la extensión): ";
	read gameFile;
	echo " ";
fi
if [ ! -e "$gameFile.inf" ]; then
	echo "El archivo '$gameFile.inf' no existe.";
	exit 1;
fi

if [ "$2" != "" ]; then op=$2;
else
	echo "[1] Compilar el relato para MÁQUINA-Z"
	echo "[2] Compilar el relato para GLULX"
	echo "[3] Compilar el relato para GLULX (sin multimedia)"
	echo -n "Selecciona una opción: "
	read op;
	echo " "
fi

perl ./libs/preprocesaTexto.pl ./$gameFile\_objects.txt ./$gameFile\_langOM.inf

#===============================================================================
# Compilar el relato para GLULX (sin multimedia)
#-------------------------------------------------------------------------------
if [ "$op" = "3" ]; then
	echo "============================================="
	echo "COMPILANDO PARA GLULX (sin multimedia)..."
	echo "---------------------------------------------"
	inform +include_path=$inform_path -G $gameFile.inf ../$gameFile.ulx

	echo " "
	echo -n "Pulsa cualquier tecla para ejecutar la aplicación ('q' para salir): "
	read key

	if [ "$key" = "q" ]; then exit 0;
	fi
	if [ "$key" = "Q" ]; then exit 0;
	fi
	cd ..
	$glulx_interpreter $gameFile.ulx

#===============================================================================
# Compilar el relato para GLULX
#-------------------------------------------------------------------------------
elif [ "$op" = "2" ]; then
	echo "============================================="
	echo "COMPILANDO PARA GLULX..."
	echo "---------------------------------------------"
	inform +include_path=$inform_path -G $gameFile.inf $gameFile.ulx
	$bresc_location/bres $gameFile.res
	inform +include_path=$inform_path -G $gameFile.inf
	$bresc_location/bresc $gameFile.res
	mv $gameFile.gblorb ../$gameFile.gblorb
	rm $gameFile.ulx

	echo " "
	echo -n "Pulsa cualquier tecla para ejecutar la aplicación ('q' para salir): "
	read key

	if [ "$key" = "q" ]; then exit 0;
	fi
	if [ "$key" = "Q" ]; then exit 0;
	fi
	cd ..
	$glulx_interpreter $gameFile.gblorb

#===============================================================================
# Compilar el relato para MÁQUINA-Z
#-------------------------------------------------------------------------------
else
	echo "============================================="
	echo "COMPILANDO PARA MÁQUINA-Z..."
	echo "---------------------------------------------"
	inform +include_path=$inform_path $gameFile.inf ../$gameFile.z5

	echo " "
	echo -n "Pulsa cualquier tecla para ejecutar la aplicación ('q' para salir): "
	read key

	if [ "$key" = "q" ]; then exit 0;
	fi
	if [ "$key" = "Q" ]; then exit 0;
	fi
	cd ..
	$zcode_interpreter $gameFile.z5
fi

exit 0;
