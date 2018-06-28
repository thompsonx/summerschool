program types
    use heat
    implicit none

    type(tempfield) :: t
    integer :: nx, ny
    nx = 10
    ny = 10

    call init_temp(nx, ny, t)

    write(*,*) t % nx
    write(*,*) t % ny
    write(*,*) t % dx
    write(*,*) t % dy
    ! write(*,*) t % points

end program