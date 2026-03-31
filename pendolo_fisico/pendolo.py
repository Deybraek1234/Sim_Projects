from sim import operations as calc
import numpy as np
import matplotlib.pyplot as plot
import matplotlib.animation as animation
from matplotlib.widgets import Button, Slider
import time

px = 1/plot.rcParams['figure.dpi']
# set up figures/rod/bobs/dots on graphs
fig1, axs1 = plot.subplots(nrows=2, figsize = [1900*px, 1000*px] )
fig2, axs2 = plot.subplots(figsize = [600*px, 600*px])
fig2.subplots_adjust(right=0.8)
rod, = axs2.plot([],[],'k-', lw = 2)
bob, = axs2.plot([],[],'bo', markersize = 20)
dot_theta, = axs1[0].plot([],[],'ro', markersize=8)
dot_omega, = axs1[1].plot([],[],'ro', markersize=8)

# initial conditions/constants
initial_theta = float(input("Initial Angle: ") or np.pi/2)
initial_omega = float(input("Initial Angular Velocity:" ) or "0.0")
dampening = float(input("Dampening Factor (higher means less oscillations): ") or "0.2")
total_time = 100
dt = 0.01
L = 1
n_steps = 10000

# more axis and button
axs2.set_xlim(-L-0.5, L+0.5)
axs2.set_ylim(-L-0.5, L+0.5)
axs2.set_aspect('equal')
baxis = fig2.add_axes([0.90, 0.01, 0.1, 0.075])
breset = Button(baxis, "Reset")

def Main():
    start_time = time.time()
    theta_history, omega_history, time_history = update_data()
    print(time.time() - start_time)

    x = []
    y = []
    for i in range(n_steps):
        temp = calc.polar_to_xy(L, theta_history[i])
        x.append(temp[0])
        y.append(temp[1])   

    def animate(i):
        rod.set_data([0, x[i]], [0, y[i]])
        bob.set_data([x[i]], [y[i]])

        dot_theta.set_data([time_history[i]], [theta_history[i]])
        dot_omega.set_data([time_history[i]], [omega_history[i]])

        return rod, bob, dot_theta, dot_omega

    ani = animation.FuncAnimation(fig2, animate, frames=len(time_history), interval=10, blit=True)

    def reset_sim(event):
        ani.event_source.stop()
        ani.frame_seq = ani.new_frame_seq()
        animate(0)
        fig2.canvas.draw()
        ani.event_source.start()
    
    breset.on_clicked(reset_sim)
    plot.show()


def update_data():
    theta_history, omega_history, time_history = calc.sim(L, initial_theta, initial_omega, dampening, dt)
    axs1[0].plot(time_history, theta_history, label = 'Angle')
    axs1[1].plot(time_history, omega_history, label = 'Angular Velocity')

    return (theta_history, omega_history, time_history)

if __name__ == "__main__":
    Main()