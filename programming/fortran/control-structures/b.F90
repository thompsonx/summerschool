program number
    implicit none

    integer :: num = 6

    if  (num == 0) then
        write (*,*) 'ZERO'
    else if (num < 0) then
        write (*,*) 'NEGATIVE'
    else if (num > 100) then
        write (*,*) 'LARGER THAN 100'
    else
        write (*,*) 'IN (0,100]'
    end if

end program number