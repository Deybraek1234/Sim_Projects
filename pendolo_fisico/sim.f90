module operations
    implicit none

real, parameter:: g=9.81
contains
    subroutine sim(l, initial_theta, initial_omega, dampening, dt, theta_history, omega_history, time_history) 
        real, intent(in):: initial_theta, initial_omega, dt, l, dampening
        integer, parameter :: n_steps = 10000
        integer:: i
        real, dimension(n_steps), intent(out):: theta_history, omega_history, time_history
        real, dimension(4):: k_theta, k_omega
        real::current_t, current_o

        theta_history(1) = initial_theta
        omega_history(1) = initial_omega
        time_history(1) = 0.0

        do i = 1, n_steps-1;
            current_t = theta_history(i)
            current_o = omega_history(i)

            k_theta(1) = current_o*dt
            k_omega(1) = ((-g/L * sin(current_t)) - (dampening * current_o))*dt

            k_theta(2) = (current_o + 0.5 * k_omega(1)) * dt
            k_omega(2) = ((-g / L * sin(current_t + 0.5 * k_theta(1))) - (dampening * (current_o * 0.5 * k_omega(1))))*dt

            k_theta(3) = (current_o + 0.5 * k_omega(2))*dt
            k_omega(3) = ((-g / L * sin(current_t + 0.5 * k_theta(2))) - (dampening * (current_o + 0.5 * k_omega(2))))*dt

            k_theta(4) = (current_o + k_omega(3)) * dt
            k_omega(4) = ((-g / L * sin(current_t + k_theta(3))) - (dampening * (current_o + k_omega(3))))*dt

            theta_history(i+1) = theta_history(i) + (k_theta(1) + 2*k_theta(2) + 2*k_theta(3) + k_theta(4))/6.
            omega_history(i+1) = omega_history(i) + (k_omega(1) + 2*k_omega(2) + 2*k_omega(3) + k_omega(4))/6.

            time_history(i+1) = time_history(i) + dt
        end do
    end subroutine
    
    function polar_to_xy(r,t) result(xy)
        real, intent(in):: r, t
        real, dimension(2):: xy
        xy(1) = r * sin(t)
        xy(2) = -r * cos(t)
        
    end function polar_to_xy

    function xy_to_polar(x,y) result(rt)
        real, intent(in):: x, y
        real, dimension(2)::rt
        rt(1) = sqrt(x**2 + y**2)
        rt(2) = atan(y/x)
    end function xy_to_polar
end module operations


