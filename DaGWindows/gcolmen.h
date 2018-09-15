! GColumnMenu   - GWindows multi-column menu display widget
!
! Usage: as gmenu
! User-definable properties:
!  columnwidth: (default: 15) the width of each column
!  columns(): (default: window width/column width) the maximum number of
!       columns to display
!
! Inherits from: GMenu
! Derived classes: GAutoColMenu
ifndef GW_GCOLMEN_H;
system_file;
Constant GW_GCOLMEN_H;
include "gmenu";

Class GColumnMenu
 class GMenu,
 with   columnwidth 15,
        columns [;
                    return ((self.width/self.columnwidth));
                    ],
        displayEntries [;
                return ((self.height-1) * self.columns());
                ],
        locateEntry [x y col;
                       y--;
                       col=y/(self.height-1);
                       y=y%(self.height-1);
                       glk_window_move_cursor(self.winid,
                                x+(col*self.columnwidth),
                                y+1);
                    ],
         char_event [x;
                        if (x==keycode_Left)
                          self.sel_num=self.sel_num-self.height+1;
                        else if (x==keycode_Right)
                         self.sel_num=self.sel_num+self.height-1;
                        self.GMenu::char_event(x);
                ],
         convertclick [x y;
                x=x/self.columnwidth;

                return y+(x*(self.height-1));
                ];
        
endif;
