! GWindows Sound System   L. Ross Raszewski
! Version .2b
! (c) 2003

ifndef GS_GSOUND_H;
Constant GS_GSOUND_H;
system_file;
include "gcore";
ifdef GS_GSOUND_H;
endif;
Default GS_MULTICHAN_MAX 64;
Constant GS_SOUNDOK 1;
Constant GS_VOLOK 2;
Constant GS_NTFYOK 4;
Constant GS_MUSOK 8;
Global GS_ABILITIES;

constant GS_LOOP_FOREVER $ffffffff;

class GSvChannel(GS_MULTICHAN_MAX)
 with schanid,
      vol $10000,
      
      short_name [; if (self in GSMultiChannel) {
                        print "Virtual channel ", (age) self;
                        rtrue;
                        }
                    rfalse;
                 ],
      cancel [;
                if (~~self.schanid) return;
                if (self hasnt on) return;
                if (self hasnt open) return;
                glk_schannel_stop(self.schanid);
                give self ~on;
             ],
      mute [;   give self absent;
                if (self has on)
                gs_set_volume(self);
              ],
        unmute [; if (self hasnt absent) return;
                  give self ~absent;
                  if (self has on)
                  gs_set_volume(self);
                  ],
      sound_event [o;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Sound notification received on channel ", (name) self, "; signaling channel is unused and running after-effects.^";
GConsole.penoff();
#endif;
        give self ~on;
        objectloop(o in self)
        if (o provides after) o.after(self.playing);
#ifdef USE_GCONSOLE;
if (self has on) GConsole.write("[GSound]: Note: Channel has been reactivated.^");
#endif;
      ],
      playing,
      init [o;
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Initializing sound channel ", (name) self, ".^";
GConsole.penoff();
#endif;
              if (GS_ABILITIES & GS_SOUNDOK == 0)
               {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Sound not available; aborting.^");
#endif;
                rfalse;
               }
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Trying to find an existing unused sound channel.^";
#endif;
             objectloop(o ofclass GSvChannel)
              if (o hasnt on && o has open && o hasnt static) 
              {
#ifdef USE_GCONSOLE;
               print "[GSound]: Channel found. Shutting down channel ", (name) o,
               " and claiming Glk channel ", o.schanid, ".^";
#endif;
               self.schanid=o.schanid;
	       o.schanid=0;
               give o ~open;
               give self open;
               if (o in GSMultiChannel)
               {
                remove o;
                GSvChannel.destroy(o);
               }
#ifdef USE_GCONSOLE;
               GConsole.penoff();
#endif;
                gs_set_volume(self);
               rtrue;
              }
#ifdef USE_GCONSOLE;
print "[GSound]: Couldn't find an available channel. Opening a new one.^";
GConsole.penoff();
#endif;
              o = self;
              self.schanid=glk_schannel_create(o);
              if (self.schanid==0)
              {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Failed to open a new channel. Trying to retire
        a playing sound from the multichannel.^");
#endif;
               o=child(GSMultichannel);
               if (~~o)
               {
                rfalse;
               }
               self.schanid=o.schanid;
		o.schanid=0;
               remove o;
               GSvChannel.destroy(o);
               }
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Success. Glk sound channel is ", self.schanid, ".^";
GConsole.penoff();
#endif;
              give self open;
              gs_set_volume(self);
              rtrue;
            ],
       number 1,
       play [ x v i;
                if (GSOund hasnt on) rfalse;
                if (GS_ABILITIES & GS_SOUNDOK == 0)
                {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Sound not available; aborting.^");
#endif;
                 rfalse;
                }
                if (v==0) v=self.vol;

#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Attempting to play sound ", x, " on channel ", (name) self, ".^";
GConsole.penoff();
#endif;
                if (self has open)
                {
                if (v ~=self.vol)
                 {
                  self.vol=v;
                  gs_set_volume(self);
                 }
                } else {
                self.vol=v;
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Sound channel is not live. Initalizing.^");
#endif;
                if (~~self.init())
                {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Sound channel failed to initialize.^");
#endif;
                return 0;
                }
                }
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Channel ready. Running pre-effects.^");
#endif;
                objectloop(i in self)
                 if (i provides before) i.before(x);
                v=0;
                if (GS_ABILITIES & GS_NTFYOK)
                 v=self;

#ifdef USE_GCONSOLE;
if (v==0) GConsole.write("[GSound]: Warning: Sound notification not available; after-effects will not occur and channel will not be automatically reclaimed.^");
               GConsole.penon();
                print "[GSound]: Playing sound ", x, " on sound channel ", (name) self,
                "(", self.schanid, ").^";
#endif;
                i=glk_schannel_play_ext(self.schanid,x,self.number,
                        v);
                if (i)
                {
#ifdef USE_GCONSOLE;
                 print "[GSound]: Sound started playing.^";
#endif;
                 give self on;
                 self.playing=x;
                }
                else {
#ifdef USE_GCONSOLE;
                print "[GSound]: Sound did not play.^";
#endif;
                i=0;
                }
#ifdef USE_GCONSOLE;
                GConsole.penoff();
#endif;
                return i;
             ];
