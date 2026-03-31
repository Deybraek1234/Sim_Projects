module operations
    implicit none

contains
    subroutine sim(l, initial_theta, initial_omega, dampening, dt, theta_history, omega_history, time_history) 
        real, intent(in):: initial_theta, initial_omega, l, dt, dampening
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
            k_omega(1) = (f(current_t) - (dampening * current_o))*dt

            k_theta(2) = (current_o + 0.5 * k_omega(1))*dt
            k_omega(2) = (f(current_t + 0.5 * k_theta(1)) - (dampening * (current_o * 0.5 * k_omega(1))))*dt

            k_theta(3) = (current_o + 0.5 * k_omega(2))*dt
            k_omega(3) = (f(current_t + 0.5 * k_theta(2)) - (dampening * (current_o + 0.5 * k_omega(2))))*dt

            k_theta(4) = (current_o + k_omega(3))*dt
            k_omega(4) = (f(current_t + k_theta(3)) - (dampening * (current_o + k_omega(3))))*dt

            theta_history(i+1) = theta_history(i) + (k_theta(1) + 2*k_theta(2) + 2*k_theta(3) + k_theta(4))/6.
            omega_history(i+1) = omega_history(i) + (k_omega(1) + 2*k_omega(2) + 2*k_omega(3) + k_omega(4))/6.

            time_history(i+1) = time_history(i) + dt
        end do
    end subroutine

    subroutine sim2(dt, L1, L2, m1, m2, th1_int, th2_int, omeg1_int, omeg2_int, dampening, th1_hist, th2_hist, omeg1_hist, omeg2_hist, t_hist)
        real, intent(in):: dt, L1, L2, m1, m2, th1_int, th2_int, omega1_int, omega2_int, dampening
        integer, parameter::n_steps = 10000
        real, dimension(n_steps), intent(out):: th1_hist, th2_hist, omeg1_hist, omeg2_hist, t_hist
        real, dimension(4):: k1_theta, k2_theta, k1_omega, k2_omega

        real::a1, a2, m_eff
        
        time_history(1) = 0.0
        th1_hist(1) = th1_int
        th2_hist(1) = th2_int
        omeg1_hist(1) = omeg1_int
        omeg2_hist(1) = omeg2_int

        do i = 1,n_steps
            delta = th1_hist(i) - th2_hist(i)
            m_eff = 2*m1 + m2 - m2*cos(2*delta)

            a1 = (-g(2*m1 + m2)*sin(th1_hist(i)) - m2*g*sin(th1_hist(i)-2th2_hist(i)) - 2*sin(delta)*m2*(omeg2_hist(i)**2 *L2 + omeg1_hist(i)**2 * L1 * cos(delta)))/(L1*m_eff)
            a2 = (2*sin(delta)*(omeg1_hist(i)**2 L1(m1+m2)) + g*(m1+m2)cos(th1_hist(i)) + omeg2_hist(i)**2 * L2 * m2 * cos(delta))/(L*m_eff)

            a1 = a1 - (dampening*omega1_hist(i))
            a2 = a2 - (dampening*omega2_hist(i))

            
        end do
    end subroutine sim2

    real function f(x) result(res)
        real, intent(in)::x
        real:: g = 9.81, l = 1.

        res = -g/l * sin(x)
    end function f
    
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


