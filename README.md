
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
	-	Identify MACRO definitions
	-	Add arguments in Argument List Array
	-	Add MACRO name in MACRO Name Table
	-	Add MACRO definition in the MACRO Definition Table
## Pass 2
- Replacing MACRO calls by its definition
	- Search for MACRO Name in MNT
	- Substitute the values for arguments
	- Replace the MACRO call by MACRO definition from MDT
