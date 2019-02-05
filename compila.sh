#! /bin/sh

#===============================================================================
# Script para compilar y ejecutar relatos interactivos programados en Inform 6.
# Herramientas utilizadas:
#	<>	bresc:			Blorb resource compiler (sólo en Glulx)
#	<>	gargoyle-free:	Intérprete multi-plataforma
#	<>	inform:			Compilador Inform 6
#-------------------------------------------------------------------------------

bresc_location=~/data/bin
zcode_interpreter=gargoyle-free;
glulx_interpreter=gargoyle-free;

inform_path=,/usr/share/inform6/library/,/usr/share/inform6/extensions/,/usr/share/inform6/extensions/gwindows/,/usr/share/inform6/extensions/vorple/

#-------------------------------------------------------------------------------

preprocesa_textos() {
	for i in *.xinf; do
	    [ -f "$i" ] || break
		perl ./libs/preprocesaTexto.pl "$i" "${i%.xinf}.inf"
	done
}

limpia_ficheros_temporales() {
	for i in *.xinf; do
	    [ -f "$i" ] || break
		rm "${i%.xinf}.inf"
	done
	if [ -e "$gameFile.ulx" ]; then
		rm $gameFile.ulx
	fi
}

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

#===============================================================================
# Compilar el relato para GLULX (sin multimedia)
#-------------------------------------------------------------------------------
if [ "$op" = "3" ]; then

	if [ -e "../$gameFile.ulx" ]; then
		rm ../$gameFile.ulx
	fi

	echo "============================================="
	echo "COMPILANDO PARA GLULX (sin multimedia)..."
	echo "---------------------------------------------"
	preprocesa_textos
	inform +include_path=$inform_path -G $gameFile.inf ../$gameFile.ulx
	limpia_ficheros_temporales

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

	if [ -e "../$gameFile.gblorb" ]; then
		rm ../$gameFile.gblorb
	fi

	echo "============================================="
	echo "COMPILANDO PARA GLULX..."
	echo "---------------------------------------------"
	preprocesa_textos
	inform +include_path=$inform_path -G $gameFile.inf $gameFile.ulx
	$bresc_location/bres $gameFile.res
	inform +include_path=$inform_path -G $gameFile.inf
	$bresc_location/bresc $gameFile.res
	mv $gameFile.gblorb ../$gameFile.gblorb
	limpia_ficheros_temporales

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

	if [ -e "../$gameFile.z5" ]; then
		rm ../$gameFile.z5
	fi

	echo "============================================="
	echo "COMPILANDO PARA MÁQUINA-Z..."
	echo "---------------------------------------------"
	preprocesa_textos
	inform +include_path=$inform_path $gameFile.inf ../$gameFile.z5
	limpia_ficheros_temporales

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
