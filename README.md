
# Two-Pass-Macro-Processor
Implementation of Two-Pass-Macro-Processor
## Data Structures
- MACRO Definition table
- MACRO Name Table
- Argument Array List 
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
