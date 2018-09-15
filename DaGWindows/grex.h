!GREX - GWindows Graphics Add-on
!
! GREX provides a set of scalable primitives for generating graphics
!  in a Glulx graphics window.
!
! Please note: Some GREX primitives are fairly slow; Glk does not
! like being made to do intensive graphical manipulation.
!  
! How GREX Works:
!  GREX provides a GWindows canvas widget. GREX_Primitive objects inside
!  the canvas are rendered according to their drawing rules
!  A GCanvas specifies the size of its own internal co-ordinate system.
!  At run-time, each Primitive's size is recalibrated to correspond with the
!  actual size of the canvas. Primitives are drawn in order, so younger primitives will
!  overlap elder ones.
!  
!
! Classes: 
! GCanvas: This is a GWindows widget representing a GREX-enabled window.
!       It has three relevant properties:
!         col - the background color of the window
!         scale_width, scale_height - this is the "model co-ordinate system"
!               for the canvas (default: 1000x1000). Primitives are
!               positioned relative to this co-ordinate system, so
!               a primitive located at (500,500) will appear in the center
!               of the canvas, regardless of the actual canvas size. (You will
!               probably want to adjust the scale_width and height to reflect
!               the desired aspect ratio of the canvas)
!
! Primitives:
! GREX_Primitive : This is the base class for all GREX primitives.
!       GREX primitives provide the following properties:
!       xpos, ypos  - the primitive's location in the model co-ordinate space
!       width,height - the primitive's width and height (many primitives derive this)
!       redraw(x) - method to render the primitive. The parameter is the
!               winid (*not* the GWindow) for the canvas.
!       prepare(x) - This is called immediately before rendering. The parameter
!               is the Canvas (which generally should be the parent of the primitive)
!               The primitive is expected to "prepare" itself for use
!       col - the color of the primitive
!       release(x) - The converse of prepare; any work that should be done after
!               drawing can be done here.
!
!       GREX primitives have the following additional properties, which are set
!       by GREX:
!       xx,yy - the *actual* location of the primitive. In the redraw function,
!               you should use these values, and *not* xpos,ypos
!       ww,hh - the actual width and height.
!
! Grex_Rectangle (fast) - Draws a colored rectangle at the given (xpos,ypos) of
!       the specified size
! Grex_Point (fast) - Draws a single point
!    Properties: thickness - size of the point
! Grex_Box (fair) - Draws a rectangular box, a "hollowed out" version
!  of Grex_Rectangle
!    Properties: thickness - width of the lines
! Grex_HLine (fast) - Draws a horizontal line extending right from (xpos,ypos)
!    Properties: thickness - thickness of the line
!                length - length of the line
! Grex_VLine (fast) - Draws a vertical line extending down from its position
!    Properties: as HLine
! Grex_Line (slow) - draws a line between any two points
!   Notes: For horizontal and vertical lines, this is fairly fast, but
!       still not as fast as HLine and VLine. Performance decreases as the
!       slope of the line approaches 1
!   Properties (endx, endy) The endpoint of the line
!               thickness - as above
! Grex_Sprite (fast) - draws a blorb image
!       Properties: image - the blorb image to draw
! Grex_AutoSprite (fast) - draws a blorb image
!    Notes: This is very slightly slower than Grex_Sprite, but it automatically
!       sets the model-size of the sprite to the actual size of the image.
!       If the model co-ordinate system reflects the aspect ratio of the screen,
!       AutoSprites will always have the correct proportions.
! Grex_PolyLine (slow) - draws a polyline of its children. Children of a
!        PolyLine should each provide an xpos and ypos property. The polyline
!        will be drawn through the points in order.
!       Notes: The time to draw a polyline is equal to the time to draw a line
!               times the number of segments
!       Properties: as Line
! Grex_PolyLoop (slow) - As polyline, but the final segment connects back to
!       the first point
!
! Grex_Pixmap (very slow) - Draws an arbitrary bitmapped figure
!       properties:  bitmap -  the bitmap to draw
!               A bitmap is an array which describes the color of every
!               pixel in a rectangular region. The Grex Pixmap format is this:
!               -->0 and -->1 are taken to be the width and height of the pixmap.
!               The remaining entries are the pixel values in row-major form.
!               For example:
!               Array pixmap --> 5 5
!                (-1) (-1) 0   (-1) (-1)
!                (-1) (-1) 0   (-1) (-1)
!                0     0    $ff    0     0
!                (-1) (-1) 0 (-1) (-1)
!                (-1) (-1) 0 (-1) (-1);
!               This is a pixmap for a black cross with a blue dot in the middle.
!                The pixmap is 5x5, so
!               every group of five entries denotes one row of the map.
!               The special value (-1) indicates that nothing should be drawn
!               for this square; it will be transparent.
!
! Grex_Bitmap (very slow) - Draws an arbitrary bilevel image
!    properties: col - the color of the bitmap
!                bitmap - the bitmap to draw
!                Bitmaps are a compressed form of pixmaps for black-and-white
!                images. They are somewhat faster and substantially smaller
!                than Pixmaps.
!                In a bitmap, binary values are used to indicate whether or not
!                a particular pixel should be opaque. Entries -->0 and -->1
!                still hold the width and height. For example:
!                Array bitmap -> 0 0 0 8 0 0 0 5
!                       $$00010000
!                       $$00010000
!                       $$11111111
!                       $$00010000
!                       $$00010000;
!                 This is also a cross. Notice that we write the width
!                 as '0 0 0 8'; this is because we have chosen to use a
!                 byte array. We could have done this:
!                Array bitmap2 --> 8 5
!                       $$00010000000100001111111100010000
!                       $$00010000000000000000000000000000;
!                Which means the same thing, but is harder to read.
!                One further note about bitmaps: Because of the way they are
!                packed, the total width of a bitmap *must* be divisible by 8.
!                If you want another width, you must add zeroes to make it come
!                out to. (That is, if the width is 15, then every row must have
!                a length of 16. GREX will assume this, and round each row up
!                as it draws)
!                Here is a larger bitmap:
!               Array bigmap -> 0 0 0 16 0 0 0 8
!                      $$00010000 $$00001000
!                      $$00111000 $$00011100
!                      $$00010000 $$00001000
!                      $$00000000 $$00000000
!                      $$00000000 $$00000000
!                      $$01111111 $$11111100
!                      $$00000000 $$00100100
!                      $$00000000 $$00011000;
! Grex_String: (very slow/moderately slow) This primitive draws a string of
!       text.
!       The width of a Grex_String is the *total* width of the text;
!       the letters will be much larger in a string of 5 letters than in
!       a string of 50 if they both have the same width.
!       A Grex_String consists of a single line of text, without word or
!       line wrapping.
!       The maximum size of a string is determined by the constant
!       MAX_GREX_STRING, which defaults to 256.
!       Properties: text - any printable, the text of the string
!                   renderer - the character renderer.
!               To render a string, you must have a Grex_CharRenderer
!               A Grex_CharRenderer provides the following properties:
!                render(winid,char,color,x,y,width,height) -
!                        render the character x in the given window,
!                        at the given position, with the given color,
!                        width, and height.
!                        If the given character does not exist in the font,
!                        the renderer is free to render as it likes;
!                        it may render an approximation, a space, a
!                        "bad character" symbol, or nothing at all.
!                        It may not, however, crash.
!                getHeight(x) - return the "natural" height of the character
!                getWidth(x) - return the natural width of the character
!       Three types of Character renderer are defined, these all use
!       the property char_map to store their font.
!
!        Grex_Sprite_CharRenderer - This is for fonts which consist of
!               Blorb images. char_map is an associative array mapping
!               characters to blorb resources. See utility.h for
!               details on associative arrays. Characters may be any size,
!               but are assumed to be proportional to each other (that is,
!               if the image for an 'M' is twice as big as the image for an
!               'i', then 'M' will be drawn twice as big as 'i') Because
!               this is an associative array, you are not obligated to provide
!               every possible character; the default value should be a bitmap
!               to be used for invalid characters
!        Grex_BM_CharRenderer - this is for bitmapped fonts. Char_Map is
!               an associative array mapping characters to bitmaps. Characters
!               may be any size, but are assumed to be proportional to each
!               other. Because this is an associative array, you may
!               omit characters
!         Grex_FastBM_CharRenderer - this is a highly optimized renderer for
!               bitmapped fonts. char_map is a *flat* array of the bitmaps
!               (that is, if each bitmap is 32 bytes long, then the first 32
!               bytes is the bitmap for the space character, the next 32
!               is the bitmap for the exclamation point, etc.) in ASCII
!               order from ' ' to '~'. Because this is not an associative array,
!               you must provide a bitmap for *every* character in the range.
!               Furthermore, all the bitmaps must be the same size; the width and
!               height property of the renderer specifies the size of the font.
!               This is only suitable for fixed-pitch fonts, but is much faster than
!               the other renderers.
!
!   No fonts are included in GREX itself as they are very large. The file
!   gchar.h provides a 'Grex_Default_Renderer' which is a Grex_FastBM_CharRenderer
!   using an 8x8 font.
!
!         
!
ifndef GW_GREX_H;
Constant GW_GREX_H;
system_file;
GWin_Module "GREX" with number ".1B (Public Beta)";
Class GCanvas
 class GraphWin,
 with redraw [o  ;
                glk_window_set_background_color(self.winid, self.col);
                glk_window_clear(self.winid);
                objectloop(o in self)
                {
                  o.deep_prepare(self);
                  o.redraw(self.winid);
                  o.deep_release(self);
                 }
                ],
        scale_width 1000,
        scale_height 1000,
        col $ffffff;

