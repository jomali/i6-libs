! GDrawImageMap - GWindows dynamically-drawn Image maps
!
! GDrawImageMap behaves exactly as a GImageMap, except that
! each item in the map is given the chance to draw itself
!
! Properties of the grid items:
!  image: this is the image to draw in the on the
!         image map
!
! Inherits from: GImageMap

ifndef GW_GDRMAP_H;
system_file; 
Constant GW_GDRMAP_H;
Include "gimap";

Class gDrawImageMap
 class gImageMap,
 with redraw [o; self.gImageMap::redraw();
                 if (self.current_map)
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GDrawImageMap]: Window ", (name) self, " repainting children of ",
        (name) self.current_map, ".^";
GConsole.penoff();
#endif;

                 objectloop(o in self.current_map)
                  if (o.image)
                  gwin_image_draw_auto(self.winid,o.image,
                                  (o.xpos*self.width)/self.real_width,
                                  (o.ypos*self.height)/self.real_height,
                                  (o.width*self.width)/self.real_width,
                                  (o.height*self.height)/self.real_height);
                ];
endif;
