program loops
  implicit none
  integer, parameter :: nx = 10, ny = 10
  real, dimension(nx, ny) :: A
  integer :: i, j
  real :: x, y
  real :: xinc, yinc

  xinc = 1. / nx
  yinc = 1. / ny

  y = 0.0
  do j = 1, ny
    x = 0.0
    do i = 1, nx
      A(i,j) = x**2 + y**2
      x = x + xinc
    end do
    y = y + yinc
  end do

  !--------------------------------------------------
  ! Print out the array
  ! the ':' syntax means the whole row, see the Fortran arrays lecture
  do i = 1, nx
     write(*, '(12F6.1)') A(i,:)
  end do

end program loops