Class Grex_Primitive
 with width, height, col, xpos, ypos, redraw [x; return x; ],
      ww, hh, xx, yy, lsw, lsh,
        deep_prepare [o;
                 if (self provides prepare) self.prepare(o);
                 if (~~(self.lsw==o.width && self.lsh == o.height))
                 {
                  self.xx = (self.xpos * o.width)/o.scale_width;
                  self.yy = (self.ypos * o.height)/o.scale_height;
                  self.ww = (self.width * o.width)/o.scale_width;
                  self.hh = (self.height * o.height)/o.scale_height;
                  self.lsh = o.width;
                  self.lsw = o.height;
                 }
                ],
        deep_release [ o;
!                  if (self provides release) self.release(o);
                  ];
Class Grex_Rectangle class Grex_Primitive
 with redraw [o;
                if (self.ww==0) self.ww=1;
                if (self.hh==0) self.hh=1;
GConsole.penon();
print "[GREX] Drawing rectangle: original size ", self.width, "x",self.height, ". Scaled size ",self.ww,"x",self.hh,".^";
GConsole.penoff();
                glk_window_fill_rect(o,self.col,self.xx,self.yy,self.ww,self.hh);
             ];
Class Grex_Sprite class Grex_Primitive
 with redraw [o;
                gwin_image_draw_auto(o,self.image, self.xx,self.yy,self.ww,self.hh);
             ],
       image;
