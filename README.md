
# Two-Pass-Macro-Processor
Implementation of Two-Pass-Macro-Processor
## Language Used
- C
- Assembly (for input)
## Data Structures
- MACRO Definition table
- MACRO Name Table
- Argument Array List 
## Format of Data Structures
### MACRO Definition Table
| Index|      Definition      |  Arguments |
|----------|:-------------:|------:|
| 1 |  INCR  | &arg1, &arg2 |
|2 |    A   |   #1 |
|3 | A | #2 |
|4 | MEND| |
> Note: Argument list contains the index of the argument in the argument list array.
 ### MACRO Name Table
| Index|      Name      |  MDT Index |
|----------|:-------------:|------:|
| 1 |  "INCR"  | 1 |

> Note: MDT index contains the starting index of the MACRO in MDT.
 ### Argument List Array
| Index|      Argument      | 
|----------|:-------------:|
| 1 |  "DATA 1bbb"  |
| 2 | "DATA 2bbb" |

> Note: MDT index contains the starting index of the MACRO in MDT.
## Pass 1
- Definition of MACROS
	- Pass1 of macro processor makes a line-by-line scanover it's input.
	- Set MDTC = 1 and MNTC = 1.
	- Read next line of input program.
	- If it is a MACRO pseudo-op, the entire macro definition except MACRO line is stored in MDT.
## Pass 2
- Replacing MACRO calls by its definition
	- Search for MACRO Name in MNT
	- Substitute the values for arguments
	- Replace the MACRO call by MACRO definition from MDT