Class GSChannel class GSvChannel;
Class GSMusicChannel class GSChannel
 with play [x v;
                if (GS_ABILITIES & GS_MUSOK) return self.GSvChannel::play(x,v);
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Music not available; aborting.^");
#endif;
                rfalse;
           ];
object GSMultiChannel
 with vol $10000,
      play [ x v r o;
                if (GSound hasnt on || self hasnt on) rfalse;
                if (v==0) v=self.vol;
                if (r==0 || r==GS_LOOP_FOREVER) r=1;

#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Playing sound ", x, " in the multichannel (Volume: ",v,"; Repeats: ", r, ".^";
GConsole.penoff();
#endif;
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Looking for an unused virtual channel.^");
#endif;
                objectloop(o in self)
                {
                 if (o hasnt on)
                  {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Virtual channel found. Using it.^");
#endif;
                   o.number=r;
                   remove o;
                   pmove(o,self);
                   return o.play(x,v);
                  }
                }
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: No free virtual channels. Trying to create a new one.^");
#endif;
                o=GSvChannel.create();
                if (~~o) {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: No new virtual channels available; reusing the oldest one.^");
#endif;
                o=child(self);
                }
                else if (~~o.init()) {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Virtual channel did not initialize; trying to reuse the oldest one.^");
#endif;
                        remove o;
                        GSvChannel.destroy(o);
                        o=child(self);
                        }
                if (~~o) {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: A virtual channel could not be claimed; aborting.^");
#endif;
                rfalse;
                }
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Virtual channel found and initialized; using it.^");
#endif;
                remove o;
                o.number=r;
                pmove(o,self);
                return o.play(x,v);
                ] has on;

GWin_Module GSound "GWindows Sound System"
with number ".2B (Public Beta)",
init [i j;
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: GWindows sound system initializing.^
                [GSound]: Testing the gestalt.^");
#endif;

       GS_ABILITIES=0;
       if (glk_gestalt(gestalt_Sound,0)) GS_ABILITIES = GS_ABILITIES | GS_SOUNDOK;
       if (glk_gestalt(gestalt_SoundMusic,0)) GS_ABILITIES = GS_ABILITIES | GS_MUSOK;
       if (glk_gestalt(gestalt_SoundVolume,0)) GS_ABILITIES = GS_ABILITIES | GS_VOLOK;
       if (glk_gestalt(gestalt_SoundNotify,0)) GS_ABILITIES = GS_ABILITIES | GS_NTFYOK;
       if (GWin_Core.init_reason==INIT_REASON_GW_RESTART)
        {
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Detected a UI transition. Not resetting the sound system.^");
#endif;
        return;
        }
        if (i==0)
        {
        #ifdef USE_GCONSOLE;
        GConsole.write("[GSound]: Killing all active channels.^");
        #endif;

          objectloop(i ofclass GSvChannel)
	  {
           give i ~open ~on;
	   i.schanid=0;
          }
          for(i=glk_schannel_iterate(0,0):i:i=j)
          { j=glk_schannel_iterate(i,0);
           glk_schannel_destroy(i);
          }
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Purging the multichannel.^");
#endif;

         for(i=child(GSMultiChannel):i:i=child(GSMultiChannel))
          {
           remove i;
           GSvChannel.destroy(i);
          }
#ifdef USE_GCONSOLE;
GConsole.write("[GSound]: Restarting looped sounds.^");
#endif;

          objectloop(i ofclass GSChannel)
          {
           if (i has on)
            if (i has general || i.number==GS_LOOP_FOREVER)
             i.play(i.playing);
            else give i ~on;
          }
        }
        ],
event_handler [ ev;
        if (ev-->0==evtype_SoundNotify)
        {
#ifdef USE_GCONSOLE;
GConsole.penon();
print "[GSound]: Forwarding sound event to channel ", (name) (ev-->3), ".^";
GConsole.penoff();
#endif;

          (ev-->3).sound_event();
        }
        rtrue;
               ],
 disable [o; give self ~on;
            objectloop(o ofclass GSvChannel)
             if (o has on) o.cancel();
         ],
 enable [; give self on; ],
 mute [o;   objectloop(o ofclass GSvChannel)
            o.mute();
           ],
   unmute [o; objectloop(o ofclass GSvChannel)
                o.unmute();
             ],
has on;
[ gs_set_volume o;
#ifdef USE_GCONSOLE;
 GConsole.penon();
 print "[GSound]: Adjusting volume on channel ", (name) o, " to ", o.vol, ".^";
 GCOnsole.penoff();
#endif;
if (o hasnt open) rfalse;
 if (GS_ABILITIES & GS_VOLOK)
  if (o has absent)  glk_schannel_set_volume(o.schanid,0);
  else glk_schannel_set_volume(o.schanid,o.vol);

];
#endif;
