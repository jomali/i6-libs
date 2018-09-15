! GRTS .2a by L. Ross Raszewski
ifndef GRTS_H;
Constant GRTS_H;
system_file;
include "gcore";
ifdef GRTS_H;
endif;
Default GRTS_MAX_EVENTS 16;

Array ggrts_event --> 4;
GWin_Module GRTS "GWindows Realtime System" with number "0.2a", name "grts",
master_clock 0,
time_out 0,
time_left 0,
init [x;
  if (glk_gestalt(gestalt_Timer,0)) give self open;
  else give self ~open;
  if (child(self))
  {
   x=child(self).number;
   self.time_left=child(self);
   self.time_out=(x-self.master_clock)/4;
  if (self.time_out==0) self.time_out=1;
   glk_request_timer_events(self.time_out);

  }
],
event_handler
[ev x handled;
handled=0;
 if (ev-->0==evtype_Timer)
 {
  self.master_clock=self.master_clock+self.time_out;
  for(x=child(self):x && x.number<=self.master_clock:x=child(self))
  {

    pmove(x,GRTS_exec_queue);

  }
  if (~~x) { if (GRTS has open) glk_request_timer_events(0); self.time_out=0; self.time_left=0;}
  if (x ~= self.time_left)
  {
  self.time_left=x;
  self.time_out=(x.number-self.master_clock)/4;
  if (self.time_out<=0) self.time_out=1;
  if (GRTS has open) 
  glk_request_timer_events(self.time_out);
  }
  if (GRTS_exec_queue hasnt general) GRTS_exec_queue.select();
  handled=1;

 }
return handled;
];

class GRTS_event(GRTS_MAX_EVENTS) with number 0, time_out 0, select [; ],
        deep_select [x; x=self.select;
        @tailcall x 0;
        !self.select();
        ];
class GRTS_recurrent_event(GRTS_MAX_EVENTS) class GRTS_event, with number 0, time_out 0, select [; ],
        deep_select [x; x=self.select;
                        GRTS_Schedule(self,self.time_out);

                        @tailcall x 0;
                      !self.select();
                      ];

object GRTS_exec_queue
with select [x; give self general;
               while(child(self))
               { x=child(self);
                 remove x;
                 x.deep_select();
                 glk_select_poll(ggrts_event);
                 HandleGlkEvent(ggrts_event, 1, gg_arguments);
               }
               give self ~general;
             ];

! GRTS_Schedule(event, milliseconds)
[ GRTS_sort  y x;
 return x.number-y.number;
];
[ GRTS_Schedule ev t n;
if (GRTS hasnt open) return;
if (~~(ev ofclass GRTS_event)) {
        n=ev;
        ev=GRTS_event.create();
        if (~~ev) "[BUG: Could not allocate GRTS event]";
        ev.select=n;
       }
ev.time_out=t;
ev.number=t+GRTS.master_clock;
sinsert(ev,GRTS,GRTS_sort);
!move ev to GRTS;
if (ev==child(GRTS))
{
  if (t/4)
  GRTS.time_out=t/4;
  else GRTS.time_out=1;           
  GRTS.time_left=ev;
  glk_request_timer_events(GRTS.time_out);
}

];


! GRTS_ScheduleS(event,seconds, milliseconds)
[ GRTS_ScheduleS ev s mm;
 return GRTS_Schedule(ev,GRTS_Parse_Time(0,0,s,mm));
];

! GRTS_ScheduleM(event, minutes,seconds, millis)
[ GRTS_ScheduleM ev m s mm;
 return GRTS_Schedule(ev,GRTS_Parse_Time(0,m,s,mm));
];

! GRTS_ScheduleH(event,hours,minutes,seconds,millis)
[ GRTS_ScheduleH ev h m s mm;
 return GRTS_Schedule(ev,GRTS_Parse_Time(h,m,s,mm));
];

! GRTS_Parse_Time(hours,minutes,seconds,millis)
[ GRTS_Parse_Time h m s mm;
  h=h*60;
  h=(h+m)*60;
  h=(h+s)*60;
  h=h+mm;
  return h;
];

