
import sys
import re
import glob 
import os


dir = sys.argv[1]
run_name = sys.argv[2]
date = sys.argv[3]

stats_titles = [
    "sim_ticks",
    "system.cpu.numCycles",
    "system.cpu.committedInsts",
    "system.cpu.committedOps",
    "system.cpu.cpi_total",
    "system.cpu.ipc_total",
    "system.cpu.commit.branches",
    "system.cpu.commit.branchMispredicts",
    "system.cpu.branchPred.indirectLookups",
    "system.cpu.branchPred.indirectMisses",
    "system.cpu.branchPredindirectMispredicted",
    "system.cpu.icache.overall_accesses::total",
    "system.cpu.icache.overall_misses::total",
    "system.cpu.icache.overall_miss_rate::total", # Derived from misses/accesses
    "system.cpu.icache.overall_miss_latency::total",
    "system.cpu.dcache.overall_accesses::total",
    "system.cpu.dcache.overall_misses::total",
    "system.cpu.dcache.overall_miss_rate::total", # Derived from misses/accesses
    "system.cpu.dcache.overall_miss_latency::total",
    "system.l2cache.overall_accesses::total",
    "system.l2cache.overall_misses::total",
    "system.l2cache.overall_miss_rate::total",    # Derived from misses/accesses
    "system.l2cache.overall_miss_latency::total", # Also broken down by I$, D$, and prefetcher
    "system.mem_ctrl.bw_total::.cpu.dcache.prefetcher",   # Total bandwidth to/from this memory (bytes/s)
    "system.mem_ctrl.bw_total::total",            # Total bandwidth to/from this memory (bytes/s)
    "system.cpu.fuPool.fu_ticks_busy::port0(0)",
    "system.cpu.fuPool.fu_ticks_busy::port1(0)",
    "system.cpu.fuPool.fu_ticks_busy::port2(0)",
    "system.cpu.fuPool.fu_ticks_busy::port2(1)",
    "system.cpu.fuPool.fu_ticks_busy::port2(2)",
    "system.cpu.fuPool.fu_ticks_busy::port2(3)",
    "system.cpu.fuPool.fu_ticks_busy::port2(4)",
    "system.cpu.fuPool.fu_ticks_busy::port2(5)",    
    "system.cpu.fuPool.fu_ticks_busy::port2(6)",    
    "system.cpu.fuPool.fu_ticks_busy::port2(7)",    
    "system.cpu.fuPool.fu_ticks_busy::port2(8)",    
    "system.cpu.fuPool.fu_ticks_busy::port2(9)",    
    "system.cpu.fuPool.fu_ticks_busy::port2(10)",   
    "system.cpu.fuPool.fu_ticks_busy::port2(11)",   
    "system.cpu.fuPool.fu_ticks_busy::port3(0)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(0)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(1)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(2)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(3)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(4)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(5)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(6)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(7)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(8)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(9)",    
    "system.cpu.fuPool.fu_ticks_busy::port4(10)",   
    "system.cpu.fuPool.fu_ticks_busy::port4(11)",   
    "system.cpu.fuPool.fu_ticks_busy::port5(0)",    
    "system.cpu.fuPool.fu_ticks_busy::port6(0)",    
    "system.cpu.fuPool.fu_ticks_busy::port6(1)",    
    "system.cpu.fuPool.fu_ticks_busy::port6(2)",    
    "system.cpu.fuPool.fu_ticks_busy::port7(0)",    
    "system.cpu.dcache.WriteReq_accesses::total",
    "system.cpu.dcache.ReadReq_accesses::total",
    "system.cpu.dcache.overall_avg_miss_latency::total",
    "system.cpu.dcache.replacements"
]

    # "system.cpu.fuPool.fu_ticks_busy::IntALU(0)",
    # "system.cpu.fuPool.fu_ticks_busy::IntALU(1)",
    # "system.cpu.fuPool.fu_ticks_busy::IntALU(2)",
    # "system.cpu.fuPool.fu_ticks_busy::IntALU(3)",
    # "system.cpu.fuPool.fu_ticks_busy::IntALU(4)",
    # "system.cpu.fuPool.fu_ticks_busy::IntALU(5)",
    # "system.cpu.fuPool.fu_ticks_busy::IntMultDiv(0)",
    # "system.cpu.fuPool.fu_ticks_busy::IntMultDiv(1)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_ALU(0)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_ALU(1)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_ALU(2)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_ALU(3)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_MultDiv(0)",
    # "system.cpu.fuPool.fu_ticks_busy::FP_MultDiv(1)",
    # "system.cpu.fuPool.fu_ticks_busy::SIMD_Unit(0)",
    # "system.cpu.fuPool.fu_ticks_busy::SIMD_Unit(1)",
    # "system.cpu.fuPool.fu_ticks_busy::SIMD_Unit(2)",
    # "system.cpu.fuPool.fu_ticks_busy::SIMD_Unit(3)",
    # "system.cpu.fuPool.fu_ticks_busy::RdWrPort(0)",
    # "system.cpu.fuPool.fu_ticks_busy::RdWrPort(1)",
    # "system.cpu.fuPool.fu_ticks_busy::RdWrPort(2)",
    # "system.cpu.fuPool.fu_ticks_busy::RdWrPort(3)",

stat_count = len(stats_titles)

if "print" in dir:
# Print heading 
    print("Benchmark,\tRun Name", end='')
    for i in range(stat_count):
        print(",\t{0}".format(stats_titles[i]), end='')
    print("\n", end='')

else:
    # Parse results file
    base_path = dir+'/results/m5out-clean-'+run_name+'-'+date+'/'
    # Search for file path, since m5out may be renamed
    filePaths = glob.glob(os.path.join(base_path,'stats.txt'))
    stats = stats_titles.copy()
    if filePaths:
        # Scan file for stats_titles of interest
        fp = open(filePaths[0], 'r')
        line = fp.readline() # Skip header
        line = fp.readline() # Skip header
        line = fp.readline()
        cont = True
        while line and cont:
            if"Begin Simulation Statistics" in line:
                cont = False
            line = fp.readline()
        
        cont = True
        while line and cont:
            if"Begin Simulation Statistics" in line:
                cont = False
            values = line.split()
            if(len(values)>0):
                stat_title = values[0]
                stat_value = values[1]
                # Save stats_titles of interest 
                if stat_title in stats_titles:
                    idx = stats_titles.index(stat_title)
                    stats[idx] = stat_value
            line = fp.readline()
        fp.close()

    # Print found stats_titles for this benchmark
    print("{0},\t{1}".format(dir, run_name), end='')
    for i in range(stat_count):
        print(",\t{0}".format(stats[i]), end='')
    print("\n", end='')







