! gimage.h    - GWindows Image Window Widget
!
! Usage:
! create as you would a graphics window.
! set the .image property to the image you want displayed. It will be
! automatically sized to fit the window
! and redrawn as needed.
!
! User-configurable properties:
!  image: image to be drawn
!  setimage(x): Changes the current image (and forces a redraw)
!  attribute: abssplit - If unset, the image will be scaled to the
!       actual size of the window
! 
! Inherits from: GraphWin
! Derived classes: GImageMap

ifndef GW_GIMAGE_H;
system_file;
Constant GW_GIMAGE_H;
class GImageWin
 class GraphWin,
 with image,
 col $ffffff,
 setimage [x; self.image=x;
              GW_ForceRedraw(self);
          ],
 redraw [;
        glk_window_set_background_color(self.winid, self.col);
        if (self has aspected || ~~self.image)
        ! We don't clear the window unnecessarily in case a foolish
        ! interpreter implements this by making the window flash white
        ! for a second.  Can't be helped with aspected windows if we
        ! don't want to chance leaving ghosts.
         glk_window_clear(self.winid);
        if (self.image)
          gwin_image_draw_auto(self.winid,self.image,0,0,self.width,self.height);
        ];
endif;
