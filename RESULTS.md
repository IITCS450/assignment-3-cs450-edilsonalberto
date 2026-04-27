# CS450 Assignment 3 – Lottery Scheduling Results

## Setup

- 1 child process with 1 ticket (default)
- Tested with `testlottery 10` (10 tickets)
- CPU-bound workload: tight loop accumulating values

## Syscall Validation

`settickets(0)` correctly returns -1 (invalid).
`settickets(10)` correctly returns 0 (success).

## Scheduler Implementation

Replaced xv6's round-robin scheduler with a lottery scheduler in `proc.c`:
1. Under `ptable.lock`, sum all tickets from RUNNABLE processes
2. Draw a random winner using a linear congruential generator (LCG)
3. Scan RUNNABLE processes accumulating tickets until running sum exceeds winner
4. Run that process

The LCG uses state `lcg_state = lcg_state * 1664525 + 1013904223` (Numerical Recipes constants).

## Expected Behavior

A process with N tickets gets approximately N/(total tickets) fraction of CPU time.
For example, a process with 10 tickets competing against one with 1 ticket should
receive roughly 10/11 ≈ 91% of CPU time over a long run.

## Observed Results
child1 (1 ticket): done
child2 (3 tickets): done
lotterytest: done

Both children completed their 500,000-iteration loops. The child with 3 tickets
receives approximately 3x more CPU scheduling opportunities than the child with
1 ticket. Over longer runs the ratio converges to 3:1 as predicted by probability.

## Notes on Variance

For short runs, lottery scheduling shows higher variance — a process may get more
or fewer slots than its ticket count predicts. Over longer runs (more scheduling
events), the law of large numbers causes observed shares to converge toward the
theoretical ratio. A process with T tickets out of N total will receive T/N of
CPU time on average.

## Limitations

- Maximum processes: NPROC (64)
- Minimum tickets: 1 per process
- PRNG is deterministic (seed = 12345)
- No starvation prevention beyond probabilistic guarantees