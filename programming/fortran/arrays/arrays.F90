program arrays
  implicit none
  real, allocatable :: A(:,:)
  real :: x, y, dx, dy
  integer :: nx, ny, i, j, alloc_stat

  write (*,*) 'Give number of rows and columns for matrix A:'
  read (*,*) nx, ny
  dx = 1.0/real(nx-1)
  dy = 1.0/real(ny-1)

  allocate(A(nx, ny), stat=alloc_stat)
  if (alloc_stat /= 0) stop

  y = 0.0
  do j = 1, ny
    x = 0.0
    do i = 1, nx
      A(i,j) = x**2 + y**2
      x = x + dx
    end do
    y = y + dy
  end do

  do i = 1, nx
    write(*, '(12F6.1)') A(i,:)
  end do

  deallocate(A)


end program arrays
