! GImageMap - GWindows Clickable image maps
!
! Usage:
!  This widget translates clicks in a graphic window.
!  You activate a GImageMap much like a menu -- window.activate(x);
!  Each child of the map information object provides information about
!  a region of the image. When a click occurs within that region,
!  the 'select' message is sent to the apropos object.
!
!  Map information is completely compatable with menu information;
!  any object which could be sent to a map window could also be
!  sent to a menu window (Keep this in mind when designing games that
!  should be playable on systems with a variety of abilities - if an
!  imagemap is essential to your game, you should let players opt to
!  view it as a menu)
!
! User-configurable properties:
!  activate(x): activates the window with 'x' as its map.
!  deactivate(): shuts down a map
!  update(): calls the update function of the current map
!  click_event(x,y): locates any map item in the region of the click and
!               calls its select property
!  Attribute:abssplit - If unset, the image will be stretched to fit the
!       window. Clicks will be scaled accordingly.
!
! User-testable properties:
!  real_width, real_height: The actual size of the current image,
!               as calculated when the map is activated
!  current_map: The map information currently in use
!  Attribute: on - set when the map is active
!
! Properties of the map information object:
!  update(): if provided, called when the map wants to update itself -
!    this is the place to fool with the individual items in the map.
!    it should return true if the map wants to be redrawn
!  image: This picture will be displayed in the image map window when
!       the map is active
! Properties of the map items:
!  select(): this is called when the item is clicked
!  xpos, ypos:    Each map item describes a rectangular region on the image.
!  width, height: This region begins at xpos,ypos, and has size width x height.
!                 These locations are given relative to the upper-right corner
!                 of the image. If the image is scaled when it is drawn,
!                 the mouse co-ordinates will be scaled proportionally,
!                 so these should be given as if the image is its actual size
!  Attribute: noshow - if set, ignore this item. You could use this to make
!               the current room double as the image map for a graphical
!               display of the room by setting this flag on objects
!               which do not appear in the room's graphic.
!       
! Inherits from: GImageWin
! Derived Classes: GDrawImageMap, GImageGrid

ifndef GW_GIMAP_H;
system_file; 
Constant GW_GIMAP_H;
include "gimage";

attribute noshow;
class GImageMap
 class GImageWin,
 private xpos, ypos,
 with
     activate [x;
!                if (self.current_map==x && self has on) return;
       #ifdef USE_GCONSOLE;
       GConsole.penon();
       print "[GImageMap]: Activating map ", (name) self, " with map data ", (name) x, ".^";
       GConsole.penoff();
       #endif;

                self.current_map=x;
                if (x provides image)
                 self.image=x.image;
                if (self hasnt on)
                {
                 give self on;
                 glk_image_get_info(self.image,self.&real_width,self.&real_height);
                if (self.winid) {
                 glk_request_mouse_event(self.winid);
                 GW_ForceRedraw(self);
                 }
                }
               ],
     redraw [;
              glk_image_get_info(self.image,self.&real_width,self.&real_height);
              self.GImageWin::redraw();
            ],
     deactivate [;
       #ifdef USE_GCONSOLE;
       GConsole.penon();
       print "[GImageMap]: Deactivating image map ", (name) self, ".^";
       GConsole.penoff();
       #endif;

        if (self has on)
        {
         glk_cancel_mouse_event(self.winid);
        }
        self.current_map=0;
        self.image=0;
        glk_window_clear(self.winid);
        give self ~on;
        ],
     real_width,
     real_height,
     current_map,
     update [; if (self has on && self.current_map provides update)
                if (self.current_map.update())
                self.redraw();
            ],
     click_event [ x y o;
        if (self hasnt abssplit)
        {
         x=(x*self.real_width)/self.width;
         y=(y*self.real_height)/self.height;
        }
        objectloop(o in self.current_map)
         if (o provides select && o hasnt noshow &&
            x >= o.xpos && x <= (o.xpos+o.width) &&
            y>=o.ypos && y<= o.ypos+o.height)
        {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GImageMap]: Window ", (name) self, " sending select message to ", (name) o, ".^";
GConsole.penoff();
#endif;

         o.select();
        }
        ];
endif;
