#!/usr/bin/perl

#	File:			preprocesaTexto.pl
#	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
#	Version:		2.0
#	Released:		2017/09/11
#
#	Script Perl para preprocesar un archivo de texto. Sustituye ciertas
#	etiquetas de texto por funciones definidas dentro del relato para manipular
#	el estilo de los textos, listar objetos contenidos por otro objeto, o crear
#	hipervínculos, por ejemplo.
#
#	HISTORIAL DE VERSIONES:
#
#	2.0: 2017/09/11	Redefinición de las expresiones regulares.
#	1.1: 2016/06/18	Añade etiquetas para crear hipervínuclos con distintas
#					configuraciones de parámetros.
#	1.0: 2014/09/20 Incluye las etiquetas básicas para cambiar estilos de
#					texto, listar objetos contenidos dentro de otro objeto, y
#					crear hipervínculos.

if ($#ARGV != 1) {
	print "Se deben especificar los archivos de entrada y salida del script.";
	print "\n\n";
	exit 4;
}

$input_file = $ARGV[0];
$output_file = $ARGV[1];

# Se abre el archivo de entrada:
open (FILE, "<$input_file")
	or die "No se pudo abrir el archivo de entrada $input_file: $!\n";
@lines = <FILE>;
close FILE;

# Se abre el archivo de salida:
open (STDOUT, ">$output_file")
	or die "No se pudo abrir el archivo de salida $output_file: $!\n";

# Se hacen las sustituciones (EL ORDEN EN QUE SE HACEN IMPORTA)
for (@lines) {

	# Omite las líneas de comentario (aquellas que empiezan por '!' o '#'):
	next if /^\s*(!|#)/;

	# Imprime los caracteres '[' y ']':
	s/\\\[/", (char) 91, "/g;
	s/\\\]/", (char) 93, "/g;

	# Transforma las etiquetas '**' en estilo fuerte:
	s/(?<!\\)\*{2}([^\*\n]+)(?<!\\)\*{2}/", (strong) "\1", "/g;
	# Transforma las etiquetas '*' en estilo enfatizado:
	s/(?<!\\)\*([^\*\n]+)(?<!\\)\*/", (emph) "\1", "/g;
	# Transforma las etiquetas '`' en estilo de tipo código:
	s/(?<!\\)`([^`\n]+)(?<!\\)`/", (code) "\1", "/g;

	# Imprime el nombre corto del objeto con el artículo determinado adecuado:
	s/\[\s*(el|la|los|las)\s+(.+?)\s*\]/", (the) \2, "/g;
	s/\[\s*(El|La|Los|Las)\s+(.+?)\s*\]/", (The) \2, "/g;
	# Ídem, considerando las contracciones 'al' y 'del':
	s/\[\s*(al|a\s+la|a\s+los|a\s+las)\s+(.+?)\s*\]/", (al) \2, "/g;
	s/\[\s*(Al|A\s+la|A\s+los|A\s+las)\s+(.+?)\s*\]/", (_Al) \2, "/g;
	s/\[\s*(del|de\s+la|de\s+los|de\s+las)\s+(.+?)\s*\]/", (del) \2, "/g;
	s/\[\s*(Del|De\s+la|De\s+los|De\s+las)\s+(.+?)\s*\]/", (_Del) \2, "/g;
	# Imprime el nombre corto del objeto con el artículo indeterminado adecuado:
	s/\[\s*(un|una|unos|unas)\s+(.+?)\s*\]/", (a) \2, "/g;
	s/\[\s*(Un|Una|Unos|Unas)\s+(.+?)\s*\]/", (A) \2, "/g;

	# Imprime la terminación (n/o) adecuada:
	s/\[\s*n\s+(.+?)\s*\]/", (n) \1, "/g;
	s/\[\s*o\s+(.+?)\s*\]/", (o) \1, "/g;

	# Imprime lista de objetos contenidos en otro objeto:
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\<\s*(.+?)\s*\>\s*\]/";\nWriteListFrom(child(\2), \3);\nprint "/g;
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\]/";\nWriteListFrom(child(\2), ENGLISH_BIT + PARTINV_BIT);\nprint "/g;

	# Hipervínculo asociado a un objeto, con un texto alternativo:
	s/(?<!\\)\[([^\[\]]+)(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\:\s*([^\(\)\:\s]+)(?<!\\)\)/";\nHyperlink(\1, "\2", \3);\nprint "/g;
	s/(?<!\\)\[([^\[\]]+)(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\)/";\nHyperlink(\1, "\2", 0);\nprint "/g;
	# Hipervínculo creado a partir de un texto:
	s/(?<!\\)\[(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\:\s*([^\(\)\:\s]+)(?<!\\)\)/";\nHyperlink("\1", "\1", \2);\nprint "/g;
	s/(?<!\\)\[(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)(?<!\\)\)/";\nHyperlink("\1", "\1", 0);\nprint "/g;

	# Imprime el nombre corto del objeto:
	s/\[\s*(.+?)\s*\]/", (name) \1, "/g;

	print;
}

# Cierra el archivo de salida:
close STDOUT;
