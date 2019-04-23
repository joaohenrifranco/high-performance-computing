program matMult
  implicit none
	
	integer, parameter :: MATSIZE = 2500

	integer, dimension(MATSIZE, MATSIZE) :: A
	integer, dimension(MATSIZE) :: x, b
  integer :: i, j, clock_start, clock_end, clock_rate
	real :: temp
	
	print *, "Populating operands (", MATSIZE, " x ", MATSIZE, ")"
  do i = 1, MATSIZE
    do j = 1, MATSIZE
			call random_number(temp)
	    A(i, j) = FLOOR(1028 * temp)   
    end do
		
		call random_number(temp)
		x(j) = FLOOR(1028 * temp)
  end do



	print *, "Starting column first multiplication"

	call system_clock(clock_start, clock_rate)
	do i = 1, MATSIZE
    do j = 1, MATSIZE
			b(i) = b(i) + (A(i, j) * x(j))
    end do
  end do

	call system_clock(clock_end)
	print *, "Done"

	print *, "Elapsed time: ", real(clock_end - clock_start) / real(clock_rate)
	
	print *, "Starting row first multiplication"

	call system_clock(clock_start, clock_rate)
	do j = 1, MATSIZE
    do i = 1, MATSIZE
			b(i) = b(i) + (A(i, j) * x(j))
    end do
  end do

	call system_clock(clock_end)
	print *, "Done"

	print *, "Elapsed time: ", real(clock_end - clock_start) / real(clock_rate)
	
	
  
end program matMult