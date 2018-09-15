! GTileWin         - GWindows tiled image windows
!
!
! Usage: Use a GTileWin as you would a GImageWin
!
! GTilewin tiles its image across the window.
! GVTilewin does the same thing, but only in the Y-direction
! GHTilewin does the same thing, but only in the X-direction
! Unless the windows are aspected, GVTilewin and GHTilewin will stretch
! the image to fill the other dimension. 

ifndef GW_GTILE_H;
system_file;
Constant GW_GTILE_H;
class GTileWin
 class GraphWin,
 with image,
 setimage [x; self.image=x;
              GW_ForceRedraw(self);
          ],
 overx 0,
 overy 0,
 redraw [x y;
        if (self.image)
        { glk_image_get_info(self.image,GG_ARGUMENTS,GG_ARGUMENTS+WORDSIZE);
          for(y=0:y<self.height:y=y+GG_ARGUMENTS-->1+self.overy)
          for(x=0:x<self.width:x=x+GG_ARGUMENTS-->0+self.overx)
           gwin_image_drawf(self.winid,self.image,x,y);
        }
        ];
class GVTileWin
 class GTileWin
 with
 redraw [y;
        if (self.image)
        { glk_image_get_info(self.image,GG_ARGUMENTS,GG_ARGUMENTS+WORDSIZE);
          for(y=0:y<self.height:y=y+GG_ARGUMENTS-->1+self.overy)
            gwin_image_draw_auto(self.winid,self.image,0,y,self.width,GG_ARGUMENTS-->1);
        }
        ];
class GHTileWin
 class GTileWin
 with
 redraw [x;
        if (self.image)
        { glk_image_get_info(self.image,GG_ARGUMENTS,GG_ARGUMENTS+WORDSIZE);
          for(x=0:x<self.width:x=x+GG_ARGUMENTS-->0+self.overx)
            gwin_image_draw_auto(self.winid,self.image,x,0,GG_ARGUMENTS-->0,self.height);
        }
        ];

endif;
