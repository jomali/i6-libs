! GDrawImageGrid - GWindows dynamically-drawn ImageGrids
!
! GDrawImageGrid behaves exactly as a GImageGrid, except that
! each cell is filled with the image of the associated grid item.
!
! Properties of the grid items:
!  image: this is the image to draw in the corresponding cell of the
!         image map
!
! Inherits from: GImageGrid


ifndef GW_GDRGRID_H;
system_file;
Constant GW_GDRGRID_H;

include "gigrid";
class gDrawImageGrid
 class gImageGrid,
 with firstone [x y i; x=y; i=y; return 0; ],
  lastone [x y i; x=y; i=y; return 0; ],
 redraw [i r c x y;
                self.gImageGrid::redraw();
                if (self.current_map)
                {
                i=scion(self.current_map,self.start);
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GDrawImageGrid]: Window ", (name) self, " repainting contents.
        Starting from element ", self.start, ".^";
GConsole.penoff();
#endif;

                for(r=0:r<self.rows:r++)
                for(c=0:c<self.cols:c++)
                {
                 if (i==0) break;
                 y=r*self.rowheight;
                 x=c*self.columnwidth;
                 if (r==0 && c==0 && self.firstone(x,y,i)) continue;
                 if (r==self.rows-1 && c==self.cols-1 && self.lastone(x,y,i)) continue;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GDrawImageGrid]: Window ", (name) self, " painting cell (",
        x, ",", y, ").^";
GConsole.penoff();
#endif;
                 
                 if (i provides image)
                 if (self.current_map has aspected)
                  gwin_image_draw_aspect(self.winid,i.image,x,y,self.columnwidth,self.rowheight);
                 else
                 gwin_image_draw_auto(self.winid,i.image,x,y,self.columnwidth,self.rowheight);
                 i=sibling(i);
                }
                }
             ];
endif;
