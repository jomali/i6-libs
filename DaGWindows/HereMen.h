! HereMen.h     Dynamic Updating menu controller for objects
! Copyright 2006 by L. Ross Raszewski but freely usable
!
! HereMen is a set of classes useful for generating dynamic menus and maps
! based on the contents of something in the model world.
!
! Configuration constants:
!   HW_MAX_ITEMS: The maximum number of items which can appear simultaneously
!               in all HereMen menus and maps that are active (default: 128)
!   HW_DEFAULT_IMAGE: if used in a GDrawImageMap or GDrawImageGrid,
!               the image to use if neither the map nor the object provides
!               its own.
!
! Usage:
!  Use an object derived from one of the defined classes as a Menu Data
!  Object to any GWindows Menu, Map, or Grid widget. It will automatically
!  update to show the contents of the appropriate thing.
!  When an item is selected, its name will be inserted at the end of the
!  current input.  This can be used to build a command by clicking.
!
!  When using HereMen for image maps and grids, you may provide the
!  properties 'image', 'xpos', 'ypos', 'width' and 'height' for
!  objects in the game world.  These will be transferred to the map or grid.
!
!  When using a HereMenu on an ImageMap or DrawImageMap, xpos, ypos,
!  width, and height should be supplied for every object in the model world
!
!  When using HereMenu on a DrawImageMap or DrawImageGrid, image should be
!  supplied.
!
!  A heremenu can also provide the property "def_img", which specifies an
!  image to be used for any object which does not provide its own.
!
!  If neither the menu nor the object provide one, the HM_DEFAULT_IMAGE
!  will be used.
!
! Standard HereMenus:
!  Several predefined HereMenus exist to cover most possiblities:
!   HM_Simple_Location_Menu   - A menu of all objects in the current location
!   HM_Simple_Inventory_Menu  - A menu of all items in inventory
!   HM_Simple_Scope_Menu;     - A menu of all items in scope
!   HM_Sack_Inventory_Menu    - As Simple_Inventory, but includes the
!                               contents of the player's sack-object.
!   HM_Obvious_Location_Menu  - As Simple_Location, but omits scenery and
!                               concealed objects
!   HM_Obvious_Scope_Menu     - As Simple_Scope, but omits scenery and
!                               concealed objects
!
! Custom HereMenus:
!  To further refine the behavior of HereMenus, you can create your own
!  menus based on these classes:
!   HM_Location_Menu    - Menus of objects in the current location
!   HM_Inventory_Menu   - Menus of objects in inventory
!   HM_Scope_Menu       - Menus of objects in scope
!   HM_Obvious_Menu     - When combined with one of the above, omits
!                         concealed or scenery objects.
!
!  To customize behavior, you can do one of the following:
!   * Modify/replace the method 'update' to change where the menu
!     looks for objects
!   * Provide the method hm_restrict(x).  If this method returns true,
!     the object x will not be included in the menu.
!   * Provide the property def_img, the image to use in maps and grids if
!     it does not provide its own
!   * Provide the property image, the image to be used as background for
!     maps and grids.

#ifndef HEREMENU_H;

system_file;
Constant HereMenu_h;

Default HM_MAX_ITEMS 128;
Default HM_DEFAULT_IMAGE 0;
#ifndef item_btn;
class item_btn(HM_MAX_ITEMS) with short_name [; print (name) self.obj; rtrue;],
        select [; streamword(self);],
        image HM_DEFAULT_IMAGE, xpos, ypos, width, height,

        obj 0;
#endif;

Class HM_Location_Menu
  with def_img 0,
  update [ o x;
                  for(o=child(self):o:o=x)
                  {
                   x=sibling(o);
                   if (o ofclass item_btn)
                   { remove o;
                     item_btn.destroy(o);
                   }
                  }
                  objectloop(o near player)
                  {
                   HM_Proxy.number=self;
                   HM_AddObjects(o);
                  }
                rtrue;
                ];

Class HM_Inventory_Menu
    with def_img 0,
         update [o x;

                  for(o=child(self):o:o=x)
                  {
                   x=sibling(o);
                   if (o ofclass item_btn)
                   { remove o;
                     item_btn.destroy(o);
                   }
                  }
                 objectloop(o in player)
                 {
                   HM_Proxy.number=self;
                   HM_AddObjects(o);
                 }
                rtrue;

                ];

object HM_proxy with number;
Class HM_Scope_Menu
  with update [ o x;
                  for(o=child(self):o:o=x)
                  {
                   x=sibling(o);
                   if (o ofclass item_btn)
                   { remove o;
                     item_btn.destroy(o);
                   }
                  }
                  HM_proxy.number=self;
                  LoopOverScope(HM_AddObjects);
                rtrue;
                ];

[ HM_AddObjects o s x;
   s=HM_Proxy.number;
   if (s provides hm_restrict && s.hm_restrict(o)) return;
    x=item_btn.create();
    if (~~x) return;
    x.obj=o;
    if (o provides image) x.image=o.image;
    else if (s.def_img) x.image=s.def_img;
    if (o provides xpos) x.xpos=o.xpos;
    if (o provides ypos) x.ypos=o.ypos;
    if (o provides width) x.width=o.width;
    if (o provides height) x.height=o.height;

    move x to s;

];

Class HM_Obvious_Menu
 with hm_restrict [o; return (o has concealed) || (o has scenery); ];

HM_Location_Menu HM_Simple_Location_Menu;
HM_Inventory_Menu HM_Simple_Inventory_Menu;
HM_Scope_Menu HM_Simple_Scope_Menu;
HM_Location_Menu HM_Obvious_Location_Menu class HM_Obvious_Menu;
HM_Scope_Menu HM_Obvious_Scope_Menu class HM_Obvious_Menu;

HM_Inventory_Menu HM_Sack_Inventory_Menu
 with update [o;
        self.HM_Inventory_menu::update();
        if (SACK_OBJECT~=0 && SACK_OBJECT in player)
         objectloop(o in SACK_OBJECT) {
                   HM_Proxy.number=self;
                   HM_AddObjects(o);
                }
                rtrue;
                ];
#endif;
