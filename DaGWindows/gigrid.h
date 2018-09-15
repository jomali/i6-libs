! GImageGrid - GWindows regularized clickable windows
!
! Usage:
!  This widget translates clicks in a graphic window into clicks on 
!  a cell within a grid of specified size
!
!  You activate a GImageGrid exactly as you would a GMenu (the information
!  objects are identical.)
!
!  Each GImageGrid window specifies a number of rows and columns. A click
!  within any particular cell causes the apropriate child of the grid
!  information object to be selected.
!
!  Cells are numbered left to right across rows, so if the third cell of
!  the fourth row in a 5x5 grid is clicked, this will be translated to
!  ((4-1)*5)+3 = the 18th child of the object
!
!  GImageGrids behave otherwise identically to GImageMaps
!
!
! User-configurable properties:
!  All the properties of GImageMap are available in GImageGrid. Additionally:
!   start:  Indicates the first child of the grid information object to be
!           considered. If this is set to 1, all the children
!           will be included. If it is, say, 6, the grid will start with
!           child 5. This can be used to "page" the grid.
!
! User-testable properties:
!   As GImageMap, and additionally:
!    rowheight, columnwidth: Size of each cell at the time of last redraw.
!
! Properties of the map information object:
!   See GImageMap
! Properties of the map items:
!  select(): this is called when the item is clicked
!
! Inherits from: GImageMap
! Derived Classes: GDrawImageGrid

ifndef GW_GIGRID_H;
system_file;
Constant GW_GIGRID_H;
include "gimap";

Class GImageGrid
 class gImageMap,
 with
      rows,
      cols,
      rowheight,
      columnwidth,
      start 1,
      last,
      redraw [;
              self.columnwidth=self.width/self.cols;
              self.rowheight=self.height/self.rows;
              self.last=self.start+(self.rows*self.cols);
              self.GImageMap::redraw();
              ],
       clktocol [ x; return x/self.columnwidth;
                ],
       clktorow [ y; return y/self.rowheight; ],
       click_event [ x y r c i;
                r=self.clktorow(y);
                c=self.clktocol(x);
                i=(r*self.cols)+c;
                self.click_entry(i);
                ],
       click_entry [i o;
                i=i+self.start;
                o=scion(self.current_map,i);
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GImageGrid]: Window ", (name) self, " received click in cell (",
        r,",",c,"). Sending select message to element ", i, " (",(name) o ,").^";
GConsole.penoff();
#endif;

                if (o) o.select();
                ];
         
                
endif;
