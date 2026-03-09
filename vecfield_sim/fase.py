import matplotlib.pyplot as plot
import sympy as sp
import numpy as np
import math

px = 1/plot.rcParams['figure.dpi']
x, y = sp.symbols('x y')
dt = 0.01


while True:
    user_input = input("Input x velocity:") or "y"
    #"y" particle
    try:
        u_func = sp.lambdify((x,y), sp.simplify(user_input), modules='numpy')
        break
    except: 
        print("Bad Syntax")

while True:
    user_input = input("Input y velocity:") or "-1*sin(x)"
    #"(1-x**2)*y-x" particle
    try:
        v_func = sp.lambdify((x,y), sp.simplify(user_input), modules='numpy')
        break
    except:
        print("Bad Syntax")

def Main():
    #setup points
    x_grid, y_grid = np.meshgrid(np.linspace(-10, 10, 35), np.linspace(-10, 10, 35))
    fig, axs = plot.subplots(nrows=1, ncols=2, figsize = (1900*px, 1000*px))

    #vec field
    axs[0].quiver(x_grid, y_grid, u_func(x_grid,y_grid), v_func(x_grid,y_grid), color='g')
    axs[0].set_title('Vector Field Animated')
    axs[1].quiver(x_grid, y_grid, u_func(x_grid, y_grid), v_func(x_grid, y_grid), color ='g')
    axs[1].set_title ('Vector Field')

    x_traj = []
    y_traj = []
 
    initialx, initialy, total_time = initial_values()
    x_traj.append(initialx)
    y_traj.append(initialy)

    plot.ion()
    trajectory_line, = axs[0].plot([], [], 'b', markersize=2, alpha=0.4)

    nsteps = int(total_time/dt)
    for i in range(nsteps):
        tempx, tempy = euler_step(x_traj[i], y_traj[i])
        x_traj.append(tempx)
        y_traj.append(tempy)

    axs[1].plot(initialx, initialy, 'ro', alpha=0.4)
    axs[1].plot(x_traj, y_traj, 'b', alpha=0.4)

    x_traj.clear()
    y_traj.clear()

    x_traj.append(initialx)
    y_traj.append(initialy)   

    axs[0].plot(initialx, initialy, 'ro', alpha=0.4)
    for i in range(nsteps):
        tempx, tempy = euler_step(x_traj[i], y_traj[i])

        # setup vec for norm check
        vec1 = [tempx, tempy]
        vec2 = [x_traj[i], y_traj[i]]

        if(np.linalg.norm(tempx - x_traj[i], tempy - y_traj[i]) < 0.00001):
            print("Punto equilibrio")
            break
            
        x_traj.append(tempx)
        y_traj.append(tempy)

        trajectory_line.set_data(x_traj,y_traj)
        if i % 5 ==0:
                plot.pause(0.01)
    print(nsteps)
    trajectory_line.set_color('r')
    plot.ioff()
    plot.show()

def euler_step(x,y):
    x += u_func(x,y) * dt
    y += v_func(x,y) * dt
    return (x,y)

def initial_values():
    while True:
        user_input = input("Initial x position?") or float("0.0")
        try:
            initial_x = float(user_input)
            break
        except:
            print("Enter a fucking number")
    
    while True:
        user_input = input("Initial y position?") or float("1.0")
        try:
            initial_y = float(user_input)
            break
        except:
            print("Enter a fucking number")
    
    while True:
        user_input = input("How long to run simulation? (s)") or float("180.0")
        try:
            total_time = float(user_input)
            break
        except: 
            print("Enter a fucking number")

    return initial_x, initial_y, total_time


if __name__ == "__main__":
   Main()