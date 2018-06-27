program hello
  implicit none

  real :: a = 15
  real :: b = 20

  logical :: bool = .true.

  character(len=80) :: string='CSC Summer School 2018'

  write (*,*) 'Hello world from Fortran!'

  write (*,*) 'Epic computation: ', a + b

  if (bool) then
    write (*,*) string
  end if

end program hello