Class Grex_AutoSprite class Grex_sprite
 with lastimage,
      prepare [; if (self.image ~= self.lastimage)
                 {
                  glk_image_get_info(self.image,self.&width,self.&height);
                  self.lastimage=self.image;
                  }
              ];
Class Grex_Hline class Grex_Rectangle
 with thickness 1,
      length,
      prepare [; self.height = self.thickness;
                 self.width = self.length;
                ];
Class Grex_Vline class Grex_Rectangle
 with thickness 1,
      length,
      prepare [; self.width = self.thickness;
                 self.height = self.length;
                ];
Class Grex_Box class Grex_Primitive
 with thickness 1, tt 1,
      prepare [o;
                self.tt = (self.thickness * o.width) / o.scale_width;
                if (self.tt==0) self.tt=1;
              ],
      redraw [o; 
GConsole.penon();
print "[GREX] Drawing box: original size ", self.width, "x",self.height, ", Thickness: ", self.thickness, ". Scaled size ",self.ww,"x",self.hh," Thickness:", self.tt, ".^";
GConsole.penoff();

                if (self.ww==0) self.ww=1;
                if (self.hh==0) self.hh=1;
                glk_window_fill_rect(o,self.col,self.xx,self.yy,self.ww,self.tt);
                glk_window_fill_rect(o,self.col,self.xx,self.yy,self.tt,self.hh);
                glk_window_fill_rect(o,self.col,self.xx,self.yy+self.hh,self.ww+self.tt,self.tt);
                glk_window_fill_rect(o,self.col,self.xx+self.ww,self.yy,self.tt,self.hh);
               ];
