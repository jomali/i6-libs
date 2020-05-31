#!/usr/bin/perl

#	File:		preprocesaTexto.pl
#	Author(s):	J. Francisco Martín <jfm.lisaso@gmail.com>
#	Version:	3.5
#	Released:	2020/05/31
#
#	Script Perl para preprocesar código fuente escrito en lenguaje Inform 6.
#	Permite añadir ciertas etiquetas a las descripciones de los objetos, que
#	tras el preprocesado son sustituidas por funciones para manipular el
#	estilo de los textos, crear sentencias condicionales, listar objetos
#	contenidos por otro objeto o crear hipervínculos, por ejemplo.
#
#	HISTORIAL DE VERSIONES
#
#	3.5: 2020/05/31	Modificada la expresión regular para que la sustitución de
#					género de un objeto acepte formas tanto masculina como
#					femenina
#	3.4: 2019/09/17	Al imprimir el listado de objetos contenidos por otro se
#					dejan de listar los objetos ocultos por defecto
#	3.3: 2019/09/12 Se omiten los comentarios si empiezan por '!!' (sin las
#					comillas)
#	3.2: 2019/08/07	Se generalizan las etiquetas para abrir secuencias
#					condicionales: si un objeto dado es plural; si se cumple
#					una condición dada
#	3.1: 2019/02/20	El nombre de la rutina encargada de crear hipervínculos se
#					traslada a la variable $hyperlinks_routine para facilitar
#					su modificación
#	3.0: 2018/12/24	Se redefinen las expresiones regulares para permitir
#					ejeutar el preprocesado sobre cualquier fichero con código
#					fuente escrito en Inform 6. Se añaden etiquetas para
#					mostrar texto condicional en función del número del objeto
#					controlado por el usuario y de la hora del día del modelo
#					de mundo.
#	2.1: 2018/10/09	Se utiliza una nueva rutina para crear hipervínculos
#	2.0: 2017/09/11	Redefinición de las expresiones regulares.
#	1.1: 2016/06/18	Añade etiquetas para crear hipervínuclos con distintas
#					configuraciones de parámetros.
#	1.0: 2014/09/20 Incluye las etiquetas básicas para cambiar estilos de
#					texto, listar objetos contenidos dentro de otro objeto, y
#					crear hipervínculos.

$hyperlinks_routine = "PRT__";

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

# Sustituciones (EL ORDEN EN QUE SE HACEN IMPORTA):
for (@lines) {

	# Comentarios:
	s/!!.*\n//g;

	# Caracteres '[' y ']':
	s/\\\[/", (char) 91, "/g;
	s/\\\]/", (char) 93, "/g;

	# Etiquetas para estilo fuerte: **texto**
	s/(?<!\\)\*{2}([^\*\n]+)(?<!\\)\*{2}/", (strong) "\1", "/g;
	# Etiquetas para el estilo enfatizado: *texto*
	s/(?<!\\)\*([^\*\n]+)(?<!\\)\*/", (emph) "\1", "/g;
	# Etiquetas para el estilo código: `texto`
	s/(?<!\\)`([^`\n]+)(?<!\\)`/", (monospaced) "\1", "/g;

	# Abre secuencia condicional si 'object' es plural: [plural:object]
	s/\[\s*plural:\s*(.+?)\s*\]/";\nif (IsPluralNoun(\1)) {\nprint "/g;
	# Abre secuencia condicional genérica: [if:condition]
	s/\[\s*if:\s*(.+?)\s*\]/";\nif (\1) {\nprint "/g;
	# Secuencia condicional: [else]
	s/\[\s*else\s*\]/";\n} else {\nprint "/g;
	# Final de la secuencia condicional: [fi]
	s/\[\s*fi\s*\]/";\n}\nprint "/g;

	# Nombre corto del objeto junto al artículo determinado adecuado:
	# [el/la/los/las objeto]
	s/\[\s*(el|la|los|las)\s+(.+?)\s*\]/", (the) \2, "/g;
	# [El/La/Los/Las objeto]
	s/\[\s*(El|La|Los|Las)\s+(.+?)\s*\]/", (The) \2, "/g;
	# [al/a la/a los/a las objeto]
	s/\[\s*(al|a\s+la|a\s+los|a\s+las)\s+(.+?)\s*\]/", (al) \2, "/g;
	# [Al/A la/A los/A las objeto]
	s/\[\s*(Al|A\s+la|A\s+los|A\s+las)\s+(.+?)\s*\]/", (_Al) \2, "/g;
	# [del/de la/de los/de las objeto]
	s/\[\s*(del|de\s+la|de\s+los|de\s+las)\s+(.+?)\s*\]/", (del) \2, "/g;
	# [Del/De la/De los/De las objeto]
	s/\[\s*(Del|De\s+la|De\s+los|De\s+las)\s+(.+?)\s*\]/", (_Del) \2, "/g;

	# Nombre corto del objeto junto al artículo indeterminado adecuado:
	# [un/una/unos/unas objeto]
	s/\[\s*(un|una|unos|unas)\s+(.+?)\s*\]/", (a) \2, "/g;
	# [Un/Una/Unos/Unas objeto]
	s/\[\s*(Un|Una|Unos|Unas)\s+(.+?)\s*\]/", (A) \2, "/g;

	# Terminación de número adecuada: [n obj]
	s/\[\s*n\s+(.+?)\s*\]/", (n) \1, "/g;
	# Terminación de género adeuada: [o/a obj]
	s/\[\s*(o|a)\s+(.+?)\s*\]/", (o) \2, "/g;

	# Lista de objetos contenidos por otro objeto:
	# [lista de objetos en/sobre obj<códigos de listado>]
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\<\s*(.+?)\s*\>\s*\]/";\nWriteListFrom(child(\2), \3);\nprint "/g;
	# [lista de objetos en/sobre obj]
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\]/";\nWriteListFrom(child(\2), ENGLISH_BIT + CONCEAL_BIT);\nprint "/g;

	# Hipervínculo asociado a un objeto, con texto alternativo:
	# [obj](texto:código_estilo)
	s/(?<!\\)\[([^\[\]]+)(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\:\s*([^\(\)\:\s]+)(?<!\\)\)/";\n$hyperlinks_routine(\1, "\2", \3);\nprint "/g;
	# [obj](texto)
	s/(?<!\\)\[([^\[\]]+)(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\)/";\n$hyperlinks_routine(\1, "\2");\nprint "/g;

	# Hipervínculo asociado a un texto:
	# [](texto:código_estilo)
	s/(?<!\\)\[(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)\:\s*([^\(\)\:\s]+)(?<!\\)\)/";\n$hyperlinks_routine("\1", "\1", \2);\nprint "/g;
	# [](texto)
	s/(?<!\\)\[(?<!\\)\](?<!\\)\(([^\(\)\:]+)(?<!\\)(?<!\\)\)/";\n$hyperlinks_routine("\1", "\1");\nprint "/g;

	# Imprime el nombre corto del objeto:
	s/\[\s*(.+?)\s*\]/", (name) \1, "/g;

	print;
}

# Cierra el archivo de salida:
close STDOUT;
