!
! GlulxBox.h - (c) Eliuk Blau
!

!===============================================================================
!  DREAMBYTES ADVENTURES: GLULX BOXED QUOTATION FOR INFORM 7
!  Codigo Fuente
!===============================================================================
!
!  Archivo :  Glulx Boxed Quotation.i7x
!  Fecha   :  2009/03/19
!  Version :  2
!  Autor   :  Eliuk Blau
!  e-Mail  :  eliukblau (AT) gmail.com
!
!===============================================================================
!
!  Log:
!  2009/03/19  Eliuk Blau - Nuevo Release: ** Glulx Boxed Quotation v2 **
!                         - Se corrigen algunas mensajes mal escritos.
!                         - Se incorpora la posibilidad de evitar el
!                           recuadro ASCII en las cajas de texto.
!  2009/02/25  Eliuk Blau - Primer Release: ** Glulx Boxed Quotation v1 **
!                         - Se crea el archivo.
!
!===============================================================================
!===============================================================================


Global _CurrQuoteArr_;
Global _CurrQuoteMaxLen_;

Array _GlulxBoxQuoteAux_ --> 4;

[ Box__Routine maxlen arr
  i aux lines linelen winwide indent lastnl parwin;

  aux = aux; ! Evita warning
  _CurrQuoteArr_ = arr;
  _CurrQuoteMaxLen_ = maxlen;
  
  indent = 4;
  lastnl = true;
  lines = arr-->0;
  
  if (gg_quotewin == 0) {
    gg_arguments-->0 = lines;
    i = InitGlkWindow(GG_QUOTEWIN_ROCK);
    if (i == 0) {
      glk_stylehint_set(wintype_TextGrid, style_Normal,
                        stylehint_ReverseColor, 0);
      glk_stylehint_set(wintype_TextGrid, style_BlockQuote,
                        stylehint_ReverseColor, 1);
      gg_quotewin = glk_window_open(gg_mainwin,
                                    winmethod_Fixed + winmethod_Above +
                                    winmethod_NoBorder,
                                    lines + 4, wintype_TextGrid,
                                    GG_QUOTEWIN_ROCK);
    }
  } else {
    parwin = glk_window_get_parent(gg_quotewin);
    glk_window_set_arrangement(parwin, $112, lines + 4, 0);
  }
  
  if (gg_quotewin) {
    glk_window_get_size(gg_quotewin, gg_arguments, 0);
    winwide = gg_arguments-->0;
    indent = (winwide - (maxlen + 4)) / 2;
    glk_window_clear(gg_quotewin);
    glk_set_window(gg_quotewin);
    lastnl = false;
  }
  
  new_line; if (lastnl) { new_line; }
  if (gg_quotewin) {
    glk_set_style(style_Normal); spaces indent;
    glk_set_style(style_BlockQuote);
  } else {
    glk_set_style(style_Preformatted);
    spaces indent;
  }
  
  #ifdef GBOXQUOTE_NOFRAME;
    spaces maxlen + 4;
  #ifnot;
    print (char) 43;
    for (aux = 0 : aux < maxlen + 2 : aux = aux + 1) { print (char) 45; }
    print (char) 43;
  #endif; ! GBOXQUOTE_NOFRAME
  
  glk_set_style(style_Normal);
  new_line;
  
  for (i = 0 : i < lines : i = i + 1) {
    (arr-->(i + 1)).print_to_array(_GlulxBoxQuoteAux_, 4);
    linelen = _GlulxBoxQuoteAux_-->0;
    if (gg_quotewin) {
      glk_set_style(style_Normal); spaces indent;
      glk_set_style(style_BlockQuote);
    } else {
      glk_set_style(style_Preformatted);
      spaces indent;
    }
    
    #ifdef GBOXQUOTE_NOFRAME;
      spaces 2;
    #ifnot;
      print (char) 124, (char) 32;
    #endif; ! GBOXQUOTE_NOFRAME
    
    print (string) arr-->(i + 1);
    spaces (maxlen - linelen);
    
    #ifdef GBOXQUOTE_NOFRAME;
      spaces 2;
    #ifnot;
      print (char) 32, (char) 124;
    #endif; ! GBOXQUOTE_NOFRAME
    
    glk_set_style(style_Normal);
    new_line;
  }
  
  if (gg_quotewin) {
    glk_set_style(style_Normal); spaces indent;
    glk_set_style(style_BlockQuote);
  } else {
    glk_set_style(style_Preformatted);
    spaces indent;
  }
  
  #ifdef GBOXQUOTE_NOFRAME;
    spaces maxlen + 4;
  #ifnot;
    print (char) 43;
    for (aux = 0 : aux < maxlen + 2 : aux = aux + 1) { print (char) 45; }
    print (char) 43;
  #endif; ! GBOXQUOTE_NOFRAME
  
  glk_set_style(style_Normal);
  new_line; if (lastnl) { new_line; }
  
  if (gg_quotewin) { glk_set_window(gg_mainwin); }
];

