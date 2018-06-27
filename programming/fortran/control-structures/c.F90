program fibonacci
    implicit none

    integer :: f0 = 0, f1 = 1, n = 100, i = 0
    integer :: prevprev, prev, cur

    write (*,*) f0
    write (*,*) f1

    prevprev = f0
    prev = f1

    do while (i < n)
        cur = prevprev + prev
        write (*,*) cur
        prevprev = prev
        prev = cur
        i = i + 1
    end do

end program fibonacci