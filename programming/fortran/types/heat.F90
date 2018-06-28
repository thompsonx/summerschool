module heat
    use iso_fortran_env, only : REAL64
    implicit none

    type tempfield
        integer :: nx
        integer :: ny
        real(kind=REAL64) :: dx
        real(kind=REAL64) :: dy
        real(kind=REAL64), dimension(:,:), allocatable :: points
    end type

    contains

    subroutine init_temp(x_size, y_size, field)
        implicit none
        integer, intent(in) :: x_size, y_size
        type(tempfield), intent(out) :: field

        field % nx = x_size
        field % ny = y_size
        field % dx = 0.01
        field % dy = 0.01

        allocate(field % points(x_size, y_size))

    end subroutine
end module