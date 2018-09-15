! GCombine      - Helper class for multiple inheritance
!
! BE VERY CAREFUL WITH THIS CLASS!!!
!
! To combine two classes which have conflicting members,
! also inherit from GCombiner:
!
!
! Suppose that classes X and Y both provide 'activate' and 'deactivate'
! methods. To create an object which includes both, do this:
! Object Z
!  class GCombinerAD X Y
!  ...
!
! THE ORDER MATTERS! GCombine *must* be the first class inherited.
! Other classes will be used in the order given.
!
! This file provides three forms of GCombiner:
! GCombinerAD - combines activate/deactivate
! GCombinerUR - combines redraw/update
! GCombinerADUR - combines all four
!
! You can also define your own GCombiners by inheriting from GCombiner.
! to combine property x:
! Class GCombinerX
!  class GCombiner,
! with x [y; self.thread(x,y);];
!
! if you create any GCombiners of your own, you **MUST**
! also create a table listing them. In the above example:
! Constant HAVE_GCOMBINER_LIST;  !!BEFORE including gcombine
! Array GCOMBINER_LIST table GCombinerX; !! AFTER defining your class.
!
! Failure to do this will cause stack overflow.
!
! This extention is for EXPERIENCED USERS ONLY

ifndef GW_GCOMBINE_H;
system_file;
Constant GW_GCOMBINE_H;
[ isaGCombiner x i;
 i=0;
 if (x==GCombiner or GCombinerAD or GCombinerUR or GCombinerADUR) rtrue;
 #ifdef HAVE_GCOMBINER_LIST;
 for(i=1:i<=GCOMBINER_LIST-->0:i++)
  if (x==GCOMBINER_LIST-->i) rtrue;
 #endif;
 rfalse;
];

class GCombiner
 private thread [p x i j;
        for(i=1:i<(self.#2/WORDSIZE):i++)
        {
         if (isaGCombiner(self.&2-->i)) continue;
        if (self provides (self.&2-->i)::p)
         j=(self.&2-->i)::p;
         if (j)
         if (x)
         self.j(x);
         else self.j();
         }
         ];

class GCombinerAD
 class GCombiner,
 with activate [x;
        self.thread(activate,x);
        ],
      deactivate [; self.thread(deactivate);];

class GCombinerUR
 class GCombiner,
  with redraw [; self.thread(redraw); ],
       update [; self.thread(update); ];
class GCombinerADUR
 class GCombinerAD GCombinerUR;


 
endif;
