! Main solver routines for heat equation solver
module core

contains

  ! Compute one time step of temperature evolution
  ! Arguments:
  !   curr (type(field)): current temperature values
  !   prev (type(field)): values from previous time step
  !   a (real(dp)): update equation constant
  !   dt (real(dp)): time step value
  subroutine evolve(curr, prev, a, dt)

    use heat
    implicit none

    type(field), intent(inout) :: curr, prev
    real(dp) :: a, dt, laplace
    integer :: i, j, nx, ny

    nx = curr%nx
    ny = curr%ny

    do j = 1, nx 
      do i = 1, ny
        laplace = ( (prev % data(i-1,j) - 2*prev % data(i,j) + prev % data(i+1,j)) / prev % dx**2 ) + &
                  ( (prev % data(i,j-1) - 2*prev % data(i,j) + prev % data(i,j+1)) / prev % dy**2 ) 
        curr % data(i,j) = prev % data(i,j) + dt*a*laplace
      end do
    end do
  end subroutine evolve

end module core