Class Grex_Line class Grex_Primitive
 with thickness 1, tt 1,
      endx, endy,
      prepare [o;
                self.tt = (self.thickness * o.width) / o.scale_width;
                if (self.tt==0) self.tt=1;
                self.width=self.endx;
                self.height=self.endy;
!                if (self.endx>self.xpos)
!                self.width  = self.endx - self.xpos;
!                else
!                self.width  = self.xpos - self.endx;
!                if (self.endy>self.ypos)
!                self.height = self.endy - self.ypos;
!                else
!                self.height = self.ypos - self.endy;
              ],
       redraw [ o d x y rl;
                 x = self.xx;
                 y = self.yy;
                 grex_line_render(o,self.col,self.tt,self.xx,self.yy,self.ww,self.hh);
                  ];

Class Grex_bitmap class Grex_Primitive
 with
    bitmap,
    redraw [o;
        if (self.bitmap-->0 % 8) self.bitmap-->0= self.bitmap-->0 + (8-(self.bitmap-->0 %8));
        Grex_Setscale(self.bitmap,self.ww,self.hh);
        Grex_bitmap_render(o,self.bitmap,self.col,self.xx,self.yy);
        ];
Class Grex_pixmap class Grex_bitmap
 with
   redraw [o;
            Grex_Setscale(self.bitmap,self.ww,self.hh);
            Grex_Pixmap_render(o,self.bitmap,self.xx,self.yy);
          ];
Class Grex_Palmap class Grex_bitmap
 with
   palette,
   redraw [o;
            Grex_Setscale(self.bitmap,self.ww,self.hh);
            Grex_Palmap_render(o,self.palette,self.bitmap,self.xx,self.yy);
          ];

Array Grex_BM --> 4;
[Grex_bitmap_render win bitmap cl xx yy x y cx cy kx ky c w h ct;
w=bitmap-->0;
h=bitmap-->1;
cx=Grex_BM-->0;
cy=Grex_BM-->1;
kx=Grex_BM-->2;
ky=Grex_BM-->3;
gconsole.penon();
print "[GREX] Rendering bitmap. Size is ",w,"x",h, ". Thickness is ", cx,",",cy,
        ". Cut lines are ",kx,",",ky,". Color: ",cl, "^";
gconsole.penoff();
   for(y=0:y<h:y=y+ky)
   {
   for(x=0:x<h:x=x+kx)
    {
      c=bitmap->(((w/8)*y+(x/8))+(2*WORDSIZE)) & (PowersOfTwo_TB-->(4+(x%8)));
      if (c)
!       glk_window_fill_rect(win,cl,xx+(x*cx),yy+(y*cy),cx,cy);
      ct++;
     else if (ct)
       {
        glk_window_fill_rect(win,cl,xx+((x-ct)*cx),yy+(y*cy),ct*cx,cy);
        ct=0;
       }
    }
       if (ct)
       glk_window_fill_rect(win,col,xx+((x-ct)*cx),yy+(y*cy),ct*cx,cy);
        ct=0;
   }
];
[Grex_Pixmap_render win bitmap xx yy x y cx cy kx ky c w h;
w=bitmap-->0;
h=bitmap-->1;
cx=Grex_BM-->0;
cy=Grex_BM-->1;
kx=Grex_BM-->2;
ky=Grex_BM-->3;

   for(y=0:y<h:y=y+ky)
   for(x=0:x<h:x=x+kx)
    { c=bitmap-->((w*y+x)+2);
      if (c~=-1)
      glk_window_fill_rect(win,c,xx+(x*cx),yy+(y*cy),cx,cy);
    }
];
[Grex_Palmap_render win pal bitmap xx yy x y cx cy kx ky c w h;
w=bitmap-->0;
h=bitmap-->1;
cx=Grex_BM-->0;
cy=Grex_BM-->1;
kx=Grex_BM-->2;
ky=Grex_BM-->3;

   for(y=0:y<h:y=y+ky)
   for(x=0:x<h:x=x+kx)
    { c=bitmap->((w*y+x)+(2*WORDSIZE));
      if (pal-->c ~= -1)
      glk_window_fill_rect(win,pal-->c,xx+(x*cx),yy+(y*cy),cx,cy);
    }
];
[ Grex_Setscale bitmap x y w h cx cy kx ky;
   w=bitmap-->0;
   h=bitmap-->1;
   cx=1;
   cy=1;
   kx=1;
   ky=1;
   if (x > w)
   cx = (x / w);
   else kx = (w / x);
   if (y > h)
    cy = (y / h);
   else ky = (h / y);
   Grex_BM-->0 = cx;
   Grex_BM-->1 = cy;
   Grex_BM-->2 = kx;
   Grex_BM-->3 = ky;
];
Class Grex_CharRenderer
 with render [;  ], char_map;
