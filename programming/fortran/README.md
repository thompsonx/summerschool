# Fortran exercises

 - [Compilation and execution](hello)
 - [Control structures](control-structures)
 - [Dynamic arrays](arrays)
 - [Laplacian](laplacian)
 - [Array intrinsic functions](intrinsics)
 - [Subroutines](subroutines)
 - [Input and output](io)
 - [Derived types](types)
 - [Vector module](vecmod)
 - [Heat equation](../../heat/serial/fortran)


# Course notes - TP

implicit none - do not recognize data types according to the first letter of variable
case insensitive, only strings are case sensitive
good for working with numbers, not good for string processing and hardware access
good for working with arrays, including slicing 

I/O

type of output, e.g., * -> standard output
      |
write(*,*)
        ^ formatting (similar to printf in C)

Fortran standard does not define exact precision of numeric types
 - however since fortran2003 it can be controlled by "kind" parameter