#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

"sovling an ODE with external inputs..."

from scipy.integrate import ode

class MassSpringDamper(object):
    "describes movement of a mass-spring damper driven by external force"

    def __init__(self, M, k, b, F):
        """M is the mass, k describes the spring, b is the damping factor
           and F describes the external force...
        """
        self.M, self.k, self.b, self.F = M, k, b, F

    def f(self, t, xu):
        "x and u is the displacement and speed of the mass"
        x, u = xu.tolist()
        dx = u
        du = (self.F - self.k*x - self.b*u)/self.M
        return [dx, du]

system = MassSpringDamper(M=1.0, k=0.5, b=0.2, F=1.0)
init_status = -1, 0.0
dt = 0.02

r = ode(system.f)
r.set_integrator('vode', method='bdf')
r.set_initial_value(init_status, 0)

t = []
result = []
F_arr = []
while r.successful() and r.t + dt < 50:
    r.integrate(r.t + dt)
    F = 1.0 # F can be updated here...
    system.F = F # F can be updated here...
    t.append(r.t)
    result.append(r.y)
    F_arr.append(F)

result = np.array(result)

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t, result[:, 0], label=u"displacement")
ax1.legend()
ax2.plot(t, result[:, 1], label=u"speed")
ax2.legend()