Class Grex_BM_CharRenderer class Grex_CharRenderer
 with render [ o x c xx yy ww hh v;
          v=Assoc_Lookup(x,self.char_map);
          Grex_setscale(v,ww,hh);
          Grex_Bitmap_Render(o,v, c,xx,yy);
        ],
       getheight [x v;
           v=Assoc_Lookup(x,self.char_map);
           return v-->1;
           ],
       getwidth [x v;
           v=Assoc_Lookup(x,self.char_map);
           return v-->0;
           ]
        ;
Class Grex_FastBM_CharRenderer class Grex_CharRenderer
 with width 8, height 8, number 0,
        w1,w2,w3,w4,mw,mh,
          render [ o x c xx yy ww hh v;
                if (self.number==0) self.number = self.height * (self.width/8) + 8;
          v=(x-' ')*self.number+self.char_map;
          if (ww==self.mw && hh==self.hh)
          {
           Grex_BM-->0 = self.w1;
           Grex_BM-->1 = self.w2;
           Grex_BM-->2 = self.w3;
           Grex_BM-->3 = self.w4;
          }
          else
          {
          Grex_setscale(v,ww,hh);
          self.w1 = Grex_BM-->0;
          self.w2 = Grex_BM-->1;
          self.w3 = Grex_BM-->2;
          self.w4 = Grex_BM-->3;
          self.mw = ww; self.mh =  hh;
          }
          Grex_Bitmap_Render(o,v, c,xx,yy);
        ],
       getheight [x;
                x=0; return self.width;
           ],
       getwidth [x;
       x=0; return self.height;
           ];
 
Class Grex_Sprite_CharRenderer class Grex_CharRenderer
 with render [ o x c xx yy ww hh v;
          v=Assoc_Lookup(x,self.char_map);
          gwin_image_draw_auto(o,v,xx,yy,ww,hh);
        ],
       ww,hh,
       getsize [x v;
                  v=Assoc_Lookup(x,self.char_map);
                  glk_image_get_info(v,self.&ww, self.&hh);
               ],
       getheight [x;
        self.getsize(x);
        return self.hh;
           ],
       getwidth [x;
        self.getsize(x);
        return self.ww;
           ];
Default MAX_GREX_STRING 256;
Array Grex_STR_flash -> MAX_GREX_STRING;
Class Grex_String class Grex_Primitive
 with renderer,
      text, length, lt, llength,
      prepare [o i;
                if (self.lt~=self.text)
                {
                 self.lt=self.text;
                 self.llength=printanytoarray(Grex_STR_flash,MAX_GREX_STRING,self.text);
                 self.length=0;
                 for(i=0:i<self.llength:i++)
                 self.length = self.length+self.renderer.getwidth(Grex_STR_flash->i);
                }
              ],
      redraw [o i l h x;
                printanytoarray(Grex_STR_flash,MAX_GREX_STRING,self.text);
                x=self.xx;
GConsole.penon();
print "[GREX] Drawing string: Size (scaled) ", self.ww, "x", self.hh, " String has ", self.llength, " characters.
        Total size is ", self.length, ". Rendering using ", (name) self.renderer, ".^";
GConsole.penoff();

                for(i=0:i<self.llength:i++)
                {
                l=(self.renderer.getwidth(Grex_STR_flash->i) *self.ww)/self.length;
                self.renderer.render(o,Grex_STR_flash->i,self.col,x,self.yy,l,self.hh);
                x = x + l;
                }
                ];

