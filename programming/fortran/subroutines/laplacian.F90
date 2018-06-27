module laplacian_mod
  implicit none
  real, parameter :: dx = 0.01, dy = 0.01

contains

  subroutine initialize(field0)
    implicit none
    real, dimension(:,:), intent(inout) :: field0
    real :: x, y
    integer :: nx, ny, i, j

    nx = size(field0, 1)
    ny = size(field0, 2)

    y = 0.0
    do j = 1, ny
      x = 0.0
      do i = 1, nx
          field0(i,j) =  x**2 + y**2
          x = x + dx
      end do
      y = y + dy
    end do

  end subroutine initialize

  subroutine laplacian(curr, prev)
    real, dimension(:,:), allocatable, intent(inout) :: curr
    real, dimension(:,:), allocatable, intent(in) :: prev
    integer :: nx, ny, i, j

    nx = size(prev, 1)
    ny = size(prev, 2)

    do j = 2, ny - 1
      do i = 2, nx - 1
         curr(i,j) =  ( (prev(i-1,j) - 2*prev(i,j) + prev(i+1,j)) / dx**2 ) + &
         ( (prev(i,j-1) - 2*prev(i,j) + prev(i,j+1)) / dy**2 )
      end do
   end do

  end subroutine laplacian

  subroutine write_field(array)
    real, dimension(:,:), allocatable, intent(in) :: array
    integer :: nx, ny, i

    nx = size(array, 1)
    ny = size(array, 2)

    do i = 2, nx-1
      write(*, '(12F6.1)') array(i,2:ny-1)
    end do

  end subroutine write_field

end module laplacian_mod
