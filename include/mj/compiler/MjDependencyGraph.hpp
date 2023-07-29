//
// Types of dependencies:
//
// 1. Data Dependencies    : input of B depends on output of A
// 2. Control Dependencies : execution of B depends on evaluation of A
// 4. Antidependence       : output of B will overwrite input of A
// 5. Output-Dependency    : output of B will overwrite output of A
//
// Issues
//
// data -> cyclic data dependencies
// control -> infinite loop

// dead code (code will never run or does nothing)
// duplicate code (same code is present)
// duplicate data (more convenient access to same data exists)
