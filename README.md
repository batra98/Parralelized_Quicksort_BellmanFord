# Parallelized Version of Quicksort and Bellman Ford

## Parallelized version of quicksort.
Implemented parallelized quicksort using Openmpi library.

- Split the main vector into a number of smaller parts using mpi_scatter function of mpi.
- If length of vector is |n|, then if n%numprocs == 0 --> we give m = n/numprocs to each process else we zero-pad the array and give m = n/numprocs+1 to each process.
- We then sort each individual subpart/subvectors parrallely in each process.
- We now have m sorted vectors.We need to merge them.
- We can merge by using same in O(m) time and in log(p) steps.
- In the merge step, I have used MPI_Send and MPI_Recv to exchange vectors between processes.
- Testing:
	- 1.  sequential-0.50517   parallel-0.243557
	- 2.  sequential-0.5076    parallel-0.272
	- 3.  sequential-0.482768  parallel-0.2523
	- 4.  sequential-0.499613  parallel-0.25343
	- 5.  sequential-0.343654  parallel-0.23374
	- 6.  sequential-0.365511  parallel-0.185698
	- 7.  sequential-0.414262  parallel-0.217249
	- 8.  sequential-0.452915  parallel-0.23488
	- 9.  sequential-0.4259    parallel-0.2376
	- 10. sequential-0.504616  parallel-0.243047
	- 11. sequential-0.50169   parallel-0.281339
	- 12. sequential-0.50517   parallel-0.243557
	- 13. sequential-0.50924   parallel-0.247054
	- 14. sequential-0.4852    parallel-0.2435
	- 15. sequential-0.513111  parallel-0.24779

## Parallelized version of bellman_ford.
 
- Split the edge_u,edge_v,weight vectors into smaller chunks and distributed among p process.
- Zero-padded the vectors and used the same above mentioned strategy for partitioning.
- Relaxed the edges (n-1) times (Assumption: No negative cycle is present).
- Have used MPI_AllReduce function to sync all the distances vector and the changed variable.
- Testing:
	- 1. sequential-0.000317 parallel-0.000396
	- 2. sequential-0.018164 parallel-0.009953
	- 3. sequential-0.369531 parallel-0.156303
	- 4. sequential-0.369531 parallel-0.156303
	- 5. sequential-0.473369 parallel-0.188599
	- 5. sequential-0.447071 parallel-0.257097

 
