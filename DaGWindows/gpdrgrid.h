ifndef GW_GPDRGRID_H;
system_file;
Constant GW_GPDRGRID_H;

include "gdrgrid";


class GPageDrawImageGrid
 class GDrawImageGrid,
 with prev_word 0,
 next_word 0,
 firstone [ x y i;
                if (i~=child(self.current_map))
                {
                 i=self.prev_word;
                 if (self.current_map has aspected)
                  gwin_image_draw_aspect(self.winid,i,x,y,self.columnwidth,self.rowheight);
                 else
                 gwin_image_draw_auto(self.winid,i,x,y,self.columnwidth,self.rowheight);
                
                 rtrue;
                }
                else rfalse;
            ],
 lastone [ x y i;
                if (sibling(i))
                {
                 i=self.next_word;
                 if (self.current_map has aspected)
                  gwin_image_draw_aspect(self.winid,i,x,y,self.columnwidth,self.rowheight);
                 else
                 gwin_image_draw_auto(self.winid,i,x,y,self.columnwidth,self.rowheight);
                
                 rtrue;
                }
                else rfalse;
            ],
 click_entry [i j;
                j=i;
                if (i==0 && self.start>1)
                { self.start=self.start-1;
                  if (self.start==2) self.start=1;
                  GW_ForceRedraw(self);
                  return;
                }
                else if (i==(self.rows*self.cols)-1)
                {
                 i=i+self.start;
                 if (self.start >1) i--;
                 i=scion(self.current_map, i);
                 if (i && sibling(i))
                 {
                  if (self.start==1) self.start++;
                  self.start++;
                  GW_ForceRedraw(self);
                  return;

                 }
                }

                
                if (self.start>1)
                 j--;
                 self.GImageGrid::click_entry(j);
                
             ];
