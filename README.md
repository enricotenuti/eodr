# EoDr - FMC Analysis

EoDr is a FMC analysis program that performs edge orientation and domino reduction on a user-provided scramble. The application uses the "nissy" command to conduct the analyses and generates detailed output in two separate files: `outputeo.txt` and `outputdr.txt`.

## Key Features
- Conducts EO and DR analyses on user-specified input data.
- Allows customization of maximum edge orientation and domino reduction lengths.
- Supports the option to use NISS on the edge orientation.

## Requirements
- Installation of "nissy" to perform the analyses.
- C compiler to compile the program, such as GCC.

## Installation
1. Ensure you have the C compiler installed on your system.
2. Compile the program by executing the following command:

   ```bash
   make
   ```
   
3. Run the program with the command:

   ```bash
   ./eodr
   ```
