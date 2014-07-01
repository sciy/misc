# !/usr/bin/env python
# -*- coding:utf-8 -*-

# ==============================================
# ·
# · Author: Mogei Wang
# ·
# · MogeiWang@GMail.com
# ·
# · Filename: mwAgent.py
# ·
# · COPYRIGHT 2014
# ·
# ==============================================

# -------------------------------------------------------------------------------
# - imports ... ---------------------------------------------------------------#{{{
from __future__ import division
from SimPy.Simulation import *
# from networkx import *
from pygraphviz import *
from random import *
from math import *
from time import *
import warnings
warnings.simplefilter('ignore', DeprecationWarning)
def random_range(x): a=[i for i in range(x)]; shuffle(a); return a
#}}}

# -------------------------------------------------------------------------------
# - paraments ... ---------------------------------------------------------------#{{{
RunTimes=10000
_Agent_Number=100
MsgNameLen=15
_Agent_TimeUnit=1
_Conds_TimeUnit=1
msgname0="---------------"
msgname1="..............."
msgname2="..............."
msgname3="..............."
msgname4="..............."
msgname5="..............."
_Agent_List={}
#...
#}}}

# -------------------------------------------------------------------------------
# - class MSGProcess ... ---------------------------------------------------------- {{{
class MSGProcess(Process):
    def __init__(self, name="MSG_process"):
        Process.__init__(self, name)
        self._MSGs = dict()

    def put_MSG(self, name, value=None):
        self._MSGs[name] = value

    def act_MSG(self, name, value=None):
        self._MSGs[name] = value
        reactivate(self)

    def try_MSG(self, name, value=None, cond=True):
        if cond: put_MSG(self, name, value=None)

    def taa_MSG(self, name, value=None, cond=True):
        if cond: act_MSG(self, name, value=None)

    def num_MSG(self): #return the number of items
        return len(self._MSGs)

    def get_MSG(self):
        return self._MSGs.popitem() #last=T:FILO

    def get_MSG_value(self, name):
        return self._MSGs.pop(name, None)

    def clear_MSG():
        self._MSGs.clear()
#}}}

# -------------------------------------------------------------------------------
class _Conds_(MSGProcess):
    def __init__(self, name="_Conds_"): #{{{
        MSGProcess.__init__(self, name)
        self.InMessage  = []
        self.OutMessage = [] #}}}

    def run(self):#{{{
        while True:    # The main loop of the '_Conds_'
            while self.num_MSG() > 0:
                self.InMessage = self.get_MSG()
                if self.InMessage[0][0:MsgNameLen]==msgname1:
                    #...
                elif self.InMessage[0][0:MsgNameLen]==msgname2:
                    #...
                else: print "!!Wrong Msg:", self.name, self.InMessage

            #...

            for self.i in random_range(_Agent_Number):
                self.OutMessage=[...]
                _Agent_List[self.i].put_MSG(msgname3+"%015d"%randint(1,999999999999999),self.OutMessage)
                self.OutMessage=[...]
                _Agent_List[self.i].put_MSG(msgname4+"%015d"%randint(1,999999999999999),self.OutMessage)
                self.OutMessage=[...]
                _Agent_List[self.i].put_MSG(msgname5+"%015d"%randint(1,999999999999999),self.OutMessage)
            yield hold, self, _Conds_TimeUnit # Sync with _Agent_. #}}}

# -------------------------------------------------------------------------------
class _Agent_(MSGProcess):
    def __init__(self, name="_Agent_", myid=0): #{{{
        MSGProcess.__init__(self, name)
        self.InMessage = []
        self.OutMessage = [] #}}}

    def run(self):#{{{
        while True: # the main loop of each agent(_Agent_)...
            # the Delta function (state transition):
            # clear the accumulators here.

            if self.InMessage[0][0:MsgNameLen]==msgname3 and ...:
                #...
            elif self.InMessage[0][0:MsgNameLen]==msgname4 and ...:
                #...
            elif self.InMessage[0][0:MsgNameLen]==msgname4 and ...:
                #...
            elif self.InMessage[0][0:MsgNameLen]==msgname5:
                #...
            else: print "!!Wrong Msg:", self.id, self.InMessage

            #...

            # the Omega function (output messages):
            self.OutMessage = [...]
            if ...: AIOCond.put_MSG(msgname1+"%015d"%randint(1,999999999999999), self.OutMessage)
            self.OutMessage = [...]
            if ...: AIOCond.put_MSG(msgname2+"%015d"%randint(1,999999999999999), self.OutMessage)
            yield hold, self, _Agent_TimeUnit ### Wait a while to finish the main loop #}}}

# ===============================================================================

# - the main part ... ----------------------------------------------------------- #{{{
for iii in range(XXX): # repeat the simulation for XXX times.
    startTime=time() # seconds since the 00:00:00 UTC on January 1
    print "Running the", iii, "th simulation----------------"
    initialize() # initialization for simulation (simpy)
    AIOCond=_Conds_()
    activate(AIOCond, AIOCond.run())
    for i in random_range(_Agent_Number):
        _Agent_Temp=_Agent_List[i]=_Agent_(name="_Agent_%10d"%i, myid=i)
        activate(_Agent_Temp, _Agent_Temp.run())
    simulate(until=RunTimes)#}}}
    print "Ending the", iii, "th simulation----------------"
    print "Time used:", time()-startTime, "seconds"
    print "\n\n\n"
#}}}