! based on code borrowed from John Cater                
[ Grex_line_render window col t x0 y0 x1 y1
    d dd ax ay sx sy x y;

  ! The following code is based upon 
  !  http://vinny.bridgeport.edu/MailArchives/cs411x-list/0113.html
  !  Digital Line Drawing
  !  by Paul Heckbert
  !  from "Graphics Gems", Academic Press, 1990
GConsole.penon();
print "[GREX] Rendering line from (", x0,",",y0,") to (",x1,",",y1,"), Color ", col, "; Thickness ", t,".^";
GConsole.penoff();
  dd = x1-x0;
  if (dd >= 0)
     ax = 2 * dd;
  else 
     ax = -2 * dd;
  if (dd >= 0)
     sx = 1;
  else 
     sx = -1;
  dd = y1-y0;
  if (dd >= 0)
     ay = 2 * dd;
  else 
     ay = -2 * dd;
  if (dd >= 0)
     sy = 1;
  else
     sy = -1;

  x = x0;
  y = y0;
  if ( ax > ay) { ! x dominant
        x0=1;
     d = ay - (ax / 2);
     while (x ~= x1)
     {
       if (d >= 0)
       {
          y = y + sy;
          d = d - ax;
       }
       x = x + sx;
       d = d + ay;
       if (y~=y0 || x==x1)
       {
       ! draw point x,y
       if (sx > 0)
       glk_window_fill_rect (window, col, x-x0, y0, x0, t);
       else glk_window_fill_rect (window, col, x, y0, x0, t);
       y0=y;
       x0=1;
       }
       else x0++;

     }
  }
  else { ! y dominant
        y0=1;
     d = ax - ( ay  / 2);
     while (y ~= y1)
     {
        if (d>=0)
	{
          x = x + sx;
          d = d - ay;
        }
        y = y + sy;
        d = d + ax;

       if (x~=x0 || y==y1)
       {
       ! draw point x,y
       if (sy > 0)
       glk_window_fill_rect (window, col, x0, y-y0, t, y0);
       else        glk_window_fill_rect (window, col, x0, y, t, y0);
       y0=1;
       x0=x;
       }    else y0++;


     }
  }

  return true;
];


Class Grex_Point class Grex_Rectangle
 with thickness 1, oxp,
      prepare [; if (self.xpos ~=self.oxp)
                {
                 self.xpos = self.xpos - (self.thickness / 2);
                 self.ypos = self.ypos - (self.thickness / 2);
                 self.width = self.thickness;
                 self.height = self.thickness;
                 self.oxp = self.xpos;
                }
               ];
Class Grex_PolyLine class Grex_Primitive
 with thickness 1,
        prepare [w o;

                objectloop(o in self) {
                o.deep_prepare(w);
                }
                ],
        redraw [ w o l;
GConsole.penon();
print "[GREX] Drawing polyline. ", children(self), " segments.^";
GConsole.penoff();
                   objectloop(o in self)
                   if (l==0) l=o;
                   else {
                   grex_line_render(w,self.col,self.thickness,l.xx+self.xx,
                   l.yy+self.yy,
                   o.xx+self.xx,o.yy+self.yy);
                   l=o;
                   }
                   return l;
                ];
Class Grex_PolyLoop class Grex_PolyLine
 with redraw [w l o;
                l=child(self);
                o=self.Grex_PolyLine::redraw(w);
                grex_line_render(w,self.col,self.thickness,l.xx+self.xx,l.yy+self.yy,
                   o.xx+self.xx,o.yy+self.yy);
                ];
                
#endif;
